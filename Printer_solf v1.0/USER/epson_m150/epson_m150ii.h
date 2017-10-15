#ifndef __EPSON_M150II_H
#define __EPSON_M150II_H
#include "sys.h"

#define MAX_LINE_CHAR 	16
#define HEAD            4    //四个打印头
#define LET_PER_HEAD    4    //一个打印头4个字符
#define VOL_PER_LET     6    //每个字符6列
#define LINE            10    //每个字符10行，两空行
#define LINEPERLIST				8
void Printer_IO_Config(void);
void printer_line(void);
void GPIO_ToggleBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void printer_timer_init(void);		// printer parameter init
void print_matrix_invert(void);		// matrix invert function



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

