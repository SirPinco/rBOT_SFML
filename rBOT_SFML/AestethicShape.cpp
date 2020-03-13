#pragma once
#include "PCH.h"
#include "AestethicShape.h"

AestethicShape::AestethicShape() {
	m_shape.setPosition(0, 0);
	m_shape.setFillColor(Color::Blue);
	m_shape.setSize(Vector2f(50, 50));
}
void AestethicShape::setSize(float x, float y) {
	m_shape.setSize(Vector2f(x, y));
}
Vector2f AestethicShape::getSize() {
	return m_shape.getSize();
}
FloatRect AestethicShape::getGlobalBounds() {
	return m_shape.getGlobalBounds();
}
void AestethicShape::setPosition(float x, float y) {
	m_shape.setPosition(x, y);
}
Vector2f AestethicShape::getPosition() {
	return m_shape.getPosition();
}
Vector2f AestethicShape::getLimitPosition() {
	return Vector2f(m_shape.getPosition().x + m_shape.getGlobalBounds().width - m_shape.getOutlineThickness() * 2,
		m_shape.getPosition().y + m_shape.getGlobalBounds().height - m_shape.getOutlineThickness() * 2);
}
void AestethicShape::setOutlineThickness(float size) {
	m_shape.setOutlineThickness(size);
}
float AestethicShape::getOutlineThickness() {
	return m_shape.getOutlineThickness();
}
void AestethicShape::setOutlineColor(Color color) {
	m_shape.setOutlineColor(color);
}
Color AestethicShape::getOutlineColor() {
	return m_shape.getOutlineColor();
}
void AestethicShape::setFillColor(Color color) {
	m_shape.setFillColor(color);
}
Color AestethicShape::getFillColor() {
	return m_shape.getFillColor();
}