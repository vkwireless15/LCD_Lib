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
         XPOS = (uint16)((POSN * POSCOUNT)+ XStart - Tr);
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

void CheckBox(int16 x1, int16 x2, int16 y1, int16 y2, uint32 BrColor, uint32 BackColor, uint32 ChColor, uint8 Checked)
{
	FramePanel(BrColor,BackColor,x1,x2,y1,y2,2);
	if(Checked == 1)
	{
		Line(x1+3, y1+6, x1+((x2-x1)/2), y2-3, ChColor, 2);
		Line(x1+((x2-x1)/2), y2-3, x2-3, y1+3, ChColor, 2);
	}
}

void TrackBar(int16 XStart, int16 XEnd, int16 YStart, int16 YEnd, int16 StartPos, int16 StopPos, int16 CurrPos, int32 BorderColor, uint32 FloodColor, uint32 TrackerColor, uint8 Orient, uint8 Rad)
{
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
	         XPOS = (uint16)((POSN - StartPos * POSCOUNT)+ XStart + 1);
	      }

	      if(CurrPos == StartPos)
	      {
	         STPOS = StopPos - StartPos;
	         POSCOUNT = (XEnd - XStart)/STPOS;
	         XPOS = (uint16)((POSN * POSCOUNT)+ XStart);
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
	  }

	  if(Orient == Horisontal)
	  {
	      FramePanel(BorderColor,FloodColor,XStart,XEnd,YStart, YEnd,1);
	      FillCircle(XPOS,YStart + (YEnd - YStart) / 2, Rad, TrackerColor);
	  }
	  else
	  {
		  FramePanel(BorderColor,FloodColor,XStart,XEnd,YStart, YEnd,1);
		  FillCircle(XStart + ((XEnd - XStart) / 2),YPOS,Rad,TrackerColor);
	  }
}

void VGradA(int16 x1, int16 x2, int16 y1, int16 y2, int32 ColorH, int32 ColorL)//
{
    float HRed, HGreen, HBlue;
    float LRed, LGreen, LBlue;
    y1-=1;
    x1-=1;

	if(ColorType == Color565)
	{ ColorH = Get565Color(ColorH); ColorL = Get565Color(ColorL);}

	if(ColorType == Color888)
	{ ColorH = ColorH | 0xFF << 24; ColorL = ColorL | 0xFF << 24; }

	if(x1 < 1){x1 = 1;}
	if(x2 > DispWidth){ x2 = DispWidth;}
	if(y1 < 1){ y1 = 1;}
	if(y2 > DispHeight){ y2 = DispHeight;}

    if(ColorType != Color565)
    {
       HBlue = ColorH & 0x000000ff;
       ColorH = ColorH>>8;
       HGreen = ColorH & 0x000000ff;
       ColorH = ColorH>>8;
       HRed = ColorH & 0x000000ff;

       LBlue = ColorL & 0x000000ff;
       ColorL = ColorL>>8;
       LGreen = ColorL & 0x000000ff;
       ColorL = ColorL>>8;
       LRed = ColorL & 0x000000ff;
    }
    else
    {
        HBlue = ColorH & 0x0000001f;
        ColorH = ColorH>>5;
        HGreen = ColorH & 0x0000003f;
        ColorH = ColorH>>6;
        HRed = ColorH & 0x0000001f;

        LBlue = ColorL & 0x0000001f;
        ColorL = ColorL>>5;
        LGreen = ColorL & 0x0000003f;
        ColorL = ColorL>>6;
        LRed = ColorL & 0x0000001f;
    }

    uint32 Res_Color, promej_zn;
    float Mix;

    for(int16 i = y1; i<y2; i++)
    {
     Mix = (float)(i - y1) / (float)(y2 - y1);

     if(ColorType != Color565)
     {
        Res_Color = HRed * (1 - Mix) + LRed * (Mix);
        Res_Color <<= 8;

        promej_zn = HGreen * (1 - Mix) + LGreen * (Mix);
        Res_Color |= promej_zn;
        Res_Color <<= 8;
        promej_zn = HBlue * (1 - Mix) + LBlue * (Mix);
        Res_Color |= promej_zn;
     }
     else
     {
         Res_Color = HRed * (1 - Mix) + LRed * (Mix);
         Res_Color <<= 6;
         promej_zn = HGreen * (1 - Mix) + LGreen * (Mix);
         Res_Color |= promej_zn;
         Res_Color <<= 5;
         promej_zn = HBlue * (1 - Mix) + LBlue * (Mix);
         Res_Color |= promej_zn;
     }

     for(int16 j = x1; j<x2; j++)
     {
          MemPoint(j,i,Res_Color);
     }
   }
}

