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
	D_Fill_Rectangle rec;
	D_HLine line;
	D_FillCircle ball;
	D_ProgressBar p;
	D_Circle round;
	D_CheckBox check;
	D_TrackBar tr;

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

	rec.X1 = 50;
	rec.X2 = 480;
	rec.Y1 = 50;
	rec.Y2 = 270;
	rec.Color = red;

	line.X1 = 100;
	line.X2 = 450;
	line.Y1 = 200;
	line.Color = blue;
	line.Thickness = 5;

	ball.X1 = 200;
	ball.Y1 = 125;
	ball.Color = green;
	ball.R = 40;

	p.X1 = 200;
	p.X2 = 400;
	p.Y1 = 100;
	p.Y2 = 120;
	p.StartValue = 0;
	p.StopValue = 19;
	p.CurrentValue = 6;
	p.Thickness = 3;
	p.FillColor = white;
	p.FrameColor = blue;
	p.BarColor = green;
	p.Orientation = Horisontal;

	round.X1 = 100;
	round.Y1 = 120;
	round.Color = yellow;
	round.Thickness = 3;
	round.R = 40;

	check.X1 = 50;
	check.X2 = 70;
	check.Y1 = 150;
	check.Y2 = 170;
	check.FrameColor = blue;
	check.BackColor = white;
	check.CheckColor = black;
	check.Checked = 1;

	tr.X1 = 200;
	tr.X2 = 400;
	tr.Y1 = 100;
	tr.Y2 = 105;
	tr.StartValue = 0;
	tr.StopValue = 9;
	tr.FrameColor = blue;
	tr.BackColor = white;
//	tr.Orientation = Horizontal;
	tr.Radius = 6;
	tr.TrackerColor = yellow;





    char i = 0;

	while(1) // бесконечный цикл
	{
		Fill_Display(black);
		LCD_Fill_Rectangle(&kv);
		HAL_Delay(3000);

		LCD_FramePanel(&pan);
		HAL_Delay(3000);

		Fill_Display(black);
		LCD_Fill_Rectangle(&rec);
		HAL_Delay(3000);

		Fill_Display(black);
		LCD_HLine(&line);
		HAL_Delay(3000);

		Fill_Display(black);
		LCD_FillCircle(&ball);
		HAL_Delay(3000);

		for(i = 0; i < 20; i++)
		{
			p.CurrentValue = i;
		    Fill_Display(black);
		    LCD_ProgressBar(&p);
		    HAL_Delay(400);
		}

		Fill_Display(black);
		LCD_Circle(&round);
		HAL_Delay(3000);

		Fill_Display(black);
		LCD_CheckBox(&check);
		HAL_Delay(3000);

		Fill_Display(black);
		LCD_TrackBar(&tr);
		HAL_Delay(3000);

	}
}

