#pragma once
#include "PCH.h"
#include "Cell.h"

#pragma region public:
Cell::Cell() {
	// Object constructor, creates a Normal type cell.
	m_cell.setSize(Vector2f(cell_size, cell_size));
	m_cell.setFillColor(cell_color);
	m_cell.setOutlineThickness(2);
	m_cell.setOutlineColor(Color::Black);
	m_cell.setPosition(150, 150);
	cell_type = CellType::Normal;
	focus = false;
	isStart = false;
	isTarget = false;
}

void Cell::setType(CellType type) {
	// Sets the type of  cell.
	// Start = Green, Target = Red, Normal = Yellow, Wall = Grey

	if (type == CellType::Start) {
		setStart();
	}
	else if (type == CellType::Target) {
		setTarget();
	}
	else if (type == CellType::Normal) {
		setNormal();
	}
	else if (type == CellType::Wall) {
		setWall();
	}
	else if (type == CellType::Path) {
		setPath();
	}
	else if (type == CellType::Visited) {
		setVisited();
	}
	// Cycle mode. Hierarchy: Start -> Target -> Wall -> Normal
	else if (type == CellType::cycle) {
		if (cell_type == CellType::Normal && has_start == false) {
			setStart();
		}
		else if (cell_type == CellType::Normal && has_start == true && has_target == false) {
			setTarget();
		}
		else if (cell_type == CellType::Normal) {
			setWall();
		}
		else if (cell_type == CellType::Wall) {
			setNormal();
		}
		else if (cell_type == CellType::Start && has_start == true) {
			setNormal();
			has_start = false;
			startX = -1;
			startY = -1;
		}
		else if (cell_type == CellType::Target && has_target == true) {
			setNormal();
			has_target = false;
			targetX = -1;
			targetY = -1;
		}
		else {
			setNormal();
		}
	}
}

CellType Cell::getType() {
	// Returns cell type

	return cell_type;
}

void Cell::setPosition(float x, float y) {
	// Sets the position of the cell.

	m_cell.setPosition(x, y);
}

Vector2f Cell::getPosition() {
	// Returns a Vector2f with the coordinates of the cell (top left corner).

	return m_cell.getPosition();
}

Vector2f Cell::getSize() {
	// Returns a Vector2f with the size (excluding the outline).

	return Vector2f(cell_size, cell_size);
}

FloatRect Cell::getGlobalBounds() {
	// Returns FloatRect with size of the cell (including the outline).
	//TODO: Check this function solution-wide, be sure it includes the outline. Clarify that it is different from getSize.

	FloatRect bounds(m_cell.getPosition().x, m_cell.getPosition().y, cell_size, cell_size);
	return bounds;
}

Vector2f Cell::getLimitPosition() {
	// Returns position of right-most point of object (.x) or bottom-most (.y)
	return Vector2f(m_cell.getPosition().x + m_cell.getGlobalBounds().width - m_cell.getOutlineThickness() * 2,
		m_cell.getPosition().y + m_cell.getGlobalBounds().height - m_cell.getOutlineThickness() * 2);
}
#pragma endregion

#pragma region private:
void Cell::setNormal() {
	cell_type = CellType::Normal;
	m_cell.setFillColor(Color::Yellow);
}

void Cell::setStart() {
	cell_type = CellType::Start;
	has_start = true;

	m_cell.setFillColor(Color::Green);
}

void Cell::setTarget() {
	cell_type = CellType::Target;
	has_target = true;

	m_cell.setFillColor(Color::Red);
}

void Cell::setWall() {
	cell_type = CellType::Wall;
	m_cell.setFillColor(grey_out);
}

void Cell::setPath() {
	cell_type = CellType::Path;
	m_cell.setFillColor(Color(0, 80, 255));
}

void Cell::setVisited() {
	cell_type = CellType::Visited;
	m_cell.setFillColor(Color(255, 185, 0));
}
#pragma endregion