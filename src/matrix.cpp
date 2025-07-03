#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include "matrix.h"

extern Adafruit_NeoMatrix matrix;
extern String stringView;
extern int startView;
extern int indexColor;
extern int16_t lengthTextForViewScroll;
extern const uint16_t colorsText[];

void init_Matrix_Ws2812(void)
{
    matrix.begin();
    matrix.setTextWrap(false);
    matrix.setBrightness(100);
    matrix.setTextColor(colorsText[0]);
    lengthTextForViewScroll = - (stringView.length() * WIDTH_FONT);
}

void Matrix_Ws2812_Handle(void)
{
    switch (modeLEDWS2812)
    {
    case TEST:
        matrix.fillScreen(0);
        matrix.drawCircle(4, 4, 2, matrix.Color(255, 0, 0));
        matrix.drawPixel(0, 0, matrix.Color(0, 255, 0));
        matrix.drawPixel(31, 0, matrix.Color(0, 255, 255));
        matrix.show();
        delay(50);
        break;
    case TEXT_ROLLING:
        matrix.fillScreen(0);
        matrix.setCursor(startView, 0);
        matrix.print(stringView);
        if (--startView < lengthTextForViewScroll)
        {
            startView = matrix.width();
            if (++indexColor >= 8) indexColor = 0;
            matrix.setTextColor(colorsText[indexColor]);
        }
        matrix.show();
        delay(50);
        break;
    case IMAGE_VIEW:
        matrix.fillScreen(0);
        matrix.drawBitmap(25, 0, image_Bluetooth_Idle_5x8_bits, 5, 8, matrix.Color(0, 255, 0));
        matrix.drawBitmap(17, 0, image_Lock_7x8_bits, 7, 8, matrix.Color(0, 255, 255));
        matrix.drawBitmap(9, 0, image_Unlock_7x8_bits, 7, 8, matrix.Color(255, 255, 0));
        matrix.drawBitmap(1, 1, image_Pin_star_7x7_bits, 7, 7, matrix.Color(255, 255, 255));
        matrix.show();
        break;
    case IMAGE_FULL_COLOR:
        matrix.fillScreen(0);
        matrix.drawRGBBitmap(0, 0, rgbBitmap, 3, 2);
        matrix.show();
        break;
    default:
        break;
    }
}