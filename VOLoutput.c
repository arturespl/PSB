#include <signal.h>
#include "common.h"




int main()
{
	int inputState[OUTPUTS] = {0};

	common::init(O_RDONLY);

	pinMode(RELAY1,OUTPUT);
	pinMode(RELAY2,OUTPUT);
	pinMode(RELAY3,OUTPUT);
	pinMode(RELAY4,OUTPUT);

//	int inputState[OUTPUTS] = {0};

	int inputId;
	int state;

	digitalWrite(RELAY1, 0);
	digitalWrite(RELAY2, 0);
	digitalWrite(RELAY3, 1);
	digitalWrite(RELAY4, 1);

	while(true)
	{
		common::read(inputId, state);
		if(state==-2)
		{
			printf("\nState request");
			fflush(stdout);

			states::write(inputState);
		}
		else if(state != 2)
		{
		printf("\nState changed on pin %d to %d", inputId, state);
		fflush(stdout);

			inputState[inputId] = state;
			for(int i=0; common::inputId2OutputMap[inputId][i] > -1; ++i)
			{
				digitalWrite(common::inputId2OutputMap[inputId][i], inputState[inputId] == 0 ? 1 : 0);
			}
		}
		else
		{
		printf("\nState toggled on pin %d to %d", inputId, state);
		fflush(stdout);

			inputState[inputId] = (inputState[inputId] == 0 ? 1 : 0);
			for(int i=0; common::inputId2OutputMap[inputId][i] > -1; ++i)
			{
				digitalWrite(common::inputId2OutputMap[inputId][i], inputState[inputId] == 0 ? 1 : 0);
			}
		}
	}
	return 0;
}
