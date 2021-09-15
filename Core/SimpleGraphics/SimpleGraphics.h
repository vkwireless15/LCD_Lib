#ifndef _SIMPLEGRAPHICS_H_
#define _SIMPLEGRAPHICS_H_

#define Unclicked 2
#define Horisontal 3
#define Vertical 4


//argb цвета

//Red
#define lightRed4 0xFFCCCC
#define lightRed3 0xFF9999
#define lightRed2 0xFF6666
#define lightRed1 0xFF3333
#define red 0xFF0000
#define darkRed1 0xCC0000
#define darkRed2 0x990000
#define darkRed3 0x660000
#define darkRed4 0x330000

//Orange
#define lightOrange4 0xFFE5CC
#define lightOrange3 0xFFCC99
#define lightOrange2 0xFFB266
#define lightOrange1 0xFF9933
#define orange 0xFF8000
#define darkOrange1 0xCC6600
#define darkOrange2 0x994C00
#define darkOrange3 0x663300
#define darkOrange4 0x331900

//Yellow
#define lightYellow4 0xFFFFCC
#define lightYellow3 0xFFFF99
#define lightYellow2 0xFFFF66
#define lightYellow1 0xFFFF33
#define yellow 0xFFFF00
#define darkYellow1 0xCCCC00
#define darkYellow2 0x999900
#define darkYellow3 0x666600
#define darkYellow4 0x333300

//Yellow-Green
#define lightYellowGreen4 0xE5FFCC
#define lightYellowGreen3 0xCCFF99
#define lightYellowGreen2 0xB2FF66
#define lightYellowGreen1 0x99FF33
#define yellowGreen 0x80FF00
#define darkYellowGreen1 0x66CC00
#define darkYellowGreen2 0x4C9900
#define darkYellowGreen3 0x336600
#define darkYellowGreen4 0x193300

//Green
#define lightGreen4 0xCCFFCC
#define lightGreen3 0x99FF99
#define lightGreen2 0x66FF66
#define lightGreen1 0x33FF33
#define green 0x00FF00
#define darkGreen1 0x00CC00
#define darkGreen2 0x009900
#define darkGreen3 0x006600
#define darkGreen4 0x003300

//Turquoise
#define lightTurquoise4 0xCCFFE5
#define lightTurquoise3 0x99FFCC
#define lightTurquoise2 0x66FFB2
#define lightTurquoise1 0x33FF99
#define turquoise 0x00FF80
#define darkTurquoise1 0x00CC66
#define darkTurquoise2 0x00994C
#define darkTurquoise3 0x006633
#define darkTurquoise4 0x003319

//Сyan
#define lightcyan4 0xCCFFFF
#define lightcyan3 0x99FFFF
#define lightcyan2 0x66FFFF
#define lightcyan1 0x33FFFF
#define cyan 0x00FFFF
#define darkcyan1 0x00CCCC
#define darkcyan2 0x009999
#define darkcyan3 0x006666
#define darkcyan4 0x003333

//СyanBlue
#define lightcyanBlue4 0xCCE5FF
#define lightcyanBlue3 0x99CCFF
#define lightcyanBlue2 0x66B2FF
#define lightcyanBlue1 0x3399FF
#define cyanBlue 0x0080FF
#define darkcyanBlue1 0x0066CC
#define darkcyanBlue2 0x004C99
#define darkcyanBlue3 0x003366
#define darkcyanBlue4 0x001933

//Blue
#define lightBlue4 0xCCCCFF
#define lightBlue3 0x9999FF
#define lightBlue2 0x6666FF
#define lightBlue1 0x3333FF
#define blue 0x0000FF
#define darkBlue1 0x0000CC
#define darkBlue2 0x000099
#define darkBlue3 0x000066
#define darkBlue4 0x000033

//Violet
#define lightViolet4 0xE5CCFF
#define lightViolet3 0xCC99FF
#define lightViolet2 0xB266FF
#define lightViolet1 0x9933FF
#define violet 0x7F00FF
#define darkViolet1 0x6600CC
#define darkViolet2 0x4C0099
#define darkViolet3 0x330066
#define darkViolet4 0x190033

