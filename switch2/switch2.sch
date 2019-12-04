EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+12V #PWR05
U 1 1 5DDDC104
P 4100 1500
F 0 "#PWR05" H 4100 1350 50  0001 C CNN
F 1 "+12V" H 4115 1673 50  0000 C CNN
F 2 "" H 4100 1500 50  0001 C CNN
F 3 "" H 4100 1500 50  0001 C CNN
	1    4100 1500
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR07
U 1 1 5DEB24F0
P 5050 3650
F 0 "#PWR07" H 5050 3500 50  0001 C CNN
F 1 "+12V" H 5065 3823 50  0000 C CNN
F 2 "" H 5050 3650 50  0001 C CNN
F 3 "" H 5050 3650 50  0001 C CNN
	1    5050 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5DEB24E6
P 5050 4550
F 0 "#PWR08" H 5050 4300 50  0001 C CNN
F 1 "GND" H 5055 4377 50  0000 C CNN
F 2 "" H 5050 4550 50  0001 C CNN
F 3 "" H 5050 4550 50  0001 C CNN
	1    5050 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5DEB24E0
P 4750 4000
F 0 "R2" V 4543 4000 50  0000 C CNN
F 1 "R" V 4634 4000 50  0000 C CNN
F 2 "" V 4680 4000 50  0001 C CNN
F 3 "~" H 4750 4000 50  0001 C CNN
	1    4750 4000
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5DEB24D9
P 5050 4300
F 0 "R4" V 4843 4300 50  0000 C CNN
F 1 "R" V 4934 4300 50  0000 C CNN
F 2 "" V 4980 4300 50  0001 C CNN
F 3 "~" H 5050 4300 50  0001 C CNN
	1    5050 4300
	-1   0    0    1   
$EndComp
$Comp
L Device:D D1
U 1 1 5DDD8450
P 4100 3100
F 0 "D1" V 4054 3179 50  0000 L CNN
F 1 "D" V 4145 3179 50  0000 L CNN
F 2 "" H 4100 3100 50  0001 C CNN
F 3 "~" H 4100 3100 50  0001 C CNN
	1    4100 3100
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5DF2443B
P 5950 4300
F 0 "R6" V 5743 4300 50  0000 C CNN
F 1 "330" V 5834 4300 50  0000 C CNN
F 2 "" V 5880 4300 50  0001 C CNN
F 3 "~" H 5950 4300 50  0001 C CNN
	1    5950 4300
	-1   0    0    1   
$EndComp
$Comp
L Converter_ACDC:HLK-PM12 PS1
U 1 1 5DF4EDCB
P 2650 1800
F 0 "PS1" H 2650 2125 50  0000 C CNN
F 1 "HLK-PM12" H 2650 2034 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_HiLink_HLK-PMxx" H 2650 1500 50  0001 C CNN
F 3 "http://www.hlktech.net/product_detail.php?ProId=56" H 3050 1450 50  0001 C CNN
	1    2650 1800
	1    0    0    -1  
$EndComp
$Comp
L Relay:FINDER-40.31 K1
U 1 1 5DDDA13B
P 2650 3100
F 0 "K1" H 3080 3146 50  0000 L CNN
F 1 "FINDER-40.31" H 3080 3055 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Finder_40.31" H 3790 3060 50  0001 C CNN
F 3 "http://gfinder.findernet.com/assets/Series/353/S40EN.pdf" H 2650 3100 50  0001 C CNN
	1    2650 3100
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5DF89178
P 1200 1850
F 0 "J1" H 1118 1525 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 1118 1616 50  0000 C CNN
F 2 "" H 1200 1850 50  0001 C CNN
F 3 "~" H 1200 1850 50  0001 C CNN
	1    1200 1850
	-1   0    0    1   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5DF8A861
P 1200 3150
F 0 "J2" H 1118 2825 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 1118 2916 50  0000 C CNN
F 2 "" H 1200 3150 50  0001 C CNN
F 3 "~" H 1200 3150 50  0001 C CNN
	1    1200 3150
	-1   0    0    1   
$EndComp
Wire Wire Line
	1400 1750 1650 1750
Wire Wire Line
	1650 1750 1650 1700
Wire Wire Line
	1650 1700 2250 1700
Wire Wire Line
	2250 1900 1650 1900
Wire Wire Line
	1650 1900 1650 1850
Wire Wire Line
	1650 1850 1400 1850
Wire Wire Line
	2450 3400 2450 3500
Wire Wire Line
	2450 3500 1650 3500
Wire Wire Line
	1650 3500 1650 3150
Wire Wire Line
	1650 3150 1400 3150
Wire Wire Line
	1400 3050 1650 3050
Wire Wire Line
	1650 3050 1650 2700
Wire Wire Line
	1650 2700 2350 2700
Wire Wire Line
	2350 2700 2350 2800
Wire Wire Line
	4100 2950 4100 2700
Wire Wire Line
	4100 1500 4100 1700
