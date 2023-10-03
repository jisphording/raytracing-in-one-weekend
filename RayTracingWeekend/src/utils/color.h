#pragma once

#include "./vec3.h"
#include "../GUI_SDL2.h"

#include <SDL.h>

namespace color
{
	// DEFINITIONS
	using color = vec3;

	SDL_Color createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		SDL_Color c{ r,g,b,a };
		return c;
	}

	// UTILITY FUNCTIONS


	// WRITE_COLOR
	void write_color(int image_width, int image_height, int pixel_posX, int pixel_posY)
	{
		float r = float(pixel_posX) / float(image_width);
		float g = float(pixel_posY) / float(image_height);
		float b = 0.2;

		int ir = int(255.99 * r);
		int ig = int(255.99 * g);
		int ib = int(255.99 * b);

		GUI_SDL2::setDrawColor(createColor(ir, ig, ib, 255));
		GUI_SDL2::drawPoint(pixel_posX, image_height - pixel_posY);
	}
}