//Pink
#define lightPink4 0xFFCCFF
#define lightPink3 0xFF99FF
#define lightPink2 0xFF66FF
#define lightPink1 0xFF33FF
#define pink 0xFF00FF
#define darkPink1 0xCC00CC
#define darkPink2 0x990099
#define darkPink3 0x660066
#define darkPink4 0x330033

//RedPink
#define lightRedPink4 0xFFCCE5
#define lightRedPink3 0xFF99CC
#define lightRedPink2 0xFF66B2
#define lightRedPink1 0xFF3399
#define redpink 0xFF007F
#define darkRedPink1 0xCC0066
#define darkRedPink2 0x99004C
#define darkRedPink3 0x660033
#define darkRedPink4 0x330019

//White-Black
#define black 0x000000
#define lightBlack1 0x202020
#define lightBlack2 0x404040
#define lightBlack3 0x606060
#define gray 0x808080
#define gray1 0xA0A0A0
#define gray2 0xC0C0C0
#define gray3 0xE0E0E0
#define white 0xFFFFFF

// ---------------------------
typedef struct
{
	unsigned int Start_RAM_Address;
	unsigned int Display_Height;
	unsigned int Display_Width;
	char Layers_count;
} DisplayConfig;
typedef struct
{
	unsigned int Color;
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	char Thickness;
	char Is_pressed;
	char Unvisible;
} D_HLine;
typedef struct
{
	unsigned int Color;
	unsigned int X1;
	unsigned int Y1;
	unsigned int Y2;
	char Thickness;
	char Is_pressed;
	char Unvisible;
} D_VLine;
typedef struct
{
	unsigned int FrameColor;
	unsigned int FillColor;
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	char Thickness;
	char Is_pressed;
	char Unvisible;
} D_FramePanel;
typedef struct
{
	unsigned int X;
	unsigned int Y;
	unsigned int Color;
	unsigned int ClickedColor;
	char Is_pressed;
	char Unvisible;
} D_Label;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int StartValue;
	unsigned int StopValue;
	unsigned int CurrentValue;
	unsigned int FrameColor;
	unsigned int FillColor;
	unsigned int BarColor;
	char Thickness;
	char Orientation;
	char Is_pressed;
	char Unvisible;
} D_ProgressBar;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int StartValue;
	unsigned int StopValue;
	unsigned int CurrentValue;
	unsigned int FrameColor;
	unsigned int FillColor;
	unsigned int BarColorH;
	unsigned int BarColorC;
	char Thickness;
	char Orientation;
	char Is_pressed;
	char Unvisible;
}D_ProgressBarHGradient;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int StartValue;
	unsigned int StopValue;
	unsigned int CurrentValue;
	unsigned int FrameColor;
	unsigned int FillColor;
	unsigned int BarColorH;
	unsigned int BarColorC;
	char Thickness;
	char Orientation;
	char Is_pressed;
	char Unvisible;
}D_ProgressBarVGradient;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int YBar;
	char Thickness;
	unsigned int FrameColor;
	unsigned int BarColor;
	unsigned int WindowColor;
	unsigned int TextColor;
	char Is_pressed;
	char Unvisible;
} D_Form;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int YBar;
	char Thickness;
	unsigned int FrameColor;
	unsigned int BarColorH;
	unsigned int BarColorL;
	unsigned int WindowColor;
	unsigned int TextColor;
	char Is_pressed;
	char Unvisible;
} D_HGradientForm;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int YBar;
	char Thickness;
	unsigned int FrameColor;
	unsigned int BarColorH;
	unsigned int BarColorL;
	unsigned int WindowColor;
	unsigned int TextColor;
	char Is_pressed;
	char Unvisible;
} D_VGradientForm;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int ColorH;
	unsigned int ColorL;
	char Is_pressed;
	char Unvisible;
} D_VGradient;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int ColorH;
	unsigned int ColorL;
	char Is_pressed;
	char Unvisible;
} D_HGradient;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int ColorH;
	unsigned int ColorC;
	unsigned int ColorL;
	char Is_pressed;
	char Unvisible;
} D_DualVGradient;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int ColorH;
	unsigned int ColorC;
	unsigned int ColorL;
	char Is_pressed;
	char Unvisible;
} D_DualHGradient;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	char Thickness;
	unsigned int FrameColor;
	unsigned int FillColor;
	unsigned int PressedColor;
	unsigned int TextColor;
	char Is_pressed;
	char Unvisible;
} D_Button;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int Thickness;
	unsigned int FrameColor;
	unsigned int FillColorH;
	unsigned int FillColorL;
	unsigned int TextColor;
	unsigned int PressedColorH;
	unsigned int PressedColorL;
	char Is_pressed;
	char Unvisible;
} D_GradientButton;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Thickness;
	unsigned int FrameColor;
	unsigned int FillColor;
	unsigned int TextColor;
	char Is_pressed;
	char Unvisible;
} D_TextBox;
typedef struct
{
	unsigned int X1;
	unsigned int Y1;
	unsigned int R;
	unsigned int Color;
	unsigned int Thickness;
	char Is_pressed;
	char Unvisible;
} D_Circle;
typedef struct
{
	unsigned int X1;
	unsigned int Y1;
	unsigned int R;
	unsigned int Color;
	char Is_pressed;
	char Unvisible;
} D_FillCircle;
typedef struct
{
	unsigned int X1;
	unsigned int Y1;
	unsigned int X2;
	unsigned int Y2;
	unsigned int Color;
	unsigned int Thickness;
	char Is_pressed;
	char Unvisible;
} D_Line;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int Thickness;
	unsigned int FrameColor;
	unsigned int FillColor;
	unsigned int TextColor;
	char Is_pressed;
	char Unvisible;
} D_RichTextBox;
typedef struct
{
	unsigned int X;
	unsigned int Y;
	unsigned int Radius;
	unsigned int ExCirColor;
	unsigned int InCirColor;
	unsigned int BackColor;
	unsigned int TextColor;
	char Transp_key;
	char Checked;
	char Is_pressed;
	char Unvisible;
} D_RadioButton;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int FrameColor;
	unsigned int BackColor;
	unsigned int CheckColor;
	char Checked;
	char Is_pressed;
	char Unvisible;
} D_CheckBox;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int StartValue;
	unsigned int StopValue;
	unsigned int CurrentValue;
	unsigned int FrameColor;
	unsigned int BackColor;
	unsigned int TrackerColor;
	char Orientation;
	unsigned int Radius;
	char Is_pressed;
	char Unvisible;
} D_TrackBar;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int TextColor;
	char PressedAlphaValue;
	unsigned int AlphaColor;
	char EnAlphaColor;
	char Is_pressed;
	char Is_out;
	char PHW_Flag;
	char Unvisible;
} D_BMP_Icon;
typedef struct
{
	unsigned int X1;
	unsigned int Y1;
	char Layer;
	char Alpha;
	char PHW_Flag;
	char Unvisible;
} D_BMP_Pic;
typedef struct
{
	unsigned int X1;
	unsigned int X2;
	unsigned int Y1;
	unsigned int Y2;
	unsigned int FillColor;
	unsigned int FrameColor;
	unsigned int Thickness;
	unsigned int LinesColor;
	unsigned int StepX;
	unsigned int StepY;
	unsigned int XMax;
	unsigned int XMin;
	unsigned int YMax;
	unsigned int YMin;
	char Unvisible;
} D_Graph;
typedef struct
{
	unsigned int Points_count;
	unsigned int LineColor;
	unsigned int Thickness;
	char Unvisible;
} D_GraphLine;


void Get1251(char Str[]);

unsigned int Color_565(unsigned int Color);

unsigned int Color_888_(unsigned int Color);

unsigned int Color_A888_(unsigned int Color, char Alpha);

void Graphics_Init(DisplayConfig *dcf);
void Set_Backlight(char State, unsigned int Brightness);

void Fill_Display(unsigned int Color);
void Fill_Rectangle(unsigned int Color, unsigned int StartX, unsigned int StopX, unsigned int StartY, unsigned int StopY);


void Show_to_layer(char Layer);

#endif
