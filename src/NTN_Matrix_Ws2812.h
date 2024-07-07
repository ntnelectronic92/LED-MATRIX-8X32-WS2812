#ifndef _NTN_MATRIX_WS2812_H_
#define _NTN_MATRIX_WS2812_H_
#include "NTN_App.h"
#define PIN_DATA D4
#define COLUMNS 32
#define ROWS    8
#define WIDTH_FONT 6
void NTN_Matrix_Ws2812_Init(void);
void NTN_Matrix_Ws2812_Handle(void);
#endif