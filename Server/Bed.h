#pragma once
#ifndef BED_H
#define BED_H
using namespace std;
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "sys/types.h"
#include <fcntl.h>
#include <errno.h>
#include "Server.h"
#include "Clients.h"
#include "Stopwatch.h"


class Bed : public Client {
public:

	Bed(int);
	~Bed();

	void setID(int);
	int getID();

	void bepaalSchemerLEDStatus();
	int check;

	int getSwitchStatus();
	int getDruksensorStatus();
	int getLedStatus();

	void Overdag(int, int, int);
	void Nacht(int, int, int);
	void Noodsituatie();

	string getResponseBuffer() override;
	void setResponseBuffer();
	void verwerkData(const string buffer, bool nacht, bool noodsituatie) override;
	void logica() override;

private:
	int ID;

	bool wanneerLevenWe, Nood;
	int SwitchWaarde, LedWaarde, DruksensorWaarde;

	string response;
	Stopwatch stopwatch;

	int SwitchStatus;
	int DruksensorStatus;
	int LedStatus;

};

#endif 
