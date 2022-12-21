/*
 * Licensed under the GNU General Public License version 2 with exceptions. See
 * LICENSE file in the project root for full license information
 */

/** \file
 * \brief
 * CoE Object Dictionary.
 *
 * Part of application, describe the slave and its process data.
 */

#include "esc_coe.h"
#include "utypes.h"
#include <stddef.h>

extern _Rbuffer Rb;
extern _Wbuffer Wb;
extern _Cbuffer Cb;

static const char acName1000[] = "Device Type";
static const char acName1008[] = "Manufacturer Device Name";
static const char acName1009[] = "Manufacturer Hardware Version";
static const char acName100A[] = "Manufacturer Software Version";
static const char acName1018[] = "Identity Object";
static const char acName1018_01[] = "Vendor ID";
static const char acName1018_02[] = "Product Code";
static const char acName1018_03[] = "Revision Number";
static const char acName1018_04[] = "Serial Number";
static const char acNameMO[] = "Mapped object";
static const char acName1C00[] = "Sync Manager Communication type";
static const char acName1C00_01[] = "Communications type SM0";
static const char acName1C00_02[] = "Communications type SM1";
static const char acName1C00_03[] = "Communications type SM2";
static const char acName1C00_04[] = "Communications type SM3";
static const char acName1C10[] = "Sync Manager 0 PDO Assignment";
static const char acName1C11[] = "Sync Manager 1 PDO Assignment";
static const char acName1C12[] = "Sync Manager 2 PDO Assignment";
static const char acName1C13[] = "Sync Manager 3 PDO Assignment";
static const char acNameNOE[] = "Number of entries";
static const char acName8001[] = "Slave commands";
static const char acName8001_01[] = "Reset counter";

static char ac1008_00[] = "SOES test application";
static char ac1009_00[] = "0.0.2";
static char ac100A_00[] = "0.9.3";

const _objd SDO1000[] =
    {{0x00, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acName1000[0], 0x00000000, NULL}};
const _objd SDO1008[] =
    {{0x00, DTYPE_VISIBLE_STRING, sizeof(ac1008_00) << 3, ATYPE_RO, &acName1008[0], 0, &ac1008_00[0]}};
const _objd SDO1009[] =
    {{0x00, DTYPE_VISIBLE_STRING, sizeof(ac1009_00) << 3, ATYPE_RO, &acName1009[0], 0, &ac1009_00[0]}};
const _objd SDO100A[] =
    {{0x00, DTYPE_VISIBLE_STRING, sizeof(ac100A_00) << 3, ATYPE_RO, &acName100A[0], 0, &ac100A_00[0]}};
const _objd SDO1018[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x04, NULL},
     {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acName1018_01[0], 0x00001337, NULL},
     {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acName1018_02[0], 0x12783456, NULL},
     {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acName1018_03[0], 0x00000001, NULL},
     {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acName1018_04[0], 0x00000000, NULL}};

const _objd SDO1600[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x01, NULL},
     {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x70000110, NULL}};

const _objd SDO1A00[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x01, NULL},
     {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60000110, NULL}};

const _objd SDO1A01[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x07, NULL},
     {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60010110, NULL},
     {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60010210, NULL},
     {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60010310, NULL},
     {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60010410, NULL},
     {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60010510, NULL},
     {0x06, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60010610, NULL},
     {0x07, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60010710, NULL}};

const _objd SDO1A05[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x05, NULL},
     {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60050110, NULL},
     {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60050210, NULL},
     {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60050310, NULL},
     {0x04, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60050410, NULL},
     {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60050510, NULL}};

const _objd SDO1A06[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x01, NULL},
     {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x60060110, NULL}};

const _objd SDO1C00[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x04, NULL},
     {0x01, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C00_01[0], 0x01, NULL},
     {0x02, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C00_02[0], 0x02, NULL},
     {0x03, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C00_03[0], 0x03, NULL},
     {0x04, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C00_04[0], 0x04, NULL}};

const _objd SDO1C10[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C10[0], 0x00, NULL}};

const _objd SDO1C11[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C11[0], 0x00, NULL}};

const _objd SDO1C12[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x01, NULL},
     {0x01, DTYPE_UNSIGNED16, 16, ATYPE_RO, &acNameMO[0], 0x1600, NULL}};

const _objd SDO1C13[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x07, NULL},
     {0x01, DTYPE_UNSIGNED16, 16, ATYPE_RO, &acNameMO[0], 0x1A00, NULL},
     {0x02, DTYPE_UNSIGNED16, 16, ATYPE_RO, &acNameMO[0], 0x1A01, NULL},
     {0x03, DTYPE_UNSIGNED16, 16, ATYPE_RO, &acNameMO[0], 0x1A02, NULL},
     {0x04, DTYPE_UNSIGNED16, 16, ATYPE_RO, &acNameMO[0], 0x1A03, NULL},
     {0x05, DTYPE_UNSIGNED16, 16, ATYPE_RO, &acNameMO[0], 0x1A04, NULL},
     {0x06, DTYPE_UNSIGNED16, 16, ATYPE_RO, &acNameMO[0], 0x1A05, NULL},
     {0x07, DTYPE_UNSIGNED16, 16, ATYPE_RO, &acNameMO[0], 0x1A06, NULL}};

