#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define LEFT230 	24
#define RIGHT230 	25
#define USB 		3
#define USB_CHARGER 	23

#define V_RIGHT_CLOSE 26
#define V_RIGHT_FAR 27
#define V_LEFT_CLOSE 28
#define V_LEFT_FAR 29

int main()
{
	if(wiringPiSetup() == -1)
		printf("init FIALED");
	else
		printf("init OK");

	pinMode(LEFT230,INPUT);
	pinMode(RIGHT230,INPUT);
	pinMode(USB,INPUT);
	pinMode(USB_CHARGER,INPUT);

	pinMode(V_RIGHT_CLOSE,OUTPUT);
	pinMode(V_RIGHT_FAR,OUTPUT);
	pinMode(V_LEFT_CLOSE,OUTPUT);
	pinMode(V_LEFT_FAR,OUTPUT);

	while(true)
	{
		system("clear");
		if(digitalRead(LEFT230) == 1)
		{
			printf("\nbutton LEFT230 preset");
		}
		if(digitalRead(RIGHT230) == 1)
		{
			printf("\nbutton RIGHT230 preset");
		}
		if(digitalRead(USB) == 1)
		{
			printf("\nbutton USB preset");
		}
		if(digitalRead(USB_CHARGER) == 1)
		{
			printf("\nbutton USB_CHARGER preset");
		}
		printf("\n");

		digitalWrite(V_RIGHT_CLOSE,digitalRead(LEFT230)==1 ? 0 : 1);
		digitalWrite(V_RIGHT_FAR,digitalRead(RIGHT230)==1 ? 0 : 1);
		digitalWrite(V_LEFT_CLOSE,digitalRead(USB)==1 ? 0 : 1);
		digitalWrite(V_LEFT_FAR,digitalRead(USB_CHARGER)==1 ? 0 : 1);

		delay(100);
	}
	return 0;
}
