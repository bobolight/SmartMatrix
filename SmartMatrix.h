/*
 * SmartMatrix Library - Main Header File for SmartMatrix Class
 *
 * Copyright (c) 2014 Louis Beaudoin (Pixelmatix)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SmartMatrix_h
#define SmartMatrix_h

#include <stdint.h>

#include "MatrixHardware_KitV1.h"

#include "MatrixCommon.h"

#include "Layer_Foreground.h"
#include "Layer_Background.h"

#define ENABLE_FADECANDY_GAMMA_CORRECTION               1

// color
//#if COLOR_DEPTH_RGB > 24
typedef rgb48 refreshPixel;
//#else
//typedef rgb24 refreshPixel;
//#endif

// definition telling FastLED that setBackBuffer() and getRealBackBuffer() are available
#define SMART_MATRIX_CAN_TRIPLE_BUFFER 1

// enable true triple buffering and interpolation
//#define SMARTMATRIX_TRIPLEBUFFER

typedef struct timerpair {
    uint16_t timer_oe;
    uint16_t timer_period;
} timerpair;

typedef struct addresspair {
    uint16_t bits_to_clear;
    uint16_t bits_to_set;
} addresspair;

typedef struct matrixUpdateBlock {
    timerpair timerValues;
    addresspair addressValues;
} matrixUpdateBlock;

class SmartMatrix {
public:
    SmartMatrix(uint8_t width, uint8_t height, uint8_t depth, uint8_t bufferrows, uint32_t * dataBuffer, uint8_t * blockBuffer);
    void begin(void);

    // drawing functions
    void swapBuffers(bool copy = true);
#ifdef SMARTMATRIX_TRIPLEBUFFER
    void swapBuffersWithInterpolation_frames(int framesToInterpolate, bool copy = false);
    void swapBuffersWithInterpolation_ms(int interpolationSpan_ms, bool copy = false);
#endif
    void drawPixel(int16_t x, int16_t y, const rgb24& color);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, const rgb24& color);
    void drawFastVLine(int16_t x, int16_t y0, int16_t y1, const rgb24& color);
    void drawFastHLine(int16_t x0, int16_t x1, int16_t y, const rgb24& color);
    void drawCircle(int16_t x0, int16_t y0, uint16_t radius, const rgb24& color);
    void fillCircle(int16_t x0, int16_t y0, uint16_t radius, const rgb24& outlineColor, const rgb24& fillColor);
    void fillCircle(int16_t x0, int16_t y0, uint16_t radius, const rgb24& color);
    void drawEllipse(int16_t x0, int16_t y0, uint16_t radiusX, uint16_t radiusY, const rgb24& color);
    void drawTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, const rgb24& color);
    void fillTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, const rgb24& fillColor);
    void fillTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3,
    const rgb24& outlineColor, const rgb24& fillColor);
    void drawRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, const rgb24& color);
    void fillRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, const rgb24& color);
    void fillRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, const rgb24& outlineColor, const rgb24& fillColor);
    void drawRoundRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t radius, const rgb24& outlineColor);
    void fillRoundRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t radius, const rgb24& fillColor);
    void fillRoundRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t radius,
    const rgb24& outlineColor, const rgb24& fillColor);
    void fillScreen(const rgb24& color);
    void drawChar(int16_t x, int16_t y, const rgb24& charColor, char character);
    void drawString(int16_t x, int16_t y, const rgb24& charColor, const char text[]);
    void drawString(int16_t x, int16_t y, const rgb24& charColor, const rgb24& backColor, const char text[]);
    void drawMonoBitmap(int16_t x, int16_t y, uint8_t width, uint8_t height, const rgb24& bitmapColor, const uint8_t *bitmap);
    const rgb24 readPixel(int16_t x, int16_t y);
    rgb24 *backBuffer(void);
    void setBackBuffer(rgb24 *newBuffer);
    rgb24 *getRealBackBuffer(void);

    // scroll text
    void scrollText(const char inputtext[], int numScrolls);
    void setScrollMode(ScrollMode mode);
    void setScrollSpeed(unsigned char pixels_per_second);
    void setScrollFont(fontChoices newFont);
    void setScrollColor(const rgb24 & newColor);
#define setScrollOffsetFromEdge setScrollOffsetFromTop // backwards compatibility
    void setScrollOffsetFromTop(int offset);
    void setScrollStartOffsetFromLeft(int offset);
    void updateScrollText(const char inputtext[]);
    void stopScrollText(void);
    int getScrollStatus(void);

    // foreground drawing
    void clearForeground(void);
    void setForegroundFont(fontChoices newFont);
    void drawForegroundPixel(int16_t x, int16_t y, bool opaque = true);
    void drawForegroundChar(int16_t x, int16_t y, char character, bool opaque = true);
    void drawForegroundString(int16_t x, int16_t y, const char text [], bool opaque = true);
    void drawForegroundMonoBitmap(int16_t x, int16_t y, uint8_t width, uint8_t height, uint8_t *bitmap, bool opaque = true);
    void displayForegroundDrawing(bool waitUntilComplete = true);

    // configuration
    void setRotation(rotationDegrees rotation);
    uint16_t getScreenWidth(void) const;
    uint16_t getScreenHeight(void) const;
    void setBrightness(uint8_t brightness);
    void setBackgroundBrightness(uint8_t brightness);
    void setColorCorrection(colorCorrectionModes mode);
    void setFont(fontChoices newFont);
    void setRefreshRate(uint8_t newRefreshRate);

    SMLayerForeground * foregroundLayer;
    SMLayerBackground * backgroundLayer;

    void useDefaultLayers(void);
    void addLayer(SM_Layer * newlayer);

    SM_Layer * baseLayer;

private:
    // enable ISR access to private member variables
    friend void rowCalculationISR(void);
    friend void rowShiftCompleteISR(void);

    // functions called by ISR
    static void matrixCalculations(void);

    // functions for refreshing
    static void loadMatrixBuffers(unsigned char currentRow);

    // configuration helper functions
    static void calculateTimerLut(void);

    // configuration
    static volatile bool brightnessChange;
    static volatile bool rotationChange;
    static int dimmingFactor;
    static const int dimmingMaximum;
    static rotationDegrees rotation;
    static uint8_t matrixWidth, matrixHeight;
    static uint8_t colorDepthRgb;
    static uint8_t refreshRate;

    static uint8_t latchesPerRow;
    static uint8_t dmaBufferNumRows;
    static uint8_t dmaBufferBytesPerPixel;
    static uint16_t dmaBufferBytesPerRow;

    static uint32_t * matrixUpdateData;
    static matrixUpdateBlock * matrixUpdateBlocks;
    static addresspair * addressLUT;
    static timerpair * timerLUT;
};

// single matrixUpdateBlocks buffer is divided up to hold matrixUpdateBlocks, addressLUT, timerLUT to simplify user sketch code and reduce constructor parameters
#define SMARTMATRIX_ALLOCATE_BUFFERS(width, height, depth, rows) \
static DMAMEM uint32_t matrixUpdateData[rows * width * (depth/3 / sizeof(uint32_t)) * 2]; \
static DMAMEM uint8_t matrixUpdateBlocks[(sizeof(matrixUpdateBlock) * rows * depth/3) + (sizeof(addresspair) * height/2) + (sizeof(timerpair) * depth/3)]; \
SmartMatrix matrix(width, height, depth, rows, matrixUpdateData, matrixUpdateBlocks)

#define SMARTMATRIX_SETUP_DEFAULT_LAYERS(width, height) \
    static rgb24 backgroundBitmap[2*width*height];                              \
    static SMLayerBackground backgroundLayer(backgroundBitmap, width, height);  \
    matrix.addLayer(&backgroundLayer);                                          \
    static uint8_t foregroundBitmap[2 * height * (width / 8)];                  \
    static SMLayerForeground foregroundLayer(foregroundBitmap, width, height);  \
    matrix.addLayer(&foregroundLayer);                                          \
    matrix.useDefaultLayers();                                                  \
    matrix.begin()

#define SMARTMATRIX_ALLOCATE_FOREGROUND_LAYER(layername, width, height) \
    static uint8_t foregroundBitmap[2 * width * (height / 8)];    \
    static SMLayerForeground layername(foregroundBitmap, width, height)

#endif
