#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <Windows.h>

class Window
{
public:

	// Initialize the window
	void Init(WNDCLASSEXW& wc, HWND& hwnd);

	// Clean up window resources
	void CleanupResources(HWND hWindow, WNDCLASSEXW& windowClass);
private:

};

#endif // !WINDOW_HPP
