## VGA()

### Description
Creates a variable of type VGA, to communciate with the VGA Shield.

### Syntax
VGA(*address*)

### Parameters
*address* - Address on the I2C bus of the shield to communicate with

### Returns
Instance of VGA associated with a specific VGA Shield.

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);

## begin()

### Description
Initialize the shield and start communicating with it.

### Syntax
*VGAinstance*.begin(**)

### Parameters

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
    }

## clearScreen()

### Description
Clear the screen.

### Syntax
*VGAInstance*.clearScreen(**)

### Parameters
*none

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Clear the screen
      vgaInstance.clearScreen();
    }

## setResolution()

### Description
Set the current screen resolution.

### Syntax
*VGAInstance*.setResolution(*resolution*)

### Parameters
*resolution* - One of RES_320x240, RES_640x480, or RES_800x480

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set the resolution to 640x480
      vgaInstance.setResolution(RES_640x480);
    }

## setDisplayPage()

### Description
Set which memory page is currently being displayed.

### Syntax
*VGAInstance*.setDisplayPage(*page*)

### Parameters
*page* - Page number to display

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set the current display page to 2, so all video on the VGA output will come from page 2
      // NOTE: multi-page support is only available in 320x240 resolution
      vgaInstance.setDisplayPage(2);
    }

## setReadPage()

### Description
Set which memory page is used for read operations.

### Syntax
*VGAInstance*.setReadPage(*page*)

### Parameters
*page* - Page number to use for read operations

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set the current read page to 2, so all future calls which read pixels will read them from page 2
      // NOTE: multi-page support is only available in 320x240 resolution
      vgaInstance.setReadPage(2);
    }

## setWritePage()

### Description
Set which memory page is used for write operations.

### Syntax
*VGAInstance*.setWritePage(*page*)

### Parameters
*page* - Page number to use for write operations

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set the current write page to 2, so all future drawing will take place on page 2
      // NOTE: multi-page support is only available in 320x240 resolution
      vgaInstance.setWritePage(2);
    }

## setBackground()

### Description
Set the background colour used for drawing opaque text.

### Syntax
*VGAInstance*.setBackground(*colour*)

### Parameters
*colour* - Colour to use for background when drawing opaque text.

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set the background colour of any text drawn in the future to green
      vgaInstance.setBackground(vgaInstance.generateColour(0, 255, 0));
    }

## fillShapes()

### Description
Set whether any shapes drawn are filled or outlined.  Affects only newly drawn shapes, existing shapes are not changed.

### Syntax
*VGAInstance*.fillShapes(*fill*)

### Parameters
*fill* - 0 to draw outlined shapes, 1 to draw filled shapes

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set any future shapes drawn to be filled
      vgaInstance.fillShapes(1);
    }

## copyArea()

### Description
Copy one rectangular area of the screen onto another area.

### Syntax
*VGAInstance*.copyArea(*xSrc*, *ySrc*, *xDest*, *yDest*, *width*, *height*)

### Parameters
*xSrc* - Horizontal pixel position for the top of the source area
*ySrc* - Vertical pixel position for the left side of the source area
*xDest* - Horizontal pixel position for the top of the destination area
*yDest* - Vertical pixel position for the left side of the destination area
*width* - Width of the area to copy, in pixels
*height* - Height of the area to copy, in pixels

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Copy a 100x100 pixel rectangular area of the currently displayed image from pixel location 50, 50 to 200, 200
      vgaInstance.copyArea(50, 50, 200, 200, 100, 100);
    }

## drawPixel()

### Description
Draw a single pixel.

### Syntax
*VGAInstance*.drawPixel(*x1*, *y1*, *x2*, *y2*, *colour*)

### Parameters
*x* - Horizontal pixel position for the pixel
*y* - Vertical pixel position for the pixel
*colour* - Colour to draw the pixel in

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Draw a red pixel at screen location 50, 50
      vgaInstance.drawPixel(50, 50, vgaInstance.generateColour(255, 0, 0));
    }

## drawLine()

### Description
Draw a line.

### Syntax
*VGAInstance*.drawLine(*x1*, *y1*, *x2*, *y2*, *colour*)

### Parameters
*x1* - Horizontal pixel position for the start of the line
*y1* - Vertical pixel position for the start of the line
*x2* - Horizontal pixel position for the start of the line
*y2* - Vertical pixel position for the start of the line
*colour* - Colour to draw the line in

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Draw a green line from screen location 50, 50 to 150, 150
      vgaInstance.drawLine(50, 50, 150, 150, vgaInstance.generateColour(0, 255, 0));
    }

## drawLine()

### Description
Draw a rectangle.

### Syntax
*VGAInstance*.drawLine(*x1*, *y1*, *x2*, *y2*, *colour*)

