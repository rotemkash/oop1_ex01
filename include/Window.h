#pragma once
#include "Board.h"
#include "Rectangle.h"
#include "Utilities.h"
#include "Vertex.h"

class Window {
 public:
  //==============CONSTRUCTORS=====================

  /* Constructor that creates a window using a rectangle
   * and a center point to draw the inside lines
   */
  Window(const Rectangle& rectangle, const Vertex& point);

  /* Constructor that receives a bottom left vertex and creates the outside
   * with the width and height, then it creates the center point using the given
   * vertex. */
  Window(const Vertex& start, double width, double height, const Vertex& point);

  //============PUBLIC FUNCTIONS=======================

  /* Returns the bottom left vertex */
  Vertex getBottomLeft() const;

  /* Returns the top right vertex */
  Vertex getTopRight() const;

  /* Returns the Center vvertex */
  Vertex getPoint() const;

  /* draws the windows on the board */
  void draw(Board& board) const;

  /* Returns the smallest rectangle that bounds the window */
  Rectangle getBoundingRectangle() const;

  /* returns the area of the windows */
  double getArea() const;

  /* Returns the perimeter of the window */
  double getPerimeter() const;

  /* Returns the center of the window relative to the vertices */
  Vertex getCenter() const;

  /* scales the window according to the given factor */
  bool scale(double factor);

 private:
  // members
  Rectangle m_rectangle;
  Vertex m_point;

  //====================PRIVATE FUNCTIONS========================

  /* Checks if the windows is valid, returns false otherwise*/
  bool validateWindow(const Vertex point);

  /* creates a windows with the default values */
  void defaultWindow();
};