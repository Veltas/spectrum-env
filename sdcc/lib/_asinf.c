/*-------------------------------------------------------------------------
   asinf.c - Computes asin(x)

   Copyright (C) 2001, 2002, Jesus Calvino-Fraga, jesusc@ieee.org

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library; see the file COPYING. If not, write to the
   Free Software Foundation, 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.

   As a special exception, if you link this library with other files,
   some of which are compiled with SDCC, to produce an executable,
   this library does not by itself cause the resulting executable to
   be covered by the GNU General Public License. This exception does
   not however invalidate any other reasons why the executable file
   might be covered by the GNU General Public License.


   Version 1.0 - Initial release 

   kio 2014-11-26	added #pragma std_sdcc99 for bool
   kio 2014-11-26	removed keyword FLOAT_FUNC_REENTRANT because functions on the z80 are always rentrant
*/


#pragma std_sdcc99	

#include <math.h>
#include <stdbool.h>

float asincosf(float x, bool isacos);

float asinf(float x) 
{
         if (x == 1.0) return  HALF_PI;
    else if (x ==-1.0) return -HALF_PI;
    else if (x == 0.0) return 0.0;
    else               return asincosf(x, false);
}
