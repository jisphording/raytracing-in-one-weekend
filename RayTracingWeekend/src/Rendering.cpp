#include <iostream>
#include <SDL.h>

#include "./templates/to_string.h"

#include "./utils/color.h"
#include "./utils/vec3.h"
#include "./Rendering.h"
#include "./GUI_SDL2.h"


// G R E E T I N G
// ---------- ---------- ---------- ---------- ---------- //
void rendering::message(std::string message)
{
    std::cout << message;
}

// R E N D E R I N G
// ---------- ---------- ---------- ---------- ---------- //

void rendering::render(int image_width, int image_height) {

	// INIT
	// ---------- ---------- ---------- ---------- ---------- //

	rendering::message("Rendering started!\n");
	rendering::message("Image size: " + to_string(image_width) + "x" + to_string(image_height) + "px\n");

	GUI_SDL2::sdl("RayTracingWeekend", image_width, image_height);
	GUI_SDL2::update();

	// RENDER IMAGE
	// ---------- ---------- ---------- ---------- ---------- //

    for (int pixel_posY = image_height - 1; pixel_posY >= 00; pixel_posY--) {
        for (int pixel_posX = 0; pixel_posX < image_width; pixel_posX++) {

			color::write_color(image_width, image_height, pixel_posX, pixel_posY);

        }
    }

	// DISPLAY IMAGE ON SCREEN
	// ---------- ---------- ---------- ---------- ---------- //

    while (GUI_SDL2::running) {
        GUI_SDL2::update();
    }

	// FILE I/O	
	// ---------- ---------- ---------- ---------- ---------- //
	//
	// When the Rendering loop is stopped the file is written to disk

	// .PNG
	GUI_SDL2::save_texture("../data/image_data.png");
}