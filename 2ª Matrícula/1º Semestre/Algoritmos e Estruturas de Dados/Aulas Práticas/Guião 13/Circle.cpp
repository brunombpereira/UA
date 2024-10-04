//
// Algoritmos e Estruturas de Dados - 2023/2024
//
// COMPLETE the code, according to Circle.h
//

#include "Circle.h"

#define _USE_MATH_DEFINES

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "Figure.h"
#include "Point.h"

Circle::Circle(void) {
  // Circle of radius 1 and centered at (0,0)
  // COMPLETE
}

Circle::Circle(Point center, const std::string& color, double length) {
  // Ensure that the radius is larger than 0.0
  // COMPLETE
}

Circle::Circle(double x, double y, const std::string& color, double length) {
  // Ensure that the radius is larger than 0.0
  // COMPLETE
}

double Circle::GetRadius(void) const { return radius_; }
void Circle::SetRadius(double length) {
  // Ensure that the radius is larger than 0.0
  // COMPLETE
}

std::string Circle::GetClassName(void) const { return "Circle"; }

double Circle::Area(void) const {
  // COMPLETE
}

double Circle::Perimeter(void) const {
  // COMPLETE
}

bool Circle::Intersects(const Circle& c) const {
  // |r1 - r2| < dist(C1,C2) < r1 + r2

  double distance_between_centers = GetCenter().DistanceTo(c.GetCenter());

  double sum_of_radii = radius_ + c.radius_;

  double absolute_difference_of_radii = std::abs(radius_ - c.radius_);

  return ((absolute_difference_of_radii < distance_between_centers) &&
          (distance_between_centers < sum_of_radii));
}

std::ostream& operator<<(std::ostream& os, const Circle& obj) {
  os << "Center: " << obj.GetCenter() << std::endl;
  os << "Color: " << obj.GetColor() << std::endl;
  os << "Radius = " << obj.radius_ << std::endl;
  return os;
}

std::istream& operator>>(std::istream& is, Circle& obj) {
  // COMPLETE
}
