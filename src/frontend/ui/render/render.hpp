#pragma once
#ifndef RENDER_HPP
#define RENDER_HPP

#include "../../../backend/jsonparser/jsonparser.hpp"
#include "../../../backend/api/api.hpp"

#include "../extern/fonts/fonts.hpp"
#include "../extern/images/images.hpp"

struct Render
{
	static void Init(Images& images, Fonts& fonts, const Weather& fact, const std::vector<Forecast>& forecast);
};

#endif // !RENDER_HPP
