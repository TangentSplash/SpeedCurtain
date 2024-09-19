#ifndef DISPLAY_STATE_H
#define DISPLAY_STATE_H

#include <Arduino.h>
#include <FastLED.h>
#include "Constants.h"

class DisplayState
{
  int letterNum;
  int colourNum;
  int delta;
  int column;
  int letterIndex;
  int whitespace;
  int smallLetterColumn;
  int length;
  String text;
  int colours;
  int setupDir;
  int wordNum;
  int letterInfo;
  int letterWidth;
  bool shiftDown;
  int font;
  int fontHeight;
  int startRow;
  int endRow;
  bool invert;
  
  int getLetterIndex(int letterNum);
  int getPhysicalLength();
  int getCurtainPos(int row,int column);
  CRGB getRow(int row);
  bool nextColumn();
  bool prevColumn();

  public:
  DisplayState();
  int setText(String text);
  void setColourMode(int colour);
  void setFont(int font);
  void setInvert(bool invert);
  int getSetupDir();
  bool prepareMove(int dir, CRGB leds[]);
  void addRibbon(CRGB leds[]);
  bool noNewLetters;
};

#endif