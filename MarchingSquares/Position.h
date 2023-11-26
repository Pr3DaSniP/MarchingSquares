#pragma once
#include <ostream>

class Position
{
private:
	float m_x, m_y;
public:
	Position() = default;
	Position(float x, float y);

	inline float getX() const { return m_x; }
	inline float getY() const { return m_y; }

	Position operator*(const Position& other) const;
	Position operator*(float other) const;
	Position operator/(const Position& other) const;
	Position operator/(float other) const;
	Position operator+(const Position& other) const;
	Position operator-(const Position& other) const;

	bool operator==(const Position& other) const;
	bool operator!=(const Position& other) const;
	bool operator<(const Position& other) const;
	bool operator>(const Position& other) const;
	
	friend std::ostream& operator<<(std::ostream& os, const Position& pos);

};