#include <EasyUdp.h>
#include <ArduinoJson.h>
#include <avr/wdt.h>

#define sashPin A0
#define airflowBalancePin A1

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress destination_ip(192, 168, 1, 107);
IPAddress destination_ip(10, 145, 69, 25);

// Careful: local port MUST match server side port
unsigned int localPort = 5005;

char jsonBuffer[128];

// Dynamic Json document -> Allocate memory on heap
const size_t capacity = 2*JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(5);
DynamicJsonDocument doc(capacity);

// Static Json document -> Allocate memory on stack
//StaticJsonDocument<350> doc;

// Used for timer condition
long int currentTime, previousTime;
long int previousUDPSendTime;

// Minimum delay between messages in milliseconds
int sendDelay = 10;

// Used for voltage change condition
int previousSashData, previousAirflowBalanceData;
int sashThreshold, airflowBalanceThreshold;

EasyUdp UDP(Serial);

void setup() {
  Serial.begin(9600);
  UDP.begin(destination_ip, localPort, mac);

  wdt_enable(WDTO_8S);
  JSONDocumentSetup();
}

void loop() {
  // TO-DO Update parameters based on JSON file that server sends
  //UDPRead();

  // Reset watchdog timer every loop
  wdt_reset();

  // Store current time
  currentTime = millis();

  sashThreshold = 10;
  airflowBalanceThreshold = 600;

  // Measure current voltage readings
  int currentSashData = analogRead(sashPin);
  int currentAirflowBalanceData = analogRead(airflowBalancePin);

  // Check current voltage readings to previous readings
  int sash_difference = abs(currentSashData - previousSashData);
  int airflow_balance_difference = abs(currentAirflowBalanceData - previousAirflowBalanceData);

  // Reset previous voltage readings
  previousSashData = currentSashData;
  previousAirflowBalanceData = currentAirflowBalanceData;

  // If: either voltage readings are higher than specified threshold
  // Then: Send new message for both voltage readings
  /*if(sash_difference > sashThreshold || airflow_balance_difference > airflowBalanceThreshold) {
    previousTime = millis();
    
    doc["time"] = currentTime;
    doc["sash_data"][0] = currentSashData;
    doc["airflow_balance_data"][0] = currentAirflowBalanceData;

    if(!serializeJson(doc, jsonBuffer)) Serial.println(F("Failed to serialize JSON document."));
    UDP.sendData(jsonBuffer, sizeof(jsonBuffer), sendDelay);
  }*/
  
  // Else if: Time Elapsed is greater than x seconds
  // Then: Send current voltage readings
  if(currentTime - previousTime >= 500) {
    previousTime = millis();

    doc["time"] = previousTime;
    doc["sash_data"][0] = currentSashData;
    doc["airflow_balance_data"][0] = currentAirflowBalanceData;

    if(!serializeJson(doc, jsonBuffer)) Serial.println(F("Failed to serialize JSON document."));
    UDP.sendData(jsonBuffer, sizeof(jsonBuffer), sendDelay);
  }
}

void JSONDocumentSetup() {
  //const size_t capacity = 2*JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(5);
  //DynamicJsonDocument doc(capacity);
  
  doc["room"] = "3.141";
  doc["device"] = "1";
  doc["time"] = 1351824120;

  JsonArray sash_data = doc.createNestedArray("sash_data");
  sash_data.add(1023);
  sash_data.add(0.5234);

  JsonArray airflow_balance_data = doc.createNestedArray("airflow_balance_data");
  airflow_balance_data.add(1011);
  airflow_balance_data.add(2.302);

  serializeJsonPretty(doc, Serial);
  Serial.println();
}