Connection ~ 4100 1700
$Comp
L power:GND #PWR02
U 1 1 5DFA9047
P 3200 2300
F 0 "#PWR02" H 3200 2050 50  0001 C CNN
F 1 "GND" H 3205 2127 50  0000 C CNN
F 2 "" H 3200 2300 50  0001 C CNN
F 3 "" H 3200 2300 50  0001 C CNN
	1    3200 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1900 3200 1900
Wire Wire Line
	2850 2800 2850 2700
Connection ~ 4100 2700
Wire Wire Line
	4100 2700 4100 1700
Wire Wire Line
	2850 3400 2850 3500
Wire Wire Line
	4100 3500 4100 3250
Wire Wire Line
	5050 4000 5050 4150
Wire Wire Line
	4900 4000 5050 4000
Wire Wire Line
	5050 4550 5050 4450
Wire Wire Line
	5200 4000 5050 4000
Connection ~ 5050 4000
Wire Wire Line
	5200 3800 5050 3800
Wire Wire Line
	5050 3800 5050 3650
$Comp
L power:GND #PWR011
U 1 1 5E045165
P 5950 4550
F 0 "#PWR011" H 5950 4300 50  0001 C CNN
F 1 "GND" H 5955 4377 50  0000 C CNN
F 2 "" H 5950 4550 50  0001 C CNN
F 3 "" H 5950 4550 50  0001 C CNN
	1    5950 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4000 5950 4000
Wire Wire Line
	5950 4000 5950 4150
Wire Wire Line
	5950 4450 5950 4550
$Comp
L power:+12V #PWR09
U 1 1 5E0516DE
P 5050 5150
F 0 "#PWR09" H 5050 5000 50  0001 C CNN
F 1 "+12V" H 5065 5323 50  0000 C CNN
F 2 "" H 5050 5150 50  0001 C CNN
F 3 "" H 5050 5150 50  0001 C CNN
	1    5050 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5E0516E4
P 5050 6050
F 0 "#PWR010" H 5050 5800 50  0001 C CNN
F 1 "GND" H 5055 5877 50  0000 C CNN
F 2 "" H 5050 6050 50  0001 C CNN
F 3 "" H 5050 6050 50  0001 C CNN
	1    5050 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5E0516EA
P 4750 5500
F 0 "R3" V 4543 5500 50  0000 C CNN
F 1 "R" V 4634 5500 50  0000 C CNN
F 2 "" V 4680 5500 50  0001 C CNN
F 3 "~" H 4750 5500 50  0001 C CNN
	1    4750 5500
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 5E0516F0
P 5050 5800
F 0 "R5" V 4843 5800 50  0000 C CNN
F 1 "R" V 4934 5800 50  0000 C CNN
F 2 "" V 4980 5800 50  0001 C CNN
F 3 "~" H 5050 5800 50  0001 C CNN
	1    5050 5800
	-1   0    0    1   
$EndComp
$Comp
L Device:R R7
U 1 1 5E051702
P 5950 5800
F 0 "R7" V 5743 5800 50  0000 C CNN
F 1 "330" V 5834 5800 50  0000 C CNN
F 2 "" V 5880 5800 50  0001 C CNN
F 3 "~" H 5950 5800 50  0001 C CNN
	1    5950 5800
	-1   0    0    1   
$EndComp
Wire Wire Line
	5050 5500 5050 5650
Wire Wire Line
	4900 5500 5050 5500
Wire Wire Line
	5050 6050 5050 5950
Wire Wire Line
	5200 5500 5050 5500
Connection ~ 5050 5500
Wire Wire Line
	5200 5300 5050 5300
Wire Wire Line
	5050 5300 5050 5150
$Comp
L power:GND #PWR012
U 1 1 5E051711
P 5950 6050
F 0 "#PWR012" H 5950 5800 50  0001 C CNN
F 1 "GND" H 5955 5877 50  0000 C CNN
F 2 "" H 5950 6050 50  0001 C CNN
F 3 "" H 5950 6050 50  0001 C CNN
	1    5950 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 5500 5950 5500
Wire Wire Line
	5950 5500 5950 5650
Wire Wire Line
	5950 5950 5950 6050
$Comp
L Connector_Generic:Conn_01x16 J3
U 1 1 5E091D95
P 9600 3750
F 0 "J3" H 9680 3742 50  0000 L CNN
F 1 "Conn_01x16" H 9680 3651 50  0000 L CNN
F 2 "" H 9600 3750 50  0001 C CNN
F 3 "~" H 9600 3750 50  0001 C CNN
	1    9600 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 5300 8250 5300
Wire Wire Line
	8250 5300 8250 4550
Wire Wire Line
	8250 4550 9400 4550
Wire Wire Line
	5800 3800 8250 3800
Wire Wire Line
	8250 3800 8250 4450
Wire Wire Line
	8250 4450 9400 4450
Connection ~ 8250 3800
Wire Wire Line
	8250 3800 8550 3800
Connection ~ 8250 5300
Wire Wire Line
	8250 5300 8550 5300
Wire Wire Line
	2850 3500 4100 3500
Wire Wire Line
	2850 2700 4100 2700
Wire Wire Line
	3050 1700 3650 1700
