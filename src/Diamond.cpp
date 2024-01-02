#include "Diamond.h"

Diamond::Diamond(const Vertex vertices[4])
    : m_left(vertices[0]),
      m_bottom(vertices[1]),
      m_right(vertices[2]),
      m_head(vertices[3]) {
  validateDiamond(vertices);
}

Diamond::Diamond(const IsoscelesTriangle& lower)
    : m_left(lower.getVertex(0)),
      m_bottom(lower.getVertex(1)),
      m_right(lower.getVertex(2)) {
  double height = (m_left.m_row - m_bottom.m_row) * 2;

  Vertex new_top = Vertex(m_bottom.m_col, m_bottom.m_row + height);

  if (new_top.isValid()) {
    m_head = new_top;
  } else {
    DefaultDiamond();
  }
}

Vertex Diamond::getVertex(int index) const {
  switch (index) {
    case 0:
      return m_left;
    case 1:
      return m_bottom;
    case 2:
      return m_right;
    case 3:
      return m_head;
  }
}

void Diamond::validateDiamond(const Vertex vertices[4]) {
  if (!m_left.isValid() || !m_right.isValid() || !m_bottom.isValid() ||
      !m_head.isValid()) {
    DefaultDiamond();
    return;
  } else if (m_bottom.isHigherThan(m_head) || !sameCol(m_bottom, m_head)) {
    DefaultDiamond();
    return;
  } else if (m_left.isToTheRightOf(m_right) || !sameRow(m_right, m_left)) {
    DefaultDiamond();
    return;
  } else if (m_bottom.isHigherThan(m_left) || m_bottom.isHigherThan(m_right)) {
    DefaultDiamond();
    return;
  }

  double bottomLeftEdge = distance(m_left, m_bottom);
  double bottomRightEdge = distance(m_bottom, m_right);
  double TopRightEdge = distance(m_right, m_head);
  double TopLeftEdge = distance(m_head, m_left);

  if (!(doubleEqual(bottomLeftEdge, bottomRightEdge) &&
        doubleEqual(bottomRightEdge, TopRightEdge) &&
        doubleEqual(TopRightEdge, TopLeftEdge))) {
    DefaultDiamond();
    return;
  }
}

void Diamond::DefaultDiamond() {
  m_left = Vertex(20, 20);
  m_head = Vertex(25, 25);
  m_right = Vertex(30, 20);
  m_bottom = Vertex(25, 15);
}

double Diamond::getWidth() const { return distance(m_left, m_right); }

double Diamond::getHeight() const { return distance(m_bottom, m_head); }

void Diamond::draw(Board& board) const {
  board.drawLine(m_left, m_bottom);
  board.drawLine(m_bottom, m_right);
  board.drawLine(m_right, m_head);
  board.drawLine(m_head, m_left);
}

Rectangle Diamond::getBoundingRectangle() const {
  Vertex recBottomLeft, recTopRight;

  recBottomLeft.m_col = m_left.m_col;
  recBottomLeft.m_row = m_bottom.m_row;

  recTopRight.m_col = m_right.m_col;
  recTopRight.m_row = m_head.m_row;

  return Rectangle(recBottomLeft, recTopRight);
}

double Diamond::getArea() const {
  IsoscelesTriangle topTriangle =
      IsoscelesTriangle(m_left, m_right, getHeight() / 2);

  return topTriangle.getArea() * 2;
}

double Diamond::getPerimeter() const {
  double perimeter = distance(m_left, m_bottom) + distance(m_bottom, m_right) +
                     distance(m_right, m_head) + distance(m_head, m_left);

  return perimeter;
}

Vertex Diamond::getCenter() const {
  Vertex center;

  center.m_col =
      (m_left.m_col + m_bottom.m_col + m_right.m_col + m_head.m_col) / 4;
  center.m_row =
      (m_left.m_row + m_bottom.m_row + m_right.m_row + m_head.m_row) / 4;

  return center;
}

bool Diamond::scale(double factor) {
  if (factor <= 0) return false;

  Vertex newLeft, newHead, newRight, newBottom;
  Vertex center = getCenter();

  newLeft.m_col = center.m_col - ((center.m_col - m_left.m_col) * factor);
  newLeft.m_row = m_left.m_row;

  newHead.m_row = center.m_row + ((m_bottom.m_row - center.m_row) * factor);
  newHead.m_col = m_bottom.m_col;

  newRight.m_col = center.m_col + ((m_right.m_col - center.m_col) * factor);
  newRight.m_row = m_right.m_row;

  newBottom.m_row = center.m_row - ((center.m_row - m_head.m_row) * factor);
  newBottom.m_col = m_head.m_col;

  if (!newLeft.isValid() || !newHead.isValid() || !newRight.isValid() ||
      !newBottom.isValid()) {
    return false;
  }

  m_left = newLeft;
  m_bottom = newHead;
  m_right = newRight;
  m_head = newBottom;

  return true;
}