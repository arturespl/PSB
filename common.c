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
		fflush(stdout);
	}

	common::fd = open(FIFONAME, flags);
}

void sig_hendler(int signo)
{
	if(signo == SIGINT)
	{
		printf("\nSIGINT, Closing\n");
		fflush(stdout);
		common::cleanup();
		exit(0);
	}
}

void common::init(int flag)
{
	if(signal(SIGINT, sig_hendler) == SIG_ERR)
	{
		printf("\nCan't catch SIGINT\n");
		fflush(stdout);
	}
	mkdir(DATADIR, S_IRWXU| S_IRGRP | S_IROTH | S_IXOTH | S_IXGRP);

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


FILE * states::fd;

void states::clear()
{
	int strsize = strlen(STATEFILE) + 1;
	char* filename = new char[strsize];
	strcpy(filename, STATEFILE);
	filename[strsize-1] = 0;

	//printf("\nTruncing file: %s", filename);
	fflush(stdout);

	states::fd = fopen(filename, "w");

	fclose(states::fd);
	delete filename;
}
void states::write(int * states)
{
	int strsize = strlen(STATEFILE) + 1;
	char* filename = new char[strsize];
	strcpy(filename, STATEFILE);
	filename[strsize-1] = 0;

	printf("\nWriting to file: %s\n", filename);
	fflush(stdout);

	states::fd = fopen(filename, "w");

	for(int i=0; i<OUTPUTS; ++i)
	{
		fprintf(states::fd, "%d\n", states[i]);
	}

	fclose(states::fd);

	char mode[] = "0666";
    int i;
    i = strtol(mode, 0, 8);
    if (chmod (STATEFILE,i) < 0)
    {
		printf("\nError on chmod: %s\n", filename);
		fflush(stdout);
    }
	delete filename;
}

void states::read(int * states)
{
	int strsize = strlen(STATEFILE) + 1;
	char* filename = new char[strsize];
	strcpy(filename, STATEFILE);
	filename[strsize-1] = 0;

	//printf("\nReading from file: %s", filename);
	fflush(stdout);

	states::fd = fopen(filename, "r");

	for(int i=0; i<OUTPUTS; ++i)
	{
		char buff[8] = {0};

		fgets(buff, 8, states::fd);

		states[i] = atoi(buff);
	}

	fclose(states::fd);

	delete filename;
}

FILE * pid::fd;

void pid::write(int pid)
{
	int strsize = strlen(PIDFILE) + 1;
	char* filename = new char[strsize];
	strcpy(filename, PIDFILE);
	filename[strsize-1] = 0;

	printf("\nWriting to file: %s", filename);
	fflush(stdout);

	pid::fd = fopen(filename, "w");

	if(pid::fd < 0)
	{		
		printf("\nCan't open or create pid file", filename);
		fflush(stdout);
	}

	fprintf(pid::fd, "%d\n", pid);
	
	fclose(pid::fd);
	delete filename;
}

void pid::read(int & pid)
{
	int strsize = strlen(PIDFILE) + 1;
	char* filename = new char[strsize];
	strcpy(filename, PIDFILE);
	filename[strsize-1] = 0;

	//printf("\nReading from file: %s", filename);
	fflush(stdout);

	pid::fd = fopen(filename, "r");

	if(pid::fd < 0)
	{		
		printf("\nCan't open or create pid file", filename);
		fflush(stdout);
	}

	char buff[8] = {0};

	fgets(buff, 8, pid::fd);

	pid = atoi(buff);

	fclose(pid::fd);
	delete filename;
}
