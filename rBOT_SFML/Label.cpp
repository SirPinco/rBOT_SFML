#pragma once
#include "PCH.h"
#include "Label.h"

Label::Label(string text) {
	// Object constructor, black text 25 pixel high.
	if (!default_font.loadFromFile(FONT_LOCATION))
		cout << "ERROR LOADING FONT" << endl;

	m_label.setFont(default_font);
	m_label.setCharacterSize(20);
	m_label.setFillColor(Color::Black);
	m_label.setString(text);

	m_label.setOrigin(m_label.getGlobalBounds().left, m_label.getGlobalBounds().top);
}
Label::Label() : Label("<temp fill>") {}

void Label::setPosition(float x, float y) {
	// Sets the position

	m_label.setPosition(x, y);
}

Vector2f Label::getPosition() {
	// Returns a Vector2f with the coordinates of the button(Top left corner).

	return m_label.getPosition();
}

FloatRect Label::getGlobalBounds() {
	// Returns a FloatRect with the size of the label, including any outline and external detail.

	return m_label.getGlobalBounds();
}

void Label::setCharacterSize(unsigned int size) {
	// Changes font size (in pixels).

	m_label.setCharacterSize(size);
	m_label.setOrigin(m_label.getOrigin().x + m_label.getGlobalBounds().left,	// Update origin to compensate for new .top
		m_label.getOrigin().y + m_label.getGlobalBounds().top);
}

void Label::setString(string text) {
	// Sets the text to be displayed

	m_label.setString(text);
}

string Label::getString() {
	// Returns text

	return m_label.getString();
}
void Label::setOrigin(float x, float y) {
	// Set new origin

	m_label.setOrigin(x, y);
}
Vector2f Label::getOrigin() {
	// Returns origin

	return m_label.getOrigin();
}

void Label::setTextColor(Color color) {
	// Sets the text color.

	m_label.setFillColor(color);
}

void Label::setOutlineThickness(float size) {
	// Sets outline thickness

	m_label.setOutlineThickness(size);
}

float Label::getOutlineThickness() {
	// Returns thickness of outline.

	return m_label.getOutlineThickness();
}

void Label::setOutlineColor(Color color) {
	// Sets the color of the outline.

	m_label.setOutlineColor(color);
}

Vector2f Label::getLimitPosition() {
	// Returns position of right-most point of object (.x) or bottom-most (.y)

	return Vector2f(m_label.getPosition().x + m_label.getGlobalBounds().width - m_label.getOutlineThickness() * 2,
		m_label.getPosition().y + m_label.getGlobalBounds().height - m_label.getOutlineThickness() * 2);
}