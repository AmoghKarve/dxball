/*****************************************************************************************
*Copyright (C) Amogh Karve amogh.karve@gmail.com
*This program is a free software; you can redistribute it and/or modify it
*under the terms of the GNU Lesser General Public License as published by
*the Free Software Foundation; either version 2.1 of the License, or
*(at your option) any later version.
*
*This program is distributed in the hope taht it will be useful,
*but WITHOUT ANY WRRANTY; without even implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*GNU Lesser Public License for more details.
*
*You should have received a copy of the GNU Lesser General Public License
*along with this program; if not write to the Free Software Foundation,
*INC., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
********************************************************************************************/



#ifndef __BRICKS_H
#define __BRICKS_H
#include "structures.h"

void drawbricks(WINDOW *orig,brick **bricks,float y,int x,int i,int j,int *xstart,int *xend,int level);
#endif
