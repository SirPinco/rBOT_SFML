#pragma once
#include "PCH.h"
#include "ErrorProvider.h"

ErrorProvider::ErrorProvider() {
	// Object constructor, creates a red dot.

	m_errorProvider.setRadius(5);
	m_errorProvider.setFillColor(Color::Red);
	m_errorProvider.setOutlineColor(Color::Black);
	m_errorProvider.setOutlineThickness(2);
	m_errorProvider.setPosition(0, 0);
}

void ErrorProvider::setPosition(float x, float y) {
	// Sets the position.

	m_errorProvider.setPosition(x, y);
}

Vector2f ErrorProvider::getPosition() {
	// Returns a Vector2f with the coordinates.

	return m_errorProvider.getPosition();
}

void ErrorProvider::raise(bool value) {
	// Raise error flag.

	raised = value;
}

bool ErrorProvider::isRaised() {
	// Returns if error is raised or not.

	return raised;
}

Vector2f ErrorProvider::getLimitPosition() {
	// Returns position of right-most point of object (.x) or bottom-most (.y)
	return Vector2f(m_errorProvider.getPosition().x + m_errorProvider.getGlobalBounds().width - m_errorProvider.getOutlineThickness() * 2,
		m_errorProvider.getPosition().y + m_errorProvider.getGlobalBounds().height - m_errorProvider.getOutlineThickness() * 2);
}