### Parameters
*x1* - Horizontal pixel position for the left side of the rectangle
*y1* - Vertical pixel position for the top of the rectangle
*x2* - Horizontal pixel position for the right side of the rectangle
*y2* - Vertical pixel position for the bottom of the rectangle
*colour* - Colour to draw the rectangle in

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Draw a green line from screen location 50, 50 to 150, 150
      vgaInstance.drawLine(50, 50, 150, 150, vgaInstance.generateColour(0, 255, 0));
    }

## drawCircle()

### Description
Draw a circle.

### Syntax
*VGAInstance*.drawCircle(*x*, *y*, *radius*, *colour*)

### Parameters
*x* - Horizontal pixel position for the center of the circle
*y* - Vertical pixel position for the center of the circle
*radius* - Radius of the circle in pixels
*colour* - Colour to draw the circle in

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Draw a red circle centered at screen location 250, 250, with a radius of 50 pixels
      vgaInstance.drawCircle(250, 250, 50, vgaInstance.generateColour(255, 0, 0));
    }

## drawEllipse()

### Description
Draw an ellipse/oval.

### Syntax
*VGAInstance*.drawEllipse(*x*, *y*, *radiusX*, *radiusY*, *colour*)

### Parameters
*x* - Horizontal pixel position for the center of the circle
*y* - Vertical pixel position for the center of the circle
*radiusX* - Horizontal radius of the circle in pixels
*radiusY* - Vertical radius of the circle in pixels
*colour* - Colour to draw the ellipse in

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Draw a green ellipse centered at screen location 250, 250, with a radius of 50 pixels across and 25 pixels up/down
      vgaInstance.drawEllipse(250, 250, 50, 25, vgaInstance.generateColour(255, 0, 0));
    }

## replaceColour()

### Description
Replace one colour with another in a certain rectangular area.

### Syntax
*VGAInstance*.replaceColour(*x1*, *y1*, *x2*, *y2*, *oldColour*, *newColour*)

### Parameters
*x1* - Horizontal pixel position for the left side of the area
*y1* - Vertical pixel position for the top of the area
*x2* - Horizontal pixel position for the right side of the area
*y2* - Vertical pixel position for the bottom of the area
*oldColour* - Colour to be replaced
*newColour* - Colour to replace with

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Replace all black pixels with purple pixels in a rectangular area from pixel location 50, 50 to 150, 150
      vgaInstance.replaceColour(50, 50, 150, 150, vgaInstance.generateColour(0, 0, 0), vgaInstance.generateColour(255, 0, 255));
    }

## setFont()

### Description
Set the current font to use when drawing characters or text.

### Syntax
*VGAInstance*.setFont(*font*)

### Parameters
*font* - Font name (one of the following monospace fonts: FONT_5x7, FONT_8x8, FONT_8x12, FONT_12x16, or one of the following proportional fonts: FONT_5x7_PROP, FONT_8x8_PROP, FONT_8x12_PROP, FONT_12x16_PROP)

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set the font for future text drawing operations to 12x16 pixel proportional
      vgaInstance.setFont(FONT_12x16_PROP);
    }

## textBackgroundOpaque()

### Description
Set whether text is drawn with a transparent or opaque background.

### Syntax
*VGAInstance*.textBackgroundOpaque(*opaque*)

### Parameters
*opaque* - 0 to draw text with a transparent background, 1 to draw with an opaque background

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set text background to transparent for all future text drawing operations
      vgaInstance.textBackgroundOpaque(0);
    }

## initSprite()

### Description
Initialize an 8x8 pixel sprite, storing the data on the shield for later drawing.

### Syntax
*VGAInstance*.initSprite(*id*, *sprite*)

### Parameters
*id* - Sprite ID to initialize
*sprite* - Sprite data, as 8 8-bit bytes where each byte is one horizontal line of the sprite

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set up an 8x8 pixel sprite at ID 2 to later draw with drawSprite()
      byte spriteData[8];
      spriteData[0] = 0x18;
      spriteData[1] = 0x24;
      spriteData[2] = 0x42;
      spriteData[3] = 0x81;
      spriteData[4] = 0x81;
      spriteData[5] = 0x42;
      spriteData[6] = 0x24;
      spriteData[7] = 0x18;
      vgaShield.initSprite(2, spriteData);
    }

## initSprite()

### Description
Initialize a 16x16 pixel sprite, storing the data on the shield for later drawing.

### Syntax
*VGAInstance*.initSprite(*id*, *sprite*)

