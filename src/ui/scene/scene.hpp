#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include "../imgui/imgui.h"

#include <string>

class Scene
{
public:
	static void Render();

private:
	struct SceneParams
	{
		static inline std::string title = "##begin_scene";
		static inline ImVec2 size = { 850.f, 500.f };
	};
};

#endif // !SCENE_HPP
