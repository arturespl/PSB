#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#define LEFT230 	24
#define RIGHT230 	25
#define USB 		3
#define USB_CHARGER 	23

#define INPUTS 4

#define V_RIGHT_CLOSE 26
#define V_RIGHT_FAR 27
#define V_LEFT_CLOSE 28
#define V_LEFT_FAR 29

#define OUTPUTS 4

#define FIFONAME "pipe.fifo"



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

void sig_hendler(int);
