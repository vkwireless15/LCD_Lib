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
	D_ProgressBar pa;
	D_Circle round;
	D_CheckBox check;
	D_TrackBar tr;
	D_TrackBar tra;
	D_VGradient vgr;
	D_HGradient hgr;


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
	p.StopValue = 10;
	p.CurrentValue = 6;
	p.Thickness = 3;
	p.FillColor = black;
	p.FrameColor = blue;
	p.BarColor = red;
	p.Orientation = Horisontal;

	pa.X1 = 100;
	pa.X2 = 120;
	pa.Y1 = 10;
	pa.Y2 = 262;
	pa.StartValue = 0;
	pa.StopValue = 10;
	pa.CurrentValue = 6;
	pa.Thickness = 3;
	pa.FillColor = black;
	pa.FrameColor = blue;
	pa.BarColor = red;
	pa.Orientation = Vertical;

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
	tr.Y1 = 85;
	tr.Y2 = 90;
	tr.StartValue = 0;
	tr.StopValue = 10;
	tr.FrameColor = blue;
	tr.BackColor = red;
	tr.Orientation = Horisontal;
	tr.Radius = 6;
	tr.TrackerColor = yellow;

	tra.X1 = 20;
	tra.X2 = 25;
	tra.Y1 = 10;
	tra.Y2 = 262;
	tra.StartValue = 0;
	tra.StopValue = 10;
	tra.FrameColor = blue;
	tra.BackColor = red;
	tra.Orientation = Vertical;
	tra.Radius = 6;
	tra.TrackerColor = yellow;

	vgr.X1 = 240;
	vgr.X2 = 340;
	vgr.Y1 = 190;
	vgr.Y2 = 262;
	vgr.ColorH = red;
	vgr.ColorL = lightBlue1;
	vgr.Unvisible = 0;
	vgr.Is_pressed = 0;

	hgr.X1 = 135;
	hgr.X2 = 235;
	hgr.Y1 = 190;
	hgr.Y2 = 262;
	hgr.ColorH = red;
	hgr.ColorL = lightBlue1;
	hgr.Unvisible = 0;
	hgr.Is_pressed = 0;





    char i = 0;

	while(1) // бесконечный цикл
	{
//		Fill_Display(black);
//		LCD_Fill_Rectangle(&kv);
//		HAL_Delay(3000);
//
//		LCD_FramePanel(&pan);
//		HAL_Delay(3000);
//
//		Fill_Display(black);
//		LCD_Fill_Rectangle(&rec);
//		HAL_Delay(3000);
//
//		Fill_Display(black);
//		LCD_HLine(&line);
//		HAL_Delay(3000);
//
//		Fill_Display(black);
//		LCD_FillCircle(&ball);
//		HAL_Delay(3000);

		vgr.X1 = 240;
		vgr.X2 = 340;
		vgr.Y1 = 190;
		vgr.Y2 = 262;

		hgr.X1 = 135;
		hgr.X2 = 235;
		hgr.Y1 = 190;
		hgr.Y2 = 262;

		for(i = 0; i < 11; i++)
		{
			p.CurrentValue = i;
			pa.CurrentValue = i;
			tr.CurrentValue = i;
			tra.CurrentValue = i;

			Fill_Display(darkBlue3);
		    LCD_ProgressBar(&p);
		    LCD_ProgressBar(&pa);
		    LCD_TrackBar(&tr);
		    LCD_TrackBar(&tra);
		    LCD_VGradient(&vgr);
		    LCD_HGradient(&hgr);
		    HAL_Delay(100);
		}
		HAL_Delay(300);

		vgr.X1 = 2;
		vgr.X2 = 479;
		vgr.Y1 = 2;
		vgr.Y2 = 271;

		hgr.X1 = 2;
		hgr.X2 = 479;
		hgr.Y1 = 2;
		hgr.Y2 = 271;

		Fill_Display(green);
		LCD_VGradient(&vgr);
		HAL_Delay(5000);

		Fill_Display(green);
		LCD_HGradient(&hgr);
		HAL_Delay(5000);

//		Fill_Display(black);
//		LCD_Circle(&round);
//		HAL_Delay(3000);
//
//		Fill_Display(black);
//		LCD_CheckBox(&check);
//		HAL_Delay(3000);

	}
}

