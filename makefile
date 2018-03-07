ALL: panel vol udp state

panel:
	g++ -o panelInput panelInput.c common.c -lwiringPi

vol:
	g++ -o VOLoutput VOLoutput.c common.c -lwiringPi

udp:
	g++ -o UdpInput UdpInput.c common.c -lwiringPi

udptest:
	g++ -o UdpSenderTest UdpSenderTest.c

state:
	g++ -o OutputState OutputState.c common.c  -lwiringPi
