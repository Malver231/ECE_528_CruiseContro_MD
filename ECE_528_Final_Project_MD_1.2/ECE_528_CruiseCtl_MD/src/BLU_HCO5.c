/*
 * EUSCI_A3_UART.c
 *
 *  Created on: Nov 29, 2025
 *      Author: malver
 */

#include"../inc/BLU_HCO5.h"



void HC05_A2_UART_INIT(void)
{

    //Configure pins 3.2(RX) and 3.3(TX)
    P3->SEL0 |=0X0C;
    P3->SEL1 &=~0X0C;

    EUSCI_A2->CTLW0 |=0X0001;
    EUSCI_A2->MCTLW &=~0XFF;
    EUSCI_A2->CTLW0 &=~0X8000;
    EUSCI_A2->CTLW0 &=~0X4000;
    EUSCI_A2->CTLW0 &=~0X2000;
    EUSCI_A2->CTLW0 &=~0X1000;
    EUSCI_A2->CTLW0 &=~0X0800;
    EUSCI_A2->CTLW0 &=~0X0600;
    EUSCI_A2->CTLW0 &=~0X0100;
    EUSCI_A2->CTLW0 |=0X0080;
    EUSCI_A2->BRW=1250;// N=(12MHz)/(9600 baud rate)=1250
    EUSCI_A2->IE &=~0X0C;
    EUSCI_A2->IE |=0X01;
    EUSCI_A2->IFG &=~0X01;
    EUSCI_A2->CTLW0 &=~0X01;

}

volatile uint8_t in_buf_index =0;
volatile uint8_t in_buf_cmd_ready=0;
volatile char IN_BUFFER[IN_BUFFER_SIZE];

void EUSCIA2_IRQHandler(void)
{
    //P2->OUT ^= BIT0;
    //char char_rxbuf;
    //LED2_Output(RGB_LED_BLUE);

    char c = EUSCI_A2->RXBUF;

     if (c == '\r' || c == '\n')
     {
         if (in_buf_index > 0)
         {
             IN_BUFFER[in_buf_index] = '\0';
             in_buf_cmd_ready = 1;
             in_buf_index = 0;
         }
     }
     else
     {
         if (in_buf_index < IN_BUFFER_SIZE - 1)
             IN_BUFFER[in_buf_index++] = c;
         else
             in_buf_index = 0;
     }
    //LED2_Output(RGB_LED_GREEN);
}
