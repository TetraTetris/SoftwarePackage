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

#include "tetratetris.h"

tetratetris::tetratetris()
  {
	memset(Matrix, 0, sizeof Matrix);

  }

void tetratetris::TTRowToMatrix(uint16_t row, uint8_t rowNumber)
{
	for (uint8_t i = 0; i < DISPLAYHEIGHT; i++)
		if (row & (0x1 << i))
			Matrix[rowNumber][i] = I;
}

void tetratetris::matrixToPixel(void)
{
	uint16_t actCol;

	for (uint16_t row = 0; row < DISPLAYWIDTH; row++)
	{
		for (uint16_t col = 0; col < DISPLAYHEIGHT; col++)
		{
			// Odd rows run backwards
			if (row & 0x0001)
				actCol = (DISPLAYHEIGHT - 1) - col;
			else
				actCol = col;
			strip.setPixelColor(row * DISPLAYHEIGHT + col, Matrix[row][actCol]);
		}
	}
	return;
}

void tetratetris::matrixShow(void)
{
	matrixToPixel();
	strip.show();
}

uint8_t tetratetris::doBrick(uint8_t ranBrck, uint8_t flowRow, int8_t moveCol, uint8_t rotate, uint8_t checkDrawUndraw)
//this function is able to check if there is space on the desired place in the DisplayMatrix
//and to draw and undraw a BRick on the desired Place
{
	int8_t matrixCol, matrixRow;
	for (uint8_t brickRow = 0; brickRow < BRICKHEIGHT; brickRow++){
		for (uint8_t brickCol = 0; brickCol < BRICKWIDTH; brickCol++)
		{
			//is there a stone in the Brickarray. also it is neccessary to draw or not
			if (BRICK[ranBrck][brickCol][brickRow] != 0){

				switch (rotate){
				case 0:
					//001
					//111
					//000
					matrixCol = BRICKSTART + brickCol + moveCol;
					matrixRow = brickRow + flowRow;
					break;
				case 1:
					//010
					//010
					//011
					matrixCol = BRICKSTART + BRICKHEIGHT - brickRow + moveCol;
					matrixRow = brickCol + flowRow;
					break;
				case 2:
					//000
					//111
					//100
					matrixCol = BRICKSTART + BRICKHEIGHT - brickCol + moveCol;
					matrixRow = BRICKHEIGHT - brickRow + flowRow;
					break;
				case 3:
					//110
					//010
					//010
					matrixCol = BRICKSTART + brickRow + moveCol;
					matrixRow = BRICKHEIGHT - brickCol + flowRow;
					break;
				default:
					break;
				}//switch rotate
				switch (checkDrawUndraw){
				case check:
					//check right and left edge
					if (matrixCol < 0)
						return occupied;
					if (matrixCol >= DISPLAYWIDTH)
						return occupied;
					//check if lowest row is reached
					if (matrixRow == DISPLAYHEIGHT)
						return occupied;
					//check if space is occupied
					if (Matrix[matrixCol][matrixRow] != 0)
						return occupied;
					break;
				case draw:
					Matrix[matrixCol][matrixRow] = BRICK[ranBrck][brickCol][brickRow];
					break;
				case undraw:
					Matrix[matrixCol][matrixRow] = 0;
					break;
				}//switch checkDrawUndraw



			}
		}
	}
	if (checkDrawUndraw == check)return freeSpace;
	return drawn;
}

int8_t tetratetris::drawBrick(uint8_t ranBrck, uint8_t flowRow, int8_t moveCol, uint8_t rotate, uint8_t moveDir){
	uint8_t brickState = doBrick(ranBrck, flowRow, moveCol, rotate, check);

	if (brickState == freeSpace){
		doBrick(ranBrck, flowRow, moveCol, rotate, draw);
		matrixShow();
		doBrick(ranBrck, flowRow, moveCol, rotate, undraw);
		return 1;//moveCol;
	}
	else{
		switch (moveDir){
		case rightDir:
			return 0;// (moveCol - 1);
		case leftDir:
			return 0;//(moveCol + 1);
		case rotatePosDir:
			return 0;//(rotate - 1);
		case rotateNegDir:
			return 0;//(rotate + 1);
		case bottomDir:
			if (flowRow > 0)
				doBrick(ranBrck, flowRow - 1, moveCol, rotate, draw);
			matrixShow();
			return 0;//brickRemains;
		default:
			break;
			//return drawn
		}
	}
}

byte tetratetris::checkNesButton(byte* lastButton, uint8_t buttonOfInterrest){
	
	
	byte currButton = nintendo.buttons();

	if ((*lastButton & buttonOfInterrest) && !(currButton & buttonOfInterrest)){
		*lastButton = 0;
		return 1;
	}
	*lastButton = currButton;
	return 0;
	/*
	uint8_t nesButtons[8] = { NES_A, NES_B, NES_SELECT, NES_START, NES_UP, NES_DOWN, NES_LEFT, NES_RIGHT };
	byte currButton = nintendo.buttons();

	for (uint8_t i = 0; i < 8; i++){
		if ((*lastButton & nesButtons[i]) && !(currButton & nesButtons[i])){
			*lastButton = 0;
			if(nesButtons[i] == buttonOfInterrest) return 1;
		}
	}
	*lastButton = currButton;
	return 0;
	*/


}



