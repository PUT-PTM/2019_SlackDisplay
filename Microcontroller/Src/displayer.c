#include "displayer.h"
#include "usbd_cdc_if.h"
void menu(int num_of_messe)
{

	int position=5;
	switch(position){



        case 5:
            lcd_clear();
            lcd_send_first_line("MENU");
            lcd_send_second_line(">>CHECK CHANNELS");
            HAL_Delay(100);

            break;
	}
}