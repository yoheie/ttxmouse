; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=TTXMouse
AppVerName=TTXMouse 1.0.1
AppPublisher=Yohei Endo
AppPublisherURL=https://yoheie.sakura.ne.jp/ttxmouse/
AppSupportURL=https://yoheie.sakura.ne.jp/ttxmouse/
AppUpdatesURL=https://yoheie.sakura.ne.jp/ttxmouse/
DefaultDirName={pf}\TTXMouse
DefaultGroupName=TTXMouse
AllowNoIcons=yes
OutputDir=Setup
OutputBaseFilename=TTXMouse-1.0.1-Setup
Compression=lzma
SolidCompression=yes
DisableWelcomePage=no
DisableDirPage=no

[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl"
Name: "ja"; MessagesFile: "compiler:Languages\Japanese.isl"

[CustomMessages]
en.CreateStartupIcon=Create a &startup icon
ja.CreateStartupIcon=スタートアップにアイコンを作成する(&s)

[Tasks]
Name: startupicon; Description: "{cm:CreateStartupIcon}"; GroupDescription:"{cm:AdditionalIcons}"
Name: desktopicon; Description: "{cm:CreateDesktopIcon}"; GroupDescription:"{cm:AdditionalIcons}"; Flags:unchecked

[Files]
Source: "Project\Release Unicode\TTXMouse.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "Project\TTXMouse_vc2010express.vcxproj"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\TTXMouse_vc2010express.vcxproj.filters"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\TTXMouse_vs2012express.vcxproj"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\TTXMouse_vs2012express.vcxproj.filters"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\TTXMouse_vs2013express.vcxproj"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\TTXMouse_vs2013express.vcxproj.filters"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\TTXMouse_vs2015express.vcxproj"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\TTXMouse_vs2015express.vcxproj.filters"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\TTXMouse.c"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\XMouseRegistry.c"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\XMouseRegistry.h"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\NotifyIcon.c"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\NotifyIcon.h"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\resource.h"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\TTXMouse.rc"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\Makefile"; DestDir: "{app}\Project"; Flags: ignoreversion
Source: "Project\res\icon_disable.ico"; DestDir: "{app}\Project\res"; Flags: ignoreversion
Source: "Project\res\icon_enable.ico"; DestDir: "{app}\Project\res"; Flags: ignoreversion
Source: "Project\res\icon_main.ico"; DestDir: "{app}\Project\res"; Flags: ignoreversion
Source: "Documents\ReadMe.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "Documents\ReadMe_ja.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "Documents\License.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "Documents\License_ja.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "Documents\Changes.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "Documents\Changes_ja.txt"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\TTXMouse"; Filename: "{app}\TTXMouse.exe"
Name: "{group}\{cm:UninstallProgram,TTXMouse}"; Filename: "{uninstallexe}"
Name: "{commonstartup}\TTXMouse"; Filename: "{app}\TTXMouse.exe"; Tasks:startupicon
Name: "{commondesktop}\TTXMouse"; Filename: "{app}:TTXMouse.exe"; Tasks:desktopicon

[Run]
Filename: "{app}\TTXMouse.exe"; Description: "{cm:LaunchProgram,TTXMouse}"; Flags: nowait postinstall skipifsilent
