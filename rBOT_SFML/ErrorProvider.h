#pragma once
#include "PCH.h"
#include "Header.h"

class ErrorProvider : public CircleShape {
public:
	ErrorProvider();

	void setPosition(float x, float y);
	Vector2f getPosition();
	template<typename ObjectType>
	void tieTo(ObjectType* object) {
		// Complementary template function that works with tie(), refer to Header.h for a detailed explanation of how it all works.
		// <object> is the the object associated with the EP.

		PTR_tiedTo = &object;

		// Set the position relative to the tied-to object, offset to the right by EP_offset.
		m_errorProvider.setPosition(object->getPosition().x + object->getGlobalBounds().width + EP_OFFSET,
			object->getPosition().y + object->getOutlineThickness() / 2 + ceil((object->getGlobalBounds().height - m_errorProvider.getGlobalBounds().height) / 2));
	}
	void raise(bool value);
	bool isRaised();
	Vector2f getLimitPosition();

private:
	// Necessary draw function ovverride for custom Drawables, gets drawn only if raised.
	virtual void ErrorProvider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if (raised) {
			target.draw(m_errorProvider, states);
		}
	}

	bool raised;
	void* PTR_tiedTo;

	CircleShape m_errorProvider;
};
