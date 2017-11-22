// modulo para servidor HTTP
const express = require('express');

// modulo para interpretar mensagens vindas de clientes
const bodyParser = require('body-parser');

// module para logging de eventos para console
const morgan = require('morgan');

const cors = require('cors');

const app = express();

// configuração para deixar respostas legíveis
app.set('json spaces', 2);


app.use(cors());

// biblioteca para o servidor 
app.use(bodyParser.json());

app.use('/grafico', express.static('grafico'));

/**
 * Formato das temperaturas:
 * {
 *   idKit: [{
 *     temp: 25, // temperatura em celcius
 *     timestamp: 1507653312813 // data do cadastro, em millis desde 1/1/1970
 *   }, ...]
 * }
 */
const temperaturas = {};

function cadastrarTemperatura(registro) {
  // inicializar coleção do kit para uma array vazia caso não exista
  temperaturas[registro.id] = temperaturas[registro.id] || [];

  // adicionar registro na array
  temperaturas[registro.id].push({
    timestamp: (new Date()).getTime(),
    temp: registro.temp
  });
  console.info(`Temperatura cadastrada para kit ${registro.id}`);
}

app.use(morgan('combined'));

app.post('/', function(req, res) {
  let dados = req.body;
  cadastrarTemperatura(dados);
  res.status(200).end();
});


app.get('/:id', function(req, res) {
  // recuperar coleção para kit
  const dadosKit = temperaturas[req.params.id];
  if (!dadosKit) {
    return res.status(404).send(`Sem dados encontrados para kit ${req.params.id}`);
  }
  res.json(dadosKit);
});

app.get('/', function(req, res) {
  // retornar todos os dados
  res.json(temperaturas);
});

// para testar: curl -X POST -H "Content-Type: application/json" -d '{ "temp": 30, "id": 10 }' http://localhost:8080
app.listen(8080, function() {
  console.log('Servidor ligado!');
});
