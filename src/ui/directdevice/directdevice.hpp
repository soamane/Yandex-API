#pragma once
#ifndef DIRECT_DEVICE_HPP
#define DIRECT_DEVICE_HPP

#include <d3d11.h>

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

#endif // !DIRECT_DEVICE_HPP
