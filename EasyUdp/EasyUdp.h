/*
	EasyUdp.h - Library for sending datagrams over UDP
	Created by Ricky Chen, April 23, 2019
*/

#ifndef EasyUdp_h
#define EasyUdp_h

#include "Arduino.h"
#include "SPI.h"
#include "Ethernet.h"
#include "EthernetUdp.h"

class EasyUdp {
	public:
		EasyUdp(Print &print);
		void begin(IPAddress server, uint16_t port, byte mac[]);
		void sendData(int val);
		void sendData(char val);
		void sendData(char array[], int size, int delay_time);
		void receiveData();
	private:
		Print* _stream;
		IPAddress _server;
		uint16_t _port;
		EthernetUDP Udp;

		long int previousSendTime;
};

#endif