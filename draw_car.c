#include "car.h"
#include "lauta.xbm"

static float end_point_x[2], keula_point_x[2];
static float end_point_y[2], keula_point_y[2];

void draw_body(int j)
{
    XSetLineAttributes(display, gc, 4, LineSolid, CapButt, JoinBevel);
    XDrawLine(display, win, gc,
	      (int) keula_point_x[j], (int) keula_point_y[j],
	      (int) end_point_x[j], (int) end_point_y[j]);
}

void draw_axles(int j)
{
    XSetLineAttributes(display, gc, 1, LineSolid, CapButt, JoinBevel);

    XDrawLine(display, win, gc,
	      cos(cars[j].suunta + 1) * 6 + keula_point_x[j],
	      sin(cars[j].suunta + 1) * 6 + keula_point_y[j],
	      cos(cars[j].suunta - 1) * 6 + keula_point_x[j],
	      sin(cars[j].suunta - 1) * 6 + keula_point_y[j]);
    XDrawLine(display, win, gc,
	      cos(cars[j].suunta + 2) * 6 + end_point_x[j],
	      sin(cars[j].suunta + 2) * 6 + end_point_y[j],
	      cos(cars[j].suunta - 2) * 6 + end_point_x[j],
	      sin(cars[j].suunta - 2) * 6 + end_point_y[j]);
}

void draw_tyres(int j)
{
    XSetLineAttributes(display, gc, 2, LineSolid, CapButt, JoinBevel);

    XDrawLine(display, win, gc,
	      cos(cars[j].suunta + 1.3) * 5.48 + keula_point_x[j],
	      sin(cars[j].suunta + 1.3) * 5.48 + keula_point_y[j],
	      cos(cars[j].suunta + 0.785) * 7.35 + keula_point_x[j],
	      sin(cars[j].suunta + 0.785) * 7.35 + keula_point_y[j]);
    XDrawLine(display, win, gc,
	      cos(cars[j].suunta - 1.3) * 5.48 + keula_point_x[j],
	      sin(cars[j].suunta - 1.3) * 5.48 + keula_point_y[j],
	      cos(cars[j].suunta - 0.785) * 7.35 + keula_point_x[j],
	      sin(cars[j].suunta - 0.785) * 7.35 + keula_point_y[j]);
    XDrawLine(display, win, gc,
	      cos(cars[j].suunta + 2) * 5.48 + end_point_x[j],
	      sin(cars[j].suunta + 2) * 5.48 + end_point_y[j],
	      cos(cars[j].suunta + 2.53) * 7.35 + end_point_x[j],
	      sin(cars[j].suunta + 2.53) * 7.35 + end_point_y[j]);
    XDrawLine(display, win, gc,
	      cos(cars[j].suunta - 2) * 5.48 + end_point_x[j],
	      sin(cars[j].suunta - 2) * 5.48 + end_point_y[j],
	      cos(cars[j].suunta - 2.53) * 7.35 + end_point_x[j],
	      sin(cars[j].suunta - 2.53) * 7.35 + end_point_y[j]);
}

void paint_car()
{
    int j;
    float pit = 20;

    for (j = 0; j < 2; j++) {
	if (lauta_bits[((int) cars[j].coord.y * lauta_width
			+ (int) cars[j].coord.x) / 8] > 1) {
	    cars[j].kaasu = -0.5;
	    XCopyArea(display, i, win, gc,
		      ((keula_point_x[j] + end_point_x[j]) / 2) - 12,
		      ((keula_point_y[j] + end_point_y[j]) / 2) - 12, 24,
		      24, ((keula_point_x[j] + end_point_x[j]) / 2) - 12,
		      ((keula_point_y[j] + end_point_y[j]) / 2) - 12);
	    XNextEvent(display, &event);
	} else {
	    XSetForeground(display, gc, gray.pixel);
	    draw_axles(j);
	    draw_body(j);
	    draw_tyres(j);
	}
	XSetForeground(display, gc, BlackPixel(display, s_num));

	cars[j].kaasu = (cars[j].kaasu > 0) ? 0 : cars[j].kaasu;

	keula_point_x[j] =
	    cos(cars[j].suunta + M_PI) * cars[j].kaasu + cars[j].coord.x;
	keula_point_y[j] =
	    sin(cars[j].suunta + M_PI) * cars[j].kaasu + cars[j].coord.y;

	cars[j].coord.x = keula_point_x[j];
	cars[j].coord.y = keula_point_y[j];

	end_point_y[j] = sin(cars[j].suunta) * pit + keula_point_y[j];
	end_point_x[j] = cos(cars[j].suunta) * pit + keula_point_x[j];

	draw_axles(j);
	draw_tyres(j);
	if (j)
	    XSetForeground(display, gc, red.pixel);
	else
	    XSetForeground(display, gc, blue.pixel);
	draw_body(j);
	XSetForeground(display, gc, BlackPixel(display, s_num));
	XFlush(display);

    }
}
