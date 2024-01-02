#pragma once

#include <stdlib.h>

#include "Board.h"
#include "Rectangle.h"
#include "Utilities.h"
#include "Vertex.h"

class IsoscelesTriangle {
 public:
  //==============CONSTRUCTORS=====================

  /* Creates a Triangle using an array of 3 vertices */
  IsoscelesTriangle(const Vertex vertices[3]);
  /* Creates a triangle using the base verticecs and the height */
  IsoscelesTriangle(const Vertex& left, const Vertex& right, double height);

  //============PUBLIC FUNCTIONS=======================

  /* receives the number of the vertex and it returns it*/
  Vertex getVertex(int index) const;

  /* calculates and returns the length of the base */
  double getBaseLength() const;

  /* calculates and returns the length of the legs */
  double getLegLength() const;

  /* calcualtes and returns the length of the height */
  double getHeight() const;

  /* draws the triangle on the board*/
  void draw(Board& board) const;

  /* This function returns the smallest rectangle that bound our triangle */
  Rectangle getBoundingRectangle() const;

  /* Calculates and returns the area of the trinagle */
  double getArea() const;

  /* Calculates and returns the perimeter of the trinagle */
  double getPerimeter() const;

  /* returns the center of the triangle, relatice to the vertices */
  Vertex getCenter() const;

  /* scales the triagnle according to the given factor */
  bool scale(double factor);

 private:
  // Members
  Vertex m_left, m_right, m_head;

  //====================PRIVATE FUNCTIONS========================

  /* checks if the rectangle is valid or not */
  bool validateRectangle(const Vertex left, const Vertex head, const Vertex right);
};