
#ifndef BLU_HCO5_H_
#define BLU_HCO5_H_

#include <stdint.h>
#include <stdio.h>
#include "msp.h"
#include "file.h"
#include "inc/GPIO.h"
#define IN_BUFFER_SIZE 16

extern  volatile uint8_t in_buf_index;
extern volatile uint8_t in_buf_cmd_ready;
extern volatile char IN_BUFFER[IN_BUFFER_SIZE];



void HC05_A2_UART_INIT(void);


#endif //BLU_HCO5_H_
