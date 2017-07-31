ALL: old panel vol udp

old:
	g++ -o 230stateUpdater wiring.c -lwiringPi

panel:
	g++ -o panelInput panelInput.c common.c -lwiringPi

vol:
	g++ -o VOLoutput VOLoutput.c common.c -lwiringPi

udp:
	g++ -o UdpInput UdpInput.c common.c -lwiringPi

udptest:
	g++ -o UdpSenderTest UdpSenderTest.c
