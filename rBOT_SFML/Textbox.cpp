#pragma once
#include "PCH.h"
#include "Textbox.h"

Textbox::Textbox(int max_chars, bool numeric) {
	// Object constructor, creates a white box with black outlines.

	if (!default_font.loadFromFile(FONT_LOCATION))
		cout << "ERROR LOADING FONT" << endl;

	max_length = max_chars;

	m_textbox.setFont(default_font);
	m_textbox.setCharacterSize(20);
	m_textbox.setFillColor(Color::Black);
	m_textbox.setString(to_string((int)pow(10, max_chars - 1)));	// Sets the length of the box relative to the maxium amount of chars that can be entered.
	m_textbox.setOrigin(m_textbox.getGlobalBounds().left, m_textbox.getGlobalBounds().top);
	m_gshape.setSize(Vector2f(m_textbox.getGlobalBounds().width + 10, m_textbox.getGlobalBounds().height + 8));
	m_gshape.setFillColor(Color::White);
	m_gshape.setOutlineThickness(2);
	m_gshape.setOutlineColor(Color::Black);

	if (numeric) {	// Values between ACII 47->58 are the numbers 0->9
		min_ascii = 47;
		max_ascii = 58;
	}

	focus = false;
	PTR_tiedTo = NULL;
}
Textbox::Textbox(int max_chars) : Textbox(max_chars, false) {}	// Non numeric TB
Textbox::Textbox(bool numeric) : Textbox(2, numeric) {}		// 2 char long TB
Textbox::Textbox() : Textbox(6, false) {}	// 6 char long non numeric TB

void Textbox::setTextColor(Color color) {
	// Sets text color.

	m_textbox.setFillColor(color);
}

void Textbox::setPosition(float x, float y) {
	// Sets the input text position, m_gshape then gets updated around it.

	if (max_length > 1)		// See constructor
		m_textbox.setString(to_string((int)pow(10, max_length - 1)));
	else
		m_textbox.setString("0");

	m_textbox.setPosition(x, y);
	m_gshape.setSize(Vector2f(m_textbox.getGlobalBounds().width + 10, m_textbox.getGlobalBounds().height + 8));
	m_gshape.setPosition(m_textbox.getPosition().x + (m_textbox.getGlobalBounds().width - m_gshape.getSize().x) / 2,
		m_textbox.getPosition().y + (m_textbox.getGlobalBounds().height - m_gshape.getSize().y) / 2);

	m_textbox.setString("");
}

Vector2f Textbox::getPosition() {
	// Returns a Vector2f with the coordinates of the button(Top left corner).

	return m_gshape.getPosition();
}

Vector2f Textbox::getSize() {
	// Returns a Vector2f with the size.

	return m_gshape.getSize();
}

String Textbox::getString() {
	// Returns the text as an sf::String.

	return m_textbox.getString();
}

void Textbox::setFocus(bool value) {
	// Sets focus to the TB.

	focus = value;
}

bool Textbox::isFocused() {
	// Returns if object is focused.

	return focus;
}

FloatRect Textbox::getGlobalBounds() {
	// Returns a FloatRect with the size of the textbox, including any outline and external detail.

	return m_gshape.getGlobalBounds();
}

void Textbox::setEP(bool value) {
	// Sets the value of the tied ErrorProvider (Raised/Lowered)

	ErrorProvider* EP_ptr = static_cast<ErrorProvider*>(PTR_tiedTo);
	EP_ptr->raise(value);
}

bool Textbox::input(Uint32 text_char) {
	// Handles the text input.
	//TODO: Display text filling from the right instead of left-to-right

	string content = m_textbox.getString().toAnsiString();

	if (text_char == 13 || text_char == 27) {	// If CARRIAGE_RETURN/ESC is pressed then unfocus
		focus = false;
		return false;
	}
	else if (text_char == 8 && m_textbox.getString().getSize() > 0) {	// If BACKSPACE is pressed and there is text in the TB remove last char
		content.resize(m_textbox.getString().getSize() - 1);
		m_textbox.setString(content);
	}
	else if (m_textbox.getString().getSize() < max_length) {		// If the max amount of chars hasn't been reached append the new char
		if (text_char > min_ascii&& text_char < max_ascii) {
			m_textbox.setString(m_textbox.getString() + text_char);
		}
		else
			return false;
	}

	return true;
}

unsigned int Textbox::getMaxLength() {
	// Returns the max amount of chars allowed in TB.
	return max_length;
}

float Textbox::getOutlineThickness() {
	// Returns outline thickness of the box
	return m_gshape.getOutlineThickness();
}

Vector2f Textbox::getLimitPosition() {
	// Returns position of right-most point of object (.x) or bottom-most (.y)
	return Vector2f(m_gshape.getPosition().x + m_gshape.getGlobalBounds().width - m_gshape.getOutlineThickness() * 2,
		m_gshape.getPosition().y + m_gshape.getGlobalBounds().height - m_gshape.getOutlineThickness() * 2);
}

void Textbox::setTextSize(int size) {
	// Sets the size of the typed text to <size>
	//TODO: Done while distracted,

	m_textbox.setCharacterSize(size);
}

FloatRect Textbox::getTextBounds() {
	// Returns the size of the text, including outlines.
	//TODO: Separate Textbox size (outside shape), text's size in pixels and text size in "font size"

	return m_textbox.getGlobalBounds();
}

void Textbox::clear() {
	// Clears the text inside

	m_textbox.setString("");
	setEP(false);
}