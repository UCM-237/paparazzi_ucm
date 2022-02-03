/*
 * Copyright (C) 2017 Gautier Hattenberger <gautier.hattenberger@enac.fr>
 *
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
/**
 * @file "modules/sensors/sonar/sonar_bluerobotics.c"
 * @author Jesús Bautista Villar
 * 
 */

#include "modules/sonar/sonar_bluerobotics.h"

#include "std.h" 
#include "mcu_periph/uart.h"
#include <stdio.h>
#include <string.h>

#define SONAR_MAX_LEN 4096  // Es el tamaño del buffer que setea el servidor en python (mandamos strings)

char buffer[SONAR_MAX_LEN]; // tmp buffer

// Sonar message structure
struct sonar_msg_t{
  int len;
  char msg[SONAR_MAX_LEN];
};

struct sonar_msg_t sonar_msg;

// Test request message: (general_request#6--> common_protocol_version#5)
static uint8_t request_protocol_version[12] = { 
        0x42, //  0: "B"
        0x52, //  1: "R"
        4,    //  2: 4_L payload length |
        0,    //  3: 0_H                |
        6,    //  4: 6_L message ID |
        0,    //  5: 0_H            |
        0,    //  6: source ID
        0,    //  7: device ID
        5,    //  8: 5_L requested message ID |
        0,    //  9: 0_H                      |
        0xA1, // 10: 161_L message checksum (sum of all non-checksum bytes) |
        0x00  // 11: 0_H                                                    |
};

/* Initialize decoder */
extern void sonar_init(void)
{
  sonar_stream_setting = true;

  sonar_msg.len = 0;
  memset(sonar_msg.msg, 0, SONAR_MAX_LEN); // clean the strings
  memset(buffer, 0, SONAR_MAX_LEN); 
  
}


/* Send message to serial port (byte by byte) */
void sonar_send_msg(uint8_t msg[])
{
  uint8_t i = 0;
  while (msg[i]) {
  uart_put_byte(&(SONAR_DEV), 0, msg[i]);
  i++;
  }
}


/* Message parsing */
// To hexadecimal string for testing
static void dummy_sonar_parse(struct sonar_msg_t *BR_msg, uint8_t byte)
	{
	  BR_msg->len += sprintf(BR_msg->msg + BR_msg->len, "0x%02X ", byte);
	}

/* Look for data on serial port and send to parser */
void sonar_event(void)
{
  while(uart_char_available(&(SONAR_DEV))) {
    uint8_t byte = uart_getch(&(SONAR_DEV));
    dummy_sonar_parse(&sonar_msg, byte);
  }
  
  // Testing printf
  printf("Message from sonar: %s", sonar_msg.msg);
}