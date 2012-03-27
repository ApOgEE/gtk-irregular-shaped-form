/*
 * apogee_gnu.c
 * 
 * Copyright 2012 M. Fauzilkamil Zainuddin <jerungkun@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * This program was created by learning through code from:
 *   http://www.gtk.org/tutorial1.2/gtk_tut-9.html
 * 
 */
#include <gtk/gtk.h>
#include "gnu.xpm"

/* When invoked (via signal delete_event), terminates the application */
gint close_application( GtkWidget *widget,
                        GdkEvent  *event,
                        gpointer   data )
{
    gtk_main_quit();
    return(FALSE);
}

/* moving the wheelbarrow */
gboolean on_button_press_event (GtkWidget* widget, GdkEventButton * event, GdkWindowEdge edge)
{
	if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
		/* move the wheelbarrow */
		gtk_window_begin_move_drag(GTK_WINDOW(gtk_widget_get_toplevel(widget)),	event->button,
									event->x_root, event->y_root, event->time);
	} else if (event->type==GDK_2BUTTON_PRESS && event->button == 1) {
		/* exit when double clicked */
		gtk_main_quit();
	}
	return FALSE;
}

int main (int argc, char *argv[] )
{
	/* GtkWidget is the storage type for widgets */
	GtkWidget *window, *pixmap, *fixed;
	GdkPixmap *gdk_pixmap;
	GdkBitmap *mask;
	GtkStyle *style;
	GdkGC *gc;

	/* Create the main window, and attach delete_event signal to terminate
	 * the application.  Note that the main window will not have a titlebar
	 * since we're making it a popup. */
	gtk_init (&argc, &argv);
	//window = gtk_window_new( GTK_WINDOW_POPUP );
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	
	gtk_signal_connect (GTK_OBJECT (window), "delete_event", GTK_SIGNAL_FUNC (close_application), NULL);

	/* set default size */
	gtk_window_set_default_size(GTK_WINDOW(window), 50, 48);

	/* set position to center */
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	/* Set the event */
	gtk_widget_set_events( window, gtk_widget_get_events( window ) | GDK_BUTTON_PRESS_MASK );
	//gtk_signal_connect( GTK_OBJECT(window), "button_press_event", GTK_SIGNAL_FUNC(close_application), NULL );
	gtk_signal_connect( GTK_OBJECT(window), "button_press_event", GTK_SIGNAL_FUNC(on_button_press_event), NULL );

	gtk_widget_show (window);

	/* Now for the pixmap and the pixmap widget */
	style = gtk_widget_get_default_style();
	gc = style->black_gc;
	gdk_pixmap = gdk_pixmap_create_from_xpm_d( window->window, &mask,
											 &style->bg[GTK_STATE_NORMAL],
											 gnu_xpm );
	pixmap = gtk_pixmap_new( gdk_pixmap, mask );
	gtk_widget_show( pixmap );

	/* To display the pixmap, we use a fixed widget to place the pixmap */
	fixed = gtk_fixed_new();
	//gtk_widget_set_usize( fixed, 200, 200 );
	//gtk_widget_set_usize( fixed, 30, 30 );
	gtk_fixed_put( GTK_FIXED(fixed), pixmap, 0, 0 );
	gtk_container_add( GTK_CONTAINER(window), fixed );
	gtk_widget_show( fixed );

	/* This masks out everything except for the image itself */
	gtk_widget_shape_combine_mask( window, mask, 0, 0 );

	//gtk_widget_set_uposition( window, 20, 400 );

	/* show the window */
	gtk_widget_show( window );
	gtk_main ();
		  
	return(0);
}


