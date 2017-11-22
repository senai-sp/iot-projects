/*
	Exemplos utilizando a classe String da biblioteca do Arduino para converter o número
	da vaga contida no tópico para `int`

	https://www.arduino.cc/en/Reference/String
*/
int topicoParaInt(char* topico) {
	// Converter caractere '0' em String "0"
	String vaga = String(topico[6]);
	// Concatenar String "0" com o char '5'
	// a classe String implementa esta conversão
	vaga += topico[7];
	// Utilizar o método String::toInt() para interpretar os caracteres da nova String
	// como inteiro
	return vaga.toInt();
}

int topicoParaInt2(char* topico) {
	// Subtrai o valor do caractere '0' (valor 48 na tabela ASCII) de um caractere '0' até '9' (48 até 57)
	// assim obtendo o valor correspondente como inteiro
	int dezena = topico[6] - '0';
	int unidade = topico[7] - '0';

	return dezena * 10 + unidade;
}

void setup() {
	Serial.begin(9600);
	while(!Serial) {}

	char* topico = "vagas/05";
	int numeroVaga = topicoParaInt(topico);

	Serial.println("Vaga: ");
	Serial.println(numeroVaga);
}