### Parameters
*id* - Sprite ID to initialize
*sprite* - Sprite data, as 16 16-bit shorts where each short is one horizontal line of the sprite

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set up an 8x8 pixel sprite at ID 2 to later draw with drawSprite()
      byte spriteData[8];
      spriteData[0] = 0x18;
      spriteData[1] = 0x24;
      spriteData[2] = 0x42;
      spriteData[3] = 0x81;
      spriteData[4] = 0x81;
      spriteData[5] = 0x42;
      spriteData[6] = 0x24;
      spriteData[7] = 0x18;
      vgaShield.initSprite(2, spriteData);
    }

## initSprite()

### Description
Initialize a 32x32 pixel sprite, storing the data on the shield for later drawing.

### Syntax
*VGAInstance*.initSprite(*id*, *sprite*)

### Parameters
*id* - Sprite ID to initialize
*sprite* - Sprite data, as 32 32-bit longs where each long is one horizontal line of the sprite

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set up an 8x8 pixel sprite at ID 2 to later draw with drawSprite()
      byte spriteData[8];
      spriteData[0] = 0x18;
      spriteData[1] = 0x24;
      spriteData[2] = 0x42;
      spriteData[3] = 0x81;
      spriteData[4] = 0x81;
      spriteData[5] = 0x42;
      spriteData[6] = 0x24;
      spriteData[7] = 0x18;
      vgaShield.initSprite(2, spriteData);
    }

## initSpriteXbm()

### Description
Initialize a 32x32 pixel sprite with X Bitmap (XBM) data, storing the data on the shield for later drawing.

### Syntax
*VGAInstance*.initSpriteXbm(*id*, *xbmdata*)

### Parameters
*id* - Sprite ID to initialize
*xbmdata* - Sprite data, as XBM formatted data

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // array of XBM data to turn into a sprite
    static byte xbmdata_bits[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x0F, 0x00, 
      0xC0, 0xFF, 0x0F, 0x00, 0xC0, 0x0F, 0xCF, 0x00, 0xC0, 0x0F, 0xCF, 0x00, 
      0xC0, 0x0F, 0x0F, 0x00, 0xC0, 0x0F, 0x0F, 0x00, 0xC0, 0x0F, 0xFF, 0x03, 
      0xC0, 0x0F, 0xFF, 0x03, 0xC0, 0x0F, 0xFF, 0x03, 0xC0, 0x0F, 0xFF, 0x03, 
      0xC0, 0xFF, 0xFF, 0x03, 0xC0, 0xFF, 0xFF, 0x03, 0xC0, 0x0F, 0xFF, 0x03, 
      0xC0, 0x0F, 0xFF, 0x03, 0xCC, 0xFF, 0xFF, 0x33, 0xCC, 0xFF, 0xFF, 0x33, 
      0x0C, 0x00, 0x00, 0x30, 0x0C, 0x00, 0x00, 0x30, 0xFC, 0xFF, 0xFF, 0x3F, 
      0xFC, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0xFC, 0xFF, 0xFF, 0x3F, 0xFC, 0xFF, 0xFF, 0x3F, 0xFC, 0xFF, 0xFF, 0x33, 
      0xFC, 0xFF, 0xFF, 0x33, 0xFC, 0xFF, 0xFF, 0x3F, 0xFC, 0xFF, 0xFF, 0x3F, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
    
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Set up a 32x32 pixel sprite from the data above at ID 2 to later draw with drawSprite()
      vgaInstance.initSpriteXbm(0, xbmdata_bits);
    }

## drawSprite()

### Description
Draw a previously-initialized sprite at a given location in a given colour.

### Syntax
*VGAInstance*.drawSprite(*type*, *id*, *x*, *y*, *colour*)

### Parameters
*type* - Type of sprite, either SPRITE_8x8, SPRITE_16x16, or SPRITE_32x32
*id* - Sprite ID to draw
*x* - Horizontal position at which to draw the upper left corner of the sprite
*y* - Vertical position at which to draw the upper left corner of the sprite

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Draw 8x8 pixel sprite ID 2 (previously set up using initSprite()) at pixel location 50, 50 in blue
      vgaInstance.drawSprite(SPRITE_8x8, 2, 50, 50, vgaInstance.generateColour(0, 0, 255));
    }

## drawCharacter()

### Description
Draw one character of text at a given text grid location using the previously set font.

### Syntax
*VGAInstance*.drawCharacter(*chr*, *x*, *y*, *colour*)

### Parameters
*chr* - Character to draw (normal ASCII values)
*x* - Horizontal grid position at which to draw the character
*y* - Vertical grid position at which to draw the character
*colour* - Colour to draw the character in

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Draw a blue letter C at text grid location 10, 10
      vgaInstance.drawCharacter('C', 10, 10, vgaInstance.generateColour(0, 0, 255));
    }

## drawGraphicsCharacter()

