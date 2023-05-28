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

	  while(1)
	  {
		  Fill_Display(black);
		  //LCD_FramePanel();

		  for(int i = 1; i < 270; i++)
		  {
		      RichTextBox(1, i*2, 1, i, 3, red, white, darkBlue3, "\nEnter,\n0,1,2,3,4,5,6,7,8,9,10,11\nABCDEFGHJKLMNOPQRST\abcdefghjk\n123");
		      HAL_Delay(300);
		  }


//		  LCD_Label(30, 5, "Progress bar >>>");
//
//		  for(int i = 0; i < 10; i++)
//		  {
//		    LCD_Progress_bar(50, 430, 135, 155, 0, 9, i, Horisontal);
//		    LCD_Progress_bar_gradient(50, 430, 160, 180, 0, 9, i, Horisontal);
//		    HAL_Delay(100);
//		  }
//		  HAL_Delay(3000);
//		  LCD_FramePanel();
//		  LCD_Label(110, 5, "Progress bar >>>");
//
//		  for(int j = 0; j < 10; j++)
//		  {
//		    LCD_Progress_bar(50, 70, 20, 270, 0, 9, j, Vertical);
//		    LCD_Progress_bar_gradient(80, 100, 20, 270, 0, 9, j, Vertical);
//		    HAL_Delay(100);
//		  }
//		  HAL_Delay(3000);
//		  LCD_FramePanel();
//		  LCD_Label(30, 290, "Simple Progress bar >>>");
//
//		  LCD_Progress_bar(50, 430, 10, 30, 0, 10, 0, Horisontal);
//		  LCD_Progress_bar(50, 430, 35, 55, 0, 10, 1, Horisontal);
//		  LCD_Progress_bar(50, 430, 60, 80, 0, 10, 2, Horisontal);
//		  LCD_Progress_bar(50, 430, 85, 105, 0, 10, 3, Horisontal);
//		  LCD_Progress_bar(50, 430, 110, 130, 0, 10, 4, Horisontal);
//		  LCD_Progress_bar(50, 430, 135, 155, 0, 10, 5, Horisontal);
//		  LCD_Progress_bar(50, 430, 160, 180, 0, 10, 6, Horisontal);
//		  LCD_Progress_bar(50, 430, 185, 205, 0, 10, 7, Horisontal);
//		  LCD_Progress_bar(50, 430, 210, 230, 0, 10, 8, Horisontal);
//		  LCD_Progress_bar(50, 430, 235, 255, 0, 10, 9, Horisontal);
//		  //LCD_Progress_bar(50, 430, 260, 280, 0, 10, 10, Horisontal);
//		  HAL_Delay(5000);
//		  LCD_FramePanel();
//		  LCD_Label(30, 290, "Gradient Progress bar >>>");
//
//		  LCD_Progress_bar_gradient(50, 430, 10, 30, 0, 10, 0, Horisontal);
//		  LCD_Progress_bar_gradient(50, 430, 35, 55, 0, 10, 1, Horisontal);
//		  LCD_Progress_bar_gradient(50, 430, 60, 80, 0, 10, 2, Horisontal);
//		  LCD_Progress_bar_gradient(50, 430, 85, 105, 0, 10, 3, Horisontal);
//		  LCD_Progress_bar_gradient(50, 430, 110, 130, 0, 10, 4, Horisontal);
//		  LCD_Progress_bar_gradient(50, 430, 135, 155, 0, 10, 5, Horisontal);
//		  LCD_Progress_bar_gradient(50, 430, 160, 180, 0, 10, 6, Horisontal);
//		  LCD_Progress_bar_gradient(50, 430, 185, 205, 0, 10, 7, Horisontal);
//		  LCD_Progress_bar_gradient(50, 430, 210, 230, 0, 10, 8, Horisontal);
//		  LCD_Progress_bar_gradient(50, 430, 235, 255, 0, 10, 9, Horisontal);
//		  //LCD_Progress_bar_gradient(50, 430, 260, 280, 0, 10, 10, Horisontal);
//		  HAL_Delay(5000);
//
//		  LCD_FramePanel();
//		  LCD_Label(30, 5, "Textbox >>>");
//		  LCD_TextBox(30, 130, 40, "Text, Num");
//		  HAL_Delay(5000);
//		  LCD_Form("Form1 >>>");
//		  LCD_Button(20, 100, 40, 80, "Open list");
//		  HAL_Delay(5000);
//		  LCD_Gradient_Form_A("Gradient Form A");
//		  HAL_Delay(5000);
//		  LCD_Gradient_Form_B("Gradient Form B");
//		  HAL_Delay(5000);
	  }

}

