# MIDI_to_DMX
An Arduino sketch to convert Proclaim's MIDI output to lighting DMX.

Modified to drive 4 cheap RGB lights with various scenes.

DMX Channel Config for lights:

  `1,2,3,4,      // Light 1 - GlobalBrightness,R,G,B`
  
  `10,11,12,13,  // Light 2 - GlobalBrightness,R,G,B`
  
  `20,21,22,23,  // Light 3 - GlobalBrightness,R,G,B`
  
  `30,31,32,33   // Light 4 - GlobalBrightness,R,G,B`
