#include "common.h"

int outputStates[OUTPUTS];

int main(int argc, char** argv)
{
	FILE * fd;
	int pid;

	pid::read(pid);

	if(argc!=2)
	{
		printf("\n Usage:\n\targv[1] [output ID to test]\n");
		return -1;
	}

	states::clear();


	//printf("\nSending signal to process pid: %d", pid);
	kill(pid, 10);

	int input = atoi(argv[1]);


	states::read(outputStates);

	if(input>=0 && input < OUTPUTS)
	{
		printf("%d", outputStates[input]);
	}
	else
	{
		printf("%d", -1);
	}



	return 0;
}
