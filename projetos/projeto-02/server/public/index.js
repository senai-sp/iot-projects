/*global Vue*/
/*global mqtt*/
const url = new URL(window.location.href);
const data = {
  href: url.toString(),
  url: url.host,
  count: 0,
  topics: {
  }
};

new Vue({
  el: "#app",
  data
});

url.protocol = 'ws://';
const brokerUrl = url.toString();
const topicPrefix = 'vagas/';
console.log('attempting connection');
var client = mqtt.connect(brokerUrl);

function updateCount() {
  let count = 0;
  for (let topic in data.topics) {
    if (data.topics.hasOwnProperty(topic)) {
      const msg = data.topics[topic];
      if (+msg) {
        count++;
      }
    }
  }
  data.count = count;
}

client.on('connect', () => {
  console.info('MQTT connection successful');
  client.subscribe(topicPrefix + '#');
});
client.on('message', (topic, message) => console.info(topic, message.toString()));
client.on('message', (topic, message) => {
  const msg = message.toString();
  if (msg === '') {
    Vue.delete(data.topics, topic, msg);
  } else {
    Vue.set(data.topics, topic, msg);
  }
  updateCount();
});
