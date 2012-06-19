
#include "Rect.h"

Rect::Rect(){
	x=0;y=0;w=TILE;h=TILE;
}
Rect::Rect(int xx,int yy){
	x=xx;y=yy;w=TILE;h=TILE;
}
Rect::Rect(int xx,int yy,int ww,int hh){
    x=xx;y=yy;w=ww;h=hh;
}
