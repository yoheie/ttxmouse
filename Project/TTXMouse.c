/*
 * Copyright (c) 2011 Yohei Endo <yoheie@gmail.com>
 * 
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 *     1. The origin of this software must not be misrepresented; you must not
 *        claim that you wrote the original software. If you use this software
 *        in a product, an acknowledgment in the product documentation would be
 *        appreciated but is not required.
 * 
 *     2. Altered source versions must be plainly marked as such, and must not
 *        be misrepresented as being the original software.
 * 
 *     3. This notice may not be removed or altered from any source
 *        distribution.
 */

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "XMouseRegistry.h"
#include "NotifyIcon.h"
#include "resource.h"

#define WM_NOTIFYICON (WM_APP + 0)

static HANDLE g_hIconEnable;
static HANDLE g_hIconDisable;

static HMENU g_hMenu;
static HMENU g_hPopupMenu;

static TCHAR g_strName[16];
static TCHAR g_strVersion[16];
static TCHAR g_strVersionMessage[64];
static TCHAR g_strSettingsFormat[128];
static TCHAR g_strSettingEnabled[16];
static TCHAR g_strSettingDisabled[16];
static TCHAR g_strErrorMessage1[48];
static TCHAR g_strErrorMessage2[48];

static TCHAR g_strSettingsMessage[160];

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	HANDLE     hmutex;
	HWND       hwnd;
	MSG        msg;
	BOOL       bmsgget;
	WNDCLASSEX wndclassex;

	hmutex = CreateMutex(NULL, TRUE, _T("TTXMouse_Mutex"));
	if (hmutex == NULL) {
		return 0;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		return 0;
	}

	g_hIconEnable = LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON_ENABLE), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	g_hIconDisable = LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON_DISABLE), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	g_hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU_MAIN));
	g_hPopupMenu = GetSubMenu(g_hMenu, 0);
	LoadString(hInstance, IDS_NAME, g_strName, sizeof(g_strName) / sizeof(TCHAR));
	LoadString(hInstance, IDS_VERSION, g_strVersion, sizeof(g_strVersion) / sizeof(TCHAR));
	LoadString(hInstance, IDS_VERSIONMESSAGE, g_strVersionMessage, sizeof(g_strVersionMessage) / sizeof(TCHAR));
	LoadString(hInstance, IDS_SETTINGSFORMAT, g_strSettingsFormat, sizeof(g_strSettingsFormat) / sizeof(TCHAR));
	LoadString(hInstance, IDS_SETTINGENABLED, g_strSettingEnabled, sizeof(g_strSettingEnabled) / sizeof(TCHAR));
	LoadString(hInstance, IDS_SETTINGDISABLED, g_strSettingDisabled, sizeof(g_strSettingDisabled) / sizeof(TCHAR));
	LoadString(hInstance, IDS_ERRORMESSAGE1, g_strErrorMessage1, sizeof(g_strErrorMessage1) / sizeof(TCHAR));
	LoadString(hInstance, IDS_ERRORMESSAGE2, g_strErrorMessage2, sizeof(g_strErrorMessage2) / sizeof(TCHAR));

	wndclassex.cbSize        = sizeof(WNDCLASSEX);
	wndclassex.style         = 0;
	wndclassex.lpfnWndProc   = WindowProc;
	wndclassex.cbClsExtra    = 0;
	wndclassex.cbWndExtra    = 0;
	wndclassex.hInstance     = hInstance;
	wndclassex.hIcon         = NULL;
	wndclassex.hCursor       = NULL;
	wndclassex.hbrBackground = NULL;
	wndclassex.lpszMenuName  = NULL;
	wndclassex.lpszClassName = _T("TTXMouse_Main");
	wndclassex.hIconSm       = NULL;

	if(RegisterClassEx(&wndclassex) == 0) {
		return 0;
	}

	hwnd = CreateWindow(
		_T("TTXMouse_Main"),
		g_strName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_MESSAGE,
		NULL,
		hInstance,
		NULL
		);
	if (hwnd == NULL) {
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while ((bmsgget = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bmsgget == -1) {
			return 0;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	DestroyMenu(g_hMenu);

	return (int)msg.wParam;
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static NOTIFYICONDATA notifyIcon;
	static UINT wm_taskbarcreated;
	static BOOL benabled = FALSE;
	static BOOL braiseenabled = FALSE;
	static DWORD dwdelay = 0;
	static BOOL bregenabled = FALSE;
	static BOOL bregraiseenabled = FALSE;
	static DWORD dwregdelay = 0;

	switch (uMsg) {
	case WM_CREATE:
		wm_taskbarcreated = RegisterWindowMessage(_T("TaskbarCreated"));
		SystemParametersInfo(SPI_GETACTIVEWINDOWTRACKING, 0, &benabled, 0);
		SystemParametersInfo(SPI_GETACTIVEWNDTRKZORDER, 0, &braiseenabled, 0);
		SystemParametersInfo(SPI_GETACTIVEWNDTRKTIMEOUT, 0, &dwdelay, 0);
		NotifyIcon_Create(&notifyIcon, hwnd, benabled ? g_hIconEnable : g_hIconDisable, WM_NOTIFYICON, g_strName);
		break;
	case WM_DESTROY:
		NotifyIcon_Delete(&notifyIcon);
		PostQuitMessage(0);
		break;
	case WM_NOTIFYICON:
		switch (lParam) {
		case WM_LBUTTONDOWN:
			SystemParametersInfo(SPI_SETACTIVEWINDOWTRACKING, 0, benabled ? (PVOID)0 : (PVOID)1, SPIF_SENDCHANGE);
			SystemParametersInfo(SPI_GETACTIVEWINDOWTRACKING, 0, &benabled, 0);
			NotifyIcon_Change(&notifyIcon, benabled ? g_hIconEnable : g_hIconDisable);
			PostMessage(hwnd, WM_NULL, 0, 0);
			break;
		case WM_RBUTTONDOWN:
			{
				POINT point;
				MENUITEMINFO menuiteminfo;
				menuiteminfo.cbSize = sizeof(MENUITEMINFO);
				menuiteminfo.fMask = MIIM_STATE;
				GetCursorPos(&point);
				SetForegroundWindow(hwnd);
				SystemParametersInfo(SPI_GETACTIVEWNDTRKZORDER, 0, &braiseenabled, 0);
				if (GetMenuItemInfo(g_hPopupMenu, ID_AUTORAISE, FALSE, &menuiteminfo)) {
					menuiteminfo.fState = (menuiteminfo.fState & ~MFS_CHECKED) | (braiseenabled ? MFS_CHECKED : 0);
					SetMenuItemInfo(g_hPopupMenu, ID_AUTORAISE, FALSE, &menuiteminfo);
				}
				TrackPopupMenu(g_hPopupMenu, TPM_LEFTALIGN | TPM_BOTTOMALIGN,point.x, point.y, 0,hwnd, NULL);
				PostMessage(hwnd, WM_NULL, 0, 0);
			}
			break;
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_AUTORAISE:
			SystemParametersInfo(SPI_SETACTIVEWNDTRKZORDER, 0, braiseenabled ? (PVOID)0 : (PVOID)1, SPIF_SENDCHANGE);
			break;
		case ID_SAVETOREGISTRY:
			SystemParametersInfo(SPI_GETACTIVEWINDOWTRACKING, 0, &benabled, 0);
			SystemParametersInfo(SPI_GETACTIVEWNDTRKZORDER, 0, &braiseenabled, 0);
			SystemParametersInfo(SPI_GETACTIVEWNDTRKTIMEOUT, 0, &dwdelay, 0);
			if (!XMouseRegistry_Save(benabled, braiseenabled, dwdelay)) {
				MessageBox(hwnd, g_strErrorMessage1, g_strName, MB_OK);
			}
			break;
		case ID_SHOWSETTINGS:
			SystemParametersInfo(SPI_GETACTIVEWINDOWTRACKING, 0, &benabled, 0);
			SystemParametersInfo(SPI_GETACTIVEWNDTRKZORDER, 0, &braiseenabled, 0);
			SystemParametersInfo(SPI_GETACTIVEWNDTRKTIMEOUT, 0, &dwdelay, 0);
			if (!XMouseRegistry_Load(&bregenabled, &bregraiseenabled, &dwregdelay)) {
				MessageBox(hwnd, g_strErrorMessage2, g_strName, MB_OK);
			}
			else {
				_stprintf_s(
					g_strSettingsMessage,
					sizeof(g_strSettingsMessage) / sizeof(TCHAR),
					g_strSettingsFormat,
					benabled ? g_strSettingEnabled : g_strSettingDisabled,
					braiseenabled ? g_strSettingEnabled : g_strSettingDisabled,
					dwdelay,
					bregenabled ? g_strSettingEnabled : g_strSettingDisabled,
					bregraiseenabled ? g_strSettingEnabled : g_strSettingDisabled,
					dwregdelay
					);
				MessageBox(hwnd, g_strSettingsMessage, g_strName, MB_OK);
			}
			break;
		case ID_VERSION:
			MessageBox(hwnd, g_strVersionMessage, g_strName, MB_OK);
			break;
		case ID_QUIT:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}
		break;
	default:
		if (uMsg == wm_taskbarcreated) {
			NotifyIcon_Create(&notifyIcon, hwnd, benabled ? g_hIconEnable : g_hIconDisable, WM_NOTIFYICON, g_strName);
		}
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
