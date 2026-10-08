#pragma once

#include <cstdint>
#include <vector>

struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

class Canvas {
  public:
	int screenWidth;
	int screenHeight;
	std::vector<uint32_t> pixels;
	Canvas(int screenWidth, int screenHeight, Color color)
		: screenWidth(screenWidth), screenHeight(screenHeight),
		  pixels(screenWidth * screenHeight, pack(color))
	{
	}
	void putPixel(int x, int y, Color color)
	{
		int screen_X = screenWidth / 2 + x;
		int screen_Y = screenHeight / 2 - y;
		if (screen_X < 0 || screen_X >= screenWidth || screen_Y < 0 ||
			screen_Y >= screenHeight)
			return;
		pixels[screen_Y * screenWidth + screen_X] = pack(color);
	}

  private:
	uint32_t pack(Color color)
	{
		return (0xFF << 24) | (color.r << 16) | (color.g << 8) | (color.b);
	}
};
