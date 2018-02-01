const http = require('http');

const server = http.createServer(function(req, res) {
	console.log('req');
	res.end(JSON.stringify({
			value: 1003
		}));
});

server.listen(8080);
console.log('listening');
