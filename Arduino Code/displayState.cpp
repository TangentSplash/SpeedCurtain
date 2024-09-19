#include "displayState.h"

DisplayState::DisplayState()
{
  whitespace=0;
  letterNum=0;
  colourNum=0;
  delta=1;
  column=0;
  noNewLetters = false;
  smallLetterColumn=0;
  wordNum = 0;
  letterInfo = 0;
  letterWidth = 8;
  shiftDown = false;
  colours = 0;
  text="";
  font = 0;
  fontHeight = 0;

  startRow = 0;
  endRow = 0;

  invert = false;

  setupDir = FORWARD;
  #ifdef SERIALDEBUG
    Serial.println();
    Serial.print("Start Coulmn ");
    Serial.println(column);
    Serial.print("Start Whitespace: ");
    Serial.println(whitespace);
    Serial.println();
    Serial.println();
  #endif
}

int DisplayState::setText(String Text)
{
  text=Text;
  length=text.length();
  int physicalLength=getPhysicalLength();
  letterIndex=getLetterIndex(letterNum);
  return physicalLength;
}

void DisplayState::setColourMode(int colour)
{
  colours = colour;
}

void DisplayState::setFont(int chosenFont)
{
  font = chosenFont;
  fontHeight = FONT_HEIGHTS[font];
  Serial.print("Font height");
  Serial.println(fontHeight);
  startRow = (ROWSPERCOLUMN-fontHeight)/2;
  Serial.println(startRow);
  endRow = startRow + fontHeight;
}

void DisplayState::addRibbon(CRGB leds[])
{
  int upperRibbon = startRow-2;
  int lowerRibbon = endRow + 2;
  if (upperRibbon>=0 && lowerRibbon< ROWS)
  {
    for (int i = STARTCOLUMN; i<ENDCOLUMN; i++)
    {
      int idx = getCurtainPos(upperRibbon,i);
      leds[idx] = CRGB::Red;
    }
    for (int i = STARTCOLUMN; i<ENDCOLUMN; i++)
    {
      int idx = getCurtainPos(lowerRibbon,i);
      leds[idx] = CRGB::Red;
    }
  }
}

void DisplayState::setInvert(bool invertbool)
{
  invert = invertbool;
}

bool DisplayState::prepareMove(int dir, CRGB leds[]) 
{   
  bool moreLetters = false; 
  if (dir == FORWARD)
  { 
    for (int row=0;row<endRow-startRow;row++)
    {                            
      int curtainRow = row + startRow;
      // Shift Columns - like shift register
      for (int col=STARTCOLUMN;col<ENDCOLUMN;col++)
      {
        int pos = getCurtainPos(curtainRow,col); // These will change in a predictable way - could change based on last value?
        int oldPos = getCurtainPos(curtainRow,col+1);
        leds[pos] = leds[oldPos];                   // The value of this LED is the old value of the LED to its right  
      }
      // Display the new Column
      int pos = getCurtainPos(curtainRow,ENDCOLUMN);
      leds[pos] = getRow(row);
    }

    moreLetters = nextColumn();
  }
  else
  {

    for (int row=0;row<endRow-startRow;row++)
    {   
      int curtainRow = row + startRow;                         
      // Shift Columns - like shift register
      for (int col=ENDCOLUMN;col>STARTCOLUMN;col--)
      {
        int pos = getCurtainPos(curtainRow,col); // These will change in a predictable way - could change based on last value?
        int oldPos = getCurtainPos(curtainRow,col-1);
        leds[pos] = leds[oldPos];                   // The value of this LED is the old value of the LED to its right  
      }
      // Display the new Column
      int pos = getCurtainPos(curtainRow,STARTCOLUMN);
      leds[pos] = getRow(row);
    }
    
    moreLetters = prevColumn();
  }

  if (dir != setupDir)
  {
    setupDir = dir;
    return false;
  }
  return moreLetters;
}

/*void DisplayState::shiftRegister(int writeNew, int shift)
{
  for (int row=0;row<ROWS;row++)
  {                            
    // Shift Columns - like shift register
    for (int col=STARTCOLUMN;col<ENDCOLUMN;col++)
    {
      int pos = displayState.getListPos(row,col); // These will change in a predictable way - could change based on last value?
      leds[pos] = leds[pos+20];                   // The value of this LED is the old value of the LED to its right  
    }
    // Display the new Column
    int pos = displayState.getListPos(row,ENDCOLUMN);
    leds[pos] = displayState.getRow(row);
  }
}*/

