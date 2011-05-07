## VGA()

### Description
Creates a variable of type VGA, to communciate with the VGA Shield.

### Syntax
VGA(*address*)

### Parameters
*address* - Address on the I2C bus of the shield to communicate with

### Returns
Instance of VGA associated with a specific VGA Shield.

## begin()

### Description
Initialize the shield and start communicating with it.

### Syntax
*VGAinstance*.begin(**)

### Parameters

### Returns
none

## clearScreen()

### Description
Clear the screen.

### Syntax
*VGAInstance*.clearScreen(**)

### Parameters
*none

### Returns
none

## setResolution()

### Description
Set the current screen resolution.

### Syntax
*VGAInstance*.setResolution(*resolution*)

### Parameters
*resolution* - One of RES_320x240, RES_640x480, or RES_800x480

### Returns
none

## setDisplayPage()

### Description
Set which memory page is currently being displayed.

### Syntax
*VGAInstance*.setDisplayPage(*page*)

### Parameters
*page* - Page number to display

### Returns
none

## setReadPage()

### Description
Set which memory page is used for read operations.

### Syntax
*VGAInstance*.setReadPage(*page*)

### Parameters
*page* - Page number to use for read operations

### Returns
none

## setWritePage()

### Description
Set which memory page is used for write operations.

### Syntax
*VGAInstance*.setWritePage(*page*)

### Parameters
*page* - Page number to use for write operations

### Returns
none

## setBackground()

### Description
Set the background colour used for drawing opaque text.

### Syntax
*VGAInstance*.setBackground(*colour*)

### Parameters
*colour* - Colour to use for background when drawing opaque text.

### Returns
none

## fillShapes()

### Description
Set whether any shapes drawn are filled or outlined.  Affects only newly drawn shapes, existing shapes are not changed.

### Syntax
*VGAInstance*.fillShapes(*fill*)

### Parameters
*fill* - 0 to draw outlined shapes, 1 to draw filled shapes

### Returns
none

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

## setFont()

### Description
Set the current font to use when drawing characters or text.

### Syntax
*VGAInstance*.setFont(*font*)

### Parameters
*font* - Font name (one of the following monospace fonts: FONT_5x7, FONT_8x8, FONT_8x12, FONT_12x16, or one of the following proportional fonts: FONT_5x7_PROP, FONT_8x8_PROP, FONT_8x12_PROP, FONT_12x16_PROP)

### Returns
none

## textBackgroundOpaque()

### Description
Set whether text is drawn with a transparent or opaque background.

### Syntax
*VGAInstance*.textBackgroundOpaque(*opaque*)

### Parameters
*opaque* - 0 to draw text with a transparent background, 1 to draw with an opaque background

### Returns
none

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

## initSprite()

### Description
Initialize a 32x32 pixel sprite with X Bitmap (XBM) data, storing the data on the shield for later drawing.

### Syntax
*VGAInstance*.initSprite(*id*, *xbmdata*)

### Parameters
*id* - Sprite ID to initialize
*xbmdata* - Sprite data, as XBM formatted data

### Returns
none

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

