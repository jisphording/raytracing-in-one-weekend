#include <iostream>
#include <SDL.h>

#include "./templates/to_string.h"

#include "./utils/color.h"
#include "./utils/Ray.h"
#include "./utils/vec3.h"

#include "./Rendering.h"
#include "./GUI_SDL2.h"
#include "./Camera.h"

// G R E E T I N G
// ---------- ---------- ---------- ---------- ---------- //
void rendering::message(std::string message)
{
    std::cout << message;
}

// U T I L I T Y
// ---------- ---------- ---------- ---------- ---------- //

// Hit Sphere
bool hit_sphere(const point3& center, double radius, const Ray& ray) {
	vec3 oc = ray.origin() - center;
	auto a = dot(ray.direction(), ray.direction());
	auto b = 2.0 * dot(oc, ray.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

// Ray color
color::color ray_color(const Ray& m_ray) {
	// Color Red if sphere is hit
	if (hit_sphere(point3(0, 0, -1), 0.5, m_ray))
		return color::color(1, 0, 0);

	vec3 unit_direction = unit_vector( m_ray.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	
	return (1.0 - a) * color::color(1.0, 1.0, 1.0) + a * color::color(0.5, 0.7, 1.0);
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

	// CAMERA
	// ---------- ---------- ---------- ---------- ---------- //

	camera::camera(image_width, image_height);

	// RENDER IMAGE
	// ---------- ---------- ---------- ---------- ---------- //

    for (int pixel_posY = image_height - 1; pixel_posY >= 00; pixel_posY--) {
        for (int pixel_posX = 0; pixel_posX < image_width; pixel_posX++) {

			auto pixel_center = camera::pixel_00_location + (pixel_posX * camera::pixel_pitch_u) + (pixel_posY * camera::pixel_pitch_v);
			auto ray_direction = pixel_center - camera::camera_center;
			Ray ray(camera::camera_center, ray_direction);

			color::color pixel_color = ray_color(ray);
			//color::write_color(image_width, image_height, pixel_posX, pixel_posY);
			color::simple_color(image_width, image_height, pixel_posX, pixel_posY, pixel_color);

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