#include <X11/xpm.h>
#include "car.h"

Pixmap load_image(char *xpm_name, Pixmap * mask)
{

    int status;
    Pixmap pixmap;
    XpmAttributes attribs;
    /* (From xpm.h)
     * Return ErrorStatus codes:
     * null     if full success
     * positive if partial success
     * negative if failure
     */
    char *xpm_status[] = {
	"XpmColorFailed",	/* -4 */
	"XpmNoMemory",		/* -3 */
	"XpmFileInvalid",	/* -2 */
	"XpmOpenFailed",	/* -1 */
	"XpmSuccess",		/*  0 */
	"XpmColorError"		/*  1 */
    };

    attribs.valuemask = XpmColormap | XpmCloseness;
    attribs.colormap = screen_colormap;
    attribs.closeness = 0xffff;

    if ((status = XpmReadFileToPixmap
	 (display, win, xpm_name, &pixmap, mask, &attribs)) < 0) {
	fprintf(stderr, "Exiting: %s\n", xpm_status[status + 4]);
	exit(0);
    }
    return pixmap;
}
