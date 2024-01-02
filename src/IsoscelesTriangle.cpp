#include "IsoscelesTriangle.h"

IsoscelesTriangle::IsoscelesTriangle(const Vertex vertices[3])
    : m_left(vertices[0]), m_head(vertices[1]), m_right(vertices[2]) {
  if (!validateRectangle(m_left, m_head, m_right)) {
    m_left = Vertex(20, 20);
    m_head = Vertex(25, 25);
    m_right = Vertex(30, 20);
  }
}

IsoscelesTriangle::IsoscelesTriangle(const Vertex& left, const Vertex& right,
                                     double height)
    : m_left(left), m_right(right) {
  m_head =
      Vertex(left.m_col + (distance(left, right) / 2), left.m_row + height);

  if (!validateRectangle(m_left, m_head, m_right)) {
    m_left = Vertex(10, 20);
    m_head = Vertex(25, 25);
    m_right = Vertex(30, 20); 
  }
}

Vertex IsoscelesTriangle::getVertex(int index) const {
  switch (index) {
    case 0:
      return m_left;
    case 1:
      return m_head;
    case 2:
      return m_right;
  }
}

double IsoscelesTriangle::getBaseLength() const {
  return (distance(m_left, m_right));
}

double IsoscelesTriangle::getLegLength() const {
  return (distance(m_left, m_head));
}

double IsoscelesTriangle::getHeight() const {
  return abs(m_head.m_row - m_left.m_row);
}
void IsoscelesTriangle::draw(Board& board) const {
  board.drawLine(m_left, m_right);
  board.drawLine(m_right, m_head);
  board.drawLine(m_left, m_head);
}

Rectangle IsoscelesTriangle::getBoundingRectangle() const {
  if (m_head.isHigherThan(m_right)) {
    Vertex topRight = Vertex(m_right.m_col, m_head.m_row);
    return Rectangle(m_left, topRight);
  }

  Vertex bottomLeft = Vertex(m_left.m_col, m_head.m_row);
  return Rectangle(bottomLeft, m_right);
}

double IsoscelesTriangle::getArea() const {
  return ((getBaseLength() * getHeight()) / 2);
}

double IsoscelesTriangle::getPerimeter() const { return getBaseLength() * 3; }

Vertex IsoscelesTriangle::getCenter() const {
  return Vertex((m_left.m_col + m_head.m_col + m_right.m_col) / 3,
                (m_left.m_row + m_head.m_row + m_right.m_row) / 3);
}

bool IsoscelesTriangle::scale(double factor) {
  if (factor < 0.0)
    return false;
  else {
    Vertex center = getCenter();
    double disX, disY;

    disX = (m_right.m_col - center.m_col) * factor;
    disY = (m_right.m_row - center.m_row) * factor;
    Vertex new_right(center.m_col + disX, center.m_row + disY);

    disX = (center.m_col - m_left.m_col) * factor;
    disY = (center.m_row - m_left.m_row) * factor;
    Vertex new_left(center.m_col - disX, center.m_row - disY);

    disX = (center.m_col - m_head.m_col) * factor;
    disY = (center.m_row - m_head.m_row) * factor;
    Vertex new_head(center.m_col - disX, center.m_row - disY);

    if (new_left.isValid() && new_right.isValid() && new_head.isValid()) {
      m_left = new_left;
      m_right = new_right;
      m_head = new_head;

      return true;
    }
  }
  return false;
}

bool IsoscelesTriangle::validateRectangle(const Vertex left, const Vertex head,
                                          const Vertex right) {
  if (!(left.isValid() && head.isValid() && right.isValid())) {
    return false;
  }
  if (left.isToTheRightOf(right)) {
    return false;
  }
  if (!sameRow(right, left)) {
    return false;
  }
  if (!(doubleEqual(distance(left, head), distance(right, head)))) {
    return false;
  }
  return true;
}