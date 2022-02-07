/*
 * This file is part of paparazzi
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/*
 * @file "modules/sensors/sonar/sonar_bluerobotics.c"
 * @author Jesús Bautista Villar
 * 
 */
 
#ifndef SONAR_BLUEROBOTICS_H
#define SONAR_BLUEROBOTICS_H

#include "std.h"

/* TODO: BLUEROBOTICS SONAR messages IDs */

/* Message structure 
 * We need this structure because the array that we use
 * contains both u8 (1 Byte) and u16 (2 Bytes) fields.
 
struct sonar_msg{
    enum { is_u8, is_u16} type;
    union {
        uint8_t u8val;
        uint16_t u16val;
    } val;
};

// Test messages
extern struct sonar_msg sonar_ping_protocol;
*/

/* External functions (called by the state machine)*/
extern void sonar_init(void);
extern void sonar_ping(void);
extern void sonar_event(void);

// Variable to start/stop requesting
extern bool sonar_stream_setting;

#define LENGTH(x)  (sizeof(x) / sizeof(*x))

#endif
