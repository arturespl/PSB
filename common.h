#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define SWITCH1 	24
#define SWITCH2 	25
#define SWITCH3 	3
#define SWITCH4 	23

#define INPUTS 4

#define RELAY1 26 //gniazdka sterowane
#define RELAY2 27 //lewe gniazdko sterowane
#define RELAY3 28 //prawe niazdko sterowane
#define RELAY4 29 //zasilacz wewnetrzny

#define OUTPUTS 4

#define DATADIR "/tmp/PSB/"
#define FIFONAME "/tmp/PSB/pipe.fifo"
#define STATEFILE "/tmp/PSB/states"
#define PIDFILE "/tmp/PSB/pid"


class common
{
public:
	static int fd;
	static int additionalFdToClose;
private:
	static void fifoInit(int flags);

public:
	static void init(int flag);
	static void cleanup();

	static void write(int state, int pin);
	static void read(int & state, int & pin);

	static int inputId2OutputMap[INPUTS][OUTPUTS];
	static int inputId2wiringPiID[INPUTS];
};

class states
{
	static FILE * fd;
public:

	static void clear();
	static void write(int * states);
	static void read(int * states);
};

class pid
{
	static FILE * fd;
public:

	static void write(int pid);
	static void read(int & pid);
};


void sig_hendler(int);
