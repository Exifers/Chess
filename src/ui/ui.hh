#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <iostream>

#include <chess/chess.hh>
#include <chess/piece.hh>

struct tileData {
  Chess *chess;
  int posX;
  int posY;
  bool picked;
};

class UI {
  public:
    UI(Chess& chess);
    int launch(int argc, char **argv);
  
    static void activate_cb(GtkApplication *app, gpointer userData);
    static void drag_begin_cb(GtkWidget *widget, GdkDragContext *context,
      gpointer user_data); 
    static void drag_end_cb(GtkWidget *widget, GdkDragContext *context,
      gpointer user_data);
    static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data);

    static void drag_data_received_cb(GtkWidget *widget, GdkDragContext *context,
      gint x, gint y, GtkSelectionData *data, guint info, guint time,
      gpointer userData);
    static void drag_data_get_cb(GtkWidget *widget, GdkDragContext *context,
      GtkSelectionData *data, guint info, guint time,
      gpointer userData);
  
    static gboolean drag_drop_cb(GtkWidget *widget, GdkDragContext *context,
      gint x, gint y, guint time, gpointer userData); 

    static gboolean drag_failed_cb(GtkWidget *widget, GdkDragContext *context,
      GtkDragResult result, gpointer userData);

    static gboolean
      drag_motion_cb(GtkWidget *widget, GdkDragContext *context, gint x,
        gint y, guint time, gpointer userData);
  private:
    Chess& chess_;

    struct tileData *buildAllUserData();
    static GtkWidget *buildGrid(struct tileData *allUserData);
};
