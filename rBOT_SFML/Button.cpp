#pragma once
#include "PCH.h"
#include "Button.h"

Button::Button(string content, Text::Style style) {
	// Object constructor, creates a grey button 70x40 button.
	if (!default_font.loadFromFile(FONT_LOCATION))
		cout << "ERROR LOADING FONT" << endl;

	m_button.setSize(Vector2f(70, 40));
	m_button.setFillColor(Color(150, 150, 150));
	m_button.setOutlineColor(Color::Black);
	m_button.setOutlineThickness(2);

	m_text.setFont(default_font);
	m_text.setCharacterSize(18);
	m_text.setFillColor(Color::Black);
	m_text.setString(content);
	m_text.setStyle(style);
	m_text.setOrigin(m_text.getGlobalBounds().left, m_text.getGlobalBounds().top);

	toggle = false;
}
Button::Button(string content) : Button(content, Text::Style::Regular) {}	// If the style is not specified use Regular
Button::Button() : Button("<temp fill>", Text::Style::Regular) {}	// If nothing is specified create a basic placeholder button.

void Button::setPosition(float x, float y) {
	// Sets the position of the button, both the shape and the text.

	FloatRect text_bounds = m_text.getGlobalBounds();

	m_button.setPosition(x, y);

	m_text.setPosition(m_button.getPosition().x + floor((m_button.getSize().x - text_bounds.width) / 2),
		m_button.getPosition().y + floor((m_button.getSize().y - text_bounds.height) / 2));
}

Vector2f Button::getPosition() {
	// Returns a Vector2f with the coordinates of the button(Top left corner).

	return m_button.getPosition();
}

void Button::setString(string text) {
	// Sets the text of the button.

	m_text.setString(text);
}

void Button::setFocus(bool value) {
	// Focuses/unfocuses the button. If it's a toggle button (click->ON, click again->OFF) it switches the state.

	if (toggle == true) {
		if (pressed == false) {
			pressed = true;
			focus = value;
		}
		else {
			pressed = false;
			focus = !value;
		}
	}
	else
		focus = value;
}

bool Button::isFocused() {
	// Returns the focus type.True = focused, false = not in focus.

	return focus;
}

void Button::setFillColor(Color color) {
	// Changes the color of the box.

	m_button.setFillColor(color);
}

void Button::setSize(float x, float y) {
	// Sets the size given the height and width.

	m_button.setSize(Vector2f(x, y));
}

Vector2f Button::getSize() {
	// Returns a Vector2f with the size of the button (without the outline).

	return m_button.getSize();
}

FloatRect Button::getGlobalBounds() {
	return m_button.getGlobalBounds();
}

float Button::getOutlineThickness() {
	// Returns outline thickness
	return m_button.getOutlineThickness();
}

void Button::setToggle(bool value) {
	// Changes button between standard click-release (false) to toggle (true) type.

	toggle = value;
}

Vector2f Button::getLimitPosition() {
	// Returns position of right-most point of object (.x) or bottom-most (.y)
	return Vector2f(m_button.getPosition().x + m_button.getGlobalBounds().width - m_button.getOutlineThickness() * 2,
		m_button.getPosition().y + m_button.getGlobalBounds().height - m_button.getOutlineThickness() * 2);
}

void Button::clear() {
	// Placeholder necessary for focus_object() and tie().
}