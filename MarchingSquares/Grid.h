#pragma once
#include <vector>
#include <unordered_map>
#include <random>
#include "Sommet.h"


class Grid
{
private:
	bool USE_CALCULATED_COORDINATES = false;
	int m_width, m_height;
	int m_cellSize;
	float m_threshold;
	std::vector<std::vector<Sommet>> m_grid;

	int getState(std::vector<int>& bin);

	std::vector<Position> computeCoordinates(std::vector<Sommet*> sommets, float isovaleur);

	Position computeCoordinate(Sommet* s1, Sommet* s2, float isovaleur);

	Sommet* getSommet(int x, int y);

	/*
	*
	*		+---A---+
	*		|		|
	*		D		B
	*		|		|
	*		+---C---+
	*
	*	A->B = 0
	*	B->C = 1
	*	C->D = 2
	*	D->A = 3
	*	A->C = 4
	*   B->D = 5
	*
	*/
	std::unordered_map<int, std::vector<int>> m_marchingSquareTable =
	{
		{1,		{2}		},
		{2,		{1}		},
		{3,		{5}		},
		{4,		{0}		},
		{5,		{3,	1}	},
		{6,		{4}		},
		{7,		{3}		},
		{8,		{3}		},
		{9,		{4}		},
		{10,	{0, 2}	},
		{11,	{0}		},
		{12,	{5}		},
		{13,	{1}		},
		{14,	{2}		}
	};

	void update();
public:
	Grid(int width, int height, int cellSize, float threshold);

	void draw(olc::PixelGameEngine& pge);

	void toggleCalculatedCoordinates();

	void increaseThreshold();

	void decreaseThreshold();

	void randomize();

	void drawLine(Position& p1, Position& p2, olc::PixelGameEngine& pge);
};