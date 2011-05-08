#include <Wire.h>
#include <MultiSerial.h>
#include <VGA.h>

#define RES_X  640
#define RES_Y  480

#define WHITE          vgaShield.generateColour(0xFF, 0xFF, 0xFF)
#define RED            vgaShield.generateColour(0xFF, 0x00, 0x00)
#define GREEN          vgaShield.generateColour(0x00, 0xFF, 0x00)
#define BLUE           vgaShield.generateColour(0x00, 0x00, 0xFF)
#define BLACK          vgaShield.generateColour(0x00, 0x00, 0x00)
#define GRAY           vgaShield.generateColour(0x80, 0x80, 0x80)
#define GREY           GRAY
#define RANDOM_COLOUR  vgaShield.generateColour(random(0, 255), random(0, 255), random(0, 255))
#define RANDOM_BRIGHT_COLOUR  vgaShield.generateColour(random(100, 255), random(100, 255), random(100, 255))
#define RANDOM_DARK_COLOUR    vgaShield.generateColour(random(0, 128), random(0, 128), random(0, 128))
#define RANDOM_SIMPLE_COLOUR vgaShield.generateColour(random(0, 2) * 255, random(0, 2) * 255, random(0, 2) * 255)

VGA vgaShield = VGA(0x4D);

void setup(void) {
  Serial.begin(9600);
  
  vgaShield.begin();

  vgaShield.setResolution(RES_640x480);
  vgaShield.textBackgroundOpaque(1);  
  vgaShield.fillShapes(0);
  vgaShield.setFont(FONT_12x16);
  vgaShield.clearScreen();
  
  /*
  byte i;
  for(i=0; i<0xFF; i++) {
    vgaShield.drawLine(i, 0, i, 100, vgaShield.generateColour(i, 0, 0));
  }
  for(i=0; i<0xFF; i++) {
    vgaShield.drawLine(i, 150, i, 250, vgaShield.generateColour(0, i, 0));
  }
  for(i=0; i<0xFF; i++) {
    vgaShield.drawLine(i, 300, i, 400, vgaShield.generateColour(0, 0, i));
  }
  while(1) {}
  */
}

void loop(void) {
  pixelDemo();
  delay(5000);
  vgaShield.clearScreen();
  
  circleDemo();
  delay(5000);
  vgaShield.clearScreen();
  
  ellipseDemo();
  delay(5000);
  vgaShield.clearScreen();
  
  rectDemo();
  delay(5000);
  vgaShield.clearScreen();
  
  lineDemo();
  delay(5000);
  vgaShield.clearScreen();
  
  triangleDemo();
  delay(5000);
  vgaShield.clearScreen();
  
  vgaShield.setFont(FONT_8x12);
  copyPasteDemo();
  delay(5000);
  vgaShield.clearScreen();
  vgaShield.setFont(FONT_12x16);
  
  colourReplaceDemo();
  delay(5000);
  vgaShield.clearScreen();
  
  textDemo();
  delay(5000);
  vgaShield.clearScreen();
  
  imageVideoDemo();
  delay(5000);
  vgaShield.clearScreen();
}

void statusUpdate(char *text) {
  vgaShield.drawText(text, 1, 1, WHITE);
}

void pixelDemo(void) {
  short x, y;
  
  statusUpdate("VGA Shield Demo 1: Pixel Drawing");
  
  for(y = 0; y < RES_Y; y += RES_Y/15) {
    for(x = 0; x < RES_X; x += RES_X/15) {
      vgaShield.drawPixel(x, y, RANDOM_BRIGHT_COLOUR);
    }
  }

}

void circleDemo(void) {
  short x, y;
  boolean filled = false;
  
  statusUpdate("VGA Shield Demo 2: Circle Drawing");
  
  byte radius = RES_X / 10 / 2;
  for(y = radius; y < RES_Y; y += RES_Y/10/2*2) {
    vgaShield.fillShapes(filled);
    filled = !filled;
    for(x = radius; x < RES_X; x += radius * 2) {
      vgaShield.drawCircle(x, y, radius, RANDOM_BRIGHT_COLOUR);
    }
  }
}

void ellipseDemo(void) {
  short x, y;
  boolean filled = false;
  
  statusUpdate("VGA Shield Demo 3: Ellipse Drawing");
  
  byte radiusX = RES_X / 10 / 2;
  byte radiusY = RES_Y / 10 / 2;  
  for(y = radiusY; y < RES_Y; y += radiusY * 2) {
    vgaShield.fillShapes(filled);
    filled = !filled;
    for(x = radiusX; x < RES_X; x += radiusX * 2) {
      vgaShield.drawEllipse(x, y, radiusX, radiusY, RANDOM_BRIGHT_COLOUR);
    }
  }
}

void rectDemo(void) {
  short x, y;
  boolean filled = false;
  
  statusUpdate("VGA Shield Demo 4: Rectangle Drawing");
  
  byte sizeX = RES_X / 10 / 2;
  byte sizeY = RES_Y / 10 / 2;
  for(y = sizeY; y < RES_Y; y += sizeY * 2) {
    vgaShield.fillShapes(filled);
    filled = !filled;
    for(x = sizeX; x < RES_X; x += sizeX * 2) {
      vgaShield.drawRectangle(x-sizeX+5, y-sizeY+5, x+sizeX-5, y+sizeY-5, RANDOM_BRIGHT_COLOUR);
    }
  }
}

