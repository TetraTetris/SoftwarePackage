/*
  tetratetris - Arduino library for the creative coding workshop tetratetris

  Version: 1.0 (15/12/2016) - Created (Bastian Brabec)

  This file is part of tetratetris.

  tetratetris is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  tetratetris is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with tetratetris.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef tetratetris_h
#define tetratetris_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif
#include <Adafruit_NeoPixel.h>
#include <NESPad.h>

#define NEOPIXELPIN 6
#define DISPLAYWIDTH 5
#define DISPLAYHEIGHT 7
#define NUMBERBRICKS 7
#define BRICKSTART 1
#define PIXCNT DISPLAYHEIGHT*DISPLAYWIDTH
#define BRICKWIDTH 4
#define BRICKHEIGHT 2
#define TTSPEED 1500
#define L ((uint32_t)0 << 16) | ((uint32_t)0 <<  8) | 255
#define J ((uint32_t)0 << 16) | ((uint32_t)255 <<  8) | 0
#define S ((uint32_t)255 << 16) | ((uint32_t)0 <<  8) | 0
#define Z ((uint32_t)255 << 16) | ((uint32_t)255 <<  8) | 0
#define T ((uint32_t)0 << 16) | ((uint32_t)255 <<  8) | 255
#define I ((uint32_t)255 << 16) | ((uint32_t)255 <<  8) | 255
#define O ((uint32_t)255 << 16) | ((uint32_t)0 <<  8) | 255

#define NES_A       B00000001
#define NES_B       B00000010
#define NES_SELECT  B00000100
#define NES_START   B00001000
#define NES_UP      B00010000
#define NES_DOWN    B00100000
#define NES_LEFT    B01000000
#define NES_RIGHT   B10000000
/*
uint32_t Matrix[DISPLAYWIDTH][DISPLAYHEIGHT] = { 0 };
uint32_t BRICK[NUMBERBRICKS][BRICKWIDTH][BRICKHEIGHT] = { { { L, 0 },
{ L, 0 },
{ L, L },
{ 0, 0 } },

{ { 0, J },
{ 0, J },
{ J, J },
{ 0, 0 } },

{ { S, 0 },
{ S, S },
{ 0, S },
{ 0, 0 } },

{ { 0, Z },
{ Z, Z },
{ Z, 0 },
{ 0, 0 } },

{ { 0, T },
{ T, T },
{ 0, T },
{ 0, 0 } },

{ { I, 0 },
{ I, 0 },
{ I, 0 },
{ I, 0 } },

{ { 0, 0 },
{ O, O },
{ O, O },
{ 0, 0 } }
};
*/
enum{ bottomDir, rightDir, leftDir, rotateNegDir, rotatePosDir };

class tetratetris {

  public:

	  
	tetratetris();
	void TTRowToMatrix(uint16_t row, uint8_t rowNumber);
	void matrixShow(void);

	int8_t drawBrick(uint8_t ranBrck, uint8_t flowRow, int8_t moveCol, uint8_t rotate, uint8_t moveDir);
	byte checkNesButton(byte* currButton, uint8_t lastButton);
	uint32_t Matrix[DISPLAYWIDTH][DISPLAYHEIGHT];// = { 0 };

	Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXCNT, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
	NESpad nintendo = NESpad(11, 12, 13);
  private:
	  void matrixToPixel(void);
	  uint8_t doBrick(uint8_t ranBrck, uint8_t flowRow, int8_t moveCol, uint8_t rotate, uint8_t checkDrawUndraw);

	 
	  uint32_t BRICK[NUMBERBRICKS][BRICKWIDTH][BRICKHEIGHT] = { { { L, 0 },
	  { L, 0 },
	  { L, L },
	  { 0, 0 } },

	  { { 0, J },
	  { 0, J },
	  { J, J },
	  { 0, 0 } },

	  { { S, 0 },
	  { S, S },
	  { 0, S },
	  { 0, 0 } },

	  { { 0, Z },
	  { Z, Z },
	  { Z, 0 },
	  { 0, 0 } },

	  { { 0, T },
	  { T, T },
	  { 0, T },
	  { 0, 0 } },

	  { { I, 0 },
	  { I, 0 },
	  { I, 0 },
	  { I, 0 } },

	  { { 0, 0 },
	  { O, O },
	  { O, O },
	  { 0, 0 } }
	  };

	  enum{ check, draw, undraw };
	  enum{ drawn, freeSpace, occupied };
	  enum{ brickRemains = 127 };

};

#endif

