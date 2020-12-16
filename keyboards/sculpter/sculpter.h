/* Copyright 2020 Chris Paynter
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

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 * 
 * Each of the k__ variables needs to be unique, and typically they follow the format k<row><col>.
 */
#define LAYOUT( \
  /**/ K01, /**/ K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, /**/ /**/ /**/ /**/ \
  /**/ K11, /**/ K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, /**/ K1E, /**/ /**/ \
  /**/ K21, /**/ K23, K24, K25, K26, /**/ K28, K29, K2A, K2B, K2C, /**/ K2E, /**/ /**/ \
  /**/ K31, /**/ K33, K34, K35, K36, K37, K38, K39, K3A, /**/ K3C, /**/ K3E, /**/ /**/ \
  /**/ /**/ K42, K43, K44, K45, /**/ K47, K48, K49, K4A, K4B, K3C, /**/ /**/ K3F, /**/ \
  /**/ K51, K52, K53, /**/ K55, K56, /**/ K58, K59, K5A, K5B, K5C, K5D, /**/ /**/ /**/ \
  K60, K61, /**/ K63, K64, /**/ /**/ K67, K68, K69, K6A, /**/ /**/ /**/ /**/ /**/ K6G, \
  /**/ K71, /**/ K73, K74, K75, K76, K67, K68, K69, K6A, K6B, K6C, /**/ K7E  /**/ /**/ \
) { \
    { k00, k01,   k02 }, \
    { k10, KC_NO, k12 }  \
}
