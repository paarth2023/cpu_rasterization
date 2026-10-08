#include "Canvas.h"
#include "Point.h"
#include <vector>

std::vector<float> Interpolate(int d0, int i0, int d1, int i1);

void DrawLine(Canvas &canvas, Point p0, Point p1, Color color);
