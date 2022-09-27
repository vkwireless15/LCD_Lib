#include "Code.h"
#include "SDRAM.h"
#include "SimpleGraphics.h"

short unsigned int RGB[272*480];

extern LTDC_HandleTypeDef hltdc;
DisplayConfig ds;

void MainFunc ()
{
	ds.Color_Type = Color565;
	ds.Display_Height = 272;
	ds.Display_Width = 480;
	ds.Layers = 1;
	ds.Start_RAM_Address = (uint32_t)&RGB;

	HAL_LTDC_SetAddress(&hltdc,(uint32_t)&RGB,0);  // запускаем модуль LTDC (железный)
	Graphics_Init(&ds); //инит библиотеки (из структуры ds)

	Fill_Display(green);
	HAL_Delay(1000);

	D_Fill_Rectangle kv;
	D_FramePanel pan;

	kv.X1 = 200;
	kv.X2 = 400;
	kv.Y1 = 30;
	kv.Y2 = 230;
	kv.Color = green;

	pan.FrameColor = blue;
	pan.FillColor = yellow;
	pan.Thickness = 2;
	pan.X1 = 1;
	pan.X2 = 480;
	pan.Y1 = 1;
	pan.Y2 = 272;


	while(1) // бесконечный циклс
	{
		Fill_Display(black);
		LCD_Fill_Rectangle(&kv);
		HAL_Delay(3000);

		LCD_FramePanel(&pan);
		HAL_Delay(3000);

	}
}

