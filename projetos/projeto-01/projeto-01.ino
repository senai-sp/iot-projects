void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  setupPortao();
  setupLuz();
  setupFeedback();

  ethernetConnect();
  mqttSetup();
}

void loop()
{
  mqttLoop();
  loopPortao();
  loopLuz();
  loopFeedback();
}