void lineDemo(void) {
  short x, y;
  
  statusUpdate("VGA Shield Demo 5: Line Drawing");
  
  byte spacingX = RES_X / 20 / 2;
  byte spacingY = RES_Y / 20 / 2;
  for(x = spacingX; x < RES_X; x += spacingX * 2) {
    vgaShield.drawLine(x, 0, x, RES_Y, RANDOM_BRIGHT_COLOUR);
  }
  for(y = spacingY; y < RES_Y; y += spacingY * 2) {
    vgaShield.drawLine(0, y, RES_X, y, RANDOM_BRIGHT_COLOUR);
  }
}

void triangleDemo(void) {
  short x, y;
  boolean filled = false;
  
  statusUpdate("VGA Shield Demo 6: Triangle Drawing");
  
  byte spacingX = RES_X / 14 / 2;
  byte spacingY = RES_Y / 7 / 2;
  for(y = spacingY; y < RES_Y; y += spacingY * 2) {
    vgaShield.fillShapes(filled);
    filled = !filled;
    for(x = spacingX; x < RES_X; x += spacingX * 2) {
      vgaShield.drawTriangle(x, y, x-spacingX+2, y+spacingY, x+spacingX-2, y+spacingY, RANDOM_BRIGHT_COLOUR);
    }
  }
}

void copyPasteDemo(void) {
  short x, y;
  boolean filled = false;
  
  statusUpdate("VGA Shield Demo 7: Screen Area Copy");
  
  byte sizeX = RES_X / 10 / 2;
  byte sizeY = RES_Y / 10 / 2;
  for(y = sizeY; y < RES_Y/2; y += sizeY * 2) {
    vgaShield.fillShapes(filled);
    filled = !filled;
    for(x = sizeX; x < RES_X/2; x += sizeX * 2) {
      vgaShield.drawRectangle(x-sizeX+5, y-sizeY+5, x+sizeX-5, y+sizeY-5, RANDOM_BRIGHT_COLOUR);
    }
  }
  
  vgaShield.copyArea(0, 0, RES_X/2, 0, RES_X/2, RES_Y/2);
  vgaShield.copyArea(0, 0, 0, RES_Y/2, RES_X, RES_Y/2);
}

void colourReplaceDemo(void) { 
  short x, y;
  boolean filled = false;
  
  statusUpdate("VGA Shield Demo 8: Colour Replacement");
  vgaShield.fillShapes(1);
  byte radius = RES_X / 10 / 2;
  for(y = radius+RES_Y/10/2*2; y < RES_Y; y += RES_Y/10/2*2) {
    for(x = radius; x < RES_X; x += radius * 2) {
      vgaShield.drawCircle(x, y, radius, RANDOM_SIMPLE_COLOUR);
    }
  }
  vgaShield.replaceColour(0, 0, RES_X, RES_Y, WHITE, RANDOM_DARK_COLOUR);
}

void textDemo(void) {
  char buffer[50];
  statusUpdate("VGA Shield Demo 9: Text Drawing");
  strcpy(buffer, "The quick brown emu jumped over the lazy ostrich.");
  
  vgaShield.setFont(FONT_5x7);
  vgaShield.drawText(buffer, 1, 10, RANDOM_BRIGHT_COLOUR);
  vgaShield.setFont(FONT_8x8);
  vgaShield.drawText(buffer, 1, 14, RANDOM_BRIGHT_COLOUR);
  vgaShield.setFont(FONT_8x12);
  vgaShield.drawText(buffer, 1, 13, RANDOM_BRIGHT_COLOUR);
  vgaShield.setFont(FONT_12x16);
  vgaShield.drawText(buffer, 1, 13, RANDOM_BRIGHT_COLOUR);
  
  
  vgaShield.setFont(FONT_5x7_PROP);
  vgaShield.drawText(buffer, 1, 11, RANDOM_BRIGHT_COLOUR);
  vgaShield.setFont(FONT_8x8_PROP);
  vgaShield.drawText(buffer, 1, 15, RANDOM_BRIGHT_COLOUR);
  vgaShield.setFont(FONT_8x12_PROP);
  vgaShield.drawText(buffer, 1, 14, RANDOM_BRIGHT_COLOUR);
  vgaShield.setFont(FONT_12x16_PROP);
  vgaShield.drawText(buffer, 1, 14, RANDOM_BRIGHT_COLOUR);
}

void imageVideoDemo(void) {
  statusUpdate("VGA Shield Demo 10: Displaying Images...");

  vgaShield.displayImageFromRawSD(0x0, 50, 100);
  delay(2000);
  vgaShield.textBackgroundOpaque(0);  
  statusUpdate("                                        and Video!");
  vgaShield.textBackgroundOpaque(1);  
  vgaShield.playVideoFromRawSD(0x0005C4, 200, 200, 33);
}
