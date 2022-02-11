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

/* Parser msg struct */
#define SONAR_MAX_PAYLOAD 256
struct sonar_parse_t {
  uint16_t payload_len;
  uint16_t msg_id;
  uint8_t src_id;
  uint8_t dev_id;

  uint8_t msgData[SONAR_MAX_PAYLOAD] __attribute__((aligned));
  uint8_t status;
  
  uint8_t ck;
  bool msg_available;
};

extern struct sonar_parse_t br_sonar;

/* TODO: BLUEROBOTICS SONAR messages IDs */
// Common
#define BR_PROTOCOL_VERSION 5
#define BR_REQUEST 6

// BR Ping 1D
#define BR_SET_DEVICE_ID 1000
#define BR_DEVICE_ID 1201
#define BR_DISTANCE_SIMPLE 1211

// Variable to start/stop requesting
extern bool sonar_stream_setting;

/* Testing zone */
extern uint8_t checksum; // Telemetry testing variable


/* Message structure 
struct SonarMsg {
  uint8_t start1;
  uint8_t start2;
  uint8_t payloadLen_L;
  uint8_t payloadLen_H;
  uint8_t msgId_L;
  uint8_t msgId_H;
  uint8_t srcID;
  uint8_t devID;

  uint8_t payload[SONAR_MAX_PAYLOAD] __attribute__((aligned));

  uint8_t checksum_L;
  uint8_t checksum_H;
};*/

/* External functions (called by the autopilot)*/
#include "pprzlink/pprzlink_device.h"
#include "mcu_periph/uart.h"

extern void sonar_init(void);
extern void sonar_ping(void);
extern void sonar_event(void);

#endif
