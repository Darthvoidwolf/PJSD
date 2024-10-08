#include "Stopwatch.h"


Stopwatch::Stopwatch():begintijd(0),eindtijd(0), lopend(false){}

//Stopwatch::~Stopwatch() {
//
//}

void Stopwatch::reset() {
    begintijd=0;
    eindtijd=0;
	lopend = false;
}

void Stopwatch::begin() {

	struct timeval tijd;
	gettimeofday(&tijd,0);
	begintijd=tijd.tv_sec;
	lopend = true;
}

void Stopwatch::stop() {
	struct timeval tijd;
	gettimeofday(&tijd,0);
	eindtijd=tijd.tv_sec;
	lopend = false; 
}

unsigned int Stopwatch::deTijd() const {
	if (lopend) {
        struct timeval nu;
        gettimeofday(&nu, 0);
        return nu.tv_sec - begintijd;
    } else {
        return eindtijd - begintijd;
    }
}

bool Stopwatch::isLopend() const {
    return lopend;
}