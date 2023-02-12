#include "car.h"

XSetWindowAttributes setwinattr;
Display *display;		/* pointer to X Display structure.           */
Window win;			/* pointer to the newly created window.      */
GC gc;				/* GC (graphics context) used for drawing    */
XFontStruct *font_info;
char *display_name ;	/* address of the X display.      */
Colormap screen_colormap;     /* color map to use for allocating colors.   */
XColor red, brown, blue, yellow, green, gray;
Pixmap bitmap, b, i;
KeyCode Up, Le, Ri, Do, Up2, Le2, Ri2, Do2;
XEvent event;
unsigned int bitmap_width, bitmap_height;
int s_num, dep;
int kup, kdown, kleft, kright, kup2, kdown2, kleft2, kright2;
float suunta_old;

#define t_msec (long)(tv.tv_sec*1000+tv.tv_usec/1000)
struct timeval tv;

void *get_time(void *arg)
{
    int i;
    static long record = 99999999;
    while (1) {
	for (i = 0; i < 2; i++) {
	    if ((cars[i].coord.x < 250) && (cars[i].coord.y > 450) &&
		(!cars[i].tim.has_time)) {
		gettimeofday(&tv, NULL);
		cars[i].tim.c_time = t_msec - cars[i].tim.start_time;
		cars[i].tim.has_time = 1;
		cars[i].tim.start_time = t_msec;
		if (cars[i].tim.c_time < cars[i].tim.best) {
		    cars[i].tim.best = cars[i].tim.c_time;
		    if (record > cars[i].tim.best) {
			record = cars[i].tim.best;
			print_time(i, cars[i].tim.c_time, 2);
		    } else {
			print_time(i, cars[i].tim.c_time, 1);
		    }
		} else {
		    print_time(i, cars[i].tim.c_time, 0);
		}
	    }
	    if ((cars[i].coord.y < 450) && cars[i].tim.has_time) {
		cars[i].tim.has_time = 0;
	    }
	}
    }
    pthread_exit((void *) 0);
    return (void *) NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t, timer;
    int eventmask =
	KeyReleaseMask | KeyPressMask | ButtonPressMask | ExposureMask;

    gettimeofday(&tv, NULL);

    cars[0].tim.start_time = t_msec - 60000;
    cars[0].coord.x = 400;
    cars[0].coord.y = 40;
    cars[0].tim.best = LONG_MAX;
    cars[0].tim.has_time = 0;
    cars[0].color = red.pixel;

    cars[1].tim.start_time = t_msec - 60000;
    cars[1].coord.x = 400;
    cars[1].coord.y = 80;
    cars[1].tim.best = LONG_MAX;
    cars[1].tim.has_time = 0;
    cars[1].color = blue.pixel;

    kup = kleft = kright = kdown = FALSE;
    init_win();
    init_keyb();

    XSync(display, False);
    XAutoRepeatOff(display);
    XSelectInput(display, win, eventmask);

    pthread_create(&t, NULL, print_clock, (void *) NULL);
    pthread_create(&timer, NULL, get_time, (void *) NULL);

    for (;;) {
	//get_time();
	usleep(20000);
	while (XPending(display)) {
	    XFlush(display);
	    XNextEvent(display, &event);
	    switch (event.type) {
	    case ButtonPress:
		break;
	    case ButtonRelease:
		MenuButton[0].func();
		break;
	    case Expose:
		redraw();
		ExposeButton(0);
		break;
	    case EnterNotify:
		XSetLineAttributes(display, gc, 1,
				   LineSolid, CapButt, JoinBevel);
		XDrawRectangle(display, MenuButton[0].window,
			       gc, 1, 1, SB_WIDTH - 3, SB_HEIGHT - 3);
		break;
	    case LeaveNotify:
		ExposeButton(0);
		break;
	    case KeyPress:
		if (event.xkey.keycode == Up)
		    kup = TRUE;
		if (event.xkey.keycode == Do)
		    kdown = TRUE;
		if (event.xkey.keycode == Ri)
		    kright = TRUE;
		if (event.xkey.keycode == Le)
		    kleft = TRUE;
		if (event.xkey.keycode == Up2)
		    kup2 = TRUE;
		if (event.xkey.keycode == Do2)
		    kdown2 = TRUE;
		if (event.xkey.keycode == Ri2)
		    kright2 = TRUE;
		if (event.xkey.keycode == Le2)
		    kleft2 = TRUE;
		break;
	    case KeyRelease:
		if (event.xkey.keycode == Up)
		    kup = FALSE;
		if (event.xkey.keycode == Do)
		    kdown = FALSE;
		if (event.xkey.keycode == Ri)
		    kright = FALSE;
		if (event.xkey.keycode == Le)
		    kleft = FALSE;
		if (event.xkey.keycode == Up2)
		    kup2 = FALSE;
		if (event.xkey.keycode == Do2)
		    kdown2 = FALSE;
		if (event.xkey.keycode == Ri2)
		    kright2 = FALSE;
		if (event.xkey.keycode == Le2)
		    kleft2 = FALSE;
		break;

	    default:
		break;
	    }
	}
	do_key();
	paint_car();
    }
    pthread_join(t, NULL);
    return 0;
}
