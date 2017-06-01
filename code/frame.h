class Frame
{
    uint8_t width, height, address;

    public:
    Frame(uint8_t w, uint8_t h, byte* frame)
    {
        width = w/8;    //number of columns are total bytes
        height = h;
        byte frame[height][width];
    }

    void getWidth()
        return width;

    void getHeight()
        return height;

    void getAddress()
        return address;
    
    void putPixel(uint8_t x, uint8_t y, bool val)
    {
        bitWrite((frame[x,(y/8)]), (8 - (y%8)), (val ? 1:0))    //bitWrite(x,n,b)   8-y%8 because functions starts writing from LSB. So if y%8 == 1, set 7th bit.
    }

    void resetFrameToTemplate()     //source bitmap from the _template datarray
    {
        for(int i = 0; i < height; i++)
            for(int j=0; j < width; j++)
                frame[i][j] = _template[i][j];
    }

    void clearFrame()               //reset every bit to 0
    {
        for(int i = 0; i < height; i++)
            for(int j=0; j < width; j++)
                frame[i][j] = 0b00000000;   
    }
}

void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    uint8_t xmin = constrain(min(x1,x2), 0 , 63);
    uint8_t xmax = constrain(max(x1,x2), 0 , 63);
    for(i = xmin; i < xmax; i++)
        frame.putPixel(i, y1, true);
}

void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    uint8_t xmax = constrain(max(x1,x2), 0 ,63);
    uint8_t ymax = constrain(max(y1,y2), 0 ,63);
    uint8_t xmin = constrain(min(x1,x2), 0 ,63);
    uint8_t ymin = constrain(min(y1,y2), 0 ,63);
    for(int i = ymin; i <= ymax; i++)
        for(int j = xmin; j <= xmax; j++)
            frame.putPixel(i, j, true);
}