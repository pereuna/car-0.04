#include <X11/Xlib.h>
#include <X11/Xutil.h>		/* BitmapOpenFailed, etc. */
#include <X11/keysymdef.h>

#include <stdio.h>
#include <stdlib.h>		/* getenv(), etc. */
#include <unistd.h>		/* sleep(), etc.  */
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdarg.h>

#include <limits.h>

#define TRUE  1 
#define FALSE 0
#define MAX(A,B) ((A) > (B) ? (A) : (B))
#define SB_WIDTH   60      /* Button Width */
#define SB_HEIGHT   20      /* Button Height */
#define SB_LONGLABEL   50      /* Longest MenuButton label */
#define SB_CURSOR   XC_hand1   /* Cursor for inside MenuButton */
#define SB_INPUTMASK   ExposureMask | EnterWindowMask | LeaveWindowMask | \
          ButtonPressMask | ButtonReleaseMask
	  
extern XSetWindowAttributes setwinattr;
extern Display *display;/* pointer to X Display structure.           */
extern Window win;	/* pointer to the newly created window.      */
extern GC gc;		/* GC (graphics context) used for drawing    */
extern XFontStruct *font_info;
extern char *display_name ;/* address of the X display.      */
extern Colormap screen_colormap; /* color map to use for allocating colors.   */
extern XColor red, brown, blue, yellow, green, gray;
extern Pixmap bitmap, b, i;
extern KeyCode Up, Le, Ri, Do, Up2, Le2, Ri2, Do2;
extern XEvent event;
extern unsigned int bitmap_width, bitmap_height;
extern int s_num, dep;
extern int kup, kdown, kleft, kright, kup2, kdown2, kleft2, kright2;

struct coordinate {
    float x;
    float y;
};

struct times {
    long best;
    long start_time;
    long c_time;
    int has_time;
};

struct car {
    char *name;
    unsigned long color; 
    float suunta;
    float suunta_old;
    float kaasu;
    int vaihde;
    struct times tim;
    struct coordinate coord;
};

struct {
   Window         window;
   char         label[SB_LONGLABEL];
   int                     (*func)();
} MenuButton[9];

void print_time(int i, long msec, int best);
void load_font(Display * display, GC gc);	
void paint_car(void);
void init_win(void);
void do_key(void);
void init_keyb(void);
Pixmap load_image(char *xpm_name, Pixmap *mask);
void * print_clock(void *);
void redraw(void);
void MakeButton(char *label, int(*fun)(), int id);
void HandleButton(int id, XEvent *event);
void ExposeButton(int id);
int Exit(void);	
	
struct car cars[2];
