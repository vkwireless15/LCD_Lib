#include "SimpleGraphics.h"
#include "Graphics_IO.h"
#include "Coordinates.h"
#include "Font.h"

uint32 DispHeight = 0, DispWidth = 0;
uint8 ColorType = Color565;

uint32 Color_A888_(uint32 Color, uint8 Alpha) //преобразует отдельные значения цвета  и прозрачности в формат А888(альфа канал + 24 бита цвета)
{
	return Color | Alpha << 24;
}
uint32 FontHParameter() //Возвращает значение высоты шрифта
{
	uint8 FontH = calibri[1];
	return FontH;
}
uint16 Get565Color(uint32 Color) //Возвращает значение цвета в формате пикселя 565(5 бит - красный цвет, 6 - зеленый, 5 - синий)
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
void Set_Backlight(uint8 State, uint32 Brightness) //Управление подсветкой и ее яркостью(не поддерживается упр. яркостью для платы STM32F746Disco)
{
	Backlight(Brightness, State);
}
uint8 is_Disp_Res(int32 x1, int32 x2, int32 y1, int32 y2) //
{
	if((x1 > 0)&&(x2 <= DispWidth))
	{
		if((y1 > 0)&&(y2 <= DispHeight))
		{
			return Ok;
		}
	}
	return Error;
}

void Graphics_Init(DisplayConfig *dcf) //Инициализация самой бибиллиотеки а также инициализация графических устройств(дисплей, графические ускорители, тач-панели)
{
	DispHeight = dcf->Display_Height;
	DispWidth = dcf->Display_Width;
	ColorType = dcf->Color_Type;
	Init_Graphics_System(dcf->Display_Height, dcf->Display_Width, dcf->Start_RAM_Address, dcf->Layers, dcf->Color_Type);
}

void Fill_Display(uint32 Color) //Заливает весь дисплей определенным цветом
{

	if(ColorType == Color565)
	{ Fill_all(Get565Color(Color)); }

	if(ColorType == Color888)
	{ Fill_all(Color | 0xFF << 24); }

	if(ColorType == Color_A888)
	{ Fill_all(Color); }
}
void Fill_Rectangle(uint32 Color, int32 StartX, int32 StopX, int32 StartY, int32 StopY) //заливает цветом прямоугольную область
{
	if(((StartX > 0) && (StartX <= DispWidth)) || ((StopX > 0) && (StopX <= DispWidth)))
	{
		if(((StartY > 0) && (StartY <= DispHeight)) || ((StopY > 0) && (StopY <= DispHeight)))
		{
			if(StartX <= 0)
			{ StartX = 1;}
			if(StopX > DispWidth)
			{ StartX = DispWidth;}

			if(StartY <= 0)
			{ StartY = 1;}
			if(StopY > DispHeight)
			{ StartY = DispHeight;}

			if(ColorType == Color565)
			{ Fill_rectangle(Get565Color(Color), StartX, StopX, StartY, StopY); }

			if(ColorType == Color888)
			{ Fill_rectangle(Color | 0xFF << 24, StartX, StopX, StartY, StopY); }

			if(ColorType == Color_A888)
			{ Fill_all(Color); }
		}
	}
}
void HLine(uint32 Color, int16 x1, int16 x2, int16 y1, uint8 Tolshina)//
{
    if(Tolshina > 0)
    {
    	Tolshina--;
    	Fill_Rectangle(Color, x1, x2, y1, y1+Tolshina);
    }
}
void VLine(uint32 Color, int16 x1, int16 y1, int16 y2, uint8 Tolshina)
{
	if(Tolshina > 0)
	{
		Tolshina--;
		Fill_Rectangle(Color, x1, x1+Tolshina, y1, y2);
	}
}
void FramePanel(uint32 BorderColor, uint32 FloodColor, int16 x1, int16 x2, int16 y1, int16 y2, uint8 Tolshina)
{
	Tolshina --;
	Fill_Rectangle(FloodColor,x1,x2,y1,y2);
    HLine(BorderColor,x1,x2,y1,Tolshina + 1);
    HLine(BorderColor,x1,x2,y2 - Tolshina,Tolshina +1);
    VLine(BorderColor,x1,y1,y2,Tolshina + 1);
    VLine(BorderColor,x2 - Tolshina,y1,y2,Tolshina + 1);
}

//для внешнего пользования(прикладныз программ)

void LCD_Fill_Rectangle(D_Fill_Rectangle *FR)
{
    Fill_Rectangle(FR->Color, FR->X1, FR->X2, FR->Y1, FR->Y2);
}
void LCD_HLine(D_HLine *hline)
{
	HLine(hline->Color, hline->X1, hline->X2, hline->Y1, hline->Thickness);
}
void LCD_VLine(D_VLine *vline)
{
	VLine(vline->Color, vline->X1, vline->Y1, vline->Y2, vline->Thickness);
}
uint8 LCD_FramePanel(D_FramePanel *framePanel)
{
	//uint8 TouchDet = GetCursorPosition();
	FramePanel(framePanel->FrameColor, framePanel->FillColor, framePanel->X1, framePanel->X2, framePanel->Y1, framePanel->Y2, framePanel->Thickness);
	/*if(CursorX >= framePanel->X1 && CursorX <= framePanel->X2 && CursorY >= framePanel->Y1 && CursorY <= framePanel->Y2 && TouchDet == Clicked)
	{
		framePanel->Is_pressed = Clicked;
	 	return Clicked;
	}
	else
	{
		if(TouchDet == NotClicked)
		{
		    if(CursorX >= framePanel->X1 && CursorX <= framePanel->X2 && CursorY >= framePanel->Y1 && CursorY <= framePanel->Y2 && TouchDet == NotClicked)
		    {
		    	if(framePanel->Is_pressed == Clicked)
		    	{
		    		framePanel->Is_pressed = NotClicked;
			        return Unclicked;
		    	}
		    }
	    }
		else
		{
			framePanel->Is_pressed = NotClicked;
			return NotClicked;
		}
	} */
	return NotClicked;
}



