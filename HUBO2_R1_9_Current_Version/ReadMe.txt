2010-04-26_2125
Hubo2_R1_9
Added serial functionality:
Stand on one foot: [255, 83]
Flap Arms: [ 255, 74, 102, (0-2) ] 0 = slow, 1 = normal, 2 = fast
Flap Clap Hands: [ 255, 74, 67, (0-2) ] 0 = slow, 1 = normal, 2 = fast

2010-04-26_0040
Hubo2_R1_8
Added Serial safty checkeing for all gestures.
added the following serial gesture responses:
Welcome: [ 255, 119 ]
Hand Wave: [ 255, 104 ]
ChooChoo: [ 255, 74, 99, (0-2) ] 0 = slow, 1 = normal, 2 = fast


2010-04-19_0133
Hubo2_R1_7
Added serial checking for tapping.
fixed buttons for tapping.  Now safties are on you can't tap until the motion is over.
Need to fix (Check all motion flags)

2010-01-06
Hubo2_R1_6
Added functions to allow for pointing fingers left and right
increase the number of gestures


2009-08-20
HUBO2_R1_5
Added functions by Rob
Some of the buttons still do not work, but they are not attached to anything so it will not dammage Hubo


2009-05-25
2:00
Scripting works like a charm


2009-05-25
20:00
Moved timing information in all gestures to Profile functions, kept T arguement in profile for compatibility
made script function in Core.cpp
tested & verified basic functions



Morning
New finger motion code in more compact implementation
Tested and tweaked fast versions of gestures
Gestures are tested at all speeds, may need minor polish but will not kill anything
added conditoonal test that only starts a new motion (on Rob's buttons) if older motions are completed


2009-05-24_1312
Hand New hand motions added by Min-su
Tie-Chi short has finger movements on them now
new Hand gesture movenents.
Slow Simon Says Gestures added:
-Raise Right hand
-Raise Left Hand
-Raise Right arm
-Raise Left arm
-Right Arm Circle
-Left Arm Circle
-Touch head
-hand clap
-touch nose
-flip arms
-tip hat (does not work)
-hands on hip
-rub stomach (does not work)
-train horn (ChooChoo)
Also More blank buttons added for gestures
three radio buttons added, they are not connected to anything

2009-05-10_2216:
Auto Calibrate function added in Z-Phase
Press the (Auto Setup) button to start an auto setup, it will do all of the joints from top left to right of the screen.  it will try each lower joint once and each upper joint twice.  It will automatically abort if a lower limb fails once and an upper one fails twice

2009-02-11_1148:
Tapping functionality for Com2 working at 115200 baud
't' = tap
's' = start tapping mode
'e' = end tapping mode
'r' = reset buttons
'c' = close window