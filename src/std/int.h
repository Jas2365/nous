_Pragma("once");

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned long long size_t;

// signed mins
#define _int8_min (-128)
#define _int16_min (-32768)
#define _int32_min (-2147483647 - 1)
#define _int64_min (-9223372036854775807LL - 1)

// signed maxs
#define _int8_max 128
#define _int16_max 32768
#define _int32_max 2147483647
#define _int64_max 9223372036854775807LL

// unsigned maxs
#define _uint8_max 0xff
#define _uint16_max 0xffff
#define _uint32_max 0xffffffffU
#define _uint64_max 0xffffffffffffffffULL
