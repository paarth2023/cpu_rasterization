#include "Canvas.h"
#include "DrawLine.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <cstdint>
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 600;

int main()
{
	std::cout << "Hello, World!" << std::endl;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "INIT failed" << std::endl;
		return 1;
	}
	SDL_Window *window = SDL_CreateWindow("window", screenWidth, screenHeight,
										  SDL_WINDOW_RESIZABLE);
	if (!window) {
		std::cout << "Window creation failed" << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		std::cout << "Renderer could not be created" << std::endl;
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
		SDL_PollEvent(&event);
		if (event.type == SDL_EVENT_QUIT) {
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
		SDL_RenderTexture(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;
}
