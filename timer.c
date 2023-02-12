#include <string.h>
#include "car.h"

void print_time(int i, long msec, int best)
{
    char text_string[256];
    int box_h = font_info->ascent + font_info->descent;

    if (!i) {
	XClearArea(display, win, 150, 400, 80, box_h, False);
	sprintf(text_string, "%0.3f", (float) msec / 1000);
	XDrawString(display, win, gc, 155, 400 + font_info->ascent,
		    text_string, strlen(text_string));
	if (best) {
	    XClearArea(display, win, 150, 400+box_h+1 , 80, box_h, False);
	    sprintf(text_string, "%0.3f", (float) msec / 1000);
	    XDrawString(display, win, gc, 155, 400+box_h+1 + font_info->ascent,
			text_string, strlen(text_string));
	}

    } else if (i == 1) {
	XClearArea(display, win, 400, 400, 80, box_h, False);
	sprintf(text_string, "%0.3f", (float) msec / 1000);
	XDrawString(display, win, gc, 405, 400 + font_info->ascent,
		    text_string, strlen(text_string));
	if (best) {
	    XClearArea(display, win, 400, 400+box_h+1, 80, box_h, False);
	    sprintf(text_string, "%0.3f", (float) msec / 1000);
	    XDrawString(display, win, gc, 405, 400 +box_h+1+ font_info->ascent,
			text_string, strlen(text_string));
	}

    }
    if (best==2) {
	XClearArea(display, win, 200, 250, 110, box_h, False);
	sprintf(text_string, "%0.3f", (float) msec / 1000);
	XDrawString(display, win, gc, 205, 250 + font_info->ascent,
		    text_string, strlen(text_string));
    }
    XFlush(display);
}

void *print_clock(void *arg)
{
    char text_string[256];
    struct tm *loc_t = NULL;
    time_t cur_t;

    while (1) {
	cur_t = time(NULL);
	loc_t = localtime(&cur_t);
	sleep(1);

	XClearArea(display, win, 0, 50,
		   75, font_info->ascent + font_info->descent, False);

	sprintf(text_string, "%02d.%02d.%02d", loc_t->tm_hour,
		loc_t->tm_min, loc_t->tm_sec);
	XDrawString(display, win, gc, 0, 50 + font_info->ascent,
		    text_string, strlen(text_string));
	printf("moi\n");
	XFlush(display);
    }
    pthread_exit((void *) 0);
    return (void *) NULL;
}


void load_font(Display * display, GC gc)
{

    char *fontname = "9x15";
    if ((font_info = XLoadQueryFont(display, fontname)) == NULL) {
	(void) fprintf(stderr, "Could not get font\n");
	exit(-1);
    }
    XSetFont(display, gc, font_info->fid);
}
