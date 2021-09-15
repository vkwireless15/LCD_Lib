#ifndef _GRAPHICS_IO_H_
#define _GRAPHICS_IO_H_

void Init_Graphics_System(unsigned int H, unsigned int W, unsigned int LCD_RAM_START_ADDRESS, char Layers);
void Fill_all(unsigned int Color);
void Fill_rectangle(unsigned int Color, unsigned int StartX, unsigned int StopX, unsigned int StartY, unsigned int StopY);
void MemPoint(unsigned int Address, unsigned int x, unsigned int y, unsigned int Color);
void Show(char Layer);
void Backlight(unsigned int Brightness, char State);

#endif
