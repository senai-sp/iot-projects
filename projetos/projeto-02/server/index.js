const mosca = require('mosca');

const mqttServer = new mosca.Server({
  port: 1883,
  http: {
    port: 8080,
    static: './public/'
  },
  persistence: {
    factory: mosca.persistence.Memory
  }
});

mqttServer.on('ready', () => console.log('server ready'));
