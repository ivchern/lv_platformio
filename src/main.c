#include "lvgl.h"
#include "app_hal.h"

#define LV_USE_ILI9341  1

void create_main_menu(lv_obj_t * parent);
void create_file_menu(lv_obj_t * parent, lv_obj_t * prev_scr);

lv_obj_t * prev_scr = NULL;
lv_obj_t * label_time;
lv_obj_t * label_battery;

void create_status_bar(lv_obj_t * parent) {
    // Create a container for the status bar
    lv_obj_t * status_bar = lv_menu_cont_create(parent);
    lv_obj_align(status_bar, LV_ALIGN_TOP_MID, 0, 0);  // Align to the top of the screen

    // Create label for time
    label_time = lv_label_create(status_bar);
    lv_label_set_text(label_time, "00:00");  // Initial text for time
    lv_obj_align(label_time, LV_ALIGN_RIGHT_MID, 10, 0);  // Align to the left inside the status bar

    // Create label for battery percentage
    label_battery = lv_label_create(status_bar);
    lv_label_set_text(label_battery, LV_SYMBOL_BATTERY_FULL);  // Initial text for battery percentage
    lv_obj_align(label_battery, LV_ALIGN_RIGHT_MID, 20, 0);  // Align to the right inside the status bar

}


void menu_event_handler(lv_event_t * e) {
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_t * list = lv_obj_get_parent(obj);
    const char * txt = lv_list_get_button_text(list, obj);

    // Создание нового экрана
    lv_obj_t * new_scr = lv_obj_create(NULL);

    if (strcmp(txt, "New File") == 0) {
        // Создаем новое меню или элементы для "New File"
        create_file_menu(new_scr, lv_scr_act());
    } else {
        // Создаем основное меню на новом экране
        create_main_menu(new_scr);
    }

    // Загрузка нового экрана
    lv_scr_load(new_scr);
}

void back_event_handler(lv_event_t * e) {
    // Возвращаемся на предыдущий экран
    if (prev_scr) {
        lv_scr_load(prev_scr);
        prev_scr = NULL;  // Обнуляем, чтобы предотвратить повторный возврат
    }
}

void settings_event_handler(lv_event_t * e){

    // lv_obj_t * obj_target = lv_event_get_target(e);
    // lv_obj_t * obj_parent = lv_obj_get_parent(obj_target);

    lv_obj_t * new_scr = lv_obj_create(NULL);

    lv_obj_t * list = lv_list_create(new_scr);
    lv_obj_align(list, LV_ALIGN_CENTER, 0, 0);
    create_status_bar(list);

    lv_obj_t * btn;

    btn = lv_list_add_btn(list, LV_SYMBOL_SETTINGS, "GPS");
    lv_obj_add_event_cb(btn, menu_event_handler, LV_EVENT_CLICKED, NULL);

    // Устанавливаем размер списка
    lv_obj_set_size(list, 240,320);
    lv_scr_load(new_scr);
}

void create_main_menu(lv_obj_t * parent) {
    // Создаем список
    lv_obj_t * list = lv_list_create(parent);
    lv_obj_align(list, LV_ALIGN_CENTER, 0, 0);
    create_status_bar(list);

    // Добавляем элементы списка
    lv_obj_t * btn;

    btn = lv_list_add_btn(list, LV_SYMBOL_SETTINGS, "Settings");
    lv_obj_add_event_cb(btn, settings_event_handler, LV_EVENT_CLICKED, NULL);

    btn = lv_list_add_btn(list, LV_SYMBOL_DIRECTORY, "TEST2");
    lv_obj_add_event_cb(btn, menu_event_handler, LV_EVENT_CLICKED, NULL);

    btn = lv_list_add_btn(list, LV_SYMBOL_CLOSE, "TEST3");
    lv_obj_add_event_cb(btn, menu_event_handler, LV_EVENT_CLICKED, NULL);

    btn = lv_list_add_btn(list, LV_SYMBOL_EDIT, "TEST4");
    lv_obj_add_event_cb(btn, menu_event_handler, LV_EVENT_CLICKED, NULL);

    btn = lv_list_add_btn(list, LV_SYMBOL_SAVE, "TEST5");
    lv_obj_add_event_cb(btn, menu_event_handler, LV_EVENT_CLICKED, NULL);

    // Устанавливаем размер списка
    lv_obj_set_size(list, 240,320);
}


void create_file_menu(lv_obj_t * parent, lv_obj_t * prev_scr_ref) {
    prev_scr = prev_scr_ref;

    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_size(cont, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL)); 
    lv_obj_align(cont, LV_ALIGN_CENTER, 0, 0);
    create_status_bar(cont);
    lv_obj_set_size(cont, 240,320);

    // Создаем кнопку "Назад"
    lv_obj_t * btn_back = lv_btn_create(cont);
    lv_obj_align(btn_back, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(btn_back, back_event_handler, LV_EVENT_CLICKED, NULL);

    // lv_obj_t * label_back = lv_label_create(btn_back);
    // lv_label_set_text(label_back, "Back");

    // Создаем метку для нового меню
    lv_obj_t * label = lv_label_create(cont);
    lv_label_set_text(label, "New File Selected");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

int main(void)
{
	lv_init();

	hal_setup();
  lv_obj_t * base_scr = lv_scr_act();
  lv_obj_set_size(base_scr, 240,320);
  create_main_menu(base_scr);
  // lv_demo_widgets();
	hal_loop();
}
