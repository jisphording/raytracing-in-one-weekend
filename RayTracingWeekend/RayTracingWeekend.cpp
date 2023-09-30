#include <fstream>
#include <iostream>
#include <string> // to_string
#include <sstream> // to_string

#include "sdltemplate.h"
#include "color.h"
#include "vec3.h"

// TO_STRING
//
// For some reason to have to_string work I have to define it as a template here.
template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}


// M A I N
// ---------- ---------- ---------- ---------- ---------- //

int main(int argc, char* argv[]) { // those args in the brackets are needed on windows for SDL2 to work

	// IMAGE SIZE
	// ---------- ---------- ---------- ---------- ---------- //

	int width = 800;
	int height = 400;

	std::string img_format("P3\n" + to_string(width) + ' ' + to_string(height) + "\n255");
	std::string img_data_stream("");
	std::string img_data("");

	// RENDER IMAGE
	// ---------- ---------- ---------- ---------- ---------- //

	sdltemplate::sdl("Ray Tracer", width, height);
	sdltemplate::loop();

	// Print an array of random colors to the screen
	for (int y = height - 1; y >= 00; y--) {
		// Progress indicator
		std::clog << "\rScanlines remaining: " << (height - y) << ' ' << std::flush;

		for (int x = 0; x < width; x++) {
			vec3 col(
				float(x) / float(width), 
				float(y) / float(height), 
				0.2);

			auto pixel_color = color(
				double(x) / (width - 1),
				double(y) / (height - 1), 
				0);
			
			write_color(col, height, x, y);

			/*
			// Convert int to string...
			std::string sr = to_string(ir);
			std::string sg = to_string(ig);
			std::string sb = to_string(ib);

			// ...to write to file
			std::stringstream ss(sr + ' ' + sg + ' ' + sb);
			img_data = img_data + '\n' + ss.str(); 
			*/
		}
	}

	// DISPLAY IMAGE ON SCREEN
	// ---------- ---------- ---------- ---------- ---------- //

	while (sdltemplate::running) {
		sdltemplate::loop();
	}

	// FILE I/O	
	// ---------- ---------- ---------- ---------- ---------- //
	//
	// When the Rendering loop is stopped the file is written to disk

	// .PPM
	/*
	std::ofstream file("./data/img_data.ppm");
	file << img_format + img_data;
	file.close();
	*/

	// .PNG
	sdltemplate::save_texture("./data/image_data.png");

	return 0; // SDL2 has to return something to work on windows
}