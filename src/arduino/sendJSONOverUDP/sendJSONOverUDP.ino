#include <EasyUdp.h>
#include <ArduinoJson.h>
#include <avr/wdt.h>

#define sashPin A0
#define airflowBalancePin A1

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress destination_ip(192, 168, 1, 107);

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
int sashDifference, airflowBalanceDifference;

// Hard coded threshold values for when to send new data
// Analog input is 10-bit: Digital range from 0-1023 value
int sashThreshold = 10;
int airflowBalanceThreshold = 600;

// Attach serial connection to UDP object for debugging purposes
EasyUdp UDP(Serial);

void setup() {
  // Begin serial communication for debugging purposes
  Serial.begin(9600);

  // Initialize UDP communication
  // Specify: 
  //    - destination IP address
  //    - local port address
  //    - local mac address
  UDP.begin(destination_ip, localPort, mac);

  // Enable watchdog timer
  // Currently specified 8 second timeout before reset
  wdt_enable(WDTO_8S);

  // Helper function to instantiate JSON document
  JSONDocumentSetup();
}

void loop() {
  // TO-DO Update parameters based on JSON file that server sends
  //UDPRead();

  // Reset watchdog timer every loop to avoid unnecessary reset
  wdt_reset();

  // Store current time
  currentTime = millis();

  // Measure current voltage readings
  int currentSashData = analogRead(sashPin);
  int currentAirflowBalanceData = analogRead(airflowBalancePin);

  // Check current voltage readings to previous readings
  sashDifference = abs(currentSashData - previousSashData);
  airflowBalanceDifference = abs(currentAirflowBalanceData - previousAirflowBalanceData);

  // If: either voltage readings are higher than specified threshold
  // Then: Send new message for both voltage readings
  if(sashDifference >= sashThreshold || airflowBalanceDifference >= airflowBalanceThreshold) {
    // Reset previous message send time
    previousTime = millis();

    // Reset previous voltage readings
    previousSashData = currentSashData;
    previousAirflowBalanceData = currentAirflowBalanceData;
    
    doc["time"] = currentTime;
    doc["sash_data"][0] = currentSashData;
    doc["airflow_balance_data"][0] = currentAirflowBalanceData;

    if(!serializeJson(doc, jsonBuffer)) Serial.println(F("Failed to serialize JSON document."));
    UDP.sendData(jsonBuffer, sizeof(jsonBuffer), sendDelay);
  }
  
  // Else If: Time Elapsed is greater than x seconds
  // Then: Send current voltage readings
  // Hard coded time interval between inactive message transmissions (in milliseconds)
  else if(currentTime - previousTime >= 3000) {
    previousTime = millis();

    doc["time"] = previousTime;
    doc["sash_data"][0] = currentSashData;
    doc["airflow_balance_data"][0] = currentAirflowBalanceData;

    if(!serializeJson(doc, jsonBuffer)) Serial.println(F("Failed to serialize JSON document."));
    UDP.sendData(jsonBuffer, sizeof(jsonBuffer), sendDelay);
  }
}

// Helper function to instantiate JSON document
// Hard code:
//  - Room Number
//  - Device Number
// Add dummy values for:
//    - Initial time
//    - Sash data digital
//    - Sash data analog
// Add dummy values for:
//    - Airflow balance data digital
//    - Airflow balance data analog
// All dummy values will be reset on first loop iteration
void JSONDocumentSetup() {
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
