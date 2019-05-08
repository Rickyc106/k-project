/*
	EasyUdp.cpp - Library for sending datagrams over UDP
	Created by Ricky Chen, April 23, 2019
*/

#include "EasyUdp.h"

EasyUdp::EasyUdp(Print &print) {
	_stream = &print;
}

void EasyUdp::begin(IPAddress server, uint16_t port, byte mac[]) {
	_stream->println("Initializing Ethernet Communication...");

	if(!Ethernet.begin(mac)) {
		_stream->println("Failed to initialize Ethernet Communication");
		return;
	}
	
	_stream->println("Initializing UDP Port...");
	Udp.begin(port);

	_stream->print("Arduino IP (retrieved from DHCP server): ");
	_stream->println(Ethernet.localIP());
	_stream->print("Destination IP (set by user): ");
	_stream->println(server);

	_server = server;
	_port = port;
}

void EasyUdp::sendData(int val) {
	if(!Udp.beginPacket(_server, _port)) _stream->println(F("Failed to begin packet"));
	Udp.print(val);
	if(!Udp.endPacket()) Serial.println(F("Failed to send packet."));
}

void EasyUdp::sendData(char val) {
	if(!Udp.beginPacket(_server, _port)) _stream->println(F("Failed to begin packet"));
	Udp.print(val);
	if(!Udp.endPacket()) Serial.println(F("Failed to send packet."));
}

void EasyUdp::sendData(char array[], int size, int delay_time) {
	if((millis() - previousSendTime) >= delay_time) {
		if(!Udp.beginPacket(_server, _port)) _stream->println(F("Failed to begin packet"));

		for(int i = 0; i != (size - 1); i++) {
			Udp.print(array[i]);
		}

		if(!Udp.endPacket()) _stream->println(F("Failed to send packet."));

		previousSendTime = millis();
	}
}

void EasyUdp::receiveData() {

}