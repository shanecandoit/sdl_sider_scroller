
#ifndef RECT_H
#define RECT_H


#define TILE 64

class Rect{
public:
    Rect();
    Rect(int xx,int yy);
    Rect(int xx,int yy,int ww,int hh);
private:
    int x,y,w,h;
};

#endif
