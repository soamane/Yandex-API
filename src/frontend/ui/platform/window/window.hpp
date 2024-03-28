#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <Windows.h>

class Window
{
public:

	// Initialize the window
	static void Init(WNDCLASSEXW& wc, HWND& hwnd);

	// Clean up window resources
	static void CleanupResources(HWND hWindow, WNDCLASSEXW& windowClass);
};

#endif // !WINDOW_HPP
