#include "car.h"
#include <X11/xpm.h>


void init_win()
{

    display = XOpenDisplay(NULL);

    s_num = DefaultScreen(display);
    dep = DefaultDepth(display, s_num);


    win = XCreateSimpleWindow(display, RootWindow(display, s_num),
			      0, 0, 800, 600, 0,
			      BlackPixel(display, s_num),
			      WhitePixel(display, s_num));

    gc = XCreateGC(display, win, 0, NULL);
    XSetFillStyle(display, gc, FillSolid);

    screen_colormap = DefaultColormap(display, s_num);
    if ((XAllocNamedColor(display, screen_colormap, "red", &red, &red)) == 0)
		perror("XAllocNamedColor");
    if ((XAllocNamedColor(display, screen_colormap, "gray", &gray, &gray)) == 0)
		perror("XAllocNamedColor");
    if ((XAllocNamedColor(display, screen_colormap, "blue", &blue, &blue)) == 0)
		perror("XAllocNamedColor");

    load_font(display, gc);

    b = XCreatePixmap(display, win, 800, 600, dep);
    i = load_image("rata.xpm", NULL);


    XMapRaised(display, win);
    XClearWindow(display, win);
    XFlush(display);

    XCopyArea(display, i, win, gc, 0, 0, 800, 600, 0, 0);
    MakeButton("File", Exit, 1);
    MakeButton("Quit", Exit, 0);
    MakeButton("About", Exit, 2);
    XSync(display, True);

}

void redraw()
{
    XCopyArea(display, i, win, gc, 0, 0, 800, 600, 0, 0);
    XSync(display, True);
}
