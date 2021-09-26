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

	HAL_LTDC_SetAddress(&hltdc,(uint32_t)&RGB,0);
	Graphics_Init(&ds);

	Fill_Display(green);
	HAL_Delay(1000);

	while(1)
	{
		Fill_Display(white);
		Fill_Rectangle(darkBlue4, 1, 480, 1, 272);
		HAL_Delay(3000);

		Fill_Display(white);
		Fill_Rectangle(darkBlue4, 2, 479, 2, 271);
		HAL_Delay(3000);

		Fill_Display(white);
		Fill_Rectangle(darkBlue4, 3, 478, 3, 270);
		HAL_Delay(3000);

		Fill_Display(white);
		Fill_Rectangle(darkBlue4, 50, 400, 70, 180);
		HAL_Delay(3000);

		/*HAL_Delay(1000);
		Fill_Display(green);
		HAL_Delay(1000);
		Fill_Display(blue);
		HAL_Delay(2000); */
	}
}

