/*
 * Licensed under the GNU General Public License version 2 with exceptions. See
 * LICENSE file in the project root for full license information
 */

 /** \file
 * \brief
 * Header file for Application types.
 *
 * Part of the application, host declarations of application types mapped against
 * ServiceData Objects and ProcessData Objects.
 */

#ifndef __utypes_h__
#define __utypes_h__

#include <cc.h>

CC_PACKED_BEGIN
typedef struct
{
   // current IMU data
   int16_t accelerometerX; // raw data
   int16_t accelerometerY;
   int16_t accelerometerZ;

   int16_t gyroscopeX; // raw data.
   int16_t gyroscopeY;
   int16_t gyroscopeZ;

   int16_t temperature; // Celsius degrees
}CC_PACKED imu;
CC_PACKED_END


CC_PACKED_BEGIN
typedef struct
{
   uint16_t watchdogCounter;

   imu ankleIMU;

   uint16_t forceSensor0;
   uint16_t forceSensor1;
   uint16_t forceSensor2;
   uint16_t forceSensorVref;
   uint16_t forceSensor4;

   uint16_t boardStatus;
}CC_PACKED _Rbuffer;
CC_PACKED_END

CC_PACKED_BEGIN
typedef struct
{
   uint16_t watchdogCounter;
}CC_PACKED _Wbuffer;
CC_PACKED_END

CC_PACKED_BEGIN
typedef struct
{
   uint32_t reset_counter;
}CC_PACKED _Cbuffer;
CC_PACKED_END

#endif
