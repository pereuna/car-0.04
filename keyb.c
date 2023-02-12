#include "car.h"
void do_key()
{
    if (kup2)
	cars[0].kaasu -= 0.1;
    if (kdown2)
	cars[0].kaasu += 0.5;
    if (kright2 && (cars[0].kaasu < 0)) {
	cars[0].suunta_old = cars[0].suunta;
	cars[0].suunta += 0.05;
    }
    if (kleft2 && (cars[0].kaasu < 0)) {
	cars[0].suunta_old = cars[0].suunta;
	cars[0].suunta -= 0.05;
    }

    if (kup)
	cars[1].kaasu -= 0.1;
    if (kdown)
	cars[1].kaasu += 0.5;
    if (kright && (cars[1].kaasu < 0)) {
	cars[1].suunta_old = cars[1].suunta;
	cars[1].suunta += 0.05;
    }
    if (kleft && (cars[1].kaasu < 0)) {
	cars[1].suunta_old = cars[1].suunta;
	cars[1].suunta -= 0.05;
    }
    return;
}

void init_keyb()
{
    Up = XKeysymToKeycode(display, XK_Up);
    Do = XKeysymToKeycode(display, XK_Down);
    Ri = XKeysymToKeycode(display, XK_Right);
    Le = XKeysymToKeycode(display, XK_Left);

    Up2 = XKeysymToKeycode(display, XK_q);
    Do2 = XKeysymToKeycode(display, XK_a);
    Ri2 = XKeysymToKeycode(display, XK_x);
    Le2 = XKeysymToKeycode(display, XK_z);

    return;
}
