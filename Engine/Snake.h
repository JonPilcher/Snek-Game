#pragma once
#include "Board.h"
#include <vector>

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(Color c);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& dalta_loc) const;
	void Grow();
	void Draw(Board& brd) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
	bool IsTurnBack(const Location& target)const;
	bool IsSnakeFull();
	int GetLength();
private:
	static constexpr Color HeadColor = Colors::Green;
	static const int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};