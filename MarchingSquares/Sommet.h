#pragma once

#include "olcPixelGameEngine.h"
#include "Position.h"

class Sommet
{
private:
	Position m_position;
	int m_value;
	float m_threshold;
	bool m_boolValue = m_value <= m_threshold;
	olc::Pixel color = m_boolValue ? olc::BLACK : olc::WHITE;
public:
	Sommet(Position position, int value, float threshold);

	inline Position getPosition() const { return m_position; }
	inline int getValue() const { return m_value; }
	inline float getThreshold() const { return m_threshold; }
	inline bool getBoolValue() const { return m_boolValue; }
	inline olc::Pixel getColor() const { return color; }

	void update(float threshold);
	void setValue(int value);
};