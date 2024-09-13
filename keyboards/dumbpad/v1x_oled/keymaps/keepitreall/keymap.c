/* Copyright 2020 imchipwood
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /*
            BASE LAYER
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |  Bkspc  |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |   * \   |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |   +  -  |
    |-------------|---------|---------|---------|---------|
    | L, R        | .       |    0    | Enter   |  LayerUP|
    \-----------------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_P7,		KC_P8,		KC_P9,		KC_BSPC,
                    KC_P4,		KC_P5,		KC_P6,		KC_PAST,
                    KC_P1,		KC_P2,		KC_P3,		KC_PPLS,
	KC_NUM,			KC_PDOT,	KC_P0,		KC_PENT,	TT(1)
    ),
    /*
            BASE LAYER
    /-----------------------------------------------------`
    |             |         |         |         |         |
    |             |---------|---------|---------|---------|
    |             |         |         |         |         |
    |             |---------|---------|---------|---------|
    |             |  Home   |   UP    |  End    |         |
    |-------------|---------|---------|---------|---------|
    | Volume      | Left    |   Down  | Right   |         |
    \-----------------------------------------------------'
    */
    [1] = LAYOUT(
                    KC_NO,		KC_NO,	KC_NO,		KC_NO,
					KC_NO,		KC_NO,	KC_NO,		KC_NO,
					KC_HOME,	KC_UP,	KC_END,		KC_NO,
	KC_NO,			KC_LEFT,	KC_DOWN,KC_RGHT,	KC_TRNS
    )
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][1] ={
		[0] = { ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
		[1] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) }
};
#endif

/*
 * The three functions below allow 2 symbols to be on the same key controlled by autoshift
 * example ( and )
 */
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case KC_PAST:
			return true;
		case KC_PPLS:
			return true;
		default:
			return false;
	}
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_PAST:
            register_code16((!shifted) ? KC_PAST : KC_PSLS);
            break;
        case KC_PPLS:
        	register_code16((!shifted) ? KC_PPLS : KC_PMNS);
        	break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_PAST:
            unregister_code16((!shifted) ? KC_PAST : KC_PSLS);
            break;
        case KC_PPLS:
        	unregister_code16((!shifted) ? KC_PPLS : KC_PMNS);
        	break;
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}
