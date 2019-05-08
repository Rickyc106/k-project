#include <EasyUdp.h>

// Map analog pin to A0
#define analogPin A0

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress destinationIP(192, 168, 1, 107);

// Careful: local port MUST match server side port
unsigned int localPort = 5005;

// Minimum delay between messages specified in milliseconds
int sendDelay = 10;

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
  UDP.begin(destinationIP, localPort, mac);
}

void loop() {
  // Read data through analog pin A0
  int knobPosition = analogRead(analogPin);

  // Send data over UDP pipeline
  // Specify:
  //  - Data
  //  - Length of expected data buffer
  //  - Minimum interval between messages sent
  UDP.sendData(knobPosition, sizeof(knobPosition), sendDelay);
}
