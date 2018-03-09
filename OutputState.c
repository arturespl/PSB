#include "common.h"

int outputStates[OUTPUTS];

int main(int argc, char** argv)
{
	delay(100);
	if(argc!=2)
	{
		printf("\n Usage:\n\targv[1] [output ID to test]\n");
		return -1;
	}


	int input = atoi(argv[1]);

	//printf("\nUID: %d\ncalling proces uid: %d", getuid(), geteuid());

	states::read(outputStates);

	if(input>=0 && input < OUTPUTS)
	{
		printf("%d", outputStates[input]);
	}
	else if(input==-1)
	{
		for(int i=0; i<OUTPUTS; ++i)
		{
			printf("%d ", outputStates[i]);
		}
	}



	return 0;
}
