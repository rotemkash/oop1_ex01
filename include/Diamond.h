#pragma once

#include "Board.h"
#include "IsoscelesTriangle.h"
#include "Rectangle.h"
#include "Vertex.h"
class Diamond {
 public:
  //==============CONSTRUCTORS=====================

  /* This constructor creates a diamond using four vertices */
  Diamond(const Vertex vertices[4]);

  /* This constructor recevies the lower triangle of a diamond
   * then it mirrors it along the x axis to create a ful diamond.
   */
  Diamond(const IsoscelesTriangle& lower);

  //============PUBLIC FUNCTIONS=======================

  /* returns the vertex according to the given index*/
  Vertex getVertex(int index) const;

  /* Returns the width of the diamond shape*/
  double getWidth() const;

  /* Returns the height of the diamond shape */
  double getHeight() const;

  /* Draws the diamond on the board */
  void draw(Board& board) const;

  /* Returns the smalles bounding rectangle of the diamond*/
  Rectangle getBoundingRectangle() const;

  /* retunrs the area of the diamond shpe */
  double getArea() const;

  /* returns the perimeter of the diamond */
  double getPerimeter() const;

  /* returns the center of the diamond relative to it's vertices */
  Vertex getCenter() const;

  /* scales the diamond according to the factor given*/
  bool scale(double factor);

 private:
  // Members
  Vertex m_left, m_right, m_head, m_bottom;

  //====================PRIVATE FUNCTIONS========================

  /*checks if the diamond is valid, returns false if not*/
  void validateDiamond(const Vertex vertices[4]);

  /* crates a diamond with the default values */
  void DefaultDiamond();
};