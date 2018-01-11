const express = require('express');
const fs = require('fs');

const app = express();

// Quando o servidor receber uma requisição GET /
app.get('/', function(request, response) {
	// retorna o conteúdo de nossa página html
	// __dirname é o diretório do arquivo atual
	response.sendFile(__dirname + '/index.html');
});

app.listen(3000, function() {
	console.log('Servidor iniciado em http://localhost:3000');
});
