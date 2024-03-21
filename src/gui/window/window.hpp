#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <windows.h>
#include <string>

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	WNDCLASSEXW InitWindowClass();
	HWND InitWindow();
	void Destroy();

private:
	HWND hwnd;
	WNDCLASSEXW windowClass;

	const std::string windowName = "123";
	const std::string className = "123";
};

#endif // !WINDOW_HPP
