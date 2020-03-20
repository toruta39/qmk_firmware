#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
    #include "lufa.h"
    #include "split_util.h"
#endif
#ifdef SSD1306OLED
    #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _GAME 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 5

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    BACKLIT,
    RGBRST,
    MP_HOME,
    MP_END,
    MP_PREV,
    MP_NEXT,
    MP_VOLDOWN,
    MP_VOLUP,
    MP_MUTE
};

enum macro_keycodes {
    KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_MAC   MAGIC_UNSWAP_ALT_GUI
#define KC_WIN   MAGIC_SWAP_ALT_GUI
#define KC_MMHOM MP_HOME
#define KC_MMEND MP_END
#define KC_MMPRV MP_PREV
#define KC_MMNXT MP_NEXT
#define KC_MMVOD MP_VOLDOWN
#define KC_MMVOU MP_VOLUP
#define KC_MMMUT MP_MUTE
#define KC_DFQWE DF(_QWERTY)
#define KC_DFCLM DF(_COLEMAK)
#define KC_TGGME TG(_GAME)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_kc( \
    //,-----------------------------------------.                ,-----------------------------------------.
          ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        CTLTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSFT,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                     LGUI, LOWER,   SPC,      ENT, RAISE,  RALT \
                                //`--------------------'  `--------------------'
    ),

    [_COLEMAK] = LAYOUT_kc( \
    //,-----------------------------------------.                ,-----------------------------------------.
        _____,     Q,     W,     F,     P,     G,                      J,     L,     U,     Y,  SCLN, _____,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        _____,     A,     R,     S,     T,     D,                      H,     N,     E,     I,     O,  QUOT,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        _____,     Z,     X,     C,     V,     B,                      K,     M,  COMM,   DOT,  SLSH, _____,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    _____, _____, _____,    _____, _____, _____ \
                                //`--------------------'  `--------------------'
    ),

    [_GAME] = LAYOUT_kc( \
    //,-----------------------------------------.                ,-----------------------------------------.
          TAB, _____, _____, _____, _____, _____,                  _____, _____,    UP, _____, _____, _____,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         LCTL, _____, _____, _____, _____, _____,                  _____,  LEFT,  DOWN, RIGHT, _____, _____,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        _____, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    _____, _____, _____,    _____, _____, _____ \
                                //`--------------------'  `--------------------'
    ),

    [_LOWER] = LAYOUT_kc( \
    //,-----------------------------------------.                ,-----------------------------------------.
        _____,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,    F8,    F9,   F10,  PSCR,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        _____,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  DQUO,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX,   F11,   F12, _____,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    _____, _____, _____,    _____, _____, _____ \
                                //`--------------------'  `--------------------'
    ),

    [_RAISE] = LAYOUT_kc( \
    //,-----------------------------------------.                ,-----------------------------------------.
         TILD,  EXLM,    AT,  LBRC,  RBRC,  UNDS,                   PLUS, MMHOM,    UP, MMEND,  TILD,   DEL,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        _____,  HASH,   DLR,  LPRN,  RPRN,  MINS,                    EQL,  LEFT,  DOWN, RIGHT,  PIPE,   GRV,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        _____,  PERC,  CIRC,  LCBR,  RCBR,  AMPR,                   ASTR,   INS,  HOME,   END,  BSLS, _____,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    _____, _____, _____,    _____, _____, _____ \
                                //`--------------------'  `--------------------'
    ),

    [_ADJUST] = LAYOUT_kc( \
    //,-----------------------------------------.                ,-----------------------------------------.
          RST,  LRST,   MAC,   WIN, XXXXX, XXXXX,                  XXXXX, MMPRV,  MPLY, MMNXT, XXXXX, XXXXX,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  XXXXX, MMMUT, MMVOD, MMVOU, XXXXX, XXXXX,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, DFQWE, DFCLM, TGGME, XXXXX, XXXXX,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    _____, _____, _____,    _____, _____, _____ \
                                //`--------------------'  `--------------------'
    )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}

void matrix_init_user(void) {
        #ifdef RGBLIGHT_ENABLE
            RGB_current_mode = rgblight_config.mode;
        #endif
        //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
        #ifdef SSD1306OLED
                iota_gfx_init(!has_usb());   // turns on the display
        #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_state(void);
const char *read_logo(void);
// const char *read_layer_state(void);
// void set_keylog(uint16_t keycode, keyrecord_t *record);
// const char *read_keylog(void);
// const char *read_keylogs(void);
// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
     iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        // If you want to change the display of OLED, you need to change here
        // matrix_write_ln(matrix, read_layer_state());
        // matrix_write_ln(matrix, read_keylog());
        // matrix_write_ln(matrix, read_keylogs());
        // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
        // matrix_write_ln(matrix, read_host_led_state());
        // matrix_write_ln(matrix, read_timelog());
        matrix_write(matrix, read_state());
    } else {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_mp_key(uint16_t keycode, keyrecord_t *record, bool is_windows) {
    uint16_t final_modifier_keycode = 0;
    uint16_t final_keycode = 0;

    switch (keycode) {
        case MP_HOME:
            final_modifier_keycode = is_windows ? 0 : KC_LGUI;
            final_keycode = is_windows ? KC_HOME : KC_LEFT;
            break;
        case MP_END:
            final_modifier_keycode = is_windows ? 0 : KC_LGUI;
            final_keycode = is_windows ? KC_END : KC_RGHT;
            break;
        case MP_PREV:
            final_keycode = is_windows ? KC_MPRV : KC_MRWD;
            break;
        case MP_NEXT:
            final_keycode = is_windows ? KC_MNXT : KC_MFFD;
            break;
        case MP_MUTE:
            final_keycode = is_windows ? KC_MUTE : KC__MUTE;
            break;
        case MP_VOLDOWN:
            final_keycode = is_windows ? KC_VOLD : KC__VOLDOWN;
            break;
        case MP_VOLUP:
            final_keycode = is_windows ? KC_VOLU : KC__VOLUP;
            break;
    }

    if (!final_keycode) return false;

    if (record->event.pressed) {
        if (final_modifier_keycode) register_code(final_modifier_keycode);
        register_code(final_keycode);
    } else {
        unregister_code(final_keycode);
        if (final_modifier_keycode) unregister_code(final_modifier_keycode);
    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
#ifdef SSD1306OLED
        // set_keylog(keycode, record);
        // set_timelog();
#endif
    }

    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
        case RGB_MOD:
            #ifdef RGBLIGHT_ENABLE
                if (record->event.pressed) {
                    rgblight_mode(RGB_current_mode);
                    rgblight_step();
                    RGB_current_mode = rgblight_config.mode;
                }
            #endif
            return false;
            break;
        case RGBRST:
            #ifdef RGBLIGHT_ENABLE
                if (record->event.pressed) {
                    eeconfig_update_rgblight_default();
                    rgblight_enable();
                    RGB_current_mode = rgblight_config.mode;
                }
            #endif
            break;
        case MP_HOME:
        case MP_END:
        case MP_PREV:
        case MP_NEXT:
        case MP_MUTE:
        case MP_VOLDOWN:
        case MP_VOLUP:
            return process_mp_key(keycode, record, keymap_config.swap_lalt_lgui);
            break;
    }
    return true;
}
