#include "displayer.h"
#include "usbd_cdc_if.h"
void menu(int num_of_messe)
{
	while(1)
	{
	int position=1;
	switch(position){
	case 0:
		lcd_clear();
		lcd_send_cmd(0x80);
		lcd_send_string("MENU");
		lcd_send_cmd(0xc0);
		lcd_send_string("NEW MESSEGES- ");
		lcd_send_integer(num_of_messe);
		HAL_Delay(1000);
		break;
	case 1:
		lcd_clear();
		lcd_send_cmd(0x80);
		lcd_send_string(">>MENU");
		lcd_send_cmd(0xc0);
		lcd_send_string("NEW MESSEGES- ");
		lcd_send_integer(num_of_messe);
		HAL_Delay(1000);

		break;
	case 2:
		lcd_clear();
		lcd_send_cmd(0x80);
		lcd_send_string("CHECK MESSEGES");
		lcd_send_cmd(0xc0);
		lcd_send_string("CHECK CHANNELS");
		lcd_send_integer(num_of_messe);
		HAL_Delay(1000);
		break;
	case 3:
		lcd_clear();
		lcd_send_cmd(0x80);
		lcd_send_string(">>CHECK MESSEGES");
		lcd_send_cmd(0xc0);
		lcd_send_string("CHECK CHANNELS");
		lcd_send_integer(num_of_messe);
		HAL_Delay(1000);
		break;
	case 4:
		lcd_clear();
		lcd_send_cmd(0x80);
		lcd_send_string("CHECK MESSEGES");
		lcd_send_cmd(0xc0);
		lcd_send_string(">>CHECK CHANNELS");
		lcd_send_integer(num_of_messe);
		HAL_Delay(1000);
		break;

	}
	}
}