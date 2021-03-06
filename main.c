#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "Field.h"

typedef enum { false, true } bool; // C99 has stdbool.h huh?

void drawField(Field * field, Display * display, Window window, int width, int height, GC gc)
{
	int cell_width = (width - field->size) / field->size , 
	    cell_height = (height - field->size) / field->size,
	    x, y;
	if(cell_width < 1)
		cell_width = 1;
	if(cell_height < 1) 
		cell_height = 1;
	
	for(int i = 0; i < field->size * field->size; ++i)
	{
		if(field->cur[i].state & 1)
		{
			x = ((i % field->size) * cell_height) + (i % field->size);
			y = ((i / field->size) * cell_width) + (i / field->size);
			XFillRectangle(display, window, gc, x, y, cell_width, cell_height); 
		}
	}		
}

void print_list(Node * head)
{	
	Node * itr = head;
	while(itr)
	{
		printf("%d ", itr->indx);
		itr = itr->next;
	}
	printf("\n");
}
// TO DO:
// Rethink evolve function (99 line) 
// Add comments
int main(int argc, char ** argv)
{
	srand(time(0));	
	/* Setting up a connection with the X server */
	Display * dpy = XOpenDisplay(NULL);
	if(dpy == NULL)	{
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}
	
	int screen = DefaultScreen(dpy);
	Window win = XCreateSimpleWindow(dpy, RootWindow(dpy, screen),
			50, 50, 800, 800, 1,
		       	WhitePixel(dpy, screen), BlackPixel(dpy, screen));

	XSelectInput(dpy, win, ExposureMask | KeyPressMask | StructureNotifyMask);
	XMapWindow(dpy, win);
	
	/* For closing correctly */
	Atom WM_DELETE_WINDOW = XInternAtom(dpy, "WM_DELETE_WINDOW", 0);
	XSetWMProtocols(dpy, win, &WM_DELETE_WINDOW, 1);

	/* Setting up the graphics context */
	GC gc = XCreateGC(dpy, win, 0, NULL);
	XSetForeground(dpy, gc, WhitePixel(dpy, screen));
		

	const int FIELD_SIZE = 50;
	Field field;

	if(iniField(&field, FIELD_SIZE)) {
		fprintf(stderr, "Cannot initialize the field\n");
		exit(2);
	}
	
	unsigned int display_width = 800/*DisplayWidth(dpy, screen)*/,
		     display_height = 800/*DisplayHeight(dpy, screen)*/;
	

	XMoveResizeWindow(dpy, win, 50, 50, 800, 800);

	XEvent event;
	while(1)
	{	
		if((XPending(dpy))) //Xpending() to avoid blocking XNextEvent()
		{	//this code must be in even_loop function
			XNextEvent(dpy, &event);
		
			if (event.type == ConfigureNotify)
			{
				display_width = event.xconfigure.width;
				display_height = event.xconfigure.height;
			}
			else if( event.type == ClientMessage)
			{
				break;
			}
		}
		else
		{
			usleep(100 * 1000);	//better to use nanosleep()
		//	print_list(field.alive);
			evolve(&field);
			XClearWindow(dpy, win);
		}
		drawField(&field, dpy, win, display_width, display_height, gc);
	}

	freeField(&field);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
	return 0;
}
