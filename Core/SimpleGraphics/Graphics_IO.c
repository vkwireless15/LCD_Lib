#include "Graphics_IO.h"


//Пользовательские include and define
#include "main.h"
#define TransferDelay 100
#define LOW 0

//Пользовательские переменные и т.п.
extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;

unsigned int Height = 0, Width = 0, LCD_FRAME_BUFFER0 = 0;


void Init_Graphics_System(uint32 H, uint32 W, uint32 LCD_RAM_START_ADDRESS, uint8 Layers, uint8 ColorType) //Инициализация драйвера дисплея, графического ускорителя и т.п.
{
	//LTDC_LayerCfgTypeDef pLayerCfg = {0};
	//LTDC_LayerCfgTypeDef pLayerCfg1 = {0};
	Height = H;
    Width = W;

    LCD_FRAME_BUFFER0 = LCD_RAM_START_ADDRESS;
    //LCD_FRAME_BUFFER1 = LCD_FRAME_BUFFER0 + (Height * Width * 2);
    //LCD_FRAME_BUFFER2 = LCD_FRAME_BUFFER1 + (Height * Width * 2);


  /*  hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    hltdc.Init.HorizontalSync = 40;
    hltdc.Init.VerticalSync = 9;
    hltdc.Init.AccumulatedHBP = 53;
    hltdc.Init.AccumulatedVBP = 11;
    hltdc.Init.AccumulatedActiveW = 533;
    hltdc.Init.AccumulatedActiveH = 283;
    hltdc.Init.TotalWidth = 565;
    hltdc.Init.TotalHeigh = 285;
    hltdc.Init.Backcolor.Blue = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Red = 0;
    if (HAL_LTDC_Init(&hltdc) != HAL_OK)
    {
      Error_Handler();
    }
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = 480;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = 272;
    pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
    pLayerCfg.Alpha = 255;
    pLayerCfg.Alpha0 = 0;
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
    pLayerCfg.FBStartAdress = LCD_RAM_START_ADDRESS;
    pLayerCfg.ImageWidth = 480;
    pLayerCfg.ImageHeight = 272;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 0;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
    {
      Error_Handler();
    }


    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    hltdc.Init.HorizontalSync = 40;
    hltdc.Init.VerticalSync = 9;
    hltdc.Init.AccumulatedHBP = 53;
    hltdc.Init.AccumulatedVBP = 11;
    hltdc.Init.AccumulatedActiveW = 533;
    hltdc.Init.AccumulatedActiveH = 283;
    //hltdc.Init.TotalWidth = 565;
    //hltdc.Init.TotalHeigh = 285;

    hltdc.Init.TotalWidth = 565;
    hltdc.Init.TotalHeigh = 285;

    hltdc.Init.Backcolor.Blue = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Red = 0;
    if (HAL_LTDC_Init(&hltdc) != HAL_OK)
    {

    }
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = Width;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = Height;
    pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
    pLayerCfg.Alpha = 255;
    pLayerCfg.Alpha0 = 0;
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
    pLayerCfg.FBStartAdress = LCD_FRAME_BUFFER0;
    pLayerCfg.ImageWidth = Width;
    pLayerCfg.ImageHeight = Height;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 0;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
    {
      //Error_Handler();
    }

    pLayerCfg1.WindowX0 = 0;
    pLayerCfg1.WindowX1 = Width;
    pLayerCfg1.WindowY0 = 0;
    pLayerCfg1.WindowY1 = Height;
    pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
    pLayerCfg1.Alpha = 255;
    pLayerCfg1.Alpha0 = 0;
    pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
    pLayerCfg1.FBStartAdress = LCD_FRAME_BUFFER2;
    pLayerCfg1.ImageWidth = Width;
    pLayerCfg1.ImageHeight = Height;
    pLayerCfg1.Backcolor.Blue = 0;
    pLayerCfg1.Backcolor.Green = 0;
    pLayerCfg1.Backcolor.Red = 0;
    if(Layers == 2)
    {
        if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
        {

        }
    }
    HAL_LTDC_SetAddress(&hltdc,LCD_FRAME_BUFFER0,0);

    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode = DMA2D_M2M_BLEND;
    hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
    hdma2d.Init.OutputOffset = 0;
    hdma2d.LayerCfg[1].InputOffset = 0;
    hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
    hdma2d.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
    hdma2d.LayerCfg[1].InputAlpha = 0;
    hdma2d.LayerCfg[0].InputOffset = 0;
    hdma2d.LayerCfg[0].InputColorMode = DMA2D_INPUT_ARGB8888;
    hdma2d.LayerCfg[0].AlphaMode = DMA2D_REPLACE_ALPHA;
    hdma2d.LayerCfg[0].InputAlpha = 0;
    //hdma2d.LayerCfg[0].AlphaInverted = DMA2D_REGULAR_ALPHA;
    //hdma2d.LayerCfg[0].RedBlueSwap = DMA2D_RB_REGULAR;
    if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
    {

    }
    if (HAL_DMA2D_ConfigLayer(&hdma2d, 0) != HAL_OK)
    {

    }
    if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
    {

    } */

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
	/*//if(StartX > StopX) swap(&StartX,&StopX);
	//if(StartY>StopY) swap(&StartY,&StopY);
	unsigned int addr = (LCD_FRAME_BUFFER1) + 4*(StartY * Width + StartX);
	hdma2d.Init.Mode = DMA2D_R2M;
    hdma2d.Init.OutputOffset = Width-(StopX-StartX);

    //HAL_Delay(5);
    if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
    {
    	//HAL_Delay(5);
       if (HAL_DMA2D_Start(&hdma2d, Color, addr, StopX-StartX, StopY-StartY) == HAL_OK)
       {
    	   //HAL_Delay(5);
    	   HAL_DMA2D_PollForTransfer(&hdma2d, TransferDelay);
       }
    } */

	for(uint32 y = StartY; y < StopY; y++)
	{
		for(uint32 x = StartX; x < StopX; x++)
		{
			*(__IO uint16*) (LCD_FRAME_BUFFER0 + (2*(y*Width + x))) = Color;
		}
	}
}

void MemPoint(int32 x, int32 y, int32 Color) //Отрисовка одного пикселя
{
	*(__IO uint16*) (LCD_FRAME_BUFFER0 + (2*(y*Width + x))) = Color;
}

void Show(uint8 Layer) // Отобразить содержимое на выбранный слой экрана
{
//	unsigned int RAddr = 0;
//	if(Layer == 0)
//	{
//		//RAddr = LCD_FRAME_BUFFER0;
//	}
//	else
//	{
//		//RAddr = LCD_FRAME_BUFFER2;
//	}
//	hdma2d.Init.Mode = DMA2D_M2M_PFC;
//    hdma2d.Init.ColorMode = DMA2D_ARGB8888;
//	hdma2d.Init.OutputOffset = 0;
//	hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
//	hdma2d.LayerCfg[1].InputAlpha = 0xFF;
//	hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
//	hdma2d.LayerCfg[1].InputOffset = 0;
//	if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
//	{
//	  if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK)
//	  {
//	    if (HAL_DMA2D_Start(&hdma2d, LCD_FRAME_BUFFER1, RAddr, Width, Height) == HAL_OK)
//	    {
//	      HAL_DMA2D_PollForTransfer(&hdma2d, TransferDelay);
//	    }
//	  }
//	}
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
