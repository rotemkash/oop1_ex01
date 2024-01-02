// Declaration of class Rectangle.
#pragma once

#include "Board.h"
#include "Utilities.h"
#include "Vertex.h"

class Rectangle {
 public:
  //-----------CONSTRUCTORS-------------------------

  /*
   * A Constructor that receives the bottom left and the top right vetex and
   * creates a rectangle from them.
   */
  Rectangle(const Vertex& bottomLeft, const Vertex& topRight);

  /*
   * A Constructor that receives two vertices in an array and creates
   * a rectangle using them.
   */
  Rectangle(const Vertex vertices[2]);

  /*
   * A Constructor that receives the coordinantes of the bottom left and top
   * right And using them it creates the vertices and creates the rectangle
   * using them.
   */
  Rectangle(double x0, double y0, double x1, double y1);

  /*
   * A constructor that creates a rectangle using the bottom left and
   * a width and height.
   */
  Rectangle(const Vertex& start, double width, double height);

  //===================PUBLIC FUNCTIONS==================

  /* Retturns the bottom left vertex */
  Vertex getBottomLeft() const;

  /* Returns the top right vertex */
  Vertex getTopRight() const;

  /* Returns the Width of the rectangle */
  double getWidth() const;

  /* Returns the Height of the rectangle */
  double getHeight() const;

  /* This function draws the rectangle on the Board */
  void draw(Board& board) const;

  /* This function returns the smallest rectangle that bound our rectangle*/
  Rectangle getBoundingRectangle() const;

  /* Calculates and returns the Area of the rectangle */
  double getArea() const;

  /*Calculates the perimeter of the rectangle and returns it*/
  double getPerimeter() const;

  /* Returns the center of the rectangle, relative to it's edges */
  Vertex getCenter() const;

  /* This function scales the rectangle by the given factor */
  bool scale(double factor);

 private:
  // members
  Vertex m_bottom_left;
  Vertex m_top_right;

  //====================PRIVATE FUNCTIONS========================

  /* Returns the top left vertex */
  Vertex getTopLeft() const;

  /* Returns the bottom right vertex */
  Vertex getBottomRight() const;

  /* This function checks if the rectangle we created is valid. */
  bool validateRectangle(const Vertex bottomLeft, const Vertex topRight) const;
};