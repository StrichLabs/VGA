/*
  VGA.h - Arduino library for the StrichLabs VGA Shield
  Copyright (c) 2011 Strich Labs.  Licensed under Creative Commons BY-NC-SA.
*/

// ensure this library description is only included once
#ifndef VGA_h
#define VGA_h

#if ARDUINO < 100 // Arduino pre-1.0
// include core Wiring API
#include "WProgram.h"
// include types & constants of Wiring core API
#include "WConstants.h"
#else // Arduino 1.0 or above
#include "Arduino.h"
#endif // ARDUINO < 100

// include the MultiSerial library, which is used to communicate with this shield
#include "MultiSerial.h"

// Control functions
#define CMD_AUTOBAUD    0x55  // void
#define CMD_DISPLAYCTL  0x59  // mode, value
#define CMD_SETPEN      0x70  // size
#define CMD_CHANGESPEED 0x51  // speed
#define CMD_DEVINFO     0x56
#define CMD_SETVOLUME   0x76
#define CMD_SLEEP       0x5A
#define CMD_READGPIO    0x61
#define CMD_WRITEGPIO   0x69
#define CMD_READBUS     0x79
#define CMD_WRITEBUS    0x57

// Drawing functions
#define CMD_CLEARSCREEN 0x45  // void
#define CMD_ADDBITMAP   0x41
#define CMD_DRAWBITMAP  0x44
#define CMD_DRAWCIRCLE  0x43
#define CMD_DRAWTRIANGLE  0x47
#define CMD_DRAWIMGICON 0x49
#define CMD_BACKCOLOUR  0x42
#define CMD_SETBGCOLOUR 0x4B
#define CMD_DRAWPIXEL   0x50  // x msb, x lsb, y msb, y lsb, colour msb, colour lsb
#define CMD_DRAWLINE    0x4C
#define CMD_DRAWPOLYGON 0x67
#define CMD_DRAWRECT    0x72
#define CMD_DRAWELLIPSE 0x65
#define CMD_READPIXEL   0x52
#define CMD_COPYPASTE   0x63
#define CMD_REPLCOLOUR  0x6B

// Text functions
#define CMD_SETFONT     0x46
#define CMD_TEXTTRANS   0x4F
#define CMD_DRAWCHAR    0x54
#define CMD_DRAWCHARPXL 0x74
#define CMD_DRAWTEXT    0x73
#define CMD_DRAWTEXTPXL 0x53
#define CMD_DRAWTEXTBTN 0x62

// FIXME - organize these
#define CMD_EXTENDED    0x40
#define EXTCMD_DISPLAYIMGFROMRAWSD  0x49
#define EXTCMD_PLAYVIDEOFROMRAWSD   0x56

#define EXTCMD_PLAYWAV  0x6C
#define EXTCMD_DISPLAYIMGFROMSD 0x6D

#define CTL_SETIMGFORMAT  0x06  // select old or new image format
#define CTL_SETDISPPG  0x09   // select display page
#define CTL_SETREADPG  0x0A   // select read page
#define CTL_SETWRITEPG 0x0B   // select write page
#define CTL_SETRES     0x0C   // select new screen resolution

#define RES_320x240     0x00
#define RES_640x480     0x01
#define RES_800x480     0x02
#define SPEED_9600      0x06
#define SPEED_128k      0x0E
#define SPEED_256k      0x0F
#define FONT_5x7        0x00
#define FONT_8x8        0x01
#define FONT_8x12       0x02
#define FONT_12x16      0x03
#define FONT_5x7_PROP   0x00 | 0x10
#define FONT_8x8_PROP   0x01 | 0x10
#define FONT_8x12_PROP  0x02 | 0x10
#define FONT_12x16_PROP 0x03 | 0x10
#define BUTTON_DOWN     0x00
#define BUTTON_UP       0x01
#define IMGFMT_NEW      (uint8_t)0x00
#define IMGFMT_OLD      0x01
#define SPRITE_8x8      (uint8_t)0x00
#define SPRITE_16x16    0x01
#define SPRITE_32x32    0x02

typedef short PackedColour;

// library interface description
class VGA {  
  // user-accessible "public" interface
  public:
    VGA(byte);
    void begin();
    void setResolution(byte);
    void setDisplayPage(byte);
    void setReadPage(byte);
    void setWritePage(byte);
    void setBackground(short);
    void fillShapes(byte);
    void clearScreen(void);
    
    void drawPixel(short, short, PackedColour);
    void drawLine(short, short, short, short, PackedColour);
    void drawRectangle(short, short, short, short, PackedColour);
    void drawCircle(short, short, short, PackedColour);
    void drawEllipse(short, short, short, short, PackedColour);
    void drawTriangle(short, short, short, short, short, short, PackedColour);
    void copyArea(short, short, short, short, short, short);
    void replaceColour(short, short, short, short, PackedColour, PackedColour);
    void initSprite(byte, byte[8]);
    void initSprite(byte, short[16]);
    void initSprite(byte, long[32]);
    void initSpriteXbm(byte, byte[128]);
    void drawSprite(byte, byte, short, short, PackedColour);
    
    void setFont(byte);
    void textBackgroundOpaque(byte);
    void drawCharacter(byte, byte, byte, short);
    void drawGraphicsCharacter(byte, short, short, byte, byte, PackedColour);
    void drawText(char *, byte, byte, PackedColour);
    void drawGraphicsText(char *, short, short, byte, byte, PackedColour);
    void drawButton(short, short, byte, byte, byte, PackedColour, char *, PackedColour);
    void playSound(void);
    void displayImageFromSD(char *, long, short, short);
    void displayImageFromRawSD(long, short, short);
    void playVideoFromRawSD(long, short, short, byte);

    PackedColour generateColour(byte, byte, byte);
    void passthruMode(void);
    
  // library-accessible "private" interface
  private:
    MultiSerial msVGA;
    byte addr;
    byte currentFont;
    byte currentPropFont;
    short current_x_res;
    short current_y_res;
    byte vgaWaitForAck(void);
    
};

#endif
