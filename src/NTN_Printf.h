#ifndef _NTN_LOG_H_
#define _NTN_LOG_H_
#include "NTN_System.h"
void NTN_Print_Init();
void NTN_Print_Handler();
#define NTN_PRINT_START() Serial.printf("Start [%s][%d] \r\n",__FUNCTION__,__LINE__)
#define NTN_PRINTF(...)     Serial.printf("[%s][%d] ",__FUNCTION__,__LINE__);\
                            Serial.printf(__VA_ARGS__)
#endif