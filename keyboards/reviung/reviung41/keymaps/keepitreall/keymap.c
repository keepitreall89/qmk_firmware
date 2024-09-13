/* Copyright 2019 gtips
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

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define KC_CAD LALT(LCTL(KC_DEL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung41(
    KC_BSPC,   	KC_QUOT,	KC_COMM,	KC_DOT,	KC_P,	KC_Y,		KC_F,	KC_G,	KC_C,	KC_R,	KC_L,	KC_BSPC,
    KC_TAB,  	KC_A,     	KC_O,     	KC_E,	KC_U,	KC_I,		KC_D,	KC_H,	KC_T,	KC_N,	KC_S,  	KC_TAB,
    KC_LCTL,  	KC_SCLN,    KC_Q,     	KC_J,   KC_K,   KC_X,   	KC_B,   KC_M,   KC_W,  	KC_V,   KC_Z,  	KC_ENT,
                                                     KC_LALT, LOWER,    KC_SPC,   RAISE, LOWER
  ),
  
  [_LOWER] = LAYOUT_reviung41(
    KC_ESC,  KC_GRV,  KC_NO,      KC_NO,      KC_CAD,     LGUI(KC_L), 		KC_ESC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,  	KC_DEL,
    KC_MINS, KC_ASTR, KC_SLASH,	  KC_LBRC,	  KC_LPRN,	  KC_LCBR,	  		KC_AT,   KC_QUES, KC_HASH, KC_EQL,  KC_AMPR,	KC_NO,
    KC_LSFT, OSM(MOD_LGUI),	  LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_NO,      		KC_NO,   KC_NO,	  KC_NO,   KC_NO,	KC_NO,	KC_NO,
                                                     _______,  _______,  KC_SPC,   _______, _______
  ),
  
  [_RAISE] = LAYOUT_reviung41(
    KC_NO,  		KC_HOME,   		KC_UP,     		KC_END,	KC_NO, LGUI(KC_L),      KC_NUM,  KC_PSLS, KC_PMNS, KC_P7, KC_P8, KC_P9,
    KC_NO,  		KC_LEFT,  		KC_DOWN,   		KC_RGHT,KC_NO, KC_NO,      KC_NO,   KC_PAST, KC_PPLS, KC_P4, KC_P5, KC_P6,
    OSM(MOD_LCTL),  OSM(MOD_LALT),  KC_NO,  KC_NO,  KC_NO, KC_NO,      KC_PEQL, KC_PDOT, KC_P0,   KC_P1, KC_P2, KC_P3,
													_______, _______,  KC_SPC,  _______, _______
  ),
  
  [_ADJUST] = LAYOUT_reviung41(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
	KC_NO  ,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            KC_NO,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                      KC_NO, _______,  XXXXXXX,  _______, _______
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

/*
 * The three functions below allow 2 symbols to be on the same key controlled by autoshift
 * example ( and )
 */
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case KC_AMPR:
			return true;
		case KC_ASTR:
			return true;
		case KC_LPRN:
			return true;
		case KC_LCBR:
			return true;
		case KC_QUES:
			return true;
		case KC_AT:
			return true;
		case KC_HASH:
			return true;
		case KC_ENT:
			return true;
		default:
			return false;
	}
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
    	case KC_AMPR:
            register_code16((!shifted) ? KC_AMPR : KC_DLR);
            break;
    	case KC_ASTR:
            register_code16((!shifted) ? KC_ASTR : KC_PERC);
            break;
        case KC_SLASH:
            register_code16((!shifted) ? KC_SLASH : KC_BSLS);
            break;
        case KC_LBRC:
            register_code16((!shifted) ? KC_LBRC : KC_RBRC);
            break;
        case KC_LPRN:
            register_code16((!shifted) ? KC_LPRN : KC_RPRN);
            break;
        case KC_LCBR:
            register_code16((!shifted) ? KC_LCBR : KC_RCBR);
            break;
        case KC_QUES:
            register_code16((!shifted) ? KC_QUES : KC_EXLM);
            break;
        case KC_AT:
            register_code16((!shifted) ? KC_AT : KC_CIRC);
            break;
        case KC_HASH:
        	register_code16((!shifted) ? KC_HASH : KC_PIPE);
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
    	case KC_AMPR:
            unregister_code16((!shifted) ? KC_AMPR : KC_DLR);
            break;
    	case KC_ASTR:
           	unregister_code16((!shifted) ? KC_ASTR : KC_PERC);
            break;
        case KC_SLASH:
            unregister_code16((!shifted) ? KC_SLASH : KC_BSLS);
            break;
        case KC_LBRC:
            unregister_code16((!shifted) ? KC_LBRC : KC_RBRC);
            break;
        case KC_LPRN:
            unregister_code16((!shifted) ? KC_LPRN : KC_RPRN);
            break;
        case KC_LCBR:
            unregister_code16((!shifted) ? KC_LCBR : KC_RCBR);
            break;
        case KC_QUES:
            unregister_code16((!shifted) ? KC_QUES : KC_EXLM);
            break;
        case KC_AT:
            unregister_code16((!shifted) ? KC_AT : KC_CIRC);
            break;
        case KC_HASH:
        	unregister_code16((!shifted) ? KC_HASH : KC_PIPE);
        	break;
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}
