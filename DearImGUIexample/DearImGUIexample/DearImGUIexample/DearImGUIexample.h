#pragma once
#include <Windows.h>
#include <tchar.h>
#include <d3d11.h>
#include <dxgi.h>
#include <iostream>
#include "ParseString.h"

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

static char stringInput[256] = "";

const wchar_t* windowTitle = L"Window Title";

static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

char custId[128] = "";

static ParseString parseString;
DeviceData data;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int);
static bool CreateDeviceD3D(HWND hWnd);
static void CleanupDeviceD3D();
static void CreateRenderTarget();
static void CleanupRenderTarget();
static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void draw();