$Comp
L Device:C C2
U 1 1 5E0C7F12
P 3650 2000
F 0 "C2" H 3765 2046 50  0000 L CNN
F 1 "C" H 3765 1955 50  0000 L CNN
F 2 "" H 3688 1850 50  0001 C CNN
F 3 "~" H 3650 2000 50  0001 C CNN
	1    3650 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 1850 3650 1700
Connection ~ 3650 1700
Wire Wire Line
	3650 1700 4100 1700
$Comp
L power:GND #PWR04
U 1 1 5E0CB8E9
P 3650 2300
F 0 "#PWR04" H 3650 2050 50  0001 C CNN
F 1 "GND" H 3655 2127 50  0000 C CNN
F 2 "" H 3650 2300 50  0001 C CNN
F 3 "" H 3650 2300 50  0001 C CNN
	1    3650 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 2150 3650 2300
Wire Wire Line
	3200 1900 3200 2300
$Comp
L switch2-local:KAQV214 U1
U 1 1 5DE92861
P 5500 3900
F 0 "U1" H 5500 4225 50  0000 C CNN
F 1 "KAQV214" H 5500 4134 50  0000 C CNN
F 2 "" H 5300 3550 50  0001 C CNN
F 3 "" H 5400 3900 50  0001 C CNN
	1    5500 3900
	-1   0    0    -1  
$EndComp
$Comp
L switch2-local:KAQV214 U2
U 1 1 5DE9BF11
P 5500 5400
F 0 "U2" H 5500 5725 50  0000 C CNN
F 1 "KAQV214" H 5500 5634 50  0000 C CNN
F 2 "" H 5300 5050 50  0001 C CNN
F 3 "" H 5400 5400 50  0001 C CNN
	1    5500 5400
	-1   0    0    -1  
$EndComp
Connection ~ 4100 3500
Connection ~ 3250 5200
Wire Wire Line
	4100 5200 4100 5300
Connection ~ 4100 5200
Wire Wire Line
	3250 5200 4100 5200
Wire Wire Line
	4100 4200 4100 5200
Wire Wire Line
	3250 5650 3250 6050
Wire Wire Line
	2850 5650 2850 6050
$Comp
L power:GND #PWR01
U 1 1 5E0704EA
P 2850 6050
F 0 "#PWR01" H 2850 5800 50  0001 C CNN
F 1 "GND" H 2855 5877 50  0000 C CNN
F 2 "" H 2850 6050 50  0001 C CNN
F 3 "" H 2850 6050 50  0001 C CNN
	1    2850 6050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5E070170
P 3250 6050
F 0 "#PWR03" H 3250 5800 50  0001 C CNN
F 1 "GND" H 3255 5877 50  0000 C CNN
F 2 "" H 3250 6050 50  0001 C CNN
F 3 "" H 3250 6050 50  0001 C CNN
	1    3250 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 5700 4100 6050
Wire Wire Line
	2850 5200 3250 5200
Wire Wire Line
	2850 5350 2850 5200
Wire Wire Line
	3250 5350 3250 5200
$Comp
L power:GND #PWR06
U 1 1 5E0568E6
P 4100 6050
F 0 "#PWR06" H 4100 5800 50  0001 C CNN
F 1 "GND" H 4105 5877 50  0000 C CNN
F 2 "" H 4100 6050 50  0001 C CNN
F 3 "" H 4100 6050 50  0001 C CNN
	1    4100 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 5500 4600 5500
$Comp
L Device:Q_NPN_BCE Q2
U 1 1 5E0516F6
P 4200 5500
F 0 "Q2" H 4391 5546 50  0000 L CNN
F 1 "Q_NPN_BCE" H 4391 5455 50  0000 L CNN
F 2 "" H 4400 5600 50  0001 C CNN
F 3 "~" H 4200 5500 50  0001 C CNN
	1    4200 5500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4400 4000 4600 4000
Wire Wire Line
	4100 3800 4100 3500
$Comp
L Device:C C1
U 1 1 5DF2EDBC
P 2850 5500
F 0 "C1" H 2965 5546 50  0000 L CNN
F 1 "C" H 2965 5455 50  0000 L CNN
F 2 "" H 2888 5350 50  0001 C CNN
F 3 "~" H 2850 5500 50  0001 C CNN
	1    2850 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5DE8960A
P 3250 5500
F 0 "R1" V 3043 5500 50  0000 C CNN
F 1 "R" V 3134 5500 50  0000 C CNN
F 2 "" V 3180 5500 50  0001 C CNN
F 3 "~" H 3250 5500 50  0001 C CNN
	1    3250 5500
	-1   0    0    1   
$EndComp
$Comp
L Device:Q_NPN_BCE Q1
U 1 1 5DEB24C7
P 4200 4000
F 0 "Q1" H 4391 4046 50  0000 L CNN
F 1 "Q_NPN_BCE" H 4391 3955 50  0000 L CNN
F 2 "" H 4400 4100 50  0001 C CNN
F 3 "~" H 4200 4000 50  0001 C CNN
	1    4200 4000
	-1   0    0    -1  
$EndComp
$EndSCHEMATC