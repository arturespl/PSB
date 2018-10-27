#include "common.h"

int main()
{
	common::init(O_WRONLY);

	pinMode(SWITCH1,INPUT);
	pinMode(SWITCH2,INPUT);
	pinMode(SWITCH3,INPUT);
	pinMode(SWITCH4,INPUT);

	int inputStates[INPUTS];
	int tmp;

	for(int i=0; i<INPUTS; ++i)
	{
		inputStates[i] = digitalRead(common::inputId2wiringPiID[i]);
		common::write(i, inputStates[i]);
	}

	while(true)
	{
		for(int i=0; i<INPUTS; ++i)
		{
			tmp = digitalRead(common::inputId2wiringPiID[i]);
			if(tmp != inputStates[i])
			{
				inputStates[i] = tmp;
				printf("\nChanged state to %d on pin %d", tmp, i);
				fflush(stdout);
				common::write(i, tmp);
			}
		}

		delay(100);
	}
	return 0;
}
