#include "Code.h"
#include "SDRAM.h"
#include "SimpleGraphics.h"


extern LTDC_HandleTypeDef hltdc; // Структура для управления параметрами контроллера дисплея

short unsigned int RGB[272*480]; //Резервируем память для буффера дисплея
DisplayConfig ds;                //Основные параметры библиотеки


void MainFunc ()
{
	  ds.Color_Type = Color565;
	  ds.Display_Height = 272;
	  ds.Display_Width = 480;
	  ds.Layers = 1;
	  ds.Start_RAM_Address = (uint32)&RGB;

	  ds.Window_Frame_Color = red;
	  ds.Window_Bar_Color = lightBlue2;
	  ds.Window_Bar_H_Color = blue;
	  ds.Window_Bar_L_Color = lightBlue4;
	  ds.Window_Color = white;
	  ds.Window_Text_Color = black;
	  ds.Window_Frame_Thickness = 2;

	  ds.Button_Frame_Color = lightBlack2;
	  ds.Button_Color = gray2;
	  ds.Button_Selected_Color = lightBlack3;
	  ds.Button_Text_Color = black;

	  ds.Label_Color = black;
	  ds.Label_Selected_Color = lightBlack2;
	  ds.Label_Background_Color = blue;

	  ds.Bar_Color = darkGreen2;
	  ds.Bar_Color2 = darkViolet2;
	  ds.Bar_Color3 = lightViolet2;


	  HAL_LTDC_SetAddress(&hltdc,(uint32_t)&RGB,0);  // запускаем модуль LTDC (железный)
	  Graphics_Init(&ds); //инит библиотеки (из структуры ds)

	  Fill_Display(black);

	  uint8 k = 0;

	  int16 x = 240, y = 135, r = 15;

	  while(1)
	  {
		  Fill_Display(black);
		  //LCD_FramePanel();

		  k = isTouch();


          if(k == Clicked)
          {
        	  Circle(x, y, r, red, 3);
          }

          if(k == NotClicked)
          {
        	  Circle(x, y, r, gray, 3);
          }


          if(k == LeftSwap)
          {
        	  if(x - TransitionValue() > 0)
        	  { x -= TransitionValue(); }
        	  else
        	  { x = 1;}

        	  Circle(x, y, r, gray, 3);
          }

          if(k == RightSwap)
          {
        	  if(x + TransitionValue() < 480)
        	  { x += TransitionValue(); }
        	  else
        	  { x = 480;}

        	  Circle(x, y, r, gray, 3);
          }

          if(k == UpSwap)
          {
        	  if(y - TransitionValue() > 0)
        	  { y -= TransitionValue(); }
        	  else
        	  { y = 1;}

        	  Circle(x, y, r, gray, 3);
          }

          if(k == DownSwap)
          {
        	  if(y + TransitionValue() < 272)
        	  { y += TransitionValue(); }
        	  else
        	  { y = 272;}
        	  Circle(x, y, r, gray, 3);
          }


          if(k == ZoomIn)
          {
        	  r += 5;
        	  Circle(x, y, r, gray, 3);
          }

          if(k == ZoomOut)
          {
        	  if(r - 5 > 15)
        	  { r -= 5; }
        	  else
        	  { r = 15; }
        	  Circle(x, y, r, gray, 3);
          }

		  HAL_Delay(150);


	  }

}

