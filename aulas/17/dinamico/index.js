const express = require('express');
const expressHandlebars = require('express-handlebars');
const bodyParser = require('body-parser');
const fs = require('fs');

const app = express();

// configuramos o express para processar arquivos com a extensão .hbs pelo módulo
app.engine('hbs', expressHandlebars());
app.set('view engine', 'hbs');

app.use(bodyParser.urlencoded({
	extended: true
}));

let ligada = true;

// Quando o servidor receber uma requisição GET /
app.get('/', function(req, res) {
	// processa nossa página através do módulo express-handlebars,
	// inserindo a variável `ligada` na construção do html resultante
	// ele vai procurar o arquivo em views/index.hbs
	res.render('index', {
		ligada: ligada
	});
});

app.post('/', function(req, res) {
	if(req.body.command == 'Ligar') {
		ligada = true;
	} else {
		ligada = false;
	}
	res.render('index', {
		ligada: ligada
	});
})

app.listen(3000, function() {
	console.log('Servidor iniciado em http://localhost:3000');
});
