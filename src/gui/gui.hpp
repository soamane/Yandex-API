#pragma once
#ifndef GUI_HPP
#define GUI_HPP

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include <d3d11.h>

#include "window/window.hpp"

class DirectDevice
{
public:
	static bool CreateDevice(HWND hwnd);
	static void CleanupDevice();
	static void CreateRenderTarget();
	static void CleanupRenderTarget();

public:
	static inline ID3D11Device* pDevice = nullptr;
	static inline ID3D11DeviceContext* pContext = nullptr;
	static inline IDXGISwapChain* pSwapChain = nullptr;
	static inline ID3D11RenderTargetView* pTargetView = nullptr;
};

#endif // !GUI_HPP
