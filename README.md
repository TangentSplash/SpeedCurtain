# SpeedCurtain
 The software created for the SpeedCurtain project, creating the illusion of a stationary pattern shown on a moving display.


The SpeedCurtain code to be uploaded to the Arduino is contained in the 'Arduino Code' folder. The 'Bluetooth Controller' folder contains a Python script that gives user input to the SpeedCurtain, such as message to display, colour, font etc.

'FontTransformer' contains a python script to transform .xbm files into C header files that the SpeedCurtain can display

'Long Exposure Emulator' contains a Python file that transforms a video of the SpeedCurtain in motion into a single image of the full message displayed by compiling the brightest each pixel becomes over the course of the video into a single image.