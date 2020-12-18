# sculpter

![sculpter](imgur.com image replace me!)

*A modded version of the Microsoft Sculpt ergonomic keyboard.*

* Keyboard Maintainer: [Chris Paynter](https://github.com/yourusername)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

## How to build and flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

All commands are run from the root directory of the repository. The compiled files will be in the `.build` folder.

1. Install the QMK required submodules

   ```
   make git-submodule
   ```

2. Compile the layout (change `default` to build your keymaps)

   ```
   make sculpter:default
   ```

3. Flash the firmware to your keyboard

   ```
   make sculpter:default:flash
   ```

   The `Calculator` button at the top right of the keyboard is assigned as the reset button in default layout.

# Motivation

## Primary motivators
- I've used this keyboard for 5 years, and it helped me (for the most part) fix my RSI.
- I've previously moved to try using a mechanical keyboard that was QMK compatible.
- I tried hard to make it work, but it became evident that mechanical keyboards just don't feel as comfortable or productive to me as much as the Sculpt does.
- However, I still wanted to be able to program my keyboard with the power of QMK.
- The Sculpt is running Microsoft OEM software, and is not compatible.
- Thus, this mod!

## Secondary motivators
- The wireless connection is and has always been horribly flakey.
- The dongle they provide is locked to the keyboard. You lose that, you lose the keyboard.
- I've lost a few of them :(

# What to expect from this mod

- The Microsoft Sculpt is an ergonomic keyboard with 88 keys.
- You'll be able to run QMK on the keyboard, giving you infinite possibilities in programming the keys.
- The existing microcontroller will be removed and replaced with a QMK compatible one.

## There are caveats!!!

- **You'll lose wireless capability!** 
  - This mod make this a _wired_ keyboard.
  - If you're like me, this is desirable, as per my motivators above.
  - If you want to keep wirelss, this mod is not for you.
- **The function switch will become redundant**.
  - I never used it anyway in 6 years.
  - QMK can do way more than this switch ever could.

# Hardware Modification

Before using the QMK software, you have to make physical hardware modifications to your keyboard.

> A lot of this information has been repurposed from [this TMK based Sculpt mod](https://github.com/blttll/tmk_keyboard), which was been a huge help to me in figuring out how to modify the Sculpt to work with QMK. The PCB schematic also comes from this resource. A huge help!

At a top level it'll required you to:

- Pull the keyboard apart without breaking it.
- Remove the existing PCB.
- Replace with a new PCB that you will get fabricated.
- Solder components onto the new PCB.
- Cut new channels into the Sculpt chassis to accomodate the new USB wire.
- Put the keyboard back together.

## Parts List

- [Microsoft Sculpt](https://www.microsoft.com/accessories/en-us/products/keyboards/sculpt-ergonomic-desktop/l5v-00001)
- [Printed PCB](https://oshpark.com/profiles/choffee) (I found this already in Oshpark funnily enough)
- [FFC 30 Pin Connector](https://www.molex.com/molex/products/part-detail/ffc_fpc_connectors/0522713079)
- [Teensy 2.0](https://www.pjrc.com/store/teensy.html)
- USB Mini B to USB A cable (I used a 1.5 metre cable)

If you're new to soldering, then you'll need a soldering iron, solder wire and flux.

### Why the Teensy 2.0?

The Teensy has been around for a while and has been superceded by multple new versions of the Teensy. However, it's form factor works really well for this project, allowing us to fit it on our custom board and, together, fitting it in the existing cavity of the Sculpt chassis (albeit with a little bit of modification to the case).

## The Matrix

- The Microsoft hardware matrix doesn't change.
- The original key matrix is exposed via a 30 pin ribbon cable, with a 1mm pitch.
- We can simply pull this cable out of the existing PCB, and plug it into the new one.
- We'll make slight change to the matrix structure, however this is achieved on the custom PCB.

> Note that during this mod, I only cared about the US english layout version. However, the same principles apply to other languages. You just need to map the keys correctly into their respective rows and columns. If other languages interest you, raise a GitHub issue and I could probably help.

### The Original Matrix

This original matrix uses 8 rows and 18 columns, which requires 26 pins on the micro controller (on the Teensy 2.0 we don't have that many, but we solve this issue, keep reading)

**Important:** In code we reference these rows and columns with a zero index. From here on, the documentation also refers to columns using zero index. So if "column 2" is mentioned for example, physically this represents column 3. If you're not a programmer by trade, this might get a bit tricky to get used to, but it's important to remember this.

|       | 0    | 1     | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11   | 12   | 13   | 14   | 15   | 16   | 17   |
| ----- | ---- | ----- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| **0** |      | paus  |      | del  | 0    | 9    |      | 8    | bspc | 7    | tab  | Q    | 2    | 1    |      |      |      |      |
| **1** |      | pgup  |      | F12  | lbrc | mins |      | rbrc | ins  | Y    | F5   | F3   | W    | 4    |      | F6   |      |      |
| **2** |      | home  |      | calc | P    | O    |      | I    |      | U    | R    | E    | caps | 3    |      | T    |      |      |
| **3** |      | slck  |      | ent  | scln | L    |      | K    | bsls | J    | F    | D    |      | A    |      | lgui |      |      |
| **4** |      |       |      | app  | slsh | quot | ralt |      | left | H    | G    | F4   | S    | esc  |      |      | lalt |      |
| **5** |      | end   | rsft | pgdn |      | dot  |      | comm |      | M    | V    | C    | X    | Z    | lsft |      |      |      |
| **6** | lctl | right |      | up   | down |      |      |      | rspc | N    | B    | lspc |      |      |      |      |      | rctl |
| **7** |      | pscr  |      | F11  | eql  | F9   |      | F8   | F10  | F7   | 5    | F2   | F1   | grv  |      | 6    |      |      |

### The Modded Matrix

The Teensy 2.0 microcontroller we use in this mod doesn't have enough general purpose input/output (GPIO) pins to support each of the rows and columns in the physical keyboard matrix. We're one GPIO pin short - as mentioned, 8 + 18 = 26 total pins required.

The Teensy only has 25 GPIO pins. Luckily, (and as worked out by our [primary resource](https://github.com/blttll/tmk_keyboard)), it doesn't matter as we are able to "collapse" two of those columns into one, without any of the keys clashing. By collapsing these two columns, we can still support all the keys, and we now only need 25 GIPO pins.

This is achieved by physically bridging two of the traces in the flex connector via our custom PCB. In this case, we're bridging columns 2 and 6, which physically exist on traces 16 and 12. You can see this bridge in the scematic in the PCB section.

The layout table from above will now look like this. Columns 10-16 have additional letters, this will be explained soon.

|       | 0    | 1     | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10 (A) | 11 (B) | 12 (C) | 13 (D) | 14 (E) | 15 (F) | 16 (G) |
| ----- | ---- | ----- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| **0** |      | paus  |      | del  | 0    | 9    | 8    | bspc | 7    | tab  | Q      | 2      | 1      |        |        |        |        |
| **1** |      | pgup  |      | F12  | lbrc | mins | rbrc | ins  | Y    | F5   | F3     | W      | 4      |        | F6     |        |        |
| **2** |      | home  |      | calc | P    | O    | I    |      | U    | R    | E      | caps   | 3      |        | T      |        |        |
| **3** |      | slck  |      | ent  | scln | L    | K    | bsls | J    | F    | D      |        | A      |        | lgui   |        |        |
| **4** |      |       | ralt | app  | slsh | quot |      | left | H    | G    | F4     | S      | esc    |        |        | lalt   |        |
| **5** |      | end   | rsft | pgdn |      | dot  | comm |      | M    | V    | C      | X      | Z      | lsft   |        |        |        |
| **6** | lctl | right |      | up   | down |      |      | rspc | N    | B    | lspc   |        |        |        |        |        | rctl   |
| **7** |      | pscr  |      | F11  | eql  | F9   | F8   | F10  | F7   | 5    | F2     | F1     | grv    |        | 6      |        |        |

You'll see that `ralt` (right alt) and `rsft`  (right shift) now both reside in column 2, the original column 6 is now gone, and all the preceding columns have shifted down (thus, the original column 7 is now column 6, and so on).

### Mapping the modded layout in QMK

Now that we've modded the matrix to fit into the pins on the Teensy 2.0, we can create a [custom layout](https://github.com/qmk/qmk_firmware/blob/master/docs/hardware_avr.md#keyboardh) that allows QMK to work with the Sculpt. This is defined in `sculpter.h`

This looks insane, but there is a method to the madness.

The first section defines the physical layout of the keybord. So, `K4C` for example is the escape key, `K7B` is the F1 key, and so on. Think of it as modelling the layout of the keys on the physical device (refer to the matrix table above for keycodes). The key codes you see in this part effecitvely follow one for one the physical layout of the keyboard.

The second part maps these keys into the actual matrix structure that the QMK firmware uses to know which key/s a user is pressing at any given time. It allows QMK to map keys you press to the custom layouts that you create.

You'll see that the keynames follow the format `K{ROW}{COLUMN}`, and after column 9, we move to letters (i.e 10, 11,12,... is A,B,C,... etc). Each of these codes can be referenced in our matrix table above to know which key it represents on the physical keyboard.

`KC_NO` just means that we aren't using this key in the matrix.

```c
#define LAYOUT( \
  K4C, K7B, K7A, K1A, K4A, K19, K1E, K78, K76, K75, K77, K73, K13, K71, K31, K01, K23, \
  K7C, K0C, K0B, K2C, K1C, K79, K7E, K08, K06, K05, K04, K15, K74, K07     , K03, K21, \
  K09			, K0A, K1B, K2A, K29, K2E, K18, K28, K26, K25, K24, K14, K16, K37,      K51, \
  K2B     , K3C, K4B, K3A, K39, K49, K48, K38, K36, K35, K34, K45, K33     , K17, K11, \
  K5D			, K5C, K5B, K5A, K59, K69, K68		 , K58, K56, K55, K44, K52		 , K63, K53, \
  K60			, K3E, K4F, K6A, 					 K67, 					K42, K43, K6G			, K47, K64, K61 \
) { \
    { KC_NO, K01, KC_NO, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, K11, KC_NO, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, KC_NO, K1E, KC_NO, KC_NO, }, \
    { KC_NO, K21, KC_NO, K23, K24, K25, K26, KC_NO, K28, K29, K2A, K2B, K2C, KC_NO, K2E, KC_NO, KC_NO, }, \
    { KC_NO, K31, KC_NO, K33, K34, K35, K36, K37, K38, K39, K3A, KC_NO, K3C, KC_NO, K3E, KC_NO, KC_NO, }, \
    { KC_NO, KC_NO, K42, K43, K44, K45, KC_NO, K47, K48, K49, K4A, K4B, K4C, KC_NO, KC_NO, K4F, KC_NO, }, \
    { KC_NO, K51, K52, K53, KC_NO, K55, K56, KC_NO, K58, K59, K5A, K5B, K5C, K5D, KC_NO, KC_NO, KC_NO, }, \
    { K60,   K61, KC_NO, K63, K64, KC_NO, KC_NO, K67, K68, K69, K6A, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K6G, }, \
    { KC_NO, K71, KC_NO, K73, K74, K75, K76, K77, K78, K79, K7A, K7B, K7C, KC_NO, K7E  KC_NO, KC_NO, } \
}
```





## Connecting the Matrix to the Teensy 2.0

Before the Software can be utilised, you'll obviously need to mod the Sculpt itself.

![](./images/traces.png)



## Acknowledgements
The `pcb.brd` Eagle file for this project was taken from this TMK based Sculpt mod:
- https://github.com/blttll/tmk_keyboard/tree/master/keyboard/sculpt
