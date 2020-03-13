#pragma once
#include "PCH.h"
#include "Header.h"
#include "ErrorProvider.h"

class Textbox : public Drawable {
public:
	Textbox(int max_chars, bool numeric);
	Textbox(int max_chars);
	Textbox(bool numeric);
	Textbox();

	void setTextColor(Color color);
	void setPosition(float x, float y);
	Vector2f getPosition();
	Vector2f getSize();
	String getString();
	void setFocus(bool value);
	bool isFocused();
	FloatRect getGlobalBounds();
	template<typename ObjectType> void tieTo(ObjectType* object) {
		PTR_tiedTo = object;
	}
	void setEP(bool value);
	bool input(Uint32 text_char);
	unsigned int getMaxLength();
	float getOutlineThickness();
	Vector2f getLimitPosition();
	void setTextSize(int size);
	FloatRect getTextBounds();
	void clear();

private:
	// Necessary draw function ovverride for custom Drawables
	virtual void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_gshape, states);
		target.draw(m_textbox, states);
	}

	unsigned int max_length;
	Uint32 min_ascii = 32;
	Uint32 max_ascii = 127;
	void* PTR_tiedTo;
	bool focus;
	Font default_font;

	Text m_textbox;
	RectangleShape m_gshape;
};
