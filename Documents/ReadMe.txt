                                TTXMouse ReadMe

                                                           2014-06-10 Yohei Endo


1. About TTXMouse

  TTXMouse is the utility that resides in the Task-Tray, and facilitates the
  X-Mouse setting.

  X-Mouse is a setting to switch the active window by following to the pointer.
  With the setting, Windows can be used like X Window System style window focus.

  Though the setting of X-Mouse is possible also by using Tweak UI, the
  following advantages exist by using TTXMouse.

  1. Simple operation

    From Task-Tray Icon, you can change the settings by few clicks.

  2. The change in the settings and saving to the registry are individually
     possible.

    When using Tweak UI, the registry is edited at the same time as changing the
    setting.  TTXMouse doesn't edit the registry until you specify to do so.


2. System requirements

  The system requirements of TTXMouse is as follows.

    Windows XP
    Windows Vista
    Windows 7

  The operation is confirmd on the following environments.

    Windows XP Home Edition SP3
    Windows 7 Ultimate SP1


3. How to Use

  When TTXMouse is started, the icon of the picture of "Two windows that come in
  succession" is displayed in the Task-Tray. red "X" is drawn over the icon when
  X-Mouse is disabled.

  Enable/Disable Setting of X-Mouse is switched by left-clicking the Task-Tray
  Icon. When you change the Setting, Image of the Task-Tray Icon is changed.

  When right-clicking the Task-Tray Icon, Menu is Displayed. Items of The Menu
  are listed below.

  1. AutoRaise

    Set Enable/Disable of raising the window when the window is focused.
    It is enabled when the menu is checked, and disabled when not checked.

  2. Save to Registry

    Seve X-Mouse Enable/Disable and AutoRaise Enable/Disable settings to
    Registry.

  3. Show Settings

    Display current and Registry settings for X-Mouse Enable/Disable, AutoRaise
    Enable/Disable and Focusing delay.

  4. Version

    Display Version information.

  5. Quit

    Quit TTXMouse.


4. Install/Uninstall

  To Install/Uninstall TTXMouse, Installer is provided.

  If you do not use installer, put TTXMouse.exe to anywhere you want, and make
  shortcuts to StartUp or Desktop, .
  To uninstall, delete TTXMouse.exe and the shortcuts you made.

  Though TTXMouse does not make new registry keys, it edits the existing
  registry key. The registry key which is edited by TTXMouse is as follows.

    Key  : HKCU\Control Panel\Desktop
    Name : UserPreferencesMask

  If it is necessary to restore the above registry key after uninstalling
  TTXMouse, ether of the following method should be done.
  
  1. Before Uninstalling TTXMouse, restore X-Mouse and AutoRaise settings, and
     save to registry using TTXMouse.

  2. Save the registry key before installing TTXMouse, and restore the key after
     uninstalling TTXMouse.

5. License

  TTXMouse is distributed under zlib/libpng license. Prease refer to License.txt
  for details.


                           Copyright (c) 2011-2014 Yohei Endo <yoheie@gmail.com>
