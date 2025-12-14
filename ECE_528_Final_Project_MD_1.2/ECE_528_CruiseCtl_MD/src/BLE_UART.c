/**
 * @file BLE_UART.c
 *
 * @brief Source code for the BLE_UART driver.
 *
 * This file contains the function definitions for the BLE_UART driver.
 *
 * It interfaces with the Adafruit Bluefruit LE UART Friend Bluetooth Low Energy (BLE) module, which uses the UART communication protocol.
 *  - Product Link: https://www.adafruit.com/product/2479
 *
 * The following connections must be made:
 *  - BLE UART MOD  (Pin 1)     <-->  MSP432 LaunchPad Pin P1.6
 *  - BLE UART CTS  (Pin 2)     <-->  MSP432 LaunchPad GND
 *  - BLE UART TXO  (Pin 3)     <-->  MSP432 LaunchPad Pin P9.6 (PM_UCA3RXD)
 *  - BLE UART RXI  (Pin 4)     <-->  MSP432 LaunchPad Pin P9.7 (PM_UCA3TXD)
 *  - BLE UART VIN  (Pin 5)     <-->  MSP432 LaunchPad VCC (3.3V)
 *  - BLE UART RTS  (Pin 6)     <-->  Not Connected
 *  - BLE UART GND  (Pin 7)     <-->  MSP432 LaunchPad GND
 *  - BLE UART DFU  (Pin 8)     <-->  Not Connected
 *
 * @note For more information regarding the Enhanced Universal Serial Communication Interface (eUSCI),
 * refer to the MSP432Pxx Microcontrollers Technical Reference Manual
 *
 * @author
 *
 */

#include "../inc/BLE_UART.h"

void BLE_UART_Init()
{
    //Configure pins 3.2(RX) and 3.3(TX)
    P3->SEL0 |=0X0C;
    P3->SEL1 &=~0X0C;

    P1->SEL0 &= ~0x40;
    P1->SEL1 &= ~0x40;
    P1->DIR |= 0x40;

    EUSCI_A2->CTLW0 |= 0x01;

    EUSCI_A2->MCTLW &= ~0xFF;

    EUSCI_A2->CTLW0 &= ~0x8000;

    EUSCI_A2->CTLW0 &= ~0x4000;

    EUSCI_A2->CTLW0 &= ~0x2000;

    EUSCI_A2->CTLW0 &= ~0x1000;

    EUSCI_A2->CTLW0 &= ~0x0800;

    EUSCI_A2->CTLW0 &= ~0x0600;

    EUSCI_A2->CTLW0 &= ~0x0100;

    EUSCI_A2->CTLW0 |= 0x00C0;


    EUSCI_A2->BRW = 1250;

    EUSCI_A2->IE &= ~0x0C;

    EUSCI_A2->IE |= 0x03;

    EUSCI_A2->CTLW0 &= ~0x01;

}

uint8_t BLE_UART_InChar()
{
    while((EUSCI_A2->IFG & 0x01) == 0);


    return EUSCI_A2->RXBUF;
}

void BLE_UART_OutChar(uint8_t data)
{
    while((EUSCI_A2->IFG & 0x02) == 0);


    EUSCI_A2->TXBUF = data;
}

int BLE_UART_InString(char *buffer_pointer, uint16_t buffer_size)
{
    int length = 0;
    int string_size = 0;

    //non-blocking block
      if ((EUSCI_A2->IFG & 0x01) == 0) {
             return 0;   // no data
         }
      //end of block

    char character = BLE_UART_InChar();

    while(character != LF) {

        if (character == BS) {
            if (length) {
                buffer_pointer--;
                length--;
                BLE_UART_OutChar(BS);
            }
        }
        else if (length < buffer_size) {
            *buffer_pointer = character;
            buffer_pointer++;
            length++;
            string_size++;
        }
        character = BLE_UART_InChar();
    }
    *buffer_pointer = 0;

    return string_size;



//        static uint16_t index = 0;
//        char character;
//        int  size = 0;
//        uint8_t command_complete = 0;
//
//        // If no data at all, return immediately (non-blocking)
//        if ((EUSCI_A2->IFG & 0x0001) == 0)
//        {
//            return 0;
//        }
//
//        // Drain ALL available characters from RXBUF
//        while ((EUSCI_A2->IFG & 0x0001) && (command_complete == 0))
//        {
//            character = EUSCI_A2->RXBUF;
//
//            // End of command?
//            if ((character == '\r') || (character == '\n'))
//            {
//                if (index > 0)
//                {
//                    buffer_pointer[index] = 0;   // terminate string
//                    size = (int)index;          // save length
//                    index = 0;                  // reset for next command
//                    command_complete = 1;       // tell caller we have a full command
//                }
//                // else: ignore empty newline
//            }
//            else
//            {
//                // Normal character: store if space available
//                if (index < (buffer_size - 1))
//                {
//                    buffer_pointer[index] = character;
//                    index++;
//                }
//                else
//                {
//                    // Overflow: reset to avoid corrupt string
//                    index = 0;
//                }
//            }
//        }
//
//        // If we completed a command this call, return its size
//        if (command_complete)
//        {
//            return size;
//        }
//
//        // Otherwise, no full command yet
//        return 0;

}

void BLE_UART_OutString(char *pt)
{

    while(*pt) {
        BLE_UART_OutChar(*pt);
        pt++;
    }
}

uint8_t Check_BLE_UART_Data(char BLE_UART_Data_Buffer[], char *data_string)
{
    if (strstr(BLE_UART_Data_Buffer, data_string) != NULL) {
        return 0x01;
    }
    else {
        return 0x00;
    }
}

void BLE_UART_Reset()
{
    P1->OUT |= 0x40;
    Clock_Delay1ms(1000);

    BLE_UART_OutString("ATZ\r\n");
    Clock_Delay1ms(1000);

    P1->OUT &= ~0x40;

}