void HGradA(int16 x1, int16 x2, int16 y1, int16 y2, int32 ColorH, int32 ColorL)//++
{
    float HRed, HGreen, HBlue;
    float LRed, LGreen, LBlue;
    y1-=1;
    x1-=1;

	if(ColorType == Color565)
	{ ColorH = Get565Color(ColorH); ColorL = Get565Color(ColorL);}

	if(ColorType == Color888)
	{ ColorH = ColorH | 0xFF << 24; ColorL = ColorL | 0xFF << 24; }

	if(x1 < 1){x1 = 1;}
	if(x2 > DispWidth){ x2 = DispWidth;}
	if(y1 < 1){ y1 = 1;}
	if(y2 > DispHeight){ y2 = DispHeight;}

    if(ColorType != Color565)
    {
       HBlue = ColorH & 0x000000ff;
       ColorH = ColorH>>8;
       HGreen = ColorH & 0x000000ff;
       ColorH = ColorH>>8;
       HRed = ColorH & 0x000000ff;

       LBlue = ColorL & 0x000000ff;
       ColorL = ColorL>>8;
       LGreen = ColorL & 0x000000ff;
       ColorL = ColorL>>8;
       LRed = ColorL & 0x000000ff;
    }
    else
    {
        HBlue = ColorH & 0x0000001f;
        ColorH = ColorH>>5;
        HGreen = ColorH & 0x0000003f;
        ColorH = ColorH>>6;
        HRed = ColorH & 0x0000001f;

        LBlue = ColorL & 0x0000001f;
        ColorL = ColorL>>5;
        LGreen = ColorL & 0x0000003f;
        ColorL = ColorL>>6;
        LRed = ColorL & 0x0000001f;
    }

    uint32 Res_Color, promej_zn;
    float Mix;

    for(uint16 i = x1; i<x2; i++)
    {
     if(i > x2 - 1)
     {i = DispWidth;}

     Mix = (float)(i - x1) / (float)(x2 - x1);

     if(ColorType != Color565)
     {
         Res_Color = HRed * (1 - Mix) + LRed * (Mix);
         Res_Color <<= 8;
         promej_zn = HGreen * (1 - Mix) + LGreen * (Mix);
         Res_Color |= promej_zn;
         Res_Color <<= 8;
         promej_zn = HBlue * (1 - Mix) + LBlue * (Mix);
         Res_Color |= promej_zn;
     }
     else
     {
         Res_Color = HRed * (1 - Mix) + LRed * (Mix);
         Res_Color <<= 6;
         promej_zn = HGreen * (1 - Mix) + LGreen * (Mix);
         Res_Color |= promej_zn;
         Res_Color <<= 5;
         promej_zn = HBlue * (1 - Mix) + LBlue * (Mix);
         Res_Color |= promej_zn;
     }


     for(int16 j = y1; j<y2; j++)
     {
         MemPoint(i,j,Res_Color);
     }
   }
}

void VGradB(int16 x1, int16 x2, int16 y1, int16 y2, uint32 ColorH, uint32 ColorC, uint32 ColorL)//++
{
 VGradA(x1,x2,y1,y1+((y2 - y1)/2),ColorH,ColorC);
 VGradA(x1,x2,y1+((y2 - y1)/2),y2,ColorC,ColorL);
}
void HGradB(int16 x1, int16 x2, int16 y1, int16 y2, uint32 ColorH, uint32 ColorC, uint32 ColorL)//++
{
 HGradA(x1,x1+((x2 - x1)/2),y1,y2,ColorH,ColorC);
 HGradA(x1+((x2 - x1)/2),x2,y1,y2,ColorC,ColorL);
}

