/*
  VGA.cpp - Arduino library for the StrichLabs VGA Shield
  Copyright (c) 2011 Strich Labs.  Licensed under Creative Commons BY-NC-SA.
*/

// include this library's description file
#include "VGA.h"

// include description files for MultiSerial, as this shield is electrically compatible
//#include <MultiSerial.h>

// rev. 1.5 boards use a 23.4MHz crystal
//#define XTAL_HZ 23400000

// rev. 2 boards use a 22.1184MHz crystal
#define XTAL_HZ 22118400

// enabling this outputs profiling data out the usb serial port
//#define PROFILING

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

// Description: Creates a variable of type VGA, to communciate with the VGA Shield.
// Syntax: VGA(address)
// Parameter: address - Address on the I2C bus of the shield to communicate with
// Returns: Instance of VGA associated with a specific VGA Shield.
VGA::VGA(byte shieldAddress) {
  addr = shieldAddress;
  currentFont = 0;
  currentPropFont = 0;
  current_x_res = 320;
  current_y_res = 240;
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries


// Description: Initialize the shield and start communicating with it.
// Syntax: VGAinstance.begin()
// Parameters: none
// Returns: none
void VGA::begin(void) {
  // FIXME: clean up the delays in this routine
  // start talking to the I2C->RS232 chip on the shield
  // this is hardcoded to port 0, because there is only one port :)
  msVGA = MultiSerial(addr, 0);
  msVGA.begin(9600, XTAL_HZ);
  
  // the VGA module wants 500mS dead time before talking to it
  // run the 'autobaud' command which does nothing, but the module needs it anyway...
  delay(500);
  msVGA.write(CMD_AUTOBAUD);
  vgaWaitForAck();
  
  // TODO: is dead time needed after the autobaud?
  delay(500);

  // switch to a reasonable baud rate
  msVGA.write(CMD_CHANGESPEED);
  msVGA.write(SPEED_256k);
  delay(1000);
  msVGA.begin(282353, 23400000);
  
  // change to 'new format' images, no need to support 'old format' at all
  msVGA.write(CMD_DISPLAYCTL);
  msVGA.write(CTL_SETIMGFORMAT);
  msVGA.write(IMGFMT_NEW);
  vgaWaitForAck();
}

// Description: Clear the screen.
// Syntax: VGAInstance.clearScreen()
// Parameter: none
// Returns: none
void VGA::clearScreen(void) {
  msVGA.write(CMD_CLEARSCREEN);
  vgaWaitForAck();
}

// Description: Set the current screen resolution.
// Syntax: VGAInstance.setResolution(resolution)
// Parameter: resolution - One of RES_320x240, RES_640x480, or RES_800x480
// Returns: none
void VGA::setResolution(byte resolution) {
  msVGA.write(CMD_DISPLAYCTL);
  msVGA.write(CTL_SETRES);
  msVGA.write(resolution);
  vgaWaitForAck();
  // FIXME: see if we can use the 'get version info' call to get the new res
  switch(resolution) {
    case RES_320x240:
      current_x_res = 320;
      current_y_res = 240;
      break;
    case RES_640x480:
      current_x_res = 640;
      current_y_res = 480;
      break;
    case RES_800x480:
      current_x_res = 800;
      current_y_res = 480;
      break;
  }
}

// Description: Set which memory page is currently being displayed.
// Syntax: VGAInstance.setDisplayPage(page)
// Parameter: page - Page number to display
// Returns: none
void VGA::setDisplayPage(byte page) {
  msVGA.write(CMD_DISPLAYCTL);
  msVGA.write(CTL_SETDISPPG);
  msVGA.write(page);
  vgaWaitForAck();
}

// Description: Set which memory page is used for read operations.
// Syntax: VGAInstance.setReadPage(page)
// Parameter: page - Page number to use for read operations
// Returns: none
void VGA::setReadPage(byte page) {
  msVGA.write(CMD_DISPLAYCTL);
  msVGA.write(CTL_SETREADPG);
  msVGA.write(page);
  vgaWaitForAck();
}

// Description: Set which memory page is used for write operations.
// Syntax: VGAInstance.setWritePage(page)
// Parameter: page - Page number to use for write operations
// Returns: none
void VGA::setWritePage(byte page) {
  msVGA.write(CMD_DISPLAYCTL);
  msVGA.write(CTL_SETWRITEPG);
  msVGA.write(page);
  vgaWaitForAck();
}

// Description: Set the background colour used for drawing opaque text.
// Syntax: VGAInstance.setBackground(colour)
// Parameter: colour - Colour to use for background when drawing opaque text.
// Returns: none
void VGA::setBackground(PackedColour colour) {
  msVGA.write(CMD_SETBGCOLOUR);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  vgaWaitForAck();
}

// Description: Set whether any shapes drawn are filled or outlined.  Affects only newly drawn shapes, existing shapes are not changed.
// Syntax: VGAInstance.fillShapes(fill)
// Parameter: fill - 0 to draw outlined shapes, 1 to draw filled shapes
// Returns: none
void VGA::fillShapes(byte fill) {
  msVGA.write(CMD_SETPEN);
  msVGA.write((fill ? 0 : 1));
  vgaWaitForAck();
}

// Description: Copy one rectangular area of the screen onto another area.
// Syntax: VGAInstance.copyArea(xSrc, ySrc, xDest, yDest, width, height)
// Parameter: xSrc - Horizontal pixel position for the top of the source area
// Parameter: ySrc - Vertical pixel position for the left side of the source area
// Parameter: xDest - Horizontal pixel position for the top of the destination area
// Parameter: yDest - Vertical pixel position for the left side of the destination area
// Parameter: width - Width of the area to copy, in pixels
// Parameter: height - Height of the area to copy, in pixels
// Returns: none
void VGA::copyArea(short xSrc, short ySrc, short xDest, short yDest, short width, short height) {
  // copying zero width or zero height areas causes weird issues, don't allow it
  if(width == 0 || height == 0) return;
  
  // clip at the edges of the screen if the src/dest would go offscreen
  if(xSrc  + width  > current_x_res) width  = current_x_res - xSrc;
  if(ySrc  + height > current_y_res) height = current_y_res - ySrc;
  if(xDest + width  > current_x_res) width  = current_x_res - xDest;
  if(yDest + height > current_y_res) height = current_y_res - yDest;
  
  msVGA.write(CMD_COPYPASTE);
  msVGA.write(xSrc >> 8);
  msVGA.write(xSrc & 0xFF);
  msVGA.write(ySrc >> 8);
  msVGA.write(ySrc & 0xFF);
  msVGA.write(xDest >> 8);
  msVGA.write(xDest & 0xFF);
  msVGA.write(yDest >> 8);
  msVGA.write(yDest & 0xFF);
  msVGA.write(width >> 8);
  msVGA.write(width & 0xFF);
  msVGA.write(height >> 8);
  msVGA.write(height & 0xFF);
  vgaWaitForAck();
}

// Description: Draw a single pixel.
// Syntax: VGAInstance.drawPixel(x1, y1, x2, y2, colour)
// Parameter: x - Horizontal pixel position for the pixel
// Parameter: y - Vertical pixel position for the pixel
// Parameter: colour - Colour to draw the pixel in
// Returns: none
void VGA::drawPixel(short x, short y, PackedColour colour) {
  #ifdef PROFILING
    long startTime = millis();
  #endif
  
  /*
  // prototype code, to be worked in later. saves about 1mS per pixel
  byte cmd[7];
  cmd[0] = CMD_DRAWPIXEL;
  cmd[1] = x >> 8;
  cmd[2] = x & 0xFF;
  cmd[3] = y >> 8;
  cmd[4] = y & 0xFF;
  cmd[5] = colour >> 8;
  cmd[6] = colour & 0xFF;
  msVGA.write(cmd, 7);
  */
  
  msVGA.write(CMD_DRAWPIXEL);
  msVGA.write(x >> 8);
  msVGA.write(x & 0xFF);
  msVGA.write(y >> 8);
  msVGA.write(y & 0xFF);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  vgaWaitForAck();
  #ifdef PROFILING
    Serial.print("drawPixel took ");
    Serial.print(millis()-startTime, DEC);
    Serial.println("mS");
  #endif
}

// Description: Draw a line.
// Syntax: VGAInstance.drawLine(x1, y1, x2, y2, colour)
// Parameter: x1 - Horizontal pixel position for the start of the line
// Parameter: y1 - Vertical pixel position for the start of the line
// Parameter: x2 - Horizontal pixel position for the start of the line
// Parameter: y2 - Vertical pixel position for the start of the line
// Parameter: colour - Colour to draw the line in
// Returns: none
void VGA::drawLine(short x1, short y1, short x2, short y2, PackedColour colour) {
  msVGA.write(CMD_DRAWLINE);
  msVGA.write(x1 >> 8);
  msVGA.write(x1 & 0xFF);
  msVGA.write(y1 >> 8);
  msVGA.write(y1 & 0xFF);
  msVGA.write(x2 >> 8);
  msVGA.write(x2 & 0xFF);
  msVGA.write(y2 >> 8);
  msVGA.write(y2 & 0xFF);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  vgaWaitForAck();
}

// Description: Draw a rectangle.
// Syntax: VGAInstance.drawLine(x1, y1, x2, y2, colour)
// Parameter: x1 - Horizontal pixel position for the left side of the rectangle
// Parameter: y1 - Vertical pixel position for the top of the rectangle
// Parameter: x2 - Horizontal pixel position for the right side of the rectangle
// Parameter: y2 - Vertical pixel position for the bottom of the rectangle
// Parameter: colour - Colour to draw the rectangle in
// Returns: none
void VGA::drawRectangle(short x1, short y1, short x2, short y2, PackedColour colour) {
  msVGA.write(CMD_DRAWRECT);
  msVGA.write(x1 >> 8);
  msVGA.write(x1 & 0xFF);
  msVGA.write(y1 >> 8);
  msVGA.write(y1 & 0xFF);
  msVGA.write(x2 >> 8);
  msVGA.write(x2 & 0xFF);
  msVGA.write(y2 >> 8);
  msVGA.write(y2 & 0xFF);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  vgaWaitForAck();
}

// Description: Draw a circle.
// Syntax: VGAInstance.drawCircle(x, y, radius, colour)
// Parameter: x - Horizontal pixel position for the center of the circle
// Parameter: y - Vertical pixel position for the center of the circle
// Parameter: radius - Radius of the circle in pixels
// Parameter: colour - Colour to draw the circle in
// Returns: none
void VGA::drawCircle(short x, short y, short radius, PackedColour colour) {
  msVGA.write(CMD_DRAWCIRCLE);
  msVGA.write(x >> 8);
  msVGA.write(x & 0xFF);
  msVGA.write(y >> 8);
  msVGA.write(y & 0xFF);
  msVGA.write(radius >> 8);
  msVGA.write(radius & 0xFF);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  vgaWaitForAck();
}

// Description: Draw an ellipse/oval.
// Syntax: VGAInstance.drawEllipse(x, y, radiusX, radiusY, colour)
// Parameter: x - Horizontal pixel position for the center of the circle
// Parameter: y - Vertical pixel position for the center of the circle
// Parameter: radiusX - Horizontal radius of the circle in pixels
// Parameter: radiusY - Vertical radius of the circle in pixels
// Parameter: colour - Colour to draw the ellipse in
// Returns: none
void VGA::drawEllipse(short x, short y, short radiusX, short radiusY, PackedColour colour) {
  msVGA.write(CMD_DRAWELLIPSE);
  msVGA.write(x >> 8);
  msVGA.write(x & 0xFF);
  msVGA.write(y >> 8);
  msVGA.write(y & 0xFF);
  msVGA.write(radiusX >> 8);
  msVGA.write(radiusX & 0xFF);
  msVGA.write(radiusY >> 8);
  msVGA.write(radiusY & 0xFF);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  vgaWaitForAck();
}

// NOTE: This function doesn't work for large filled triangles, this is a 4D issue.
//       They will fix this in the next firmware revision of the module.
void VGA::drawTriangle(short x1, short y1, short x2, short y2, short x3, short y3, PackedColour colour) {
  // this makes it easier to debug
  //colour = generateColour(255, 255, 255);
  /*
  // the hardware doesn't clip, and acts very oddly if you go off the screen.
  if(x1 > current_x_res) x1 = current_x_res;
  if(y1 > current_y_res) y1 = current_y_res;
  if(x2 > current_x_res) x2 = current_x_res;
  if(y2 > current_y_res) y2 = current_y_res;
  if(x3 > current_x_res) x3 = current_x_res;
  if(y3 > current_y_res) y3 = current_y_res;
  
  if(x2 >= x1) {
    Serial.println("Violated triangle rule 1!");
    return;
  }
  if(x3 <= x2) {
    Serial.println("Violated triangle rule 2!");
    return;
  }
  if(y2 <= y1) {
    Serial.println("Violated triangle rule 3!");
    return;
  }
  if(y3 <= y1) {
    Serial.println("Violated triangle rule 4!");
    return;
  }
  
  
  Serial.println("");
  Serial.println("");
  Serial.print("cmd: 0x");
  Serial.println(CMD_DRAWTRIANGLE, HEX);
  
  Serial.print("x1(msb): 0x");
  Serial.println(x1 >> 8, HEX);
  Serial.print("x1(lsb): 0x");
  Serial.println(x1 & 0xFF, HEX);
  
  Serial.print("y1(msb): 0x");
  Serial.println(y1 >> 8, HEX);
  Serial.print("y1(lsb): 0x");
  Serial.println(y1 & 0xFF, HEX);
  
  Serial.print("x2(msb): 0x");
  Serial.println(x2 >> 8, HEX);
  Serial.print("x2(lsb): 0x");
  Serial.println(x2 & 0xFF, HEX);
  
  Serial.print("y2(msb): 0x");
  Serial.println(y2 >> 8, HEX);
  Serial.print("y2(lsb): 0x");
  Serial.println(y2 & 0xFF, HEX);
  
  Serial.print("x3(msb): 0x");
  Serial.println(x3 >> 8, HEX);
  Serial.print("x3(lsb): 0x");
  Serial.println(x3 & 0xFF, HEX);
  
  Serial.print("y3(msb): 0x");
  Serial.println(y3 >> 8, HEX);
  Serial.print("y3(lsb): 0x");
  Serial.println(y3 & 0xFF, HEX);
  
  Serial.print("colour(msb): 0x");
  Serial.println(colour >> 8, HEX);
  Serial.print("colour(lsb): 0x");
  Serial.println(colour & 0xFF, HEX);

  Serial.print("Return value: 0x");
*/
  msVGA.write(CMD_DRAWTRIANGLE);
  msVGA.write(x1 >> 8);
  msVGA.write(x1 & 0xFF);
  msVGA.write(y1 >> 8);
  msVGA.write(y1 & 0xFF);
  msVGA.write(x2 >> 8);
  msVGA.write(x2 & 0xFF);
  msVGA.write(y2 >> 8);
  msVGA.write(y2 & 0xFF);
  msVGA.write(x3 >> 8);
  msVGA.write(x3 & 0xFF);
  msVGA.write(y3 >> 8);
  msVGA.write(y3 & 0xFF);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  vgaWaitForAck();
/*  
  drawRectangle(x1-5, y1-5, x1+5, y1+5, generateColour(255, 0, 0));
  drawRectangle(x2-5, y2-5, x2+5, y2+5, generateColour(0, 255, 0));
  drawRectangle(x3-5, y3-5, x3+5, y3+5, generateColour(0, 0, 255));
  delay(5000);
  while(1) {};
*/
}

// Description: Replace one colour with another in a certain rectangular area.
// Syntax: VGAInstance.replaceColour(x1, y1, x2, y2, oldColour, newColour)
// Parameter: x1 - Horizontal pixel position for the left side of the area
// Parameter: y1 - Vertical pixel position for the top of the area
// Parameter: x2 - Horizontal pixel position for the right side of the area
// Parameter: y2 - Vertical pixel position for the bottom of the area
// Parameter: oldColour - Colour to be replaced
// Parameter: newColour - Colour to replace with
// Returns: none
void VGA::replaceColour(short x1, short y1, short x2, short y2, PackedColour oldColour, PackedColour newColour) {
  msVGA.write(CMD_REPLCOLOUR);
  msVGA.write(x1 >> 8);
  msVGA.write(x1 & 0xFF);
  msVGA.write(y1 >> 8);
  msVGA.write(y1 & 0xFF);
  msVGA.write(x2 >> 8);
  msVGA.write(x2 & 0xFF);
  msVGA.write(y2 >> 8);
  msVGA.write(y2 & 0xFF);
  msVGA.write(oldColour >> 8);
  msVGA.write(oldColour & 0xFF);
  msVGA.write(newColour >> 8);
  msVGA.write(newColour & 0xFF);
  vgaWaitForAck();
}

// Description: Set the current font to use when drawing characters or text.
// Syntax: VGAInstance.setFont(font)
// Parameter: font - Font name (one of the following monospace fonts: FONT_5x7, FONT_8x8, FONT_8x12, FONT_12x16, or one of the following proportional fonts: FONT_5x7_PROP, FONT_8x8_PROP, FONT_8x12_PROP, FONT_12x16_PROP)
// Returns: none
void VGA::setFont(byte font) {
  msVGA.write(CMD_SETFONT);
  msVGA.write(font);
  vgaWaitForAck();
  // this one's used for methods that do support proportional fonts
  currentPropFont = font;
  // this is used for methods that don't support proportional fonts
  currentFont = font & ~0x10;
}

// Description: Set whether text is drawn with a transparent or opaque background.
// Syntax: VGAInstance.textBackgroundOpaque(opaque)
// Parameter: opaque - 0 to draw text with a transparent background, 1 to draw with an opaque background
// Returns: none
void VGA::textBackgroundOpaque(byte opaque) {
  msVGA.write(CMD_TEXTTRANS);
  msVGA.write(opaque);
  vgaWaitForAck();
}

// Description: Initialize an 8x8 pixel sprite, storing the data on the shield for later drawing.
// Syntax: VGAInstance.initSprite(id, sprite)
// Parameter: id - Sprite ID to initialize
// Parameter: sprite - Sprite data, as 8 8-bit bytes where each byte is one horizontal line of the sprite
// Returns: none
void VGA::initSprite(byte id, byte sprite[8]) {
  msVGA.write(CMD_ADDBITMAP);
  msVGA.write(SPRITE_8x8);
  msVGA.write(id);
  byte i;
  for(i=0; i<8; i++) {
    msVGA.write(sprite[i]);
  }
  vgaWaitForAck();
}

// Description: Initialize a 16x16 pixel sprite, storing the data on the shield for later drawing.
// Syntax: VGAInstance.initSprite(id, sprite)
// Parameter: id - Sprite ID to initialize
// Parameter: sprite - Sprite data, as 16 16-bit shorts where each short is one horizontal line of the sprite
// Returns: none
void VGA::initSprite(byte id, short sprite[16]) {
  msVGA.write(CMD_ADDBITMAP);
  msVGA.write(SPRITE_16x16);
  msVGA.write(id);
  byte i;
  for(i=0; i<16; i++) {
    msVGA.write(sprite[i] >> 8);
    msVGA.write(sprite[i] & 0xFF);
  }
  vgaWaitForAck();
}

// Description: Initialize a 32x32 pixel sprite, storing the data on the shield for later drawing.
// Syntax: VGAInstance.initSprite(id, sprite)
// Parameter: id - Sprite ID to initialize
// Parameter: sprite - Sprite data, as 32 32-bit longs where each long is one horizontal line of the sprite
// Returns: none
void VGA::initSprite(byte id, long sprite[32]) {
  msVGA.write(CMD_ADDBITMAP);
  msVGA.write(SPRITE_32x32);
  msVGA.write(id);
  byte i;
  for(i=0; i<32; i++) {
    msVGA.write(sprite[i] >> 24);
    msVGA.write(sprite[i] >> 16);
    msVGA.write(sprite[i] >> 8);
    msVGA.write(sprite[i] & 0xFF);
  }
  vgaWaitForAck();
}

// Description: Initialize a 32x32 pixel sprite with X Bitmap (XBM) data, storing the data on the shield for later drawing.
// Syntax: VGAInstance.initSpriteXbm(id, xbmdata)
// Parameter: id - Sprite ID to initialize
// Parameter: xbmdata - Sprite data, as XBM formatted data
// Returns: none
void VGA::initSpriteXbm(byte id, byte xbmdata[128]) {
  msVGA.write(CMD_ADDBITMAP);
  msVGA.write(SPRITE_32x32);
  msVGA.write(id);
  byte i;
  for(i=0; i<128; i+=4) {
    msVGA.write(xbmdata[i+3]);
    msVGA.write(xbmdata[i+2]);
    msVGA.write(xbmdata[i+1]);
    msVGA.write(xbmdata[i]);
  }
  vgaWaitForAck();  
}

// Description: Draw a previously-initialized sprite at a given location in a given colour.
// Syntax: VGAInstance.drawSprite(type, id, x, y, colour)
// Parameter: type - Type of sprite, either SPRITE_8x8, SPRITE_16x16, or SPRITE_32x32
// Parameter: id - Sprite ID to draw
// Parameter: x - Horizontal position at which to draw the upper left corner of the sprite
// Parameter: y - Vertical position at which to draw the upper left corner of the sprite
// Returns: none
void VGA::drawSprite(byte type, byte id, short x, short y, PackedColour colour) {
  msVGA.write(CMD_DRAWBITMAP);
  msVGA.write((uint8_t)type);
  msVGA.write((uint8_t)0);
  msVGA.write(x >> 8);
  msVGA.write(x & 0xFF);
  msVGA.write(y >> 8);
  msVGA.write(y & 0xFF);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  vgaWaitForAck();
}

// Description: Draw one character of text at a given text grid location using the previously set font.
// Syntax: VGAInstance.drawCharacter(chr, x, y, colour)
// Parameter: chr - Character to draw (normal ASCII values)
// Parameter: x - Horizontal grid position at which to draw the character
// Parameter: y - Vertical grid position at which to draw the character
// Parameter: colour - Colour to draw the character in
// Returns: none
void VGA::drawCharacter(byte chr, byte x, byte y, PackedColour colour) {
  msVGA.write(CMD_DRAWCHAR);
  msVGA.write(chr);
  msVGA.write(x);
  msVGA.write(y);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  vgaWaitForAck();
}

// Description: Draw one character of text at a given pixel location.
// Syntax: VGAInstance.drawGraphicsCharacter(chr, x, y, colour)
// Parameter: chr - Character to draw (normal ASCII values)
// Parameter: x - Horizontal pixel position at which to draw the character
// Parameter: y - Vertical pixel position at which to draw the character
// Parameter: width - Width of the character (stretches if it doesn't match the font size)
// Parameter: height - Height of the character (stretches if it doesn't match the font size)
// Parameter: colour - Colour to draw the character in
// Returns: none
void VGA::drawGraphicsCharacter(byte chr, short x, short y, byte width, byte height, PackedColour colour) {
  // TODO: Add support for zero width/height meaning 'use actual font size'
  msVGA.write(CMD_DRAWCHARPXL);
  msVGA.write(chr);
  msVGA.write(x >> 8);
  msVGA.write(x & 0xFF);
  msVGA.write(y >> 8);
  msVGA.write(y & 0xFF);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  msVGA.write(width);
  msVGA.write(height);
  vgaWaitForAck();
}

// Description: Draw a text string at a given text grid location.
// Syntax: VGAInstance.drawText(text, x, y, colour)
// Parameter: text - Pointer to string of text to draw
// Parameter: x - Horizontal text grid position at which to draw the text
// Parameter: y - Vertical text grid position at which to draw the text
// Parameter: colour - Colour to draw the text in
// Returns: none
void VGA::drawText(char *text, byte x, byte y, PackedColour colour) {
  msVGA.write(CMD_DRAWTEXT);
  msVGA.write(x);
  msVGA.write(y);
  msVGA.write(currentPropFont);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  msVGA.print(text);
  msVGA.write((uint8_t)0x00);
  vgaWaitForAck();
}

// Description: Draw a text string at a given pixel location.
// Syntax: VGAInstance.drawGraphicsText(text, x, y, colour)
// Parameter: text - Pointer to string of text to draw
// Parameter: x - Horizontal pixel position at which to draw the text
// Parameter: y - Vertical pixel position at which to draw the text
// Parameter: colour - Colour to draw the text in
// Returns: none
void VGA::drawGraphicsText(char *text, short x, short y, byte width, byte height, PackedColour colour) {
  msVGA.write(CMD_DRAWTEXTPXL);
  msVGA.write(x >> 8);
  msVGA.write(x & 0xFF);
  msVGA.write(y >> 8);
  msVGA.write(y & 0xFF);
  msVGA.write(currentPropFont);
  msVGA.write(colour >> 8);
  msVGA.write(colour & 0xFF);
  msVGA.write(width);
  msVGA.write(height);
  msVGA.print(text);
  msVGA.write((uint8_t)0x00);
  vgaWaitForAck();
}

// FIXME: this routine needs to be tested
void VGA::drawButton(short x, short y, byte width, byte height, byte btnState, PackedColour btnColour, char *text, PackedColour txtColour) {
  msVGA.write(CMD_DRAWTEXTBTN);
  msVGA.write(btnState);
  msVGA.write(x >> 8);
  msVGA.write(x & 0xFF);
  msVGA.write(y >> 8);
  msVGA.write(y & 0xFF);
  msVGA.write(btnColour >> 8);
  msVGA.write(btnColour & 0xFF);
  msVGA.write(currentPropFont);
  msVGA.write(txtColour >> 8);
  msVGA.write(txtColour & 0xFF);
  msVGA.write(width);
  msVGA.write(height);
  msVGA.print(text);
  msVGA.write((uint8_t)0x00);
  vgaWaitForAck();
}

void VGA::playSound(void) {
  // FIXME: None of this works properly, question posed to 4D about why, awaiting response.
  delay(1000);
  msVGA.flush();
  
  /*
  msVGA.write(0x40);
  msVGA.write(0x64);
  msVGA.print("TEST.WAV");
  msVGA.write((uint8_t)0x00);
  
  while(1) {
    if(msVGA.available()) {
       Serial.println(msVGA.read(), BYTE);
    }
  }
  */
  
  msVGA.write(0x40);
  msVGA.write(0x69);
  Serial.print("SDINIT: ");
  Serial.println(vgaWaitForAck(), DEC);
  
  msVGA.write(0x76);
  msVGA.write(0xFF);
  Serial.print("MUTE: ");
  Serial.println(vgaWaitForAck(), DEC);
  
  msVGA.write(0x76);
  msVGA.write(0x7F);
  Serial.print("VOL: ");
  Serial.println(vgaWaitForAck(), DEC);
  
  msVGA.write(CMD_EXTENDED);
  msVGA.write(EXTCMD_PLAYWAV);
  msVGA.write((uint8_t)0x00);
  msVGA.print("TEST.WAV");
  msVGA.write((uint8_t)0x00);
  Serial.print("SND: ");
  Serial.println(vgaWaitForAck(), DEC);
}

// Description: Display an image stored on a raw (non-FAT) SD card.  This image needs to be stored using 4D Systems Graphics Composer.
// Syntax: VGAInstance.displayImageFromRawSD(offset, x, y)
// Parameter: offset - Offset into the SD card at which the image is stored
// Parameter: x - Horizontal pixel position at which to draw the left side of the image
// Parameter: y - Vertical pixel position at which to draw the top of the image
// Returns: none
void VGA::displayImageFromRawSD(long offset, short x, short y) {
  msVGA.write(CMD_EXTENDED);
  msVGA.write(EXTCMD_DISPLAYIMGFROMRAWSD);
  msVGA.write(x >> 8);
  msVGA.write(x & 0xFF);
  msVGA.write(y >> 8);
  msVGA.write(y & 0xFF);
  msVGA.write(offset >> 16);
  msVGA.write(offset >> 8);
  msVGA.write(offset & 0xFF);
  vgaWaitForAck();
}

// Description: Display a video clip stored on a raw (non-FAT) SD card.  This video needs to be stored using 4D Systems Graphics Composer.
// Syntax: VGAInstance.playVideoFromRawSD(offset, x, y, ifd)
// Parameter: offset - Offset into the SD card at which the video is stored
// Parameter: x - Horizontal pixel position at which to place the left side of the video
// Parameter: y - Vertical pixel position at which to place the top of the video
// Parameter: ifd - Inter-frame delay, in milliseconds
// Returns: none
void VGA::playVideoFromRawSD(long offset, short x, short y, byte ifd) {
  msVGA.write(CMD_EXTENDED);
  msVGA.write(EXTCMD_PLAYVIDEOFROMRAWSD);
  msVGA.write(x >> 8);
  msVGA.write(x & 0xFF);
  msVGA.write(y >> 8);
  msVGA.write(y & 0xFF);
  msVGA.write(ifd);
  msVGA.write(offset >> 16);
  msVGA.write(offset >> 8);
  msVGA.write(offset & 0xFF);
  vgaWaitForAck();
}

// Description: Display an image from a GCI file stored on a microSD card.  GCI files can be created using 4D Systems Graphics Composer.
// Syntax: VGAInstance.displayImageFromSD(filename, offset, x, y)
// Parameter: filename - File name of the GCI file to pull images from
// Parameter: offset - Offset in the GCI file of the image to display
// Parameter: x - Horizontal pixel position for the left side of the image
// Parameter: y - Vertical pixel position for the top of the image
// Returns: none
void VGA::displayImageFromSD(char *filename, long offset, short x, short y) {
  msVGA.write(CMD_EXTENDED);
  msVGA.write(EXTCMD_DISPLAYIMGFROMSD);
  msVGA.write(filename);
  msVGA.write((uint8_t)0);
  msVGA.write(x >> 8);
  msVGA.write(x & 0xFF);
  msVGA.write(y >> 8);
  msVGA.write(y & 0xFF);
  msVGA.write(offset >> 24);
  msVGA.write(offset >> 16);
  msVGA.write(offset >> 8);
  msVGA.write(offset & 0xFF);
  vgaWaitForAck();
}

// Description: Generate a PackedColour from red/green/blue values, which can then be passed to all functions that require colour specification.
// Syntax: VGAInstance.generateColour(r, g, b)
// Parameter: r - Red value, from 0 to 255
// Parameter: g - Green value, from 0 to 255
// Parameter: b - Blue value, from 0 to 255
// Returns: none
PackedColour VGA::generateColour(byte r, byte g, byte b) {
  // rescale red from 0-255 to 0-31 (5 bits)
  short scaledR = ((r * 31) / 255);
	// rescale green from 0-255 to 0-63 (6 bits)
  short scaledG = ((g * 63) / 255);
  // rescale blue from 0-255 to 0-31 (5 bits)
	short scaledB = ((b * 31) / 255);

  // glue all the rescaled values together into one PackedColour short
	return (scaledR << 11) | (scaledG << 5) | scaledB;
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions available only within this library.

byte VGA::vgaWaitForAck(void) {
  while(!msVGA.available()) {
    //Serial.println("Waiting for ACK...");
    delay(50);
  }
  return msVGA.read();
}