### Description
Draw one character of text at a given pixel location.

### Syntax
*VGAInstance*.drawGraphicsCharacter(*chr*, *x*, *y*, *colour*)

### Parameters
*chr* - Character to draw (normal ASCII values)
*x* - Horizontal pixel position at which to draw the character
*y* - Vertical pixel position at which to draw the character
*width* - Width of the character (stretches if it doesn't match the font size)
*height* - Height of the character (stretches if it doesn't match the font size)
*colour* - Colour to draw the character in

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Draw a large blue letter C at pixel location 200, 200
      vgaInstance.drawGraphicsCharacter('C', 200, 200, 2, 2, vgaInstance.generateColour(0, 0, 255));
    }

## drawText()

### Description
Draw a text string at a given text grid location.

### Syntax
*VGAInstance*.drawText(*text*, *x*, *y*, *colour*)

### Parameters
*text* - Pointer to string of text to draw
*x* - Horizontal text grid position at which to draw the text
*y* - Vertical text grid position at which to draw the text
*colour* - Colour to draw the text in

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Draw the word "Ostrich" in red starting at text grid location 10, 10
      vgaInstance.drawText("Ostrich", 10, 10, vgaInstance.generateColour(255, 0, 0));
    }

## drawGraphicsText()

### Description
Draw a text string at a given pixel location.

### Syntax
*VGAInstance*.drawGraphicsText(*text*, *x*, *y*, *colour*)

### Parameters
*text* - Pointer to string of text to draw
*x* - Horizontal pixel position at which to draw the text
*y* - Vertical pixel position at which to draw the text
*colour* - Colour to draw the text in

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Draw a the word Ostrich in large green letters at pixel location 200, 200
      vgaInstance.drawGraphicsText("Ostrich", 200, 200, 2, 2, vgaInstance.generateColour(0, 255, 0));
    }

## displayImageFromRawSD()

### Description
Display an image stored on a raw (non-FAT) SD card.  This image needs to be stored using 4D Systems Graphics Composer.

### Syntax
*VGAInstance*.displayImageFromRawSD(*offset*, *x*, *y*)

### Parameters
*offset* - Offset into the SD card at which the image is stored
*x* - Horizontal pixel position at which to draw the left side of the image
*y* - Vertical pixel position at which to draw the top of the image

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Display image at index 0 of a raw (non-FAT) MicroSD card
      vgaInstance.displayImageFromRawSD(0, 150, 150);
    }

## playVideoFromRawSD()

### Description
Display a video clip stored on a raw (non-FAT) SD card.  This video needs to be stored using 4D Systems Graphics Composer.

### Syntax
*VGAInstance*.playVideoFromRawSD(*offset*, *x*, *y*, *ifd*)

### Parameters
*offset* - Offset into the SD card at which the video is stored
*x* - Horizontal pixel position at which to place the left side of the video
*y* - Vertical pixel position at which to place the top of the video
*ifd* - Inter-frame delay, in milliseconds

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Play the video stored at index 0 of a raw (non-FAT) MicroSD card at pixel location 150, 150, with 33mS between each frame
      vgaInstance.playVideoFromRawSD(0, 150, 150, 33);
    }

## displayImageFromSD()

### Description
Display an image from a GCI file stored on a microSD card.  GCI files can be created using 4D Systems Graphics Composer.

### Syntax
*VGAInstance*.displayImageFromSD(*filename*, *offset*, *x*, *y*)

### Parameters
*filename* - File name of the GCI file to pull images from
*offset* - Offset in the GCI file of the image to display
*x* - Horizontal pixel position for the left side of the image
*y* - Vertical pixel position for the top of the image

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Display image at index 0 of file ostrich.gci at pixel location 150, 150
      // ostrich.gci would need to be created using 4D Graphics Composer
      vgaInstance.displayImageFromSD("ostrich.gci", 0, 150, 150);
    }

## generateColour()

### Description
Generate a PackedColour from red/green/blue values, which can then be passed to all functions that require colour specification.

### Syntax
*VGAInstance*.generateColour(*r*, *g*, *b*)

### Parameters
*r* - Red value, from 0 to 255
*g* - Green value, from 0 to 255
*b* - Blue value, from 0 to 255

### Returns
none

### Example
    #include <Wire.h>
    #include <MultiSerial.h>
    #include <VGA.h>
    
    // Create a VGA instance to communicate with the shield at address 0x4D
    VGA vgaInstance = VGA(0x4D);
    
    void setup() {
      PackedColour colour;
      
      // Initialize the shield to get it ready to communicate with
      vgaInstance.begin();
      
      // Store the colour blue in the 'colour' variable for later use
      colour = vgaInstance.generateColour(255, 0, 0);
    }

