#include "Code.h"
#include "SDRAM.h"
#include "SimpleGraphics.h"

void MainFunc ()
{

	DisplayConfig dc;
	dc.Display_Height = 272;
	dc.Display_Width = 480;
	dc.Layers_count = 1;
	dc.Start_RAM_Address = 0xC0000000;

	SDRAM_Init();
	Set_Backlight(1, 1);
	HAL_Delay(1000);
	Graphics_Init(&dc);
	HAL_Delay(500);
    Fill_Display(Color_888_(blue));
    Fill_Rectangle(Color_888_(red), 100, 150, 100, 150);
    Show_to_layer(0);

	while(1)
	{

	}
}

