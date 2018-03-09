#include <signal.h>
#include "common.h"




int main()
{
	int inputState[OUTPUTS] = {0};

	common::init(O_RDONLY);

	pinMode(V_LEFT_CLOSE,OUTPUT);
	pinMode(V_RIGHT_CLOSE,OUTPUT);
	pinMode(V_LEFT_FAR,OUTPUT);
	pinMode(V_RIGHT_FAR,OUTPUT);

//	int inputState[OUTPUTS] = {0};

	int inputId;
	int state;

	digitalWrite(V_LEFT_FAR, 0);
	digitalWrite(V_RIGHT_FAR, 0);
	digitalWrite(V_RIGHT_CLOSE, 1);
	digitalWrite(V_LEFT_CLOSE, 1);

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
