#pragma once
#include "Board.h"
#include "Snake.h"
#include<random>

class Goal
{
public:
	Goal(std::mt19937& reg, const Board& brd, const Snake& snek);
	void Respawn(std::mt19937& reg, const Board& brd, const Snake& snek);
	void Draw(Board& brd)const;
	bool IsInTile(const Location& target)const;
	const Location& GetLocation()const;
private:
	static constexpr Color c = Colors::Yellow;
	Location loc;
};