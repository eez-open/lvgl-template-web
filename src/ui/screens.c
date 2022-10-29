#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "../flow.h"

main_t *create_screen_main() {
    main_t *screen = (main_t *)lv_mem_alloc(sizeof(main_t));
    lv_obj_t *obj = lv_obj_create(0);
    screen->screen_obj = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            // label_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            screen->obj_label_1 = obj;
            lv_obj_set_pos(obj, 356, 232);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Hello, world!");
        }
    }
    return screen;
}

void tick_screen_main(main_t *screen) {
}


#include <assert.h>

typedef screen_t (*create_screen_func_t)();

create_screen_func_t create_screen_funcs[] = {
    (create_screen_func_t)create_screen_main,
};

typedef void (*tick_screen_func_t)(screen_t);

tick_screen_func_t tick_screen_funcs[] = {
    (tick_screen_func_t)tick_screen_main,
};

screen_t screens[NUM_SCREENS];

screen_t get_screen(int screen_index) {
    assert(screen_index >= 0 && screen_index < NUM_SCREENS);
    if (!screens[screen_index]) {
        screens[screen_index] = create_screen_funcs[screen_index]();
    }
    return screens[screen_index];
}

void tick_screen(int screen_index) {
    assert(screen_index >= 0 && screen_index < NUM_SCREENS);
    tick_screen_funcs[screen_index](get_screen(screen_index));
}
