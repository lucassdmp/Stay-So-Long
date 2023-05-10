#pragma once

class Shapes
{
public:
  static void Square();
  static void Circle(float radius = 1.0f, int segments = 36, bool fill = true);
};