# sculpter

![sculpter](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Chris Paynter](https://github.com/yourusername)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*


## How to build
All commands are run from the root directory of the repository.


First, make sure you have the required submodules.

    make git-submodule


Make example for this keyboard (after setting up your build environment):

    make sculpter:default

Flashing example for this keyboard:

    make sculpter:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

The outputted files will be in the `.build` folder.

## How to load the firmware onto the keyboard
After building, as per above, you'll see a hex file in the `.build` folder at the root of the repository.

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

We will not be changing the original Microsoft wiring of the key matrix.

- The original key matrix is exposed via a 30 pin ribbon cable, with a 1mm pitch.
- We can simply pull this cable out of the existing PCB, and plug it into the new one.
- We will be changing the number of columns however, but this is done in our PCB, read on.

> Note that during this mod, I only cared about the US english layout version. However, the same principles apply to other languages. You just need to map the keys correctly into their respective rows and columns. If other languages interest you, raise a GitHub issue and I could probably help.

### The Original Layout

This original matrix uses 8 rows and 18 columns, which requires 26 pins on the micro controller (but we don't have that, see the following information)

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

### Modded US Layout

The Teensy 2.0 microcontroller we use in this mod doesn't have enough general purpose input/output (GPIO) pins to support each of the rows and columns in the physical keyboard matrix, one for one. We're one GPIO pin short - as mentioned, 8 + 18 = 26 total pins required.

The Teensy only has 25 GPIO pins. Luckily, (and as worked out by our [primary resource](https://github.com/blttll/tmk_keyboard)), it doesn't matter as we are able to "collapse" at least two of those columns in the original layout, without any of the keys clashing. By collapsing these two columns, we can still support all the keys, but we required one GPIO pin less to do so, thus, we can use the Teensy 2.0

This is achieved by physically bridging two of the traces in the flex connector via our custom PCB. In this case, we're bridging columns 2 and 6, which physically exist on traces 16 and 12.

The layout table from above will now look like this.

|       | 0    | 1     | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11   | 12   | 13   | 14   | 15   | 16   |
| ----- | ---- | ----- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| **0** |      | paus  |      | del  | 0    | 9    | 8    | bspc | 7    | tab  | Q    | 2    | 1    |      |      |      |      |
| **1** |      | pgup  |      | F12  | lbrc | mins | rbrc | ins  | Y    | F5   | F3   | W    | 4    |      | F6   |      |      |
| **2** |      | home  |      | calc | P    | O    | I    |      | U    | R    | E    | caps | 3    |      | T    |      |      |
| **3** |      | slck  |      | ent  | scln | L    | K    | bsls | J    | F    | D    |      | A    |      | lgui |      |      |
| **4** |      |       | ralt | app  | slsh | quot |      | left | H    | G    | F4   | S    | esc  |      |      | lalt |      |
| **5** |      | end   | rsft | pgdn |      | dot  | comm |      | M    | V    | C    | X    | Z    | lsft |      |      |      |
| **6** | lctl | right |      | up   | down |      |      | rspc | N    | B    | lspc |      |      |      |      |      | rctl |
| **7** |      | pscr  |      | F11  | eql  | F9   | F8   | F10  | F7   | 5    | F2   | F1   | grv  |      | 6    |      |      |

You'll see that `ralt` and `rsft` now both reside in column 2, the original column 6 is now gone, and all the preceding columns have shifted down (thus, the original column 7 is now column 6, and so on).

### Mapping the modded layout in QMK

Now that we've modded the matrix to fit into the pins on the Teensy 2.0, we can create a [custom layout](https://github.com/qmk/qmk_firmware/blob/master/docs/hardware_avr.md#keyboardh) that allows QMK to work with the Sculpt. This is defined in `sculpter.h`



## Connecting the Matrix to the Teensy 2.0

Before the Software can be utilised, you'll obviously need to mod the Sculpt itself.

![](./images/traces.png)



## Acknowledgements
The `pcb.brd` Eagle file for this project was taken from this TMK based Sculpt mod:
- https://github.com/blttll/tmk_keyboard/tree/master/keyboard/sculpt
