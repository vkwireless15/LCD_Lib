#include "Code.h"
#include "SDRAM.h"
#include "SimpleGraphics.h"


extern LTDC_HandleTypeDef hltdc; // Структура для управления параметрами контроллера дисплея

short unsigned int RGB[272*480]; //Резервируем память для буффера дисплея
DisplayConfig ds;                //Основные параметры библиотеки


void MainFunc ()
{
	ds.Color_Type = Color565; //Бит на пиксель
	ds.Display_Height = 272;
	ds.Display_Width = 480;
	ds.Layers = 1;            //Количество слоев
	ds.Start_RAM_Address = (uint32_t)&RGB; //Адрес начала кадрового буффера

	HAL_LTDC_SetAddress(&hltdc,(uint32_t)&RGB,0);  // запускаем модуль LTDC (железный)
	Graphics_Init(&ds); //инит библиотеки (из структуры ds)

	//Fill_Display(green);
	//HAL_Delay(1000);

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
	D_DualHGradient dhgr;
	D_DualVGradient dvgr;
    D_Label lb;
    D_Form fr;
    D_Button bt;
    D_HGradientForm hfr;
    D_VGradientForm vfr;
    D_ProgressBarVGradient pvg;
    D_TextBox tb;
    D_RadioButton rb;
    D_Graph gr;
    D_GraphLine grL;
    D_RichTextBox RTB;


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
	p.Y1 = 30;
	p.Y2 = 40;
	p.StartValue = 0;
	p.StopValue = 10;
	p.CurrentValue = 6;
	p.Thickness = 3;
	p.FillColor = black;
	p.FrameColor = blue;
	p.BarColor = red;
	p.Orientation = Horisontal;

	pa.X1 = 30;
	pa.X2 = 50;
	pa.Y1 = 30;
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

	check.X1 = 20;
	check.X2 = 35;
	check.Y1 = 10;
	check.Y2 = 25;
	check.FrameColor = blue;
	check.BackColor = white;
	check.CheckColor = black;
	check.Checked = 1;
	check.TextColor = white;

	tr.X1 = 200;
	tr.X2 = 400;
	tr.Y1 = 45;
	tr.Y2 = 50;
	tr.StartValue = 0;
	tr.StopValue = 10;
	tr.FrameColor = blue;
	tr.BackColor = red;
	tr.Orientation = Horisontal;
	tr.Radius = 6;
	tr.TrackerColor = yellow;

	tra.X1 = 20;
	tra.X2 = 25;
	tra.Y1 = 35;
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

	dhgr.X1 = 345;
	dhgr.X2 = 445;
	dhgr.Y1 = 190;
	dhgr.Y2 = 262;
	dhgr.ColorH  = red;
	dhgr.ColorC = green;
	dhgr.ColorL = blue;

	dvgr.X1 = 345;
	dvgr.X2 = 445;
	dvgr.Y1 = 113;
	dvgr.Y2 = 185;
	dvgr.ColorH  = red;
	dvgr.ColorC = green;
	dvgr.ColorL = blue;

    lb.X = 80;
    lb.Y = 90;
    lb.Color = white;
    lb.ClickedColor = gray;

    fr.X1 = 2;
    fr.X2 = 479;
    fr.Y1 = 2;
    fr.Y2 = 271;
    fr.YBar = 25;
    fr.BarColor = blue;
    fr.FrameColor = red;
    fr.TextColor = green;
    fr.Thickness = 1;
    fr.WindowColor = white;

    bt.FillColor = gray2;
    bt.FrameColor = black;
    bt.PressedColor = white;
    bt.TextColor = black;
    bt.Thickness = 1;
    bt.X1 = 230;
    bt.X2 = 310;
    bt.Y1 = 100;
    bt.Y2 = 120;

    hfr.X1 = 2;
    hfr.X2 = 479;
    hfr.Y1 = 2;
    hfr.Y2 = 271;
    hfr.YBar = 25;
    hfr.BarColorH = blue;
    hfr.BarColorL = lightBlue3;
    hfr.FrameColor = red;
    hfr.TextColor = green;
    hfr.Thickness = 1;
    hfr.WindowColor = white;

    vfr.X1 = 2;
    vfr.X2 = 479;
    vfr.Y1 = 2;
    vfr.Y2 = 271;
    vfr.YBar = 25;
    vfr.BarColorL = blue;
    vfr.BarColorH = lightBlue4;
    vfr.FrameColor = red;
    vfr.TextColor = green;
    vfr.Thickness = 1;
    vfr.WindowColor = white;


	pvg.X1 = 200;
	pvg.X2 = 400;
	pvg.Y1 = 70;
	pvg.Y2 = 90;
	pvg.StartValue = 0;
	pvg.StopValue = 10;
	pvg.CurrentValue = 6;
	pvg.Thickness = 1;
	pvg.FillColor = black;
	pvg.FrameColor = green;
	pvg.BarColorC = red;
	pvg.BarColorH = blue;
	pvg.Orientation = Horisontal;


	rb.BackColor = blue;
	rb.Checked = 1;
	rb.Radius = 5;
	rb.TextColor = white;
	rb.X = 25;
	rb.Y = 50;
	rb.Transp_key = 0;
	rb.ExCirColor = green;
	rb.InCirColor = blue;
	rb.Unvisible = 1;

	gr.FillColor = white;
	gr.FrameColor = green;
	gr.LinesColor = red;
	gr.StepX = 1;
	gr.StepY = 10;
	gr.X1 = 1;
	gr.X2 = 480;
	gr.XMax = 10;
	gr.XMin = 0;
	gr.Y1 = 1;
	gr.Y2 = 272;
	gr.YMax = 100;
	gr.YMin = 0;
	gr.Unvisible = 0;
	gr.Thickness = 2;

	grL.LineColor = black;
	grL.Points_count = 10;
	grL.Thickness = 2;


    RTB.Y1 = 1;
    RTB.Y2 = 40;
    RTB.Thickness = 2;
    RTB.FrameColor = white;
    RTB.FillColor = black;
    RTB.TextColor = green;




//     char S[] = {"Abcdefghigklmnopqrstuvwxyz"};
//
//    uint16 i = 0;
//
	while(1) // бесконечный цикл
	{

		LCD_Graph(&gr);
		int data[] = {90, 80, 70, 60, 50, 40, 30, 20, 10, 0};
		LCD_GraphLine(&gr, &grL, data);
		HAL_Delay(3000);

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

		Fill_Display(green);
		LCD_Form(&fr, "Form1");
		LCD_HGradient(&hgr);
		HAL_Delay(5000);

		Fill_Display(black);
		LCD_Circle(&round);
		HAL_Delay(3000);

		Fill_Display(black);
		LCD_RadioButton(&rb, "Radiobutton1");
		LCD_CheckBox(&check, "CheckButton1");
		HAL_Delay(3000);
//
//		vgr.X1 = 240;
//		vgr.X2 = 340;
//		vgr.Y1 = 190;
//		vgr.Y2 = 262;
//
//		hgr.X1 = 135;
//		hgr.X2 = 235;
//		hgr.Y1 = 190;
//		hgr.Y2 = 262;
//
//		lb.X = 100;
//		lb.Y = 60;
//		lb.Color = black;

//		RTB.X1 = 10;
//		RTB.X2 = 20;
//		RTB.Y2 = 40;
//
////		for(i = 0; i < 220; i++)
//		{
//			p.CurrentValue = i;
//			pa.CurrentValue = i;
//			tr.CurrentValue = i;
//			tra.CurrentValue = i;
//			pvg.CurrentValue = i;
//
//			lb.Y += 2;
//
//			Fill_Display(darkBlue3);
//			LCD_Form(&fr, "Form1");
//			LCD_HGradientForm(&hfr, "HForm1");
//			LCD_VGradientForm(&vfr, "VForm1");
//		    LCD_ProgressBar(&p);
//		    LCD_ProgressBar(&pa);
//		    LCD_ProgressBarVGradient(&pvg);
//		    LCD_TrackBar(&tr);
//		    LCD_TrackBar(&tra);
//		    LCD_VGradient(&vgr);
//		    LCD_HGradient(&hgr);
//		    LCD_DualHGradient(&dhgr);
//		    LCD_DualVGradient(&dvgr);
//		    LCD_Label(&lb, "Hello!");
//		    LCD_Button(&bt, "Butt1");
//		    LCD_RichTextBox(&RTB, S);
//		    HAL_Delay(300);
//
//		    RTB.X2+=1;
//		    RTB.Y2+=1;
//		}



//
//
//		vgr.X1 = 2;
//		vgr.X2 = 479;
//		vgr.Y1 = 2;
//		vgr.Y2 = 271;
//
//		hgr.X1 = 2;
//		hgr.X2 = 479;
//		hgr.Y1 = 2;
//		hgr.Y2 = 271;
//
//		Fill_Display(green);
//		LCD_VGradient(&vgr);
//		HAL_Delay(1000);
//







	}
}

