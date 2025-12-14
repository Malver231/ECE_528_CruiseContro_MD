/*
 * CRUISE_CONTROL.h
 *
 *  Created on: Nov 30, 2025
 *      Author: malve
 */

#ifndef INC_CRUISE_CONTROL_H_
#define INC_CRUISE_CONTROL_H_
#include <stdint.h>

typedef enum {
        IDLE=0,
        CRUISE,
        STOP,
        AVOID,
        MANUAL,
        FOLLOW
        }STATE_T;

        typedef enum {
            AVOID_IDLE=0,
            CHECK_LEFT,
            CHECK_RIGH,
            CHECK_RIGHT_180,
            CHECK_RIGHT_90,
            DONE
        }AVOID_STATE_T;

extern volatile STATE_T SDK_STATE;
extern volatile AVOID_STATE_T SDK_AVOID_STATE;
void CRUISE_CONTROL_INIT(void);
void CRUISE_CONTROL(uint16_t distance_mm);
void AVOID_COMMAND(uint16_t distance_mm);

#endif /* INC_CRUISE_CONTROL_H_ */
