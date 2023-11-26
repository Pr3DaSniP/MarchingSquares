#include <iostream>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Grid.h"

class MarchingSquares : public olc::PixelGameEngine
{
private:
	Grid* m_grid;
	int m_cellSize = 40;
	float m_threshold = 5.0f;

public:
	MarchingSquares()
	{
		sAppName = "Marching Squares";
	}

	bool OnUserCreate() override
	{
		m_grid = new Grid(ScreenWidth() + 1, ScreenHeight() + 1, m_cellSize, m_threshold);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::DARK_GREY);

		if (GetKey(olc::Key::ENTER).bPressed)
			m_grid->toggleCalculatedCoordinates();

		if (GetKey(olc::Key::LEFT).bPressed)
			m_grid->decreaseThreshold();

		if (GetKey(olc::Key::RIGHT).bPressed)
			m_grid->increaseThreshold();
		
		if (GetKey(olc::Key::R).bPressed)
			m_grid->randomize();
			
		m_grid->draw(*this);
		return true;
	}
};

int main()
{
	MarchingSquares app;
	if (app.Construct(1200, 600, 1, 1))
		app.Start();
	
	return 0;
}