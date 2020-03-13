#pragma once
#include "PCH.h"
#include "Header.h"

class Button : public Drawable {
public:
	Button();
	Button(string content);
	Button(string content, Text::Style style);

	void setPosition(float x, float y);
	Vector2f getPosition();
	void setString(string text);
	Vector2f getSize();
	void setSize(float x, float y);
	FloatRect getGlobalBounds();
	float getOutlineThickness();
	void setFocus(bool value);
	bool isFocused();
	void setFillColor(Color color);
	void setToggle(bool value);
	Vector2f getLimitPosition();
	void clear();

protected:
	// Necessary draw function ovverride for custom Drawables
	virtual void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_button, states);
		target.draw(m_text, states);
	}

	bool toggle;
	bool focus;
	bool pressed;

	Font default_font;
	RectangleShape m_button;
	Text m_text;
};