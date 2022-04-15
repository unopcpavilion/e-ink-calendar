﻿#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "EPD_Test.h"   //Examples
#include "EPD_Test.h"
#include "EPD_7in5_V2.h"
#include <time.h>

int drawWindow(void);

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_Module_Exit();

    exit(0);
}

int main(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

    drawWindow();

	// 	For Test
    // if(DEV_Module_Init()!=0){
        // return -1;
    // }
	// while(1) {
	    // EPD_7in5b_V2_test();
		// DEV_Delay_ms(10000);
	// }
	// DEV_Module_Exit();
	//
     return 0;
}

int drawWindow(void){
    printf("EPD_7IN5_V2_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
    EPD_7IN5_V2_Init();

    struct timespec start={0,0}, finish={0,0};
    clock_gettime(CLOCK_REALTIME,&start);
    EPD_7IN5_V2_Clear();
    clock_gettime(CLOCK_REALTIME,&finish);
    printf("%ld S\r\n",finish.tv_sec-start.tv_sec);
    DEV_Delay_ms(500);

    //Create a new image cache
    UBYTE *BlackImage;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    UWORD Imagesize = ((EPD_7IN5_V2_WIDTH % 8 == 0)? (EPD_7IN5_V2_WIDTH / 8 ): (EPD_7IN5_V2_WIDTH / 8 + 1)) * EPD_7IN5_V2_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, WHITE);




    // 1.Select Image
//    printf("SelectImage:BlackImage\r\n");
//    Paint_SelectImage(BlackImage);
//    Paint_Clear(WHITE);
//    DEV_Delay_ms(2000);//important, at least 2s
    // 2.Drawing on the image

//    printf("Drawing:BlackImage\r\n");
//    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
//    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
//    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
//    Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//    Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
//    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//    Paint_DrawCircle(45, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
//    Paint_DrawCircle(105, 95, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//    Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
//    Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
//    Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
//    Paint_DrawString_EN(10, 20, "hello world", &Font24, WHITE, BLACK);
//    Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
//    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);

    //Paint_DrawRectangle(5, 5, EPD_7IN5_V2_WIDTH-10, EPD_7IN5_V2_HEIGHT-10, BLACK, DOT_PIXEL_8X8, LINE_STYLE_SOLID);
    printf("show window BMP-----------------\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    GUI_ReadBmp("./pic/desktop_plain.bmp", 0, 0);
    EPD_7IN5_V2_Display(BlackImage);
    DEV_Delay_ms(2000);

//
//    printf("EPD_Display\r\n");
//    EPD_7IN5_V2_Display(BlackImage);
//    DEV_Delay_ms(2000);

//    printf("Clear...\r\n");
//    EPD_7IN5_V2_Clear();

    printf("Goto Sleep...\r\n");
    EPD_7IN5_V2_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();

    return 0;
}
