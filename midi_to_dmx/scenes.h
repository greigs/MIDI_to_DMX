/**
 * Scene Definitions.  This mode operates with the MIDI Note On command, and
 * specifies a full scene for each "Note" value sent.  The programming is,
 * sadly, a bit complex, due to limitations in the C++ standard the Arduino
 * environment uses.
 * 
 * The maximum scene number is 127, and it's wise to leave Scene 0 as a full
 * black scene (not required, but it's a good convention).
 * 
 * Programming is described in each section, but if this makes no sense at all,
 * it's probably better to use the fixture mode or the raw DMX mode to program
 * your lights.  You can contact the author for assistance if needed, though
 * free assistance is somewhat limited due to lack of free time.
 * 
 * If you'd like to define your own scenes, you'll need to start by laying out
 * all the DMX channels you use that need to be set (you can ignore channels set
 * in the fixed channel header as they will never change).  This example list
 * will be referenced in several places.
 * 
 * For the example, the following channels/lights are in use:
 * 4: White stage spotlights
 * 6: White congregation overhead lights
 * 66, 67, 68: RGB "side wash" lights
 * 1, 2, 3: RGB "stage edge" lights
 * 8, 9, 10: RGB "stage center" lights
 */

// Set this to however many scenes you have defined below.
#define MAX_SCENE_COUNT 19

// This must be set to the number of unique channels being controlled.
// In the example/my setup, this is 11 channels.
#define MAX_UNIQUE_CHANNELS 16

/**
 * The definitions here are the tricky part, and are tricky mostly because of
 * the C++ standards for sparse array are worse than in C, especially GNU C.
 * 
 * What's happening is that the scene array is being initialized with a series
 * of values in sequential order, but the illusion is given of specifying
 * brightness or color values for each fixture.  A set of defines and a
 * conversion array accomplish this slightly easier to read format.  But,
 * realistically, someone who knows C is probably going to have to set this up
 * the first time.
 * 
 * While going through here, remember that the colors are defined as a comma
 * separated list of the three RGB values:
 * #define COLOR_MAGENTA 255, 0, 255
 * 
 * And the brightness defines are a single value:
 * #define BRIGHTNESS_HIGH 192
 * 
 * The scene_slot_to_channel_mapping translates from the position of the value
 * in each scene to the DMX channel controlled by that position - so, for my
 * example, position 0 (stage spots) is actually controlling DMX channel 4.
 * 
 * For single channel fixtures, you only need one entry.  For RGB fixtures, you
 * need three (one for each channel).  The defines are in R, G, B order, so if
 * you have some bizarre fixture that doesn't have them aligned the same way,
 * this allows you to twiddle the values around and line things up so they work.
 * 
 * Once each of these entries is defined, create a define (below) to indicate
 * the position that each field starts in.  This allows you to define scene
 * arrays that are reasonably readable.
 * 
 * What actually happens, if you take the example scene 1, is this:
 * [1] = {
 *   [0] = 64,
 *   [1] = 255,
 *   [2] = 255, 128, 0,
 *   [5] = 0, 0, 255,
 *   [8] = 0, 0, 255,
 * },
 * 
 * Since there are no gaps, the compiler is happy.  If there is a gap, you get
 * an error:
 * sorry, unimplemented: non-trivial designated initializers not supported
 * 
 * That means that you need to go through and check your mappings again, because
 * there's a gap somewhere.
 * 
 * Alternately, if you wanted, you could just define scene 1 like this:
 * 
 * [1] = {64, 255, 255, 128, 0, 0, 0, 255, 0, 0, 255},
 * 
 * Or, like this:
 * [1] = {
 *   BRIGHTNESS_LOW,
 *   BRIGHTNESS_FULL,
 *   COLOR_BLUE,
 *   COLOR_ORANGE,
 *   COLOR_ORANGE
 * },
 * 
 * It's up to you - I feel my method is the most readable, but does require a
 * bit more upfront work.
 * 
 * Regardless of what method you use, go about setting up your scenes as
 * desired, and things should work!
 */

const PROGMEM byte scene_slot_to_channel_mapping[MAX_UNIQUE_CHANNELS] = {
  1,2,3,4,      // Light 1 - GlobalBrightness,R,G,B
  10,11,12,13, // Light 2 - GlobalBrightness,R,G,B
  20,21,22,23, // Light 3 - GlobalBrightness,R,G,B
  30,31,32,33 // Light 4 - GlobalBrightness,R,G,B
};


// RGB: 3 channels - slots 2, 3, 4
#define WASH_LIGHTS 0


