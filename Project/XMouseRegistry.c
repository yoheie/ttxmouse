/*
 * Copyright (c) 2011, 2012 Yohei Endo <yoheie@gmail.com>
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

#include <tchar.h>
#include <windows.h>
#include "XMouseRegistry.h"

#define XMOUSE_REGISTRY_SIZE 8

#define XMOUSE_REGISTRY_OFFSET 0
#define XMOUSE_REGISTRY_BIT_ENABLE 0x01
#define XMOUSE_REGISTRY_BIT_RAISE  0x40

BOOL XMouseRegistry_Save(BOOL benabled, BOOL braiseenabled, DWORD timeout)
{
	HKEY hkey;
	LONG status;
	DWORD type;
	BYTE value[XMOUSE_REGISTRY_SIZE];
	DWORD size = 0;

	status = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Control Panel\\Desktop"), 0, KEY_READ | KEY_WRITE, &hkey);
	if (status != ERROR_SUCCESS) {
		return FALSE;
	}

	status = RegQueryValueEx(hkey, _T("UserPreferencesMask"), NULL, &type, NULL, &size);
	if ((status != ERROR_SUCCESS) || ((size < 1) || (sizeof(value) < size))) {
		RegCloseKey(hkey);
		return FALSE;
	}

	status = RegQueryValueEx(hkey, _T("UserPreferencesMask"), NULL, &type, value, &size);
	if (status != ERROR_SUCCESS) {
		RegCloseKey(hkey);
		return FALSE;
	}

	if (benabled) {
		value[XMOUSE_REGISTRY_OFFSET] |= XMOUSE_REGISTRY_BIT_ENABLE;
	}
	else {
		value[XMOUSE_REGISTRY_OFFSET] &= ~XMOUSE_REGISTRY_BIT_ENABLE;
	}

	if (braiseenabled) {
		value[XMOUSE_REGISTRY_OFFSET] |= XMOUSE_REGISTRY_BIT_RAISE;
	}
	else {
		value[XMOUSE_REGISTRY_OFFSET] &= ~XMOUSE_REGISTRY_BIT_RAISE;
	}

	status = RegSetValueEx(hkey, _T("UserPreferencesMask"), 0, type, value, size);
	if (status != ERROR_SUCCESS) {
		RegCloseKey(hkey);
		return FALSE;
	}

	status = RegSetValueEx(hkey, _T("ActiveWndTrkTimeout"), 0, REG_DWORD, (CONST BYTE *)&timeout, sizeof(DWORD));
	if (status != ERROR_SUCCESS) {
		RegCloseKey(hkey);
		return FALSE;
	}

	RegCloseKey(hkey);

	return TRUE;
}

BOOL XMouseRegistry_Load(BOOL *benabled, BOOL *braiseenabled, DWORD *timeout)
{
	HKEY hkey;
	LONG status;
	BYTE value[XMOUSE_REGISTRY_SIZE];
	DWORD size = 0;

	status = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Control Panel\\Desktop"), 0, KEY_READ | KEY_WRITE, &hkey);
	if (status != ERROR_SUCCESS) {
		return FALSE;
	}

	status = RegQueryValueEx(hkey, _T("UserPreferencesMask"), NULL, NULL, NULL, &size);
	if ((status != ERROR_SUCCESS) || ((size < 1) || (sizeof(value) < size))) {
		RegCloseKey(hkey);
		return FALSE;
	}

	status = RegQueryValueEx(hkey, _T("UserPreferencesMask"), NULL, NULL, value, &size);
	if (status != ERROR_SUCCESS) {
		RegCloseKey(hkey);
		return FALSE;
	}

	if (benabled) {
		*benabled = (value[XMOUSE_REGISTRY_OFFSET] & XMOUSE_REGISTRY_BIT_ENABLE) ? TRUE : FALSE;
	}

	if (braiseenabled) {
		*braiseenabled = (value[XMOUSE_REGISTRY_OFFSET] & XMOUSE_REGISTRY_BIT_RAISE) ? TRUE : FALSE;
	}

	if (timeout) {
		size = sizeof(DWORD);

		status = RegQueryValueEx(hkey, _T("ActiveWndTrkTimeout"), NULL, NULL, (LPBYTE)timeout, &size);
		if (status != ERROR_SUCCESS) {
			RegCloseKey(hkey);
			return FALSE;
		}
	}

	RegCloseKey(hkey);

	return TRUE;
}
