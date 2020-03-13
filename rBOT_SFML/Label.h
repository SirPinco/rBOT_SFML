#pragma once
#include "PCH.h"
#include "Header.h"

class Label : public Drawable {
public:
	Label(string text);
	Label();

	void setPosition(float x, float y);
	Vector2f getPosition();
	FloatRect getGlobalBounds();
	void setCharacterSize(unsigned int size);
	void setString(string text);
	string getString();
	void setOrigin(float x, float y);
	Vector2f Label::getOrigin();
	void setTextColor(Color color);
	void setOutlineThickness(float size);
	float getOutlineThickness();
	void setOutlineColor(Color color);
	Vector2f Label::getLimitPosition();

private:
	// Necessary draw function ovverride for custom Drawables
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_label, states);
	}

	Font default_font;
	Text m_label;
};
