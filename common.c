#include "common.h"

int common::fd = -1;
int common::additionalFdToClose = -1;

int common::inputId2OutputMap[INPUTS][OUTPUTS] = {
	{V_LEFT_CLOSE, -1, -1, -1},
	{V_RIGHT_CLOSE, -1, -1, -1},
	{-1, -1, -1, -1},
	{-1, -1, -1, -1}
};

int common::inputId2wiringPiID[INPUTS] = {
	LEFT230, RIGHT230, USB, USB_CHARGER };

void common::fifoInit(int flags)
{
	common::fd = -1;
	if(mkfifo(FIFONAME, 0666) == -1)
	{
		printf("\nError while creating pipe");
	}

	common::fd = open(FIFONAME, flags);
}

void sig_hendler(int signo)
{
	if(signo == SIGINT)
	{
		printf("Closing");
		fflush(stdout);
		common::cleanup();
		exit(0);
	}
}

void common::init(int flag)
{
	if(signal(SIGINT, sig_hendler) == SIG_ERR)
		printf("Can't catch SIGINT\n");

	if(wiringPiSetup() == -1)
		printf("wiringPI init FIALED");
	else
		printf("wiringPI init OK");

	printf("\nInitializing fifo");
	fflush(stdout);
	fifoInit(flag);
	printf("\nfifoInit() = %d", fd);
	fflush(stdout);

	if(common::fd<0)
		exit(-1);
}

void common::cleanup()
{
	if(common::fd != -1)
		close(common::fd);
	if(common::additionalFdToClose != -1)
		close(common::additionalFdToClose);
}

void common::write(int state, int pin)
{
	if(common::fd == -1)
	{
		printf("\nError writing to pipe");
		fflush(stdout);
		return;
	}

	char buff[2 * sizeof(int)];
	((int*)buff)[0] = state;
	((int*)buff)[1] = pin;

	::write( (int)common::fd, (void*)buff, (size_t) 2 * sizeof(int));
}

void common::read(int & state, int & pin)
{
	if(common::fd == -1)
	{
		printf("\nError reading from pipe");
		fflush(stdout);
		return;
	}

	char buff[2 * sizeof(int)] = {0};

	::read(common::fd, (void*)buff, 2 * sizeof(int));

	state = ((int*)buff)[0];
	pin = ((int*)buff)[1];
}
