#ifndef MATRIX_H
#define MATRIX_H

#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>

#define PIN_DATA D4
#define COLUMNS 32
#define ROWS    8
#define WIDTH_FONT 6

extern Adafruit_NeoMatrix matrix;

void init_Matrix_Ws2812(void);
void Matrix_Ws2812_Handle(void);

#endif // MATRIX_H