/**
 * For no particular reason, the following color combos are used (wash/stage):
 * 1: Orange/Blue
 * 2: Blue/Orange
 * 3: Blue/Green
 * 4: Red/Blue
 * 5: White/Green
 * 6: Magenta/Cyan
 * 7: Yellow/Green
 * 8: Cyan/Red
 * 9: Green/Blue
 * 10: Green/Red
 * 11: Red/Purple
 * 12: Purple/Red
 * 13: White/Red
 * 14: Green/Purple
 * 15: Blue/Blue
 * 16: Red/Red
 * 17: Green/Green
 * 18: White/White 
 */


// Scenes!  Program at will.
const PROGMEM byte scenes[MAX_SCENE_COUNT][MAX_UNIQUE_CHANNELS] = {
  // Scene 0: Lights off.
  [0] = {
    BRIGHTNESS_FULL,0,0,0,
    BRIGHTNESS_FULL,0,0,0,
    BRIGHTNESS_FULL,0,0,0,
    BRIGHTNESS_FULL,0,0,0
  },
  // Scene 1
  [1] = {
    BRIGHTNESS_FULL, COLOR_ORANGE,
    BRIGHTNESS_FULL, COLOR_BLUE,
    BRIGHTNESS_FULL, COLOR_ORANGE,
    BRIGHTNESS_FULL, COLOR_BLUE
  },
  [2] = {
    BRIGHTNESS_FULL, COLOR_BLUE,
    BRIGHTNESS_FULL, COLOR_ORANGE,
    BRIGHTNESS_FULL, COLOR_BLUE,
    BRIGHTNESS_FULL, COLOR_ORANGE
  },
  [3] = {
    BRIGHTNESS_FULL, COLOR_BLUE,
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_BLUE,
    BRIGHTNESS_FULL, COLOR_GREEN
  },
  [4] = {
    BRIGHTNESS_FULL, COLOR_RED,
    BRIGHTNESS_FULL, COLOR_BLUE,
    BRIGHTNESS_FULL, COLOR_RED,
    BRIGHTNESS_FULL, COLOR_BLUE,
  },
  [5] = {
    BRIGHTNESS_FULL, COLOR_WHITE,
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_WHITE,
    BRIGHTNESS_FULL, COLOR_GREEN
  },
  [6] = {
    BRIGHTNESS_FULL, COLOR_MAGENTA,
    BRIGHTNESS_FULL, COLOR_CYAN,
    BRIGHTNESS_FULL, COLOR_MAGENTA,
    BRIGHTNESS_FULL, COLOR_CYAN
  },
  [7] = {
    BRIGHTNESS_FULL, COLOR_YELLOW,
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_YELLOW,
    BRIGHTNESS_FULL, COLOR_GREEN
  },
  [8] = {
    BRIGHTNESS_FULL, COLOR_CYAN,
    BRIGHTNESS_FULL, COLOR_RED,
    BRIGHTNESS_FULL, COLOR_CYAN,
    BRIGHTNESS_FULL, COLOR_RED
  },
  [9] = {
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_BLUE,
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_BLUE
  },
  [10] = {
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_RED,
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_RED
  },
  [11] = {
    BRIGHTNESS_FULL, COLOR_RED,
    BRIGHTNESS_FULL, COLOR_PURPLE,
    BRIGHTNESS_FULL, COLOR_RED,
    BRIGHTNESS_FULL, COLOR_PURPLE
  },
  [12] = {
    BRIGHTNESS_FULL, COLOR_PURPLE,
    BRIGHTNESS_FULL, COLOR_RED,
    BRIGHTNESS_FULL, COLOR_PURPLE,
    BRIGHTNESS_FULL, COLOR_RED
  },
  [13] = {
    BRIGHTNESS_FULL, COLOR_WHITE,
    BRIGHTNESS_FULL, COLOR_RED,
    BRIGHTNESS_FULL, COLOR_WHITE,
    BRIGHTNESS_FULL, COLOR_RED
  },
  [14] = {
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_PURPLE,
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_PURPLE
  },
  [15] = {
    BRIGHTNESS_FULL, COLOR_BLUE,
    BRIGHTNESS_FULL, COLOR_BLUE,
    BRIGHTNESS_FULL, COLOR_BLUE,
    BRIGHTNESS_FULL, COLOR_BLUE,
  },
  [16] = {
    BRIGHTNESS_FULL, COLOR_RED,
    BRIGHTNESS_FULL, COLOR_RED,
    BRIGHTNESS_FULL, COLOR_RED,
    BRIGHTNESS_FULL, COLOR_RED
  },
  [17] = {
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_GREEN,
    BRIGHTNESS_FULL, COLOR_GREEN
  },  
  [18] = {
    BRIGHTNESS_FULL, COLOR_WHITE,
    BRIGHTNESS_FULL, COLOR_WHITE,
    BRIGHTNESS_FULL, COLOR_WHITE,
    BRIGHTNESS_FULL, COLOR_WHITE
  }  
  
};
