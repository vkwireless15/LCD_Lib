#include "Graphics_IO.h"
#include "Touch.h"


//Пользовательские include and define
#include "main.h"
#define TransferDelay 100
#define LOW 0

//Пользовательские переменные и т.п.
extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;


extern uint32 DispHeight, DispWidth;
uint32 LCD_FRAME_BUFFER0 = 0;
uint32 LCD_FRAME_BUFFER1 = 0;
uint32 LCD_FRAME_BUFFER3 = 0;


void Init_Graphics_System(uint32 LCD_RAM_START_ADDRESS, uint8 Layers, uint8 ColorType) //Инициализация драйвера дисплея, графического ускорителя и т.п.
{
    LCD_FRAME_BUFFER0 = LCD_RAM_START_ADDRESS;
    //Пользовательский кодинициализации дисплея

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

void MemPoint(int32 x, int32 y, int32 Color) //Отрисовка одного пикселя
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


