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

	  uint8 k = 0;
	  int16 x = 240, y = 135, r = 15;

	  uint8 Refresh = 0;

	  while(1)
	  {
		  Fill_Display(black);
		  Refresh = 1;
		  while(Refresh)
		  {
			  if(LCD_Button(70, 220, 100, 170, "Demo") == Unclicked)
			  {
				  Fill_Display(black);
				  Label(10, 5, green, "Fill Display in Black");
				  HAL_Delay(4000);

				  Fill_Display(black);
				  Label(10, 5, green, "Draw Pixels");
				  Pixel(10, 30, blue, 1);
				  HAL_Delay(500);
				  Pixel(30, 40, blue, 2);
				  HAL_Delay(500);
				  Pixel(50, 50, blue, 3);
				  HAL_Delay(500);
				  Pixel(70, 60, blue, 4);
				  HAL_Delay(500);
				  Pixel(90, 70, blue, 5);
				  HAL_Delay(500);
				  Pixel(110, 80, blue, 6);
				  HAL_Delay(500);
				  Pixel(130, 90, blue, 7);
				  HAL_Delay(500);
				  Pixel(150, 100, blue, 8);
				  HAL_Delay(500);
				  Pixel(170, 110, blue, 9);
				  HAL_Delay(4000);

				  Fill_Display(black);
				  Label(10, 5, green, "Lines");
				  HLine(red, 10, 470, 50, 2);
				  HAL_Delay(500);
				  VLine(green, 100, 5, 267, 4);
				  HAL_Delay(500);
				  Line(30, 30, 450, 242, blue, 6);
				  HAL_Delay(4000);

				  Fill_Display(black);
				  Label(10, 5, green, "Circles");
				  Circle(30, 30, 10, red, 1);
				  HAL_Delay(500);
				  Circle(80, 60, 20, green, 2);
				  HAL_Delay(500);
				  Circle(110, 90, 30, blue, 3);
				  HAL_Delay(500);
				  FillCircle(160, 140, 35, red);
				  HAL_Delay(500);
				  FillCircle(210, 190, 40, green);
				  HAL_Delay(500);
				  FillCircle(260, 240, 50, blue);
				  HAL_Delay(4000);

				  Fill_Display(black);
				  Label(10, 5, green, "Gradient");
				  VGradA(30, 235, 30, 130, red, blue);
				  HAL_Delay(500);
				  HGradA(245, 450, 30, 130, red, blue);
				  HAL_Delay(500);
				  VGradB(30, 235, 140, 260, red, green, blue);
				  HAL_Delay(500);
				  HGradB(245, 450, 140, 260, red, green, blue);
				  HAL_Delay(4000);

				  Fill_Display(black);
				  Label(10, 5, green, "Frame Panel");
				  FramePanel(red, white, 50, 430, 50, 222, 3);
				  HAL_Delay(4000);

				  Form(1, 480, 1, 272, 30, 2, red, lightBlue2, white, green, "Simple form");
				  HAL_Delay(4000);

				  Form(1, 480, 1, 272, 30, 2, red, lightBlue2, white, green, "Horisontal Progress Bar");
				  for(int i = 0; i<100; i++)
				  {
					  Progress_bar(20, 460, 120, 150, 0, 99, i, red, white, violet, 2, Horisontal);
					  Progress_bar_gradient(20, 460, 160, 190, 0, 99, i, red, white, lightTurquoise3, darkTurquoise2, 2, Horisontal);
					  Fill_Rectangle(white, 10, 470, 190, 215);
					  TrackBar(20, 460, 200, 205, 0, 99, i, red, white, violet, Horisontal, 7);
					  HAL_Delay(100);
				  }
				  HAL_Delay(4000);

				  Form(1, 480, 1, 272, 30, 2, red, lightBlue2, white, green, "Vertical Progress Bar");
				  for(int i = 0; i<100; i++)
				  {
					  Progress_bar(20, 50, 35, 260, 0, 99, i, red, white, violet, 2, Vertical);
					  Progress_bar_gradient(70, 100, 35, 260, 0, 99, i, red, white, lightTurquoise3, darkTurquoise2, 2, Vertical);
					  Fill_Rectangle(white, 120, 145, 35, 270);
					  TrackBar(130, 135, 45, 260, 0, 99, i, red, white, violet, Vertical, 7);
					  HAL_Delay(100);
				  }
				  HAL_Delay(4000);

				  Refresh = 0;
			  }

			  if(LCD_Button(260, 410, 100, 170, "Control panel") == Unclicked)
			  {
				  LCD_FramePanel();
				  HAL_Delay(2500);

				  Refresh = 0;
			  }

			  HAL_Delay(100);
		  }






//		  k = isTouch();
//
//
//          if(k == Clicked)
//          {
//        	  Circle(x, y, r, red, 3);
//          }
//
//          if(k == NotClicked)
//          {
//        	  Circle(x, y, r, gray, 3);
//          }
//
//
//          if(k == LeftSwap)
//          {
//        	  if(x - TransitionValue() > 0)
//        	  { x -= TransitionValue(); }
//        	  else
//        	  { x = 1;}
//
//        	  Circle(x, y, r, gray, 3);
//          }
//
//          if(k == RightSwap)
//          {
//        	  if(x + TransitionValue() < 480)
//        	  { x += TransitionValue(); }
//        	  else
//        	  { x = 480;}
//
//        	  Circle(x, y, r, gray, 3);
//          }
//
//          if(k == UpSwap)
//          {
//        	  if(y - TransitionValue() > 0)
//        	  { y -= TransitionValue(); }
//        	  else
//        	  { y = 1;}
//
//        	  Circle(x, y, r, gray, 3);
//          }
//
//          if(k == DownSwap)
//          {
//        	  if(y + TransitionValue() < 272)
//        	  { y += TransitionValue(); }
//        	  else
//        	  { y = 272;}
//        	  Circle(x, y, r, gray, 3);
//          }
//
//
//          if(k == ZoomIn)
//          {
//        	  r += 5;
//        	  Circle(x, y, r, gray, 3);
//          }
//
//          if(k == ZoomOut)
//          {
//        	  if(r - 5 > 15)
//        	  { r -= 5; }
//        	  else
//        	  { r = 15; }
//        	  Circle(x, y, r, gray, 3);
//          }

	  }

}