bool DisplayState::nextColumn()
{
  #ifdef SERIALDEBUG
    Serial.println();
    Serial.print("Coulmn ");
    Serial.println(column);
    Serial.print("Whitespace: ");
    Serial.println(whitespace);
    Serial.println();
    Serial.println();
  #endif

  column++;
  if (column>(SCALING*letterWidth)+(WHITESPACE*SCALING))
  {
    letterNum++;
    colourNum+=delta;
    if (colourNum==0 || colourNum==NUMCOLOURS-1)
    {
      delta = -delta;
    }
    if (letterNum < length)
    {
      column=0;
      letterIndex=getLetterIndex(letterNum);
    }
    else if (letterNum > length+20)
    {
      noNewLetters = true;
      Serial.println("Finished");
      return false; //  No more columns
    }
  }
  smallLetterColumn = column/SCALING;
  return true;
}

bool DisplayState::prevColumn()
{
  #ifdef SERIALDEBUG
    Serial.println();
    Serial.print("Coulmn ");
    Serial.println(column);
    Serial.print("Whitespace: ");
    Serial.println(whitespace);
    Serial.println();
    Serial.println();
  #endif

  column--;
  if (column<0)
  {
    letterNum--;
    colourNum-=delta;
    if (colourNum==0 || colourNum==NUMCOLOURS-1)
    {
      delta = -delta;
    }
    if (letterNum >=0 )
    {
      column=(SCALING*letterWidth)+(WHITESPACE*SCALING);
      letterIndex=getLetterIndex(letterNum);
    }
    else
    {
      noNewLetters = true;
      return false; //  No more columns
    }
  }
  smallLetterColumn = column/SCALING;
  return true;
}

//CRGB wordcolourList[]={CRGB::White,CRGB::White,CRGB::White,CRGB::White,CRGB::Gold,CRGB::White,CRGB::White,CRGB::White,CRGB::White,CRGB::White,CRGB::Red};

CRGB DisplayState::getRow(int row)
{
  int letterRow = row/SCALING;
  if(smallLetterColumn<letterWidth && !noNewLetters && bitRead(LETTER_FONTS[font][letterIndex][letterRow],smallLetterColumn))
  {
    #ifdef SERIALDEBUG
      Serial.print(COLOURMODES[colours][colourNum%NUMCOLOURS].red);
      Serial.print(",");
      Serial.print(COLOURMODES[colours][colourNum%NUMCOLOURS].green);
      Serial.print(",");
      Serial.println(COLOURMODES[colours][colourNum%NUMCOLOURS].blue);
    #endif
    //if(letterNum>NUMCOLOURS)
    if(!invert)
    {
      return COLOURMODES[colours][colourNum];
    }
    {
      return CRGB::Black;
    }
  }
  else  //  This LED does not get turned on
  {
    #ifdef SERIALDEBUG
      Serial.println('0');
    #endif
    if(!invert)
    {
      return CRGB::Black;
    }
    else
    {
      return COLOURMODES[colours][colourNum];
    }
  }
}


// Get the position in the list from rows and columns
int DisplayState::getCurtainPos(int row,int currcol)
{
  #ifdef SERPENTINE
    if (currcol%2==0)
    {
      return (currcol*ROWSPERCOLUMN)+row; 
    }
    else
    {
      return ((currcol-1)*ROWSPERCOLUMN)+(2*fontHeight)-row;  // TODO Check this
    }
  #endif
  #ifndef SERPENTINE
    return (currcol*ROWSPERCOLUMN)+row;
  #endif
} 

int DisplayState::getLetterIndex(int letterNum)
{
  int index=0;
  char letter = text[letterNum];

  if (letter<32 || letter > 126)
  {
    letter = 32;
  }

  index = letter - 32;

  letterWidth = LETTER_WIDTHS[font][index];

  #ifdef SERIALDEBUG
    Serial.println(letter);
    Serial.print("Letter Width: ");
    Serial.println(letterWidth);
  #endif

  return index;
}

int DisplayState::getSetupDir()
{
  return setupDir;
}

int DisplayState::getPhysicalLength()
{
  int totalPixelWidth = 0;
  for (int i=0;i<length;i++)
  {
    getLetterIndex(i);
    totalPixelWidth += (letterWidth+WHITESPACE);
  }
  int physicalLength = totalPixelWidth*DISTBETWEENLIGHTS*100;
  Serial.println(totalPixelWidth);
  Serial.print("Total Length: ");
  Serial.print(physicalLength);
  Serial.println(" cm");
  return physicalLength;
}


