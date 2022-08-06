#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snek)
{
	Respawn(rng, brd, snek);
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake& snek)
{
	std::uniform_int_distribution<int>xDist(1, brd.GetGridWidth() -1);
	std::uniform_int_distribution<int>yDist(1, brd.GetGridHeight() -1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snek.IsInTile(newLoc));
	loc = newLoc;
}

void Goal::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

bool Goal::IsInTile(const Location& target) const
{
	if (GetLocation() == target)
	{
		return true;
	}
	return false;
}

const Location& Goal::GetLocation() const
{
	return loc;
}
