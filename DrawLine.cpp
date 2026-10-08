#include "DrawLine.h"
#include <cmath>
#include <utility>

std::vector<float> Interpolate(int d0, int i0, int d1, int i1)
{
	if (i0 == i1)
		return {float(d0)};
	std::vector<float> values;
	float a = (d1 - d0) / (float)(i1 - i0);
	float d = d0;

	for (int i = i0; i <= i1; i++) {
		values.push_back(d);
		d += a;
	}
	return values;
}

void DrawLine(Canvas &canvas, Point p0, Point p1, Color color)
{
	int dx = std::abs(p1.x - p0.x);
	int dy = std::abs(p1.y - p0.y);

	if (dx > dy) {
		if (p0.x > p1.x)
			std::swap(p0, p1);
		std::vector<float> ys = Interpolate(p0.y, p0.x, p1.y, p1.x);
		for (int x = p0.x; x <= p1.x; x++) {
			canvas.putPixel(x, int(std::lround(ys[x - p0.x])), color);
		}
	} else {
		if (p0.y > p1.y)
			std::swap(p0, p1);
		std::vector<float> xs = Interpolate(p0.x, p0.y, p1.x, p1.y);
		for (int y = p0.y; y < p1.y; y++) {
			canvas.putPixel(xs[y - p0.y], y, color);
		}
	}
}
