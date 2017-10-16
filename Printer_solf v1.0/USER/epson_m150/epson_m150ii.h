#ifndef __EPSON_M150II_H
#define __EPSON_M150II_H
#include "sys.h"

void Printer_IO_Config(void);
void Printer_line(void);
void GPIO_ToggleBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Printer_Timer_Init(void);		// printer parameter init
void print_matrix_invert(void);		// matrix invert function
void Printer_Stop(void);	// Í£Ö¹´òÓ¡»ú
void Printer_Font_Extract(char *String);

typedef struct
{
	u8 t_h;			/*1:timer=1,0:timer=0*/
	u8 r_h;			/*1:reset_dector=1,0:reset_dector=0*/

	u8 t_index;		/*??timer???????*/
	u8 r_index;		/*??reset_dector???????*/

	u8 t_num;		/*???????????*/
	u8 t_num_back;

	u8 line_num;	/*?????*/
	u8 line_num_back;


	u8 p_on;		/*??????*/
	u8 run_paper;
}PRINTER_CTR_TYPE;




#endif

