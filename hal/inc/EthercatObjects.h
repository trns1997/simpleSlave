extern "C"
{
#include "esc_coe.h"
}

#include <vector>

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
static const char acName1600[] = "Receive PDO mapping";
static const char acName1A00[] = "Transmit PDO mapping";
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
static const char acName6000[] = "Digital Inputs";
static const char acName6000_01[] = "Watchdog counter";
static const char acName7000[] = "Digital outputs";
static const char acName7000_01[] = "Watchdog counter";
static const char acName8001[] = "Slave commands";
static const char acName8001_01[] = "Reset counter";

static char ac1008_00[] = "SOES test application";
static char ac1009_00[] = "0.0.2";
static char ac100A_00[] = "0.9.3";

const _objd SDO1000[] =
    {{0, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acName1000[0], 0x00000000, NULL}};
const _objd SDO1008[] =
    {{0, DTYPE_VISIBLE_STRING, sizeof(ac1008_00) << 3, ATYPE_RO, &acName1008[0], 0, &ac1008_00[0]}};
const _objd SDO1009[] =
    {{0, DTYPE_VISIBLE_STRING, sizeof(ac1009_00) << 3, ATYPE_RO, &acName1009[0], 0, &ac1009_00[0]}};
const _objd SDO100A[] =
    {{0, DTYPE_VISIBLE_STRING, sizeof(ac100A_00) << 3, ATYPE_RO, &acName100A[0], 0, &ac100A_00[0]}};
const _objd SDO1018[] =
    {{0, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 4, NULL},
     {1, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acName1018_01[0], 0x00001337, NULL},
     {2, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acName1018_02[0], 0x12783456, NULL},
     {3, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acName1018_03[0], 0x00000001, NULL},
     {4, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acName1018_04[0], 0x00000000, NULL}};

const _objd SDO1C00[] =
    {{0, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 4, NULL},
     {1, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C00_01[0], 1, NULL},
     {2, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C00_02[0], 2, NULL},
     {3, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C00_03[0], 3, NULL},
     {4, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C00_04[0], 4, NULL}};
const _objd SDO1C10[] =
    {{0, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C10[0], 0, NULL}};
const _objd SDO1C11[] =
    {{0, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acName1C11[0], 0, NULL}};

const _objd SDO7000[] =
    {{0, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 1, NULL},
     {1, DTYPE_UNSIGNED16, 16, ATYPE_RW, &acName7000_01[0], 0, NULL}};
const _objd SDO1600[] =
    {{0, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 1, NULL},
     {1, DTYPE_UNSIGNED32, 32, ATYPE_RO, &acNameMO[0], 0x70000110, NULL}};
const _objd SDO1C12[] =
    {{0, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 1, NULL},
     {1, DTYPE_UNSIGNED16, 16, ATYPE_RO, &acNameMO[0], 0x1600, NULL}};

const _objd SDO1C13[] =
    {{0, DTYPE_UNSIGNED8, 8, ATYPE_RO, &acNameNOE[0], 1, NULL},
     {1, DTYPE_UNSIGNED16, 16, ATYPE_RO, &acNameMO[0], 0x1A00, NULL}};
