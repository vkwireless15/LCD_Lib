#include "SimpleGraphics.h"
#include "Graphics_IO.h"
#include "Coordinates.h"
#include "Font.h"

uint32 DispHeight = 0, DispWidth = 0;
uint8 ColorType = Color565;

uint32 Color_A888_(uint32 Color, uint8 Alpha)
{
	return Color | Alpha << 24;
}
uint32 FontHParameter()
{
	uint8 FontH = calibri[1];
	return FontH;
}
uint16 Get565Color(uint32 Color)
{
   uint16 RezColor = 0;
   uint8 R, G, B;
   R = (Color >> 16) & 0xff;
   G = (Color >> 8) & 0xff;
   B = Color & 0xff;

   R = 31 * R / 255;
   G = 63 * G / 255;
   B = 31 * B / 255;

   RezColor |= B;
   RezColor |= (G << 5);
   RezColor |= (R << 11);

   return RezColor;
}
void Set_Backlight(uint8 State, uint32 Brightness)
{
	Backlight(Brightness, State);
}
uint8 is_Disp_Res(int32 x1, int32 x2, int32 y1, int32 y2)
{
	if((x1 > 0)&&(x2 <= DispWidth))
	{
		if((y1 > 0)&&(y2 <= DispHeight))
		{
			return Ok;
		}
	}

	if( (x1 > 0) && (x1 <= DispWidth)  )
	{

	}

	return Error;
}

void Graphics_Init(DisplayConfig *dcf)
{
	DispHeight = dcf->Display_Height;
	DispWidth = dcf->Display_Width;
	ColorType = dcf->Color_Type;
	Init_Graphics_System(dcf->Display_Height, dcf->Display_Width, dcf->Start_RAM_Address, dcf->Layers, dcf->Color_Type);
}

void Fill_Display(uint32 Color)
{
	if(ColorType == Color565)
	{ Fill_all(Get565Color(Color)); }

	if(ColorType == Color888)
	{ Fill_all(Color | 0xFF << 24); }

	if(ColorType == Color_A888)
	{ Fill_all(Color); }
}
void Fill_Rectangle(uint32 Color, int32 StartX, int32 StopX, int32 StartY, int32 StopY)
{
	if(is_Disp_Res(StartX, StopX, StartY, StopY) == Ok)
	{
		if(ColorType == Color565)
		{ Fill_rectangle(Get565Color(Color), StartX, StopX, StartY, StopY); }

		if(ColorType == Color888)
		{ Fill_rectangle(Color | 0xFF << 24, StartX, StopX, StartY, StopY); }

		if(ColorType == Color_A888)
		{ Fill_all(Color); }
	}
}


void LCD_Fill_Rectangle(D_Fill_Rectangle *FR)
{
    Fill_Rectangle(FR->Color, FR->X1, FR->X2, FR->Y1, FR->Y2);
}

