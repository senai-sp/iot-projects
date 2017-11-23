var express = require('express');
var bodyParser = require('body-parser');
var stringify = require('json-stringify-safe');
var morgan = require('morgan');

var twilio = require('twilio');
var app = express();

// create application/x-www-form-urlencoded parser
var urlencodedParser = bodyParser.urlencoded({ extended: false });

app.use(morgan('dev'));

const serializer = (k, v) => String(v).substr(0, 6);

// POST /login gets urlencoded bodies
app.post('/sms', urlencodedParser, function(req, res) {
  if (!req.body) {
    return res.sendStatus(400);
  }
  console.log(req.body);
  var client = new twilio(req.body.sid, req.body.token);
  console.log(req.body);
  client.messages.create({
    to: "+" + req.body.to,
    from: "+" + req.body.from,
    body: req.body.body,
  })
    .then(message => res.status(200).send(stringify(message, serializer, 2)))
    .catch(err => {
      console.error(err);
      return res.status(400).end();
    });
});

app.listen(3000, function() {
  console.log('Servidor SMS ouvindo na porta 3000!');
});
