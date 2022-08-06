#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorder();
	int GetGridWidth()const;
	int GetGridHeight()const;
	bool IsInsideBoard(const Location& loc)const;
private:
	static constexpr int dimmension = 20;
	static constexpr int CellPdding = 1;
	static constexpr int width = 38;
	static constexpr int height = 28;
	static constexpr Color BorderColor = Colors::LightGray;
	static constexpr int borderWidth = 8;
	static constexpr int borderPadding = 2;
	static constexpr int x = 10;
	static constexpr int y = 10;
	Graphics& gfx;
};