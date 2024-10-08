#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <sys/time.h>

class Stopwatch {
public:
	Stopwatch();
	void reset();
	void begin();
	void stop();
	unsigned int deTijd() const;
	bool isLopend() const;

private:
	//struct timeval begintijd,eindtijd;
    long begintijd,eindtijd;
	bool lopend;

};

#endif /* STOPWATCH_H_ */