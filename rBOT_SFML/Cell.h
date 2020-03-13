#pragma once
#include "PCH.h"
#include "Header.h"

class Cell : public RectangleShape {
public:
	Cell();

	void setType(CellType type);
	CellType getType();
	void setPosition(float x, float y);
	Vector2f getPosition();
	Vector2f getSize();
	FloatRect getGlobalBounds();
	Vector2f getLimitPosition();

private:
	// Necessary draw function ovverride for custom Drawables
	virtual void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_cell, states);
	}

	void setNormal();
	void setStart();
	void setTarget();
	void setWall();
	void setPath();
	void setVisited();

	bool focus;
	bool isStart;
	bool isTarget;
	CellType cell_type;

	const float cell_size = 18;
	const Color cell_color = Color::Yellow;
	RectangleShape m_cell;
};