#ifndef _GRAPHICS_IO_H_
#define _GRAPHICS_IO_H_

#include "SimpleGraphics.h"

void Init_Graphics_System(uint32 H, uint32 W, uint32 LCD_RAM_START_ADDRESS, uint8 Layers, uint8 ColorType);
void Fill_all(unsigned int Color);
void Fill_rectangle(uint32 Color, int32 StartX, int32 StopX, int32 StartY, int32 StopY);
void MemPoint(int32 x, int32 y, int32 Color);
void Show(uint8 Layer);
void Backlight(uint32 Brightness, uint8 State);
uint8 GetCursorPosition();

#endif
