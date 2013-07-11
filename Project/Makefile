# TTXMouse Makefile for MinGW/MSYS
#
# Copyright (c) 2011 Yohei Endo <yoheie@gmail.com>
#
# This software is provided 'as-is', without any express or implied warranty.
# In no event will the authors be held liable for any damages arising from the
# use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it freely,
# subject to the following restrictions:
#
#     1. The origin of this software must not be misrepresented; you must not
#        claim that you wrote the original software. If you use this software in
#        a product, an acknowledgment in the product documentation would be
#        appreciated but is not required.
#
#     2. Altered source versions must be plainly marked as such, and must not be
#        misrepresented as being the original software.
#
#     3. This notice may not be removed or altered from any source distribution.

CC		= gcc
LD		= gcc
RM		= rm -f
CFLAGS	= -Wall -DWINVER=0x0500
LDFLAGS	= -s -mwindows

SOURCES		= TTXMouse.c XMouseRegistry.c NotifyIcon.c
HEADERS		= XMouseRegistry.h NotifyIcon.h resource.h
RCFILE		= TTXMouse.rc
RESFILES	= res/icon_main.ico res/icon_enable.ico res/icon_disable.ico
MAKEFILE	= Makefile

OBJECTS		= $(SOURCES:.c=.o) Resource.o
PROGRAM		= TTXMouse.exe

DISTFILES	= $(SOURCES) $(HEADERS) $(RCFILE) $(RESFILES) $(MAKEFILE)


.PHONY:				all clean dist

all:				$(PROGRAM)

$(PROGRAM):			$(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

TTXMouse.o:			TTXMouse.c XMouseRegistry.h NotifyIcon.h resource.h
	$(CC) $(CFLAGS) -c $<

NotifyIcon.o:		NotifyIcon.c NotifyIcon.h
	$(CC) $(CFLAGS) -c $<

XMouseRegistry.o:	XMouseRegistry.c XMouseRegistry.h
	$(CC) $(CFLAGS) -c $<

Resource.o:			$(RCFILE) $(RESFILES) resource.h
	windres $< $@

clean:
	$(RM) $(PROGRAM) $(OBJECTS)
