import os
from PIL import Image
import numpy as np

def toHex(bytebuffer):
    if len(str(hex(int(bytebuffer, 2)))) == 3:
        x = str(hex(int(bytebuffer, 2)))
        return (x[:2] + '0' + x[2:])
    else:
        return str(hex(int(bytebuffer, 2)))

def toBit(pixel, threshold, invert = 0):    #convert every pixel
    return int(not invert)
##    if (pixel <= threshold):
##        return 1 if invert == 0 else 0      #invert == 0 => treat black pixels in image as data
##    else:
##        return 0 if invert == 0 else 1      #invert == 1 => treat white pixels in image as data

def fill(sample, ch):
#     fill0 = ':'
#     fill1 = 'O'
    filler = ':' if ch=='1' else '0'
    sample.append(filler)
#     if ch == '1':
#         sample.append(fill1)
#     else:
#         sample.append(fill0)

imagePath = raw_input("Enter file name: ")
try:
    img = Image.open(imagePath)
except:
    print "File not found!"
    exit(-1)

print "Opening " + img.format + " file..."
width, height = img.size
print "Width x Height : " + str(width) + (" x ") + str(height) +" pixels"
print "Mode : "+ str(img.mode)
if img.format == "BMP" and img.palette == "None":
    #only BMP format has Palette atrribute. Print palette status only for BMP files. Need workaround for files with palette
    print "BMP files with palettes are not yet supported. File format found is " + img.format + ("." if img.format != "BMP" else (". Palette was " + ("not found." if img.palette == "None" else "found.")))

size = (128,64)                             #tuple of transform size
img = img.resize(size)
img = img.convert("L")                      #convert to black and white. This also reduces the total colourband tuple length to 1
print "Resized to 128 x 64 pixels"

bw = np.array(img)

i = 0
bits = []
hexes = []
sample = []
byteBuffer = ""
hexBuffer = ""
for x in bw:
    for y in x:
        ch = str(toBit(y,177,0))               #toBit(pixel, threshold, invert) | invert defaults to 0, use 1 to invert | higher value of threshold => more observed pixels
        if i%128==0:
            sample.append("\n")
            fill(sample,ch)
            bits.append(",\n0b" if i else "\n0b")
            bits.append(ch)
            hexes.append(",\n" if i else "\n")    
            if i:
                hexes.append(hexBuffer)
                byteBuffer = ""
            byteBuffer += ch
        elif i%8==0:
            fill(sample, ch)
            bits.append(",0b")
            bits.append(ch)
            hexes.append(", " if (i > 8) else "")
            hexBuffer = toHex(byteBuffer)
            hexes.append(hexBuffer)
            byteBuffer = ""
            byteBuffer += ch
        else:
            fill(sample,ch)
            bits.append(ch)
            byteBuffer += ch
        i+=1

hexes.append(", ")
hexBuffer = toHex(byteBuffer)
hexes.append(hexBuffer)
bits = ''.join(bits)
bitmap = open("../code/bitmap.h", "w")
bitmap.write("static const unsigned char PROGMEM bitmap[] =\n{" + bits + " };")
hexes = ''.join(hexes)
hexmap = open("../code/hexmap.h", "w")
hexmap.write("static const unsigned char PROGMEM hexmap[] =\n{" + hexes + " };")
sample = ''.join(sample)
sampleview = open("sampleview.txt", "w")
sampleview.write(sample)
