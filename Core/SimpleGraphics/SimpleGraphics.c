#include "SimpleGraphics.h"
#include "Graphics_IO.h"
#include "Coordinates.h"
#include "Font.h"

uint32 DispHeight = 0, DispWidth = 0;
uint8 ColorType = Color565;

void Graphics_Init(DisplayConfig *dcf)
{
	DispHeight = dcf->Display_Height;
	DispWidth = dcf->Display_Width;
	ColorType = dcf->Color_Type;
	Init_Graphics_System(dcf->Display_Height, dcf->Display_Width, dcf->Start_RAM_Address, dcf->Layers, dcf->Color_Type);
}
void Set_Backlight(uint8 State, uint32 Brightness)
{
	Backlight(Brightness, State);
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

void Fill_Display(uint32 Color)
{
	Fill_all(Color);
}
void Fill_Rectangle(uint32 Color, uint32 StartX, uint32 StopX, uint32 StartY, uint32 StopY)
{
	Fill_rectangle(Color, StartX, StopX, StartY, StopY);
}


void Show_to_layer(uint8 Layer)
{
	Show(Layer);
}

