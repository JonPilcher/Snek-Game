/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snek({ 19,14 }),
	goal(rng, brd, snek)
{
	title.Play();
	for (int i = 0; i < 20;i++)
	{
		brd.SpawnPoison(rng, snek, goal);
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{

	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		gameIsStarted = true;
	}
	if (!gameIsOver && gameIsStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			const Location new_delta_loc = { 0,-1 };
			const Location next = snek.GetNextHeadLocation(delta_loc);
			delta_loc = new_delta_loc;
			if (snek.IsTurnBack( next))
			{
				delta_loc = delta_loc;
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			const Location new_delta_loc = { 0,1 };
			delta_loc = new_delta_loc;
			if (delta_loc != -new_delta_loc || snek.GetLength() <= 2)
			{
				delta_loc = new_delta_loc;
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			const Location new_delta_loc = { -1,0 };
			delta_loc = new_delta_loc;
			if (delta_loc != -new_delta_loc || snek.GetLength() <= 2)
			{
				delta_loc = new_delta_loc;
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			const Location new_delta_loc = { 1,0 };
			delta_loc = new_delta_loc;
			if (delta_loc != -new_delta_loc || snek.GetLength() <= 2)
			{
				delta_loc = new_delta_loc;
			}
		}
		
		++snekMoveCounter;
		if (snekMoveCounter >= snekMovePeriod)
		{			
			snekMoveCounter = 0;	
			
		
			const Location next = snek.GetNextHeadLocation(delta_loc);
				if (!brd.IsInsideBoard(next) ||
					snek.IsInTileExceptEnd(next)||
					brd.CheckForObstacle(next)||
					snek.IsSnakeFull())
				{
					gameIsOver = true;
				}
				else
				{
					const bool eating = next == goal.GetLocation();
					if (eating)
					{
						snek.Grow();
						coin.Play();
					}
						if (brd.CheckForPoison(next))//(SCC >= SCCMax)
						{
							//SCC = 0;
							--snekMovePeriod;
							if (snekMovePeriod <= snekMoveMin)
							{
								snekMovePeriod = snekMoveMin;
							}
						}
						//++SCC;
					
					snek.MoveBy(delta_loc);
					if (eating)
					{
						goal.Respawn(rng, brd, snek);
						brd.SpawnObstacle(rng, snek, goal);
					}
				}
		}
		
					
	}
}

void Game::ComposeFrame()
{
	if (!gameIsStarted)
	{
		SpriteCodex::DrawTitle(290, 225, gfx);
	}
	else
	{
		brd.DrawBorder();
		brd.DrawPoison();
		snek.Draw(brd);
		goal.Draw(brd);
		brd.DrawObstacles();
		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(350, 265, gfx);
		}
	}
}
