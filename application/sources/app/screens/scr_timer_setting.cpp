#include "scr_timer_setting.h"
using namespace std;

static void view_scr_timer_setting();

view_dynamic_t dyn_view_timer_setting = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_timer_setting};

view_screen_t scr_timer_setting = {
	&dyn_view_timer_setting,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};
int flag = 0;
void view_scr_timer_setting()
{
	char buf[10]; // buffer chuỗi

	// clear vùng hiển thị cũ
	view_render.fillRect(0, 0, 128, 64, BLACK);

	// Vẽ khung (nếu cần)
	view_render.drawRect(0, 0, 128, 64, WHITE);

    sprintf(buf, "%d", flag);   // In số nguyên flag
	
	

	view_render.setTextSize(2);
	view_render.setTextColor(WHITE);

	// Tính toán để căn giữa
	int charWidth = 6 * 2; // font 6px, scale x2
	int textWidth = strlen(buf) * charWidth;
	int x = (128 - textWidth) / 2;

	int charHeight = 8 * 2; // font 8px, scale x2
	int y = (64 - charHeight) / 2;

	view_render.setCursor(x, y);
	view_render.print(buf);
}
void scr_timer_setting_handle(ak_msg_t *msg)
{
	switch (msg->sig)
	{
	case SCREEN_ENTRY:
	{
		APP_DBG_SIG("SCREEN_ENTRY\n");
		// task_post_pure_msg(AC_RF24_PHY_ID, AC_RF24_PHY_REV_MODE_REQ);
		// timer_set(AC_TASK_DISPLAY_ID,
		// 		  AC_DISPLAY_TEST,
		// 		  100, TIMER_PERIODIC);	
		}
	break;

	case AC_DISPLAY_BUTON_MODE_RELEASED:
	{
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED4\n");
		SCREEN_TRAN(scr_timer_handle, &scr_timer);
	}
	break;

	case AC_DISPLAY_BUTON_UP_RELEASED:
	{
		// if (flag == 1)
		// {
			APP_DBG_SIG("AC_DISPLAY_SEND\n");
		// task_post_pure_msg(AC_TASK_RF24_IF_ID, AC_RF24_IF_PURE_MSG_OUT);
		// }
		
	}
	break;

	case AC_DISPLAY_BUTON_DOWN_RELEASED:
	{
		// if (flag == 0)
		// {
			
		// 	APP_DBG_SIG("RF REV MODE\n");
		// 	flag = 1;
		// }
		// else
		// {
		// 	APP_DBG_SIG("RF SEND MODE\n");
		// 	// task_post_pure_msg(AC_RF24_PHY_ID, AC_RF24_PHY_SEND_MODE_REQ);
		// 	set_mac_send_state(MAC_SEND_STATE_SENDING); 

		// 	flag = 0;
		// }
	}
	break;

	case AC_DISPLAY_TEST:
	{
		flag++;
		// if (flag == 0)
		// {
			
		// 	APP_DBG_SIG("RF REV MODE\n");
		// 	flag = 1;
		// }
		// else
		// {
		// 	APP_DBG_SIG("RF SEND MODE\n");
		// 	// task_post_pure_msg(AC_RF24_PHY_ID, AC_RF24_PHY_SEND_MODE_REQ);
		// 	set_mac_send_state(MAC_SEND_STATE_SENDING); 

		// 	flag = 0;
		// }
	}
	break;
	default:
		break;
	}
}
