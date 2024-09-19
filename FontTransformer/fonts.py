from os import listdir
from os.path import isfile, join, isdir
import re
import copy

MIN_INDEX = 32

path = "/Fonts/"    # REPLACE WITH PATH TO FONTS

charMaps = [None]*95
widths = [None]*95
heights = [None]*95

class Font():
    def __init__(self,fontName,fontWidths,wrappedHeights,code,charNames):
        self.fontName=fontName
        self.fontWidths=fontWidths
        self.wrappedHeights=wrappedHeights
        self.code=copy.deepcopy(code)
        self.charNames=charNames
        self.maxHeight=int(re.split('_\\dx',fontName)[1])
        if (self.maxHeight<=8):
            self.underline=1
        else:
            self.underline=2

        self.normaliseHeight()

    def normaliseHeight(self):
        for index in range(len(self.fontWidths)):   # Add two under each character except gjpqy_, push'"^ up more and -~ up some
            array = self.code[index].split("\n")
            array[len(array)-3]=array[len(array)-3]+',' # Add comma to last element, so not broken during manipulation
            if not(chr(index+32) in set(['g','j','p','q','y','_',',',';']) ): # Add spaces under characters that don't drop bellow the line
                amount = min(self.underline,self.maxHeight-(len(array)-3))
                array = self.push(True,amount,array)

            if (chr(index+32) in set(['\'','"','^'])):
                amount = self.maxHeight-(len(array)-3)
                array = self.push(True,amount,array)

            amount = self.maxHeight-(len(array)-3)
            array = self.push(False,amount,array)

            out = "\n".join(array)
            self.code[index]=out

    def push(self,up,amount,array):
        if (up):
            pos = len(array)-2
        else:
            pos = 1
        for i in range(amount):
            array.insert(pos,'\t0x00,')
        return array




fonts = [d for d in listdir(path) if isdir(join(path, d))]

Fonts = []

for fnt in fonts: # Fonts

    chars = [f for f in listdir(path+fnt) if isfile(join(path+fnt, f))]
    maxHeight = 0
    charNames = []
    for ch in chars:  # Characters
        if(re.match(".*.xbm",ch)):
            info=ch.split("-")
            num=int(info[0])
            index = num - MIN_INDEX
            charname = info[1].split(".")[0]
            charNames.append(charname)
            f=open(path+fnt+"/"+ch,"r")
            code =f.read()
            f.close()

            widths[index] = int(re.split(".*_width |\n", code)[1])
            heights[index] = int(re.split(".*_height |\n", code)[2])

            out=re.sub("[\\S\\s]*{","{\t// "+charname,code)
            out = re.sub(";",",",out)
            print(out)
            charMaps[index] = out
    font = Font(fnt,widths,heights,charMaps,charNames)
    Fonts.append(font)

output = open("SpeedCurtain/Fonts.h","w")

output.write("const unsigned char LETTER_FONTS["+str(len(fonts))+"][95][19] = {\n")
for fnt in Fonts:
    output.write("{\t// ====="+fnt.fontName+"=====\n")
    for char in fnt.code:
        output.write(char)
    output.write("},\n")
output.write("};\n\n")

output.write("const byte LETTER_WIDTHS["+str(len(fonts))+"][95] = {\n")
for fnt in Fonts:
    output.write("{\t//===== "+fnt.fontName+"=====\n")
    for width in fnt.fontWidths:

    #for index in range(len(fnt.fontWidths)):
        #width=str(fnt.fontWidths[index])
        output.write(str(width)+",\n")
        #charName=fnt.charNames[index]
        #output.write(str(width)+",\t//"+charName+"\n")
    output.write("},\n\n")
output.write("};\n\n")

output.write("const byte FONT_HEIGHTS["+str(len(fonts))+"] = {\n")
for fnt in Fonts:
    output.write(str(fnt.maxHeight)+",\t//"+fnt.fontName+"\n")
output.write("};")

output.close()