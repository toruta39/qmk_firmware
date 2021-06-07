#include <stdio.h>
#include "crkbd.h"

extern keymap_config_t keymap_config;

char state_str[24];
char layers[6][8] = {
    "0",
    "1",
    "2",
    "3"
};

const char *read_state(void) {
    snprintf(
        state_str,
        sizeof(state_str),
        "LAYER:%s OS:%s",
        layers[biton32(layer_state)],
        keymap_config.swap_lalt_lgui == true ? "MAC" : "WIN");

    return state_str;
}
