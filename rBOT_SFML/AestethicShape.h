#pragma once
#include "PCH.h"
#include "Header.h"
class AestethicShape : public Drawable {
public:
	AestethicShape();
	void setSize(float x, float y);
	Vector2f getSize();
	FloatRect getGlobalBounds();
	void setPosition(float x, float y);
	Vector2f getPosition();
	Vector2f getLimitPosition();
	void setOutlineThickness(float size);

	float getOutlineThickness();
	void setOutlineColor(Color color);
	Color getOutlineColor();
	void setFillColor(Color color);
	Color getFillColor();

private:
	virtual void AestethicShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_shape, states);
	}

	RectangleShape m_shape;
};