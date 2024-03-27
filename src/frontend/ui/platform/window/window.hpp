#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <Windows.h>

class Window
{
public:
	void Init(WNDCLASSEXW& wc, HWND& hwnd);
	void CleanupResources(HWND hWindow, WNDCLASSEXW& windowClass);
private:

};

#endif // !WINDOW_HPP