uint8 Inverse(uint8 S)
{
	uint8 K = 0;
	for(uint8 i = 0; i<8; i++)
	{
		if((S & 0x01) != 0)
		{
			K = K | 0x01;
		}
		S = S >> 1;
		if(i<7)
		{
		  K = K << 1;
	    }
	}
	return K;
}

void Symbol(uint16 X, uint16 Y, uint16 *NextX, uint16 *NextY, uint8 *CharWt, uint8 *CharHt, uint32 Color, char Symbol)
{
	uint8 FontH = calibri[1];
	uint8 FirstChar = calibri[2];
	uint8 NumOfChar = calibri[3];
	uint8 Cursor = Symbol - FirstChar;
	uint16 SymbStartPos = 4 + NumOfChar;
	uint8 CharW = calibri[Cursor + 4];
	uint16 i, j, k = 0;
	uint32 CharBit = 0;

	*NextX = X + CharW;
	*NextY = Y + FontH;
	*CharWt = CharW;
	*CharHt = FontH;
	for(i = 4; i < Cursor + 4; i++)
	{
	   	if(calibri[i] <= 8)
	   	{
	   	   SymbStartPos += FontH;
	   	}

	   	if(calibri[i] > 8 && calibri[i] <= 16)
		{
	   		SymbStartPos += FontH * 2;
		}

	   	if(calibri[i] > 16 && calibri[i] <= 24)
		{
	   		SymbStartPos += FontH * 3;
		}
	   	if(calibri[i] > 24 && calibri[i] <= 32)
		{
	   		SymbStartPos += FontH * 4;
		}
	}

	for(i = Y; i < Y + FontH; i++)
	{
		if(CharW <= 8)
		{
			CharBit = Inverse(calibri[SymbStartPos + k]);
			CharBit = CharBit << 24;
			k++;
		}
		if(CharW > 8 && CharW <= 16)
		{
			CharBit = Inverse(calibri[SymbStartPos + k]);
			k++;
			CharBit = CharBit << 8;
			CharBit = CharBit | Inverse(calibri[SymbStartPos + k]);
			CharBit = CharBit << 16;
			k++;
		}
		if(CharW > 16 && CharW <= 24)
		{
			CharBit = Inverse(calibri[SymbStartPos + k]);
			k++;
			CharBit = CharBit << 8;
			CharBit = CharBit | Inverse(calibri[SymbStartPos + k]);
			k++;
			CharBit = CharBit << 8;
			CharBit = CharBit | Inverse(calibri[SymbStartPos + k]);
			CharBit = CharBit << 8;
			k++;
		}
		if(CharW > 24 && CharW <= 32)
		{
			CharBit = Inverse(calibri[SymbStartPos + k]);
			k++;
			CharBit = CharBit << 8;
			CharBit = CharBit | Inverse(calibri[SymbStartPos + k]);
			k++;
			CharBit = CharBit << 8;
			CharBit = CharBit | Inverse(calibri[SymbStartPos + k]);
			k++;
			CharBit = CharBit << 8;
			CharBit = CharBit | Inverse(calibri[SymbStartPos + k]);
			k++;
		}


		for(j = X; j < X + CharW; j++)
		{
            if((CharBit & 0x80000000) != 0)
            {
      		    if(i < DispHeight && j < DispWidth)
      		    {
      		    	MemPoint(j,i,Color);
      	        }
            }
            CharBit = CharBit << 1;
		}
	}
}
uint32 SymbolLength(char String[])
{
	uint8 FirstChar = calibri[2];
	uint8 Cursor = 0;
	uint8 CharW = 0;
	uint32 Len = 0;
	uint32 SymCh = 0;

	while(String[SymCh] != 0)
	{
		Cursor = String[SymCh] - FirstChar;
		CharW = calibri[Cursor + 4];
		Len += CharW;
		SymCh++;
	}
	return Len;
}
uint8 RU_EN_UTF16ToASCII(char S1, char S2)
{
	char S = S2 - 16;

	if(S1 == 0xD1 && S2 == 145)
	{
		return 184;
	}

	if(S1 == 0xD0 && S2 == 129)
	{
		return 168;
	}

	if(S <= 175 && S>= 128)
	{
	    return S2 + 48;
    }
	else
	{
		return S + 128;
	}
	return Error;
}
void Get1251(char Str[])
{
	 uint32 W1 = 0, cnt = 0;
	 while(Str[W1] != 0)
	 { W1++ ;}

	 for(uint32	s = 0; s < W1;)
	 {
		 if(Str[s] == 0xD0 || Str[s] == 0xD1)
		 {
			 Str[cnt] = RU_EN_UTF16ToASCII(Str[s], Str[s+1]);
			 if(s!=cnt)
			 {
				 Str[s] = 0;
				 Str[s + 1] = 0;
			 }
			 cnt++;
			 s+=2;
		 }
		 else
		 {
			 Str[cnt] = Str[s];
			 if(s!=cnt)
			 {
				 Str[s] = 0;
			 }
			 cnt++;
			 s++;
		 }
	 }
}
void Label (uint16 X, uint16 Y, uint32 Color, char String[])//++
{
  uint16 Nx = 0, Ny = 0;
  uint16 Sym = 0;
  uint8 ChW = 0;
  uint8 ChH = 0;
  while(String[Sym]!=0)
  {
  	Sym++;
  }
  for(uint16 i = 0; i<Sym; i++)
  {
  	if(String[i]>= 0x20 && String[i]<= 0xFF)
  	{

  		Symbol(X, Y, &Nx, &Ny,&ChW,&ChH, Color, String[i]);

  		if(X + ChW < DispWidth)
  		{
  		   X = Nx;
  	    }
  		else
  		{
  			break;
  		}

  	}
  }

}
void Form(uint16 x1, uint16 x2, uint16 y1, uint16 y2, uint16 y_S, uint16 TolshinaB, uint32 ColorL, uint32 ColorS, uint32 ColorW,uint32 ColorT,char FormName[])//++
{
  uint16 k = TolshinaB - 1,txty;
  txty = y1+((y1+y_S - y1)/2 - 8);

  Fill_Rectangle(ColorW,x1,x2,y1,y2);
  Fill_Rectangle(ColorS,x1,x2,y1,y1+y_S);
  VLine(ColorL,x1,y1,y2,TolshinaB);
  VLine(ColorL,x2-k,y1,y2,TolshinaB);
  HLine(ColorL,x1,x2,y1,TolshinaB);
  HLine(ColorL,x1,x2,y2-k,TolshinaB);
  HLine(ColorL,x1+k,x2 - k,y_S+y1,TolshinaB);
  Label(x1+k+2,txty+k,ColorT,FormName);
}
void Button(uint16 x1, uint16 x2, uint16 y1, uint16 y2, uint16 TolshinaB, uint32 BorderColor, uint32 BtColor, char Text[],uint32 TextColor)//++
{
  uint16 txtX, txtY, g = 0;
  txtY = y1+((y2 - y1)/2 - 8);
  g = SymbolLength(Text);
  txtX = x1+((x2 - x1)/2)-(g/2);
  FramePanel(BorderColor,BtColor,x1,x2,y1,y2,TolshinaB);
  Label(txtX, txtY, TextColor,Text);
}
void GradientFormA(uint16 x1, uint16 x2, uint16 y1, uint16 y2, uint16 y_S, uint16 TolshinaB, uint32 ColorL, uint32 ColorSH, uint32 ColorSL, uint32 ColorW,uint32 ColorT,char FormName[])//++
{
  uint16 k = TolshinaB - 1,txty, g = 0;
  txty = y1+((y1+y_S - y1)/2 - 8);
  for(int i = 0 ; i<50; i++)
  {
    if(FormName[i] >= 0x20 && FormName[i] <= 0x7f)
    {g++;}
    else
    {i = 50;}
  }
  Fill_Rectangle(ColorW,x1,x2,y1,y2);
  HGradA(x1,x2,y1,y1+y_S,ColorSH,ColorSL);
  VLine(ColorL,x1,y1,y2,TolshinaB);
  VLine(ColorL,x2-k,y1,y2,TolshinaB);
  HLine(ColorL,x1,x2,y1,TolshinaB);
  HLine(ColorL,x1,x2,y2-k,TolshinaB);
  HLine(ColorL,x1+k,x2 - k,y_S+y1,TolshinaB);
  Label(x1+k+2,txty+k,ColorT,FormName);
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

uint8 LCD_CheckBox(D_CheckBox *ctrl)
{
//	uint8 TouchDet = GetCursorPosition();
	CheckBox(ctrl->X1, ctrl->X2, ctrl->Y1, ctrl->Y2, ctrl->FrameColor, ctrl->BackColor, ctrl->CheckColor, ctrl->Checked);
	/*if(CursorX >= ctrl->X1 && CursorX <= ctrl->X2 && CursorY >= ctrl->Y1 && CursorY <= ctrl->Y2 && TouchDet == Clicked)
	{
		ctrl->Is_pressed = Clicked;
	 	return Clicked;
	}
	else
	{
		if(TouchDet == NotClicked)
		{
		    if(CursorX >= ctrl->X1 && CursorX <= ctrl->X2 && CursorY >= ctrl->Y1 && CursorY <= ctrl->Y2 && TouchDet == NotClicked)
		    {
		    	if(ctrl->Is_pressed == Clicked)
		    	{
		    		if(ctrl->Checked == 0)
		    		{ctrl->Checked = 1;}
		    		else
		    		{ctrl->Checked = 0;}
		    		ctrl->Is_pressed = NotClicked;
			        return Unclicked;
		    	}
		    }
	    }
		else
		{
			return NotClicked;
		}
	}*/
	return NotClicked;
}

uint8 LCD_TrackBar(D_TrackBar *trackBar)
{
//	uint8 TouchDet = GetCursorPosition();
//	uint16 Xdif, ValDif;
	TrackBar(trackBar->X1, trackBar->X2, trackBar->Y1, trackBar->Y2, trackBar->StartValue, trackBar->StopValue, trackBar->CurrentValue, trackBar->FrameColor, trackBar->BackColor, trackBar->TrackerColor, trackBar->Orientation, trackBar->Radius);
//	if(CursorX >= trackBar->X1 && CursorX <= trackBar->X2 && CursorY >= trackBar->Y1 && CursorY <= trackBar->Y2 && TouchDet == Clicked)
//	{
//		if(trackBar->Orientation == Horisontal)
//		{
//		    trackBar->Is_pressed = Clicked;
//		    Xdif = trackBar->X2 - trackBar->X1;
//		    ValDif = trackBar->StopValue - trackBar->StartValue;
//		    trackBar->CurrentValue = (CursorX - trackBar->X1) * ValDif / Xdif;
//		    if(CursorX <= trackBar->X2 && CursorX >= trackBar->X2 - 3)
//		    {trackBar->CurrentValue = trackBar->StopValue;}
//	 	    return Clicked;
//	    }
//		else
//		{
//		    trackBar->Is_pressed = Clicked;
//		    Xdif = trackBar->Y2 - trackBar->Y1;
//		    ValDif = trackBar->StopValue - trackBar->StartValue;
//		    trackBar->CurrentValue = trackBar->StopValue - ((CursorY - trackBar->Y1) * ValDif / Xdif);
//		    if(CursorY <= trackBar->Y2 && CursorY >= trackBar->Y2 - 3)
//		    {trackBar->CurrentValue = trackBar->StartValue;}
//	 	    return Clicked;
//		}
//	}
//	else
//	{
//		if(TouchDet == NotClicked)
//		{
//		    if(CursorX >= trackBar->X1 && CursorX <= trackBar->X2 && CursorY >= trackBar->Y1 - 5 && CursorY <= trackBar->Y1 + 5 && TouchDet == NotClicked)
//		    {
//		    	if(trackBar->Is_pressed == Clicked)
//		    	{
//		    		trackBar->Is_pressed = NotClicked;
//			        return Unclicked;
//		    	}
//		    }
//	    }
//		else
//		{
//			return NotClicked;
//		}
//	}
	return NotClicked;
}

uint8 LCD_VGradient(D_VGradient *VGradient)
{
	//uint8 TouchDet = GetCursorPosition();
	VGradA(VGradient->X1, VGradient->X2, VGradient->Y1, VGradient->Y2, VGradient->ColorH, VGradient->ColorL);

//	if(CursorX >= VGradient->X1 && CursorX <= VGradient->X2 && CursorY >= VGradient->Y1 && CursorY <= VGradient->Y2 && TouchDet == Clicked)
//	{
//		VGradient->Is_pressed = Clicked;
//	 	return Clicked;
//	}
//	else
//	{
//		if(TouchDet == NotClicked)
//		{
//		    if(CursorX >= VGradient->X1 && CursorX <= VGradient->X2 && CursorY >= VGradient->Y1 && CursorY <= VGradient->Y2 && TouchDet == NotClicked)
//		    {
//		    	if(VGradient->Is_pressed == Clicked)
//		    	{
//		    		VGradient->Is_pressed = NotClicked;
//			        return Unclicked;
//		    	}
//		    }
//	    }
//		else
//		{
//			return NotClicked;
//		}
//	}
	return NotClicked;
}

uint8 LCD_HGradient(D_HGradient *HGradient)
{
//	uint8 TouchDet = GetCursorPosition();
	HGradA(HGradient->X1, HGradient->X2, HGradient->Y1, HGradient->Y2, HGradient->ColorH, HGradient->ColorL);
//	if(CursorX >= HGradient->X1 && CursorX <= HGradient->X2 && CursorY >= HGradient->Y1 && CursorY <= HGradient->Y2 && TouchDet == Clicked)
//	{
//		HGradient->Is_pressed = Clicked;
//	 	return Clicked;
//	}
//	else
//	{
//		if(TouchDet == NotClicked)
//		{
//		    if(CursorX >= HGradient->X1 && CursorX <= HGradient->X2 && CursorY >= HGradient->Y1 && CursorY <= HGradient->Y2 && TouchDet == NotClicked)
//		    {
//		    	if(HGradient->Is_pressed == Clicked)
//		    	{
//		    		HGradient->Is_pressed = NotClicked;
//			        return Unclicked;
//		    	}
//		    }
//	    }
//		else
//		{
//			return NotClicked;
//		}
//	}
	return NotClicked;
}
uint8 LCD_DualVGradient(D_DualVGradient *DualVGradient)
{
//	uint8_t TouchDet = GetCursorPosition();
	VGradB(DualVGradient->X1, DualVGradient->X2, DualVGradient->Y1, DualVGradient->Y2, DualVGradient->ColorH, DualVGradient->ColorC, DualVGradient->ColorL);
//	if(CursorX >= DualVGradient->X1 && CursorX <= DualVGradient->X2 && CursorY >= DualVGradient->Y1 && CursorY <= DualVGradient->Y2 && TouchDet == Clicked)
//	{
//		DualVGradient->Is_pressed = Clicked;
//	 	return Clicked;
//	}
//	else
//	{
//		if(TouchDet == NotClicked)
//		{
//		    if(CursorX >= DualVGradient->X1 && CursorX <= DualVGradient->X2 && CursorY >= DualVGradient->Y1 && CursorY <= DualVGradient->Y2 && TouchDet == NotClicked)
//		    {
//		    	if(DualVGradient->Is_pressed == Clicked)
//		    	{
//		    		DualVGradient->Is_pressed = NotClicked;
//			        return Unclicked;
//		    	}
//		    }
//	    }
//		else
//		{
//			return NotClicked;
//		}
//	}
	return NotClicked;
}
uint8 LCD_DualHGradient(D_DualHGradient *DualHGradient)
{
//	uint8_t TouchDet = GetCursorPosition();
	HGradB(DualHGradient->X1, DualHGradient->X2, DualHGradient->Y1, DualHGradient->Y2, DualHGradient->ColorH, DualHGradient->ColorC, DualHGradient->ColorL);
//	if(CursorX >= DualHGradient->X1 && CursorX <= DualHGradient->X2 && CursorY >= DualHGradient->Y1 && CursorY <= DualHGradient->Y2 && TouchDet == Clicked)
//	{
//		DualHGradient->Is_pressed = Clicked;
//	 	return Clicked;
//	}
//	else
//	{
//		if(TouchDet == NotClicked)
//		{
//		    if(CursorX >= DualHGradient->X1 && CursorX <= DualHGradient->X2 && CursorY >= DualHGradient->Y1 && CursorY <= DualHGradient->Y2 && TouchDet == NotClicked)
//		    {
//		    	if(DualHGradient->Is_pressed == Clicked)
//		    	{
//		    		DualHGradient->Is_pressed = NotClicked;
//			        return Unclicked;
//		    	}
//		    }
//	    }
//		else
//		{
//			return NotClicked;
//		}
//	}
	return NotClicked;
}
void LCD_Label(D_Label *label, char Text[])
{
    Label(label->X, label->Y, label->Color, Text);
}
uint8 LCD_Form(D_Form *form, char Text[])
{
	//uint8 TouchDet = GetCursorPosition();
	Form(form->X1, form->X2, form->Y1, form->Y2, form->YBar, form->Thickness, form->FrameColor, form->BarColor, form->WindowColor, form->TextColor, Text);
//	if(CursorX >= form->X1 && CursorX <= form->X2 && CursorY >= form->Y1 && CursorY <= form->YBar && TouchDet == Clicked)
//	{
//		form->Is_pressed = Clicked;
//	 	return Clicked;
//	}
//	else
//	{
//		if(TouchDet == NotClicked)
//		{
//		    if(CursorX >= form->X1 && CursorX <= form->X2 && CursorY >= form->Y1 && CursorY <= form->YBar && TouchDet == NotClicked)
//		    {
//		    	if(form->Is_pressed == Clicked)
//		    	{
//		    		form->Is_pressed = NotClicked;
//			        return Unclicked;
//		    	}
//		    }
//	    }
//		else
//		{
//			form->Is_pressed = NotClicked;
//			return NotClicked;
//		}
//	}
	return NotClicked;
}
uint8 LCD_Button(D_Button *button, char Text[])
{
//	uint8 TouchDet = GetCursorPosition();
//	if(CursorX >= button->X1 && CursorX <= button->X2 && CursorY >= button->Y1 && CursorY <= button->Y2 && TouchDet == Clicked)
//	{
//		button->Is_pressed = Clicked;
//		Button(button->X1, button->X2, button->Y1, button->Y2, button->Thickness, button->FrameColor, button->PressedColor, Text, button->TextColor);
//	 	return Clicked;
//	}
//	else
//	{
		Button(button->X1, button->X2, button->Y1, button->Y2, button->Thickness, button->FrameColor, button->FillColor, Text, button->TextColor);
//		if(TouchDet == NotClicked)
//		{
//		    if(CursorX >= button->X1 && CursorX <= button->X2 && CursorY >= button->Y1 && CursorY <= button->Y2 && TouchDet == NotClicked)
//		    {
//		    	if(button->Is_pressed == Clicked)
//		    	{
//		    		button->Is_pressed = NotClicked;
//			        return Unclicked;
//		    	}
//		    }
//	    }
//		else
//		{
//			return NotClicked;
//		}
//	}
	return NotClicked;
}
uint8 LCD_HGradientForm(D_HGradientForm *HGradientForm, char Text[])
{
	//uint8 TouchDet = GetCursorPosition();
	GradientFormA(HGradientForm->X1, HGradientForm->X2, HGradientForm->Y1, HGradientForm->Y2, HGradientForm->YBar, HGradientForm->Thickness, HGradientForm->FrameColor, HGradientForm->BarColorH, HGradientForm->BarColorL, HGradientForm->WindowColor, HGradientForm->TextColor, Text);
//	if(CursorX >= HGradientForm->X1 && CursorX <= HGradientForm->X2 && CursorY >= HGradientForm->Y1 && CursorY <= HGradientForm->YBar && TouchDet == Clicked)
//	{
//		HGradientForm->Is_pressed = Clicked;
//	 	return Clicked;
//	}
//	else
//	{
//		if(TouchDet == NotClicked)
//		{
//		    if(CursorX >= HGradientForm->X1 && CursorX <= HGradientForm->X2 && CursorY >= HGradientForm->Y1 && CursorY <= HGradientForm->YBar && TouchDet == NotClicked)
//		    {
//		    	if(HGradientForm->Is_pressed == Clicked)
//		    	{
//		    		HGradientForm->Is_pressed = NotClicked;
//			        return Unclicked;
//		    	}
//		    }
//	    }
//		else
//		{
//			HGradientForm->Is_pressed = NotClicked;
//			return NotClicked;
//		}
//	}
	return NotClicked;
}
