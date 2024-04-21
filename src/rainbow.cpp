#include "rainbow.h"

void rainbow(Adafruit_NeoPixel* strip)
{
    // color: rgb(255, 0, 0) ;
    // color: rgb(255, 200, 0) ;
    // color: rgb(0, 255, 0) ;
    // color: rgb(0, 255, 255) ;
    // color: rgb(0, 0, 255) ;
    // color: rgb(255, 0, 255) ;

    for (int i = 0; i < PANEL_WIDTH; i += 1)
    {
        // strip->setPixelColor(ADDRESSES[0][i], 255, 0, 0);
        strip->setPixelColor(ADDRESSES[1][i], 255, 200, 0);
        strip->setPixelColor(ADDRESSES[2][i], 0, 255, 0);
        // strip->setPixelColor(ADDRESSES[3][i], 0, 255, 255);
        strip->setPixelColor(ADDRESSES[4][i], 0, 0, 255);
        // strip->setPixelColor(ADDRESSES[5][i], 255, 0, 255);
    }

    strip->show();
}
