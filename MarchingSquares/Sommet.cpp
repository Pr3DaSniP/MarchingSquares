#include "Sommet.h"

Sommet::Sommet(Position position, int value, float threshold)
	: m_position(position), m_value(value), m_threshold(threshold)
{}

void Sommet::update(float threshold)
{
	m_threshold = threshold;
	m_boolValue = m_value <= m_threshold;
	color = m_boolValue ? olc::BLACK : olc::WHITE;
}

void Sommet::setValue(int value) {
	m_value = value;
	update(m_threshold);
}