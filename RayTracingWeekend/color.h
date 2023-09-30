#pragma once

#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color(color m_col, int m_height, int x, int y)
{
	int ir = int(255.99 * m_col[0]);
	int ig = int(255.99 * m_col[1]);
	int ib = int(255.99 * m_col[2]);

	sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
	sdltemplate::drawPoint(x, m_height - y); // Flip The UV coordinate
}

#endif