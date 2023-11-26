#include "Grid.h"

int random(int min, int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

Grid::Grid(int width, int height, int cellSize, float threshold)
	: m_width(width), m_height(height), m_cellSize(cellSize), m_threshold(threshold)
{
	for (int x = 0; x < m_width; x += m_cellSize)
	{
		std::vector<Sommet> line;
		for (int y = 0; y < m_height; y += m_cellSize)
		{
			line.push_back(Sommet(Position(x, y), random(0,10), m_threshold));
		}
		m_grid.push_back(line);
	}
}

int Grid::getState(std::vector<int>& bin) 
{
	if (bin.size() != 4)
		throw std::runtime_error("Invalid vector size");

	return bin[0] * 8 + bin[1] * 4 + bin[2] * 2 + bin[3] * 1;
}

Sommet* Grid::getSommet(int x, int y)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return nullptr;

	return &m_grid[x][y];
}

Position Grid::computeCoordinate(Sommet* s1, Sommet* s2, float isovaleur)
{
	if (s1->getBoolValue() == s2->getBoolValue())
		return Position(-1, -1);
	
	float deno = std::abs(s2->getValue() - s1->getValue());
	float top1 = std::abs(isovaleur - s2->getValue());
	float top2 = std::abs(isovaleur - s1->getValue());
	return s1->getPosition() * (top1 / deno) + s2->getPosition() * (top2 / deno);
}

std::vector<Position> Grid::computeCoordinates(std::vector<Sommet*> sommets, float isovaleur)
{
	Sommet* topleft		= sommets[0];
	Sommet* topright	= sommets[1];
	Sommet* bottomright = sommets[2];
	Sommet* bottomleft	= sommets[3];

	return {
		computeCoordinate(topleft, topright, isovaleur),
		computeCoordinate(topright, bottomright, isovaleur),
		computeCoordinate(bottomright, bottomleft, isovaleur),
		computeCoordinate(bottomleft, topleft, isovaleur)
	};
}

void Grid::draw(olc::PixelGameEngine& pge)
{
	std::string str = USE_CALCULATED_COORDINATES ? "Yes" : "No";
	
	pge.DrawString(10, 10, "Press ENTER to toggle calculated coordinates", olc::CYAN, 1);
	pge.DrawString(10, 20, "Calculated coordinates : " + str, olc::CYAN, 1);
	pge.DrawString(10, 40, "Press LEFT or RIGHT to change threshold", olc::CYAN, 1);
	pge.DrawString(10, 50, "Threshold : " + std::to_string(m_threshold), olc::CYAN, 1);
	pge.DrawString(10, 70, "Press R to randomize", olc::CYAN, 1);
	
	for (auto& line : m_grid)
		for (auto& sommet : line)
			pge.FillCircle(sommet.getPosition().getX(), sommet.getPosition().getY(), 2, sommet.getColor());

	for (int i = 0; i < m_grid.size() - 1; ++i) {
		for (int j = 0; j < m_grid[i].size() - 1; ++j) {
			float x = i * m_cellSize % pge.ScreenWidth();
			float y = j * m_cellSize % pge.ScreenHeight();

			std::vector<int> edges;
			Position a, b, c, d;
			Sommet* tLeft = getSommet(i, j);
			Sommet* tRight = getSommet(i + 1, j);
			Sommet* bLeft = getSommet(i, j + 1);
			Sommet* bRight = getSommet(i + 1, j + 1);

			std::vector<int> bin = {
					tLeft->getBoolValue(),
					tRight->getBoolValue(),
					bRight->getBoolValue(),
					bLeft->getBoolValue()
			};
			int state = getState(bin);
			edges = m_marchingSquareTable[state];

			if (USE_CALCULATED_COORDINATES) {
				std::vector<Position> coords = computeCoordinates({ tLeft, tRight, bRight, bLeft }, m_threshold);
				a = coords[0]; b = coords[1]; c = coords[2]; d = coords[3];
			}
			else {
				a = Position(x + m_cellSize * 0.5f, y);
				b = Position(x + m_cellSize,		y + m_cellSize * 0.5f);
				c = Position(x + m_cellSize * 0.5f, y + m_cellSize);
				d = Position(x,						y + m_cellSize * 0.5f);
			}


			for (auto& e : edges) {
				if (e == 0) drawLine(a, b, pge);
				if (e == 1) drawLine(b, c, pge);
				if (e == 2) drawLine(c, d, pge);
				if (e == 3) drawLine(d, a, pge);
				if (e == 4) drawLine(a, c, pge);
				if (e == 5) drawLine(b, d, pge);
			}
		}
	}
}

void Grid::drawLine(Position& p1, Position& p2, olc::PixelGameEngine& pge)
{
	if (p1 != Position(-1, -1) || p2 != Position(-1, -1))
		pge.DrawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), olc::MAGENTA);
}

void Grid::toggleCalculatedCoordinates() {
	USE_CALCULATED_COORDINATES = !USE_CALCULATED_COORDINATES;
}

void Grid::increaseThreshold() {
	if (m_threshold < 10)
		m_threshold += 1;

	update();
}

void Grid::decreaseThreshold() {
	if (m_threshold > 0)
		m_threshold -= 1;

	update();
}

void Grid::update() {
	for (auto& line : m_grid)
		for (auto& sommet : line)
			sommet.update(m_threshold);
}

void Grid::randomize() {
	for (auto& line : m_grid)
		for (auto& sommet : line)
			sommet.setValue(random(0, 10));
}