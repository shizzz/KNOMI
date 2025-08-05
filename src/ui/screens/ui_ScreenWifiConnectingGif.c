#include "../ui.h"

void ui_ScreenWifiConnectingGif_screen_init(void)
{
    ui_ScreenWifiConnectingGif = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenWifiConnectingGif, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenWifiConnectingGif, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenWifiConnectingGif, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ScreenWifiConnectingGif, ui_event_ScreenWifiConnectingGif, LV_EVENT_ALL, NULL);

    ui_ScreenMainGif = lv_gif_create(ui_ScreenWifiConnectingGif);
    lv_gif_set_src(ui_ScreenMainGif, &gif_standby);
    lv_obj_clear_flag(ui_ScreenMainGif, LV_OBJ_FLAG_CLICKABLE);
}