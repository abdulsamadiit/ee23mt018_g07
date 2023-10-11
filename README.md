
# Embedded System Lab

GROUP: - 07

EE23MT001 ALOK

EE23MT018 S ABDUL SAMAD

## Aim:
TO program microontroller to transmit:

"F0" if SW1 is pressed

"AA" if SW2 is pressed 

over UART with baud rate 9600 and odd parity. 

Your program should also listen for incoming data on the UART with the same baud and parity config;

 if "AA" is received LED should be GREEN; if "F0" is recieved, the LED should be BLUE and if any error is detected LED should be RED.
## Procedure
1. Initialize Peripherals
2. Configure UART for Transmission 
   (we used UART 7 & UART 5)
3. Configure UART for Reception
   (we used UART 7 & UART 5)

## Baud Rate

UART Baud Rate =  ( f / 16 x baud divisor) 

Where f is the clock frequency of the UART module which is known and equal to system frequency. The TM4C123 Tiva C launchpad has an onboard 16MHz crystal. Hence f = 16MHz. 

Baud divisor is the value that will be loaded to baud control registers such as UARTIBRD and UARTFBRD.

9600 =  (16MHz / 16 x baud divisor) 

Baud divisor = 1000000/9600 = 104.1667

Value for the fractional baud rate register can be calculated by multiplying fraction value with 64 and adding 0.5. 

0.166 x 64 + 0.5 = 11
## Document Referred:-
1. TM4C123GH6PM microcontroller datasheet 
2. Cortex-M4 Technical Reference Manual

## Screenshots

![BOARD 1](https://github.com/Alokiitdh/ESLab2023_ee23mtG07/assets/144205496/9d315ea8-9f66-451a-9ac2-ced06f2573b6)
Board 1 is Transmitter & Board 2 is Receiver. F0 is Trasmitted.
 
![BOARD 1 (1)](https://github.com/Alokiitdh/ESLab2023_ee23mtG07/assets/144205496/a1ceb352-a349-49b5-96ae-1035f149c965)
Board 1 is Transmitter & Board 2 is Receiver. AA is Trasmitted.

 
![BOARD 1 (2)](https://github.com/Alokiitdh/ESLab2023_ee23mtG07/assets/144205496/5ad2f6f9-310d-48dc-8e95-2ea6d66c70c3)
Board 2 is Transmitter & Board 1 is Receiver. F0 is Trasmitted.

 
![BOARD 1 (3)](https://github.com/Alokiitdh/ESLab2023_ee23mtG07/assets/144205496/f9fa8bfa-9377-4729-9dbc-0d21afaac96f)
Board 2 is Transmitter & Board 1 is Receiver. AA is Trasmitted.



## Result: -
 The results successfully demonstrates UART communication