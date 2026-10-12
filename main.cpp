#include "Canvas.h"
#include "DrawLine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdint>
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 600;

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return 1;
	SDL_Window *window =
		SDL_CreateWindow("Software Rasterization", SDL_WINDOWPOS_CENTERED,
						 SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
	SDL_Renderer *renderer =
		SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (!renderer) {
		std::cout << "Renderer init failed" << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
											 SDL_TEXTUREACCESS_STREAMING,
											 screenWidth, screenHeight);
	bool quit = false;
	Canvas canvas(screenWidth, screenHeight, {0x40, 0xE0, 0xD0});

	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
		}
		SDL_SetRenderTarget(renderer, texture);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		DrawLine(canvas, {0, 0}, {100, 100}, {0x00, 0x00, 0x00});
		DrawLine(canvas, {0, 0}, {100, 0}, {0x00, 0x00, 0x00});
		DrawLine(canvas, {100, 0}, {100, 100}, {0x00, 0x00, 0x00});
		SDL_UpdateTexture(texture, NULL, canvas.pixels.data(),
						  screenWidth * sizeof(uint32_t));
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	std::cout << "Hello, World!" << std::endl;
	return 0;
}
