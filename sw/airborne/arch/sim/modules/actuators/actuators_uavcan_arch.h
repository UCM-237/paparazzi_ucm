/*
 * Copyright (C) 2020 Freek van Tienen <freek.v.tienen@gmail.com>
 *
 * This file is part of Paparazzi.
 *
 * Paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * Paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/** @file arch/sim/modules/actuators/actuators_uavcan_arch.h
 *  dummy servos handling for sim
 */

#ifndef ACTUATORS_UAVCAN_ARCH_H
#define ACTUATORS_UAVCAN_ARCH_H

#define SERVOS_TICS_OF_USEC(_v) (_v)

#define ActuatorUavcanSet(_i, _v) {}
#define ActuatorsUavcanCommit() {}

extern void actuators_uavcan_arch_init(void);

#endif /* ACTUATORS_UAVCAN_ARCH_H */