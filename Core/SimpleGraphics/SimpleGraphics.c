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

void Pixel(uint16 x, uint16 y, uint32 Color, uint16 Tolshina)
{
  uint16 i, j, tolsx, tolsy;
  x--; y--;
  tolsy = y+Tolshina;
  tolsx = x+Tolshina;
  for(i = y; i<tolsy; i++)
  {
	  for(j = x; j<tolsx; j++)
	  {
		  if(i < DispHeight && j < DispWidth)
		  {
			  MemPoint(j,i,Color);
	      }
	  }
  }
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


void Line(int16 x1, int16 y1, int16 x2, int16 y2, uint32 Color, uint16 Tolshina)//++
{
   uint16 y = 0, k = 0;
   if(x1 <= x2)
   {
	   if(y1 <= y2)
	   {
		   if(x2 - x1 != 0)
		   {
		       k = (y2 - y1)/(x2 - x1);
		       if((y2 - y1)%(x2 - x1) != 0)
		       {
		    	   if(Tolshina == 1)
		    	   {
		    	       k++;
		           }
		       }
		   }
		   else
		   {
			   k = 1;
			   x2++;
		   }

		   if(k == 0)
		   { k = 1; }

		   for(uint16 xp = x1; xp <= x2; xp++)
		   {
			   y = (xp - x1) * (y2 - y1) / (x2 - x1) + y1;
			   for(uint16 yp = 0; yp < k; yp++)
			   {
				   Pixel(xp, y, Color, Tolshina);
				   y++;
				   if(y > DispHeight)
				   {break; }
			   }
		   }
	   }
	   else
	   {
		   if(x2 - x1 != 0)
		   {
		       k = (y1 - y2)/(x2 - x1);
		       if((y1 - y2)%(x2 - x1) != 0)
		       {
		    	   if(Tolshina == 1)
	    	       {
	    	           k++;
	               }
		       }
		   }
		   else
		   {
			   k = 1;
			   x2++;
		   }

		   if(k == 0)
		   { k = 1; }

		   for(uint16 xp = x1; xp <= x2; xp++)
		   {
			   y = (xp - x1) * (y2 - y1) / (x2 - x1) + y1;
			   for(uint16 yp = 0; yp < k; yp++)
			   {
				   Pixel(xp, y, Color, Tolshina);
				   y--;
				   if(y > DispHeight)
				   {break; }
			   }
		   }
	   }
   }
   else
   {
	   if(y1 <= y2)
	   {
		   if(x1 - x2 != 0)
		   {
		       k = (y2 - y1)/(x1 - x2);
		       if((y2 - y1)%(x1 - x2) != 0)
		       {
		    	   if(Tolshina == 1)
		    	   {
		    	       k++;
		           }
               }
		   }
		   else
		   {
			   k = 1;
			   x1++;
		   }

		   if(k == 0)
		   { k = 1; }

		   for(uint16 xp = x2; xp <= x1; xp++)
		   {
			   y = (xp - x1) * (y2 - y1) / (x2 - x1) + y1;
			   for(uint16 yp = 0; yp < k; yp++)
			   {
				   Pixel(xp, y, Color, Tolshina);
				   y++;
				   if(y > DispHeight)
				   {break; }
			   }
		   }
	   }
	   else
	   {
		   if(x2 - x1 != 0)
		   {
		       k = (y1 - y2)/(x2 - x1);
		       if((y1 - y2)%(x2 - x1) != 0)
		       {
		    	   if(Tolshina == 1)
	    	       {
	    	           k++;
	               }
		       }
		   }
		   else
		   {
			   k = 1;
			   x2++;
		   }

		   if(k == 0)
		   { k = 1; }

		   for(uint16 xp = x2; xp <= x1; xp++)
		   {
			   y = (xp - x1) * (y2 - y1) / (x2 - x1) + y1;
			   for(uint16 yp = 0; yp < k; yp++)
			   {
				   Pixel(xp, y, Color, Tolshina);
				   y++;
				   if(y > DispHeight)
				   {break; }
			   }
		   }
	   }
   }
}

void Circle (int16 x1, int16 y1, int16 r,uint32 Color, uint16 Tolshina)
{
    int x = -r, y = 0, err = 2-2*r, e2;
	do {
		Pixel(x1-x, y1+y,Color,Tolshina);
		Pixel(x1+x, y1+y,Color,Tolshina);
		Pixel(x1+x, y1-y,Color,Tolshina);
		Pixel(x1-x, y1-y,Color,Tolshina);
		e2 = err;
		if (e2 <= y) {
			err += ++y*2+1;
			if (-x == y && e2 <= x) e2 = 0;
		}
		if (e2 > x) err += ++x*2+1;
	} while (x <= 0);
}

void FillCircle(uint16 x1, uint16 y1, uint16 r, uint32 Color)//
{
  uint16 r1 = r;
  while(r1 != 0)
  {
      Circle(x1,y1,r1,Color,2);
      r1--;
  }
}

void Progress_bar(uint16 XStart, uint16 XEnd, uint16 YStart, uint16 YEnd, uint16 StartPos, uint16 StopPos, uint16 CurrPos, uint32 BorderColor, uint32 FloodColor, uint32 BarColor, uint16 Tolshina, uint8 Orient)
{
  uint16 Tr = Tolshina - 1;
  float STPOS;
  float POSCOUNT;
  uint16 XPOS = 0, YPOS = 0;
  uint16 POSN = CurrPos - StartPos;

  if(Orient == Horisontal)
  {
      if(CurrPos == 1)
      {
         STPOS = StopPos - StartPos;
         POSCOUNT = (XEnd - XStart)/STPOS;
         XPOS = (uint16)((POSN - StartPos * POSCOUNT)+ XStart + 1 + Tr);
      }

      if(CurrPos == StartPos)
      {
         STPOS = StopPos - StartPos;
         POSCOUNT = (XEnd - XStart)/STPOS;
         XPOS = (uint16)((POSN * POSCOUNT)+ XStart + Tr);
      }

      if(CurrPos > StartPos)
      {
         STPOS = StopPos - StartPos;
         POSCOUNT = (XEnd - XStart)/STPOS;
         XPOS = (uint16)((POSN * POSCOUNT)+ XStart);
      }
  }
  else
  {
      STPOS = StopPos - StartPos;
      POSCOUNT = (YEnd - YStart)/STPOS;
      YPOS = (uint16)(YEnd - (POSN * POSCOUNT));
      YPOS += Tolshina;
  }

  if(Orient == Horisontal)
  {
      FramePanel(BorderColor,FloodColor,XStart,XEnd,YStart, YEnd,Tolshina);
      Fill_Rectangle(BarColor,XStart + 1 + Tr,XPOS-1,YStart + 1 + Tr,YEnd - Tr - 1);
  }
  else
  {
	  FramePanel(BorderColor,FloodColor,XStart,XEnd,YStart, YEnd,Tolshina);
	  Fill_Rectangle(BarColor, XStart + 1 + Tr,XEnd - Tr - 1, YPOS, YEnd - Tr - 1);
  }
}



//для внешнего пользования(прикладных программ) Обработка касаний, координатных штучек

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

void LCD_Circle(D_Circle *circle)
{
	Circle(circle->X1, circle->Y1, circle->R, circle->Color, circle->Thickness);
}

void LCD_Line(D_Line *line)
{
    Line(line->X1, line->Y1, line->X2, line->Y2, line->Color, line->Thickness);
}

void LCD_FillCircle(D_FillCircle *fillCircle)
{
	FillCircle(fillCircle->X1, fillCircle->Y1, fillCircle->R, fillCircle->Color);
}

void LCD_ProgressBar(D_ProgressBar *ProgressBar)
{
	Progress_bar(ProgressBar->X1, ProgressBar->X2, ProgressBar->Y1, ProgressBar->Y2, ProgressBar->StartValue, ProgressBar->StopValue, ProgressBar->CurrentValue, ProgressBar->FrameColor, ProgressBar->FillColor, ProgressBar->BarColor, ProgressBar->Thickness, ProgressBar->Orientation);
}





