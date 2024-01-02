// include definition of class Rectangle from Rectangle.h
#include "Rectangle.h"

//------------------------- Constructors -----------------------------

Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)
    : m_bottom_left(bottomLeft), m_top_right(topRight) {
  if (!validateRectangle(m_bottom_left, m_top_right)) {
    m_bottom_left = Vertex(20, 10);
    m_top_right = Vertex(30, 20);
  }
}

Rectangle::Rectangle(const Vertex vertices[2])
    : Rectangle(vertices[0], vertices[1]) {}

Rectangle::Rectangle(double x0, double y0, double x1, double y1)
    : Rectangle(Vertex{x0, y0}, Vertex{x1, y1}) {}

Rectangle::Rectangle(const Vertex& start, double width, double height)
    : m_bottom_left(start) {
  m_top_right = Vertex(start.m_col + width, start.m_row + height);

  if (!validateRectangle(m_bottom_left, m_top_right)) {
    m_bottom_left = Vertex(20, 10);
    m_top_right = Vertex(30, 20);
  }
}

//======================FUNCTIONS==================

Vertex Rectangle::getBottomLeft() const { return m_bottom_left; }

Vertex Rectangle::getTopRight() const { return m_top_right; }

double Rectangle::getWidth() const {
  return m_top_right.m_col - m_bottom_left.m_col;
}

double Rectangle::getHeight() const {
  return m_top_right.m_row - m_bottom_left.m_row;
}

void Rectangle::draw(Board& board) const {
  board.drawLine(getTopLeft(), m_top_right);
  board.drawLine(m_top_right, getBottomRight());
  board.drawLine(getBottomRight(), m_bottom_left);
  board.drawLine(m_bottom_left, getTopLeft());
}

Rectangle Rectangle::getBoundingRectangle() const {
  return Rectangle(m_bottom_left, m_top_right);
}

double Rectangle::getArea() const { return getWidth() * getHeight(); }

double Rectangle::getPerimeter() const {
  return (getWidth() + getHeight()) * 2;
}

Vertex Rectangle::getCenter() const {
  double half_height = getHeight() / 2;
  double half_Width = getWidth() / 2;

  return Vertex((m_bottom_left.m_col + half_Width),
                (m_bottom_left.m_row + half_height));
}

bool Rectangle::scale(double factor) {
  if (factor < 0) return false;

  Vertex bottomLeft, topRight;
  Vertex center = getCenter();

  double tmpCol = (center.m_col - m_bottom_left.m_col) * factor;
  double tmpRow = (center.m_row - m_bottom_left.m_row) * factor;

  bottomLeft.m_col = center.m_col - tmpCol;
  bottomLeft.m_row = center.m_row - tmpRow;

  tmpCol = (m_top_right.m_col - center.m_col) * factor;
  tmpRow = (m_top_right.m_row - center.m_row) * factor;

  topRight.m_col = center.m_col + tmpCol;
  topRight.m_row = center.m_row + tmpCol;


  // Check the validity of the new rectangle
  if (validateRectangle(bottomLeft, topRight)) {
    m_bottom_left = bottomLeft;
    m_top_right = topRight;
    return true;
  }
  return false;
}

Vertex Rectangle::getTopLeft() const {
  return Vertex(m_bottom_left.m_col, m_top_right.m_row);
}

Vertex Rectangle::getBottomRight() const {
  return Vertex(m_top_right.m_col, m_bottom_left.m_row);
}

bool Rectangle::validateRectangle(const Vertex bottomLeft,
                                  const Vertex topRight) const {
  if (!(bottomLeft.isValid() && topRight.isValid())) {
    return false;
  }

  if (bottomLeft.isToTheRightOf(topRight) || bottomLeft.isHigherThan(topRight)) {
    return false;
  }

  return true;
}