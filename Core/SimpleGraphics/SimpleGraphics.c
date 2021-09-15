#include "SimpleGraphics.h"
#include "Graphics_IO.h"
#include "Coordinates.h"
#include "Font.h"


void Graphics_Init(DisplayConfig *dcf)
{
	Init_Graphics_System(dcf->Display_Height, dcf->Display_Width, dcf->Start_RAM_Address, dcf->Layers_count);
}
void Set_Backlight(char State, unsigned int Brightness)
{
	Backlight(Brightness, State);
}

unsigned int Color_565(unsigned int Color)
{
   return 0;
}
unsigned int Color_888_(unsigned int Color)
{
	return Color | 0xff000000;
}
unsigned int Color_A888_(unsigned int Color, char Alpha)
{
	return Color | Alpha << 24;
}
unsigned int FontHParameter()
{
	char FontH = calibri[1];
	return FontH;
}

void Fill_Display(unsigned int Color)
{
	Fill_all(Color);
}
void Fill_Rectangle(unsigned int Color, unsigned int StartX, unsigned int StopX, unsigned int StartY, unsigned int StopY)
{
	Fill_rectangle(Color, StartX, StopX, StartY, StopY);
}


void Show_to_layer(char Layer)
{
	Show(Layer);
}

