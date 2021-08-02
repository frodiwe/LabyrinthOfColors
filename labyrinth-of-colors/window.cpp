//
//  init.cpp
//  labyrinth-of-colors
//
//  Created by Fiodar Navumenka on 2.08.21.
//

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "window.hpp"
#include "key_handler.hpp"

bool Window::init_window()
{
	this->window_handler = SDL_CreateWindow("Labyrinth Of Colors", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	
	return window_handler != nullptr;
}

bool Window::init_renderer(SDL_Window* window)
{
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if (renderer == nullptr) {
		return false;
	}
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	return true;
}

bool Window::init_image_loading()
{
	const auto flags = IMG_INIT_PNG;
	
	return IMG_Init(flags) & flags;
}

Window::Window() :key_handler{new KeyHandler{}}, event{new SDL_Event{}}
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	if (not init_window())
	{
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		
		return;
	}
	
	
	if (not init_renderer(window_handler))
	{
		std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		
		return;
	}
	
	if (not init_image_loading())
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		
		return;
	}
	
	is_inited = true;
}

void Window::process_events()
{
	while (SDL_PollEvent(event) != 0)
	{
		switch(event->type)
		{
			case SDL_QUIT:
				_is_quited = true;
				break;
				
			case SDL_KEYDOWN:
				key_handler->process(event->key);
		}
	}
}

void Window::render()
{
	SDL_RenderClear(renderer);
	
	// rendering goes here
	
	SDL_RenderPresent(renderer);
}

bool Window::is_quited() const
{
	return _is_quited;
}

Window::~Window()
{
	SDL_DestroyWindow(window_handler);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
}