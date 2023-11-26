#include "Position.h"

Position::Position(float x, float y)
	: m_x(x), m_y(y)
{}

Position Position::operator*(const Position& other) const
{
	return Position(m_x * other.m_x, m_y * other.m_y);
}
Position Position::operator*(float other) const
{
	return Position(m_x * other, m_y * other);
}
Position Position::operator/(const Position& other) const
{
	return Position(m_x / other.m_x, m_y / other.m_y);
}
Position Position::operator/(float other) const
{
	return Position(m_x / other, m_y / other);
}
Position Position::operator+(const Position& other) const
{
	return Position(m_x + other.m_x, m_y + other.m_y);
}

Position Position::operator-(const Position& other) const
{
	return Position(m_x - other.m_x, m_y - other.m_y);
}

bool Position::operator==(const Position& other) const
{
	return m_x == other.m_x && m_y == other.m_y;
}

bool Position::operator!=(const Position& other) const
{
	return !(*this == other);
}

bool Position::operator<(const Position& other) const
{
	return m_x < other.m_x && m_y < other.m_y;
}

bool Position::operator>(const Position& other) const
{
	return m_x > other.m_x && m_y > other.m_y;
}

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
	os << "(" << pos.m_x << ", " << pos.m_y << ")";
	return os;
}
