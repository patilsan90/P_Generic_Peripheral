#ifndef __PROJECT_CONFIG__
#define __PROJECT_CONFIG__

#include <SoftSerial.h>

#define DEBUG_MODE (0)
#define DEVICE_ID_LEN (8) //it is 8 bytes
#define PARENT_DEVICE_ID_LEN (17) //it is 8 bytes
//For EX: 5C:CF:7F:01:69:B7



#if (DEBUG_MODE == 1)
#define DEBUG_PRINT(...) serial->println(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

#endif
