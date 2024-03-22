#include "scene.hpp"

void Scene::Render() { 
    ImGui::SetNextWindowSize(SceneParams::size);
    ImGui::Begin(SceneParams::title.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    {
        
    }
    ImGui::End();
}
