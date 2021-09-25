#ifndef _GRAPHICS_IO_H_
#define _GRAPHICS_IO_H_

#include "SimpleGraphics.h"

void Init_Graphics_System(uint32 H, uint32 W, uint32 LCD_RAM_START_ADDRESS, uint8 Layers, uint8 ColorType);
void Fill_all(unsigned int Color);
void Fill_rectangle(unsigned int Color, unsigned int StartX, unsigned int StopX, unsigned int StartY, unsigned int StopY);
void MemPoint(unsigned int Address, unsigned int x, unsigned int y, unsigned int Color);
void Show(uint8 Layer);
void Backlight(uint32 Brightness, uint8 State);

#endif
