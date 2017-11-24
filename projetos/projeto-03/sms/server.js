var express = require('express');
var bodyParser = require('body-parser');
var stringify = require('json-stringify-safe');
var morgan = require('morgan');

var twilio = require('twilio');
var app = express();

// create application/x-www-form-urlencoded parser
var urlencodedParser = bodyParser.urlencoded({ extended: false });

app.use(morgan('dev'));

const serializer = (k, v) => {
  if(typeof v === 'string') {
    return v.substr(0, 12);
  }
  return v;
};

// POST /login gets urlencoded bodies
app.post('/sms', urlencodedParser, function(req, res) {
  if (!req.body) {
    return res.sendStatus(400);
  }
  var client = new twilio(req.body.sid, req.body.token);
  console.log(stringify(req.body, serializer, 2));
  client.messages.create({
    to: "+" + req.body.to,
    from: "+" + req.body.from,
    body: req.body.body,
  })
    .then(message => res.status(200).send(stringify(message, null, 2)))
    .catch(err => res.status(400).send(err.message));
});

app.listen(3000, function() {
  console.log('Servidor SMS ouvindo na porta 3000!');
});
