#include <LiquidCrystal.h>
#include <UIPEthernet.h>
byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x42 };
EthernetClient ethClient;

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// Se não definirmos o nome ONLINE, podemos utilizar uma versão diferente da
// biblioteca que simula MQTT via a comunicação serial
// podendo assim testar sem conexão
// ver https://github.com/paolobueno/SerialPubSubClient
#define ONLINE 1
#ifdef ONLINE
#include <PubSubClient.h>
#else
#include <SerialPubSubClient.h>
#endif

// const char* MQTT_SERVER = "test.mosquitto.org";
IPAddress MQTT_SERVER(192, 168, 3, 186);
const int MQTT_PORT = 1883;
const char* MQTT_CLIENT_ID = "arduino-placa-42";

const char* topic = "vagas/#";

const int QUANTIDADE_VAGAS = 50;
int vagas[QUANTIDADE_VAGAS] = {};

const int STATUS_OCUPADA = 0;
const int STATUS_LIVRE = 1;
// Terceiro estado para a vaga que indica que ela não se reportou ao broker MQTT
const int STATUS_OFFLINE = -1;

// A array vagas é inicializada com valores 0 == STATUS_OCUPADA
// porém precisamos mudar este valor para STATUS_OFFLINE para não as considerarmos na contagem
void inicializarVagas() {
  for (int i = 0; i < QUANTIDADE_VAGAS; i++) {
    vagas[i] = STATUS_OFFLINE;
  }
}

// Extrai id da vaga a partir do tópico
// este método assume que o formato do tópico seja "vagas/##"
// ex.: "vagas/15", "vagas/01", etc
int extrairIdVaga(char* topico) {
  // ver exemplos/topico-para-int.ino
  int dezena = topico[6] - '0';
  int unidade = topico[7] - '0';

  return dezena * 10 + unidade;
}

// Variável global para armazenarmos o instante que recebemos a ultima mensagem MQTT
long tempoUltimaMensagemMQTT = 0;
void callback(char* topico, byte* mensagem, unsigned int tamanhoMensagem) {
  tempoUltimaMensagemMQTT = millis();

	int idVaga = extrairIdVaga(topico);

	// Converter primeiro caractere da mensagem em número
	// isto assume que esse caractere está entre '0' e '9'
	int status = mensagem[0] - '0';

	debugMensagem(idVaga, status, tamanhoMensagem);
	processarAlteracaoVaga(idVaga, status, tamanhoMensagem);
}

void debugMensagem(int id, int status, int tamanho) {
	Serial.println("Mensagem ---");
	Serial.print("Vaga: "); Serial.println(id);
	Serial.print("Status: "); Serial.println(status);
	Serial.print("Tamanho: "); Serial.println(tamanho);
	Serial.println();

	// utilizamos o metodo flush() para garantir que o texto anterior seja
	// escrito completamente para a porta serial
	Serial.flush();
}

void processarAlteracaoVaga(int id, int status, int tamanhoMensagem) {
	// subtraímos 1 pois a contagem começa em 0
	int indice = id - 1;

	if (id <= 0 || id > QUANTIDADE_VAGAS) {
		// Vaga fora do intervalo correto
		// a instrução "return" vai sair desta função sem executar mais nada
		return;
	}

	if (tamanhoMensagem != 1) {
		// mensagem vazia ou mal-formada, devemos considerar que a vaga não existe mais
		vagas[indice] = -1;
	} else {
		vagas[indice] = status;
	}

	atualizarContagem();
}

// Percore a array de vagas para as contar novamente
void atualizarContagem() {
  int ocupadas = 0;
  int livres = 0;

  // Para cada posição das vagas...
  for (int i = 0; i < QUANTIDADE_VAGAS; i++) {
    switch(vagas[i]) {
      // contar se estão ocupadas ...
      case STATUS_OCUPADA:
      ocupadas++;
      break;

      // ou livres
      case STATUS_LIVRE:
      livres++;
      break;

      case STATUS_OFFLINE:
      // fazer nada
      break;
    }

    // O seguinte código é o equivalente do `switch/case` acima
    // utilizando `if`:

    /*
    int valor = vagas[i];
    if (valor == STATUS_OCUPADA) {
      ocupadas++;
    } else if (valor == STATUS_LIVRE) {
      livres++;
    }
    */
  }

  exibirContagem(livres, ocupadas);
}

// Atualiza LCD com contagem das vagas
void exibirContagem(int livres, int ocupadas) {
  lcd.clear();
  if (livres == 0) {
    lcd.print("SEM VAGAS LIVRES");
  } else {
    lcd.print("Livres: ");
    lcd.print(livres);
  }

  lcd.setCursor(0, 1);
  lcd.print("Ocupadas: ");
  lcd.print(ocupadas);
}

PubSubClient client(MQTT_SERVER, MQTT_PORT, callback, ethClient);

void setup() {
  Serial.begin(9600);
	while (!Serial) {};

	// Como estamos utilizando o pino analógico 0 como digital para o LCD
	// temos que configurá-lo como OUTPUT
	pinMode(A0, OUTPUT);

  lcd.begin(16, 2);

  inicializarVagas();
  #ifdef ONLINE
  configurarEthernet();

  conectarMQTT();
  #endif
}

void configurarEthernet() {
  if(!Ethernet.begin(mac)) {
    Serial.println("Falha no DHCP");
  } else {
		Serial.print("IP obtido: "); Serial.println(Ethernet.localIP());
	};
}

int conectarMQTT() {
  if(client.connect(MQTT_CLIENT_ID)) {
		client.subscribe(topic);
		Serial.println("Conectado ao broker MQTT");
		return true;
	} else {
		Serial.println("Falha a conectar ao broker MQTT");
		return false;
	}
}

// Variavel global para guardar o tempo da última tentativa de conexão
unsigned long ultimaTentativaReconectar = 0;
int checkReconectarMQTT() {
  if (!client.connected()) {
    long agora = millis();
    if(agora - ultimaTentativaReconectar > 5000) {
      Serial.println("Reconectando...");
      return conectarMQTT();
    }
    ultimaTentativaReconectar = agora;
  }
}

const long TEMPO_DESLIGAR_LED = 10 * 1000;

// Verifica se há necessidade de deligar o LCD devido a não termos recebido mensagens mqtt
void checkDesligarLCD() {
  long agora = millis();
  if(agora - tempoUltimaMensagemMQTT > TEMPO_DESLIGAR_LED) {
    lcd.noDisplay();
  } else {
    lcd.display();
  }
}

void loop() {
  checkReconectarMQTT();

  checkDesligarLCD();

  // Chamada de método requirido pela biblioteca MQTT
  // ele é necessário para que ela tenha uma oportunidade de processar envios e recebimentos de respostas
  client.loop();
}
