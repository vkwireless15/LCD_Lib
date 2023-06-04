#include "Graphics_IO.h"
#include "Touch.h"


//Пользовательские include and define
#include "main.h"
#include "Touch.h"
#define TransferDelay 100
#define LOW 0

//Пользовательские переменные и т.п.
extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;
TS_StateTypeDef TS_State;


extern uint32 DispHeight, DispWidth;
extern int16 CrPosX1, CrPosX2, CrPosX3, CrPosX4, CrPosX5, CrPosY1, CrPosY2, CrPosY3, CrPosY4, CrPosY5;
extern uint8 CrStatus;
uint32 LCD_FRAME_BUFFER0 = 0;
uint32 LCD_FRAME_BUFFER1 = 0;
uint32 LCD_FRAME_BUFFER2 = 0;


void Init_Graphics_System(uint32 LCD_RAM_START_ADDRESS, uint8 Layers, uint8 ColorType) //Инициализация драйвера дисплея, графического ускорителя и т.п.
{
    LCD_FRAME_BUFFER0 = LCD_RAM_START_ADDRESS;

    Touch_Init();

}

void Fill_all(uint32 Color) //Заливка всего дисплея цветом
{
	for(int i=0; i<480*272; i++)
	{
	  *(__IO uint16*) (LCD_FRAME_BUFFER0 + (i*2)) = Color;
	}
}

void Fill_rectangle(uint32 Color, int32 StartX, int32 StopX, int32 StartY, int32 StopY) //Заливка прямоугольной формы
{
	StartX--;
	StartY--;

	for(uint32 y = StartY; y < StopY; y++)
	{
		for(uint32 x = StartX; x < StopX; x++)
		{
			*(__IO uint16*) (LCD_FRAME_BUFFER0 + (2*(y*DispWidth + x))) = Color;
		}
	}
}

void MemPoint(int32 x, int32 y, uint32 Color) //Отрисовка одного пикселя
{
	*(__IO uint16*) (LCD_FRAME_BUFFER0 + (2*(y*DispWidth + x))) = Color;
}

void Backlight(uint32 Brightness, uint8 State) //Управление подсветкой
{
	if(State == LOW)
	{
		HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, SET);
	}
}

void GetCursor()
{
    TS_GetState(&TS_State);
    if(TS_State.touchDetected)
    {
    	CrPosX1 = TS_State.touchX[0];
		CrPosY1 = TS_State.touchY[0];

		CrPosX2 = TS_State.touchX[1];
		CrPosY2 = TS_State.touchY[1];

		CrPosX3 = TS_State.touchX[2];
		CrPosY3 = TS_State.touchY[2];

		CrPosX4 = TS_State.touchX[3];
		CrPosY4 = TS_State.touchY[3];

		CrPosX5 = TS_State.touchX[4];
		CrPosY5 = TS_State.touchY[4];

		CrStatus = Clicked;
    }
    else
    {
    	CrPosX1 = 0;
		CrPosY1 = 0;

		CrPosX2 = 0;
		CrPosY2 = 0;

		CrPosX3 = 0;
		CrPosY3 = 0;

		CrPosX4 = 0;
		CrPosY4 = 0;

		CrPosX5 = 0;
		CrPosY5 = 0;

    	TS_State.touchX[0] = 0;
		TS_State.touchY[0] = 0;

    	TS_State.touchX[1] = 0;
		TS_State.touchY[1] = 0;

    	TS_State.touchX[2] = 0;
		TS_State.touchY[2] = 0;

    	TS_State.touchX[3] = 0;
		TS_State.touchY[3] = 0;

    	TS_State.touchX[4] = 0;
		TS_State.touchY[4] = 0;

		CrStatus = NotClicked;
    }
}
