// This is the CPP file you will edit and turn in.

#include "fractals.h"
#include "math.h"
using namespace std;

void drawTriagnle(GWindow& window, double x1, double y1, \
                  double x2, double y2, double x3, double y3){
    window.drawLine(x1, y1, x2, y2);
    window.drawLine(x2, y2, x3, y3);
    window.drawLine(x3, y3, x1, y1);
}

void drawMultipleST(GWindow& window, double x1, double y1, double x2, double y2, double x3, double y3, int order_left){
    drawTriagnle(window, (x1+x2)/2, (y1+y2)/2, (x2+x3)/2, (y2+y3)/2, (x1+x3)/2, (y1+y3)/2 );
    if (order_left > 1){
        drawMultipleST(window,x1, y1 ,(x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 , order_left-1);
        drawMultipleST(window,(x1+x2)/2, (y1+y2)/2, x2, y2 , (x2+x3)/2, (y2+y3)/2, order_left-1);
        drawMultipleST(window,(x1+x3)/2, (y1+y3)/2 ,(x2+x3)/2, (y2+y3)/2, x3, y3 , order_left-1);
    }
}

void drawSierpinskiTriangle(GWindow& window, double x, double y, double size, int order) {
    if (order > 0 && size > 0 && x > 0 && y > 0){
        drawTriagnle(window, x, y, x+size, y, x+size/2, y+size/2*sqrt(3));
        if (order > 1){
            int order_left = order - 1;
            drawMultipleST(window, x, y, x+size, y, x+size/2, y+size/2*sqrt(3), order_left);
        }
    }else if (size > 0 || x > 0 || y > 0){
        throw string("invalid inputs");
    }
}

int floodFill(GWindow& window, int x, int y, int color) {
    return 0;   // this is only here so it will compile
}
