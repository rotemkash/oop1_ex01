#include "Window.h"

Window::Window(const Rectangle& rectangle, const Vertex& point)
    : m_rectangle(rectangle), m_point(point) {
  if (!validateWindow(m_point)) {
    defaultWindow();
  }
}

Window::Window(const Vertex& start, double width, double height,
               const Vertex& point)
    : m_rectangle(Rectangle(start, width, height)), m_point(point) {}

Vertex Window::getBottomLeft() const { return m_rectangle.getBottomLeft(); }

Vertex Window::getTopRight() const { return m_rectangle.getTopRight(); }

Vertex Window::getPoint() const { return m_point; }

void Window::draw(Board& board) const {
  Vertex left = Vertex(m_rectangle.getBottomLeft().m_col, m_point.m_row);
  Vertex right = Vertex(m_rectangle.getTopRight().m_col, m_point.m_row);

  Vertex top = Vertex(m_point.m_col, m_rectangle.getTopRight().m_row);
  Vertex bottom = Vertex(m_point.m_col, m_rectangle.getBottomLeft().m_row);

  m_rectangle.draw(board);

  board.drawLine(left, right);
  board.drawLine(top, bottom);
}

Rectangle Window::getBoundingRectangle() const {
  return m_rectangle.getBoundingRectangle();
}
double Window::getArea() const { return m_rectangle.getArea(); }

double Window::getPerimeter() const { return m_rectangle.getPerimeter(); }

Vertex Window::getCenter() const { return m_rectangle.getCenter(); }

bool Window::scale(double factor) {
  Vertex prevCenter = m_rectangle.getCenter();
  if (!m_rectangle.scale(factor)) {
    return false;
  }

  double newcol = (m_point.m_col - m_rectangle.getCenter().m_col) * factor;
  double newRow = (m_point.m_row - m_rectangle.getCenter().m_row) * factor;

  newcol = m_rectangle.getCenter().m_col + newcol;
  newRow = m_rectangle.getCenter().m_row + newRow;

  Vertex newPoint = Vertex(newcol, newRow);

  if (validateWindow(newPoint)) {
    m_point = newPoint;
  }

}

bool Window::validateWindow(const Vertex point) {
  if (!m_point.isValid()) {
    return false;
  }

  if (point.isHigherThan(m_rectangle.getTopRight()) ||
      point.isToTheRightOf(m_rectangle.getTopRight()) ||
      m_rectangle.getBottomLeft().isHigherThan(point) ||
      m_rectangle.getBottomLeft().isToTheRightOf(point)) {
    return false;
  }

  return true;
}

void Window::defaultWindow() {
  Rectangle tempRec = Rectangle(20, 10, 30, 20);
  m_rectangle = tempRec;
  m_point.m_col = 25;
  m_point.m_row = 15;
}
