#include <stdio.h>
#include "crkbd.h"

extern keymap_config_t keymap_config;

char state_str[24];
char layers[6][8] = {
    "DEFAULT",
    "GAME   ",
    "LOWER  ",
    "RAISE  ",
    "ADJUST "
};

const char *read_state(void) {
    snprintf(
        state_str,
        sizeof(state_str),
        "L:%s OS:%s",
        layers[biton32(layer_state)],
        keymap_config.swap_lalt_lgui == false ? "MAC" : "WIN");

    return state_str;
}