const _objd SDO6000[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x01, NULL},
     {0x01, DTYPE_UNSIGNED16, 16, ATYPE_RO, "Watchdog counter", 0, &(Rb.watchdogCounter)}};

const _objd SDO6001[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x07, NULL},
     {0x01, DTYPE_INTEGER16, 16, ATYPE_RO, "Accelerometer X", 0, &(Rb.ankleIMU.accelerometerX)},
     {0x02, DTYPE_INTEGER16, 16, ATYPE_RO, "Accelerometer Y", 0, &(Rb.ankleIMU.accelerometerY)},
     {0x03, DTYPE_INTEGER16, 16, ATYPE_RO, "Accelerometer Z", 0, &(Rb.ankleIMU.accelerometerZ)},
     {0x04, DTYPE_INTEGER16, 16, ATYPE_RO, "Gyroscope X", 0, &(Rb.ankleIMU.gyroscopeX)},
     {0x05, DTYPE_INTEGER16, 16, ATYPE_RO, "Gyroscope Y", 0, &(Rb.ankleIMU.gyroscopeY)},
     {0x06, DTYPE_INTEGER16, 16, ATYPE_RO, "Gyroscope Z", 0, &(Rb.ankleIMU.gyroscopeZ)},
     {0x07, DTYPE_INTEGER16, 16, ATYPE_RO, "Temperature", 0, &(Rb.ankleIMU.temperature)}};

const _objd SDO6005[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x05, NULL},
     {0x01, DTYPE_UNSIGNED16, 16, ATYPE_RO, "Force sensor 0", 0, &(Rb.forceSensor0)},
     {0x02, DTYPE_UNSIGNED16, 16, ATYPE_RO, "Force sensor 1", 0, &(Rb.forceSensor1)},
     {0x03, DTYPE_UNSIGNED16, 16, ATYPE_RO, "Force sensor 2", 0, &(Rb.forceSensor2)},
     {0x04, DTYPE_UNSIGNED16, 16, ATYPE_RO, "Force sensor Vref", 0, &(Rb.forceSensorVref)},
     {0x05, DTYPE_UNSIGNED16, 16, ATYPE_RO, "Force sensor 4", 0, &(Rb.forceSensor4)}};

const _objd SDO6006[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x01, NULL},
     {0x01, DTYPE_UNSIGNED16, 16, ATYPE_RO, "Board status", 0, &(Rb.boardStatus)}};

const _objd SDO7000[] =
    {{0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x01, NULL},
     {0x01, DTYPE_UNSIGNED16, 16, ATYPE_RW, "Watchdog counter", 0, &(Wb.watchdogCounter)}};

const _objd SDO8001[] =
    {
        {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 0x01, NULL},
        {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RW, &acName8001_01[0], 0, &(Cb.reset_counter)},
};

const _objectlist SDOobjects[] =
    {{0x1000, OTYPE_VAR, 0, 0, &acName1000[0], &SDO1000[0]},
     {0x1008, OTYPE_VAR, 0, 0, &acName1008[0], &SDO1008[0]},
     {0x1009, OTYPE_VAR, 0, 0, &acName1009[0], &SDO1009[0]},
     {0x100A, OTYPE_VAR, 0, 0, &acName100A[0], &SDO100A[0]},
     {0x1018, OTYPE_RECORD, 4, 0, &acName1018[0], &SDO1018[0]},
     {0x1600, OTYPE_RECORD, 0x01, 0, "RxPDO mapping 1", &SDO1600[0]},
     {0x1A00, OTYPE_RECORD, 0x01, 0, "TxPDO mapping 1", &SDO1A00[0]},
     {0x1A01, OTYPE_RECORD, 0x07, 0, "TxPDO mapping 2", &SDO1A01[0]},
     {0x1A05, OTYPE_RECORD, 0x05, 0, "TxPDO mapping 6", &SDO1A05[0]},
     {0x1A06, OTYPE_RECORD, 0x05, 0, "TxPDO mapping 7", &SDO1A06[0]},
     {0x1C00, OTYPE_ARRAY, 4, 0, &acName1C00[0], &SDO1C00[0]},
     {0x1C10, OTYPE_ARRAY, 0, 0, &acName1C10[0], &SDO1C10[0]},
     {0x1C11, OTYPE_ARRAY, 0, 0, &acName1C11[0], &SDO1C11[0]},
     {0x1C12, OTYPE_ARRAY, 0x01, 0, &acName1C12[0], &SDO1C12[0]},
     {0x1C13, OTYPE_ARRAY, 0x07, 0, &acName1C13[0], &SDO1C13[0]},
     {0x6000, OTYPE_ARRAY, 0x01, 0, "Watchdog counter", &SDO6000[0]},
     {0x6001, OTYPE_ARRAY, 0x07, 0, "Ankle IMU", &SDO6001[0]},
     {0x6005, OTYPE_ARRAY, 0x05, 0, "Force sensors", &SDO6005[0]},
     {0x6006, OTYPE_ARRAY, 0x01, 0, "Board status", &SDO6006[0]},
     {0x7000, OTYPE_ARRAY, 0x01, 0, "Watchdog counter", &SDO7000[0]},
     {0x8001, OTYPE_ARRAY, 0x01, 0, &acName8001[0], &SDO8001[0]},
     {0xffff, 0xff, 0xff, 0xff, NULL, NULL}};
