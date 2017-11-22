var express = require('express');
var bodyParser = require('body-parser');
var stringify = require('json-stringify-safe');

var twilio = require('twilio');
var app = express();

// create application/x-www-form-urlencoded parser
var urlencodedParser = bodyParser.urlencoded({ extended: false });

// POST /login gets urlencoded bodies
app.post('/send', urlencodedParser, function(req, res) {
  if (!req.body) {
    return res.sendStatus(400);
  }
  var client = twilio(req.body.sid, req.body.token);
  console.log(req.body);
  client.messages.create({
    to: "+" + req.body.to,
    from: "+" + req.body.from,
    body: req.body.body,
  }, function(err, message) {
    if(err) {
      return res.status(400).end();
    } else {
      res.status(200).send(stringify(message, null, 2));
    }
  });
});

app.listen(3000, function() {
  console.log('Servidor SMS ouvindo na porta 3000!');
});
