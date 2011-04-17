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

#include <tchar.h>
#include <windows.h>
#include "NotifyIcon.h"

BOOL NotifyIcon_Create(NOTIFYICONDATA *p_notifyIcon, HWND hwnd, HICON hicon, UINT ucallbackmessage, LPCTSTR sztip)
{
	p_notifyIcon->cbSize           = sizeof(NOTIFYICONDATA);
	p_notifyIcon->uID              = 1;
	p_notifyIcon->hWnd             = hwnd;
	p_notifyIcon->uFlags           = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	p_notifyIcon->hIcon            = hicon;
	p_notifyIcon->uCallbackMessage = ucallbackmessage;
	lstrcpyn(p_notifyIcon->szTip, sztip, sizeof(p_notifyIcon->szTip) / sizeof(TCHAR));

	return Shell_NotifyIcon(NIM_ADD, p_notifyIcon);
}

BOOL NotifyIcon_Delete(NOTIFYICONDATA *p_notifyIcon)
{
	return Shell_NotifyIcon(NIM_DELETE, p_notifyIcon);
}

BOOL NotifyIcon_Change(NOTIFYICONDATA *p_notifyIcon, HICON hicon)
{
	p_notifyIcon->hIcon = hicon;

	return Shell_NotifyIcon(NIM_MODIFY, p_notifyIcon);
}
