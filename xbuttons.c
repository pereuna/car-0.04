#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/cursorfont.h>
#include <stdio.h>
#include "car.h"

int Exit();

#define   POSX   800
#define   POSY   200
#define   WIDTH   142
#define   HEIGHT   85


void MakeButton(char *label, int (*fun) (), int id)
{
    Cursor tempcursor;

    strncpy(MenuButton[id].label, label, SB_LONGLABEL);

    MenuButton[id].func = fun;

    MenuButton[id].window = XCreateSimpleWindow(display, win,
						id * SB_WIDTH + (id * 4) +
						2, 1, SB_WIDTH, SB_HEIGHT,
						1, BlackPixel(display,
							      s_num),
						WhitePixel(display,
							   s_num));

    XSelectInput(display, MenuButton[id].window, SB_INPUTMASK);

    tempcursor = XCreateFontCursor(display, SB_CURSOR);
    XDefineCursor(display, MenuButton[id].window, tempcursor);

    setwinattr.backing_store = Always;
    XChangeWindowAttributes(display, MenuButton[id].window,
			    CWBackingStore, &setwinattr);

    XMapWindow(display, MenuButton[id].window);
    ExposeButton(id);
}


void HandleButton(int id, XEvent * event)
{

    switch (event->type) {
    case Expose:
	ExposeButton(id);
	break;
    case EnterNotify:
	XDrawRectangle(display, MenuButton[id].window,
		       gc, 1, 1, SB_WIDTH - 3, SB_HEIGHT - 3);
	break;
    case LeaveNotify:
	ExposeButton(id);
	break;
    case ButtonPress:
	if (event->xbutton.button == Button1) {
	    XDrawRectangle(display, MenuButton[id].window,
			   gc, 0, 0, SB_WIDTH - 1, SB_HEIGHT - 1);
	}
	break;
    case ButtonRelease:
	MenuButton[id].func();
	ExposeButton(id);
	XDrawRectangle(display, MenuButton[id].window,
		       gc, 1, 1, SB_WIDTH - 3, SB_HEIGHT - 3);
	break;
    default:
	break;
    }
    return;
}

void ExposeButton(int id)
{
    int width, center;

    XClearWindow(display, MenuButton[id].window);
    width = XTextWidth(font_info, MenuButton[id].label,
		       strlen(MenuButton[id].label));
    center = MAX((SB_WIDTH - width) / 2, 4);
    XDrawString(display, MenuButton[id].window, gc,
		center, font_info->ascent,
		MenuButton[id].label, strlen(MenuButton[id].label));
    XFlush(display);
    return;
}

int Exit(void)
{
    XAutoRepeatOn(display);
    XDestroyWindow(display, win);
    XFlush(display);
    exit(0);
    return 0;
}
