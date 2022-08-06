#include "Board.h"
#include<assert.h>

Board::Board(Graphics& gfx)
	:

	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int off_x = x + borderWidth + borderPadding;
	const int off_y = y + borderWidth + borderPadding;

	gfx.DrawRectDim(loc.x * dimmension + off_x + CellPdding, loc.y * dimmension + off_y + CellPdding,
		dimmension - CellPdding * 2, dimmension - CellPdding * 2, c);
}

void Board::DrawBorder() 
{
	const int top = y;
	const int left = x;
	const int bottom = top + (borderWidth + borderPadding) * 2 + height * dimmension;
	const int right = left + (borderWidth + borderPadding) * 2 + width * dimmension;
	//top
	gfx.DrawRect(left, top, right, top + borderWidth, BorderColor);
	// bottom
	gfx.DrawRect(left, bottom - borderWidth, right, bottom, BorderColor);
	//left
	gfx.DrawRect(left, top + borderWidth, left + borderWidth, bottom - borderWidth, BorderColor);
	//right
	gfx.DrawRect(right - borderWidth, top + borderWidth, right, bottom - borderWidth, BorderColor);

}

int Board::GetGridWidth()const
{
	return width;
}

int Board::GetGridHeight()const
{
	return height;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return	loc.x >= 0 && loc.x < width&&
			loc.y >= 0 && loc.y < height;
		
}
