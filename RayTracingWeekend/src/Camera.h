#pragma once

#include "./utils/vec3.h"

namespace camera
{
	// TODO:
	// I do not know yet why everything is working (as I expect it) only when I use the static keyword...
	static vec3 camera_center;
	static vec3 pixel_pitch_u;
	static vec3 pixel_pitch_v;
	static vec3 viewport_u;
	static vec3 viewport_v;
	static vec3 pixel_00_location;

	static void camera(int image_width, int image_height, float aspect_ratio_a = 16.0f, float aspect_ratio_b = 9.0f)
	{
		/*
		// Aspect Ratio
		auto aspect_ratio = aspect_ratio_a / aspect_ratio_b;

		// Calculate image heigth and make sure it is at least 1
		image_height = static_cast <int> (image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;
		*/

		// Camera Settings
		auto focal_length = 1.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * (static_cast <double> (image_width / image_height));
		camera_center = point3(0, 0, 0);

		// Calculate UV
		viewport_u = vec3(viewport_width, 0, 0);
		viewport_v = vec3(0, -viewport_height, 0);

		// Calculate Pixel Pitch
		pixel_pitch_u = viewport_u / image_width;
		pixel_pitch_v = viewport_v / image_height;

		// Calculate top left pixel location
		auto viewport_top_left =
			camera_center - vec3(0, 0, focal_length) - (viewport_u / 2) - (viewport_v / 2);

		pixel_00_location = viewport_top_left + 0.5 * (pixel_pitch_u + pixel_pitch_v);
	}
}