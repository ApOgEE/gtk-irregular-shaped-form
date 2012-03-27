#  Makefile
#  
#  Copyright 2012 M. Fauzilkamil Zainuddin <jerungkun@gmail.com>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#
#
# This program was created by learning through code from:
#   http://www.gtk.org/tutorial1.2/gtk_tut-9.html
# --------------------------------------------------------------------
CC = gcc
LIBS =`pkg-config gtk+-2.0 --libs`
CFLAGS =`pkg-config gtk+-2.0 --cflags`
WINFLAG = -mwindows
IS_WIN = yes

all: apogee_gnu

ifeq ($(IS_WIN),yes)
apogee_gnu: apogee_gnu.c apogee_gnures.o
	$(CC) $(WINFLAG) -o $@ $< apogee_gnures.o $(CFLAGS) $(LIBS) 
else
apogee_gnu: apogee_gnu.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS) 
endif

apogee_gnures.o: apogee_gnu.rc
	windres apogee_gnu.rc apogee_gnures.o
	
clean:
ifeq ($(IS_WIN),yes)
	rm -rf apogee_gnu.exe
	rm -rf apogee_gnures.o
else
	rm -rf apogee_gnu
endif
