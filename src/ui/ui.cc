#include "ui.hh"

#include <cstdio>

UI::UI(Chess& chess)
  : chess_(chess)
{} 

struct tileData *
UI::buildAllUserData() {
  struct tileData *res = (struct tileData *)
    malloc(sizeof(struct tileData) * 64); 
  for (int i = 0; i < 64; i++) {
    int x = i / 8;
    int y = i % 8;
    res[i].posX = x;
    res[i].posY = y;
    res[i].chess = &chess_;
    res[i].picked = false;
  }
  return res;
}

int
UI::launch(int argc, char **argv) {
  struct tileData *allUserData = buildAllUserData();

  GtkApplication *app = gtk_application_new("org.gtk.example",
    G_APPLICATION_FLAGS_NONE); 
  g_signal_connect(app, "activate", G_CALLBACK(activate_cb), allUserData);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}

void
UI::activate_cb(GtkApplication *app, gpointer userData) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Chess");
  gtk_window_set_default_size(GTK_WINDOW(window), 432, 432);
  gtk_container_set_border_width(GTK_CONTAINER(window), 16);
  
  GtkWidget *frame = gtk_frame_new(nullptr);
  gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
  gtk_container_add(GTK_CONTAINER(window), frame);

  struct tileData *allUserData = (struct tileData *) userData; 
  GtkWidget *grid = buildGrid(allUserData);
 
  gtk_container_add(GTK_CONTAINER(frame), grid);
  
  gtk_widget_show_all(window);

  userData = userData;
}

GtkWidget *
UI::buildGrid(struct tileData *allUserData) {
  GtkTargetEntry targets[] = {
    { (char *) "", GTK_TARGET_SAME_APP, 0 }
  };
  GtkTargetList *targetList = gtk_target_list_new(targets, 1);
  gtk_target_list_add_text_targets(targetList, 26);

  GtkWidget *grid = gtk_grid_new();
  /*
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
  */
  int i = 0;
  int j = 0;
      GtkWidget *drawing_area = gtk_drawing_area_new();
      GtkWidget *drawing_area2 = gtk_drawing_area_new();

      gtk_widget_set_size_request(drawing_area, 50, 50);
      g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb),
        &allUserData[i * 8 + j]);
      gtk_drag_source_set(drawing_area, GDK_BUTTON1_MASK, nullptr, 0,
        GDK_ACTION_COPY);
      gtk_drag_source_set_target_list(drawing_area, targetList);

      g_signal_connect(drawing_area, "drag-drop", G_CALLBACK(drag_drop_cb),
        &allUserData[i * 8 + j]);
      g_signal_connect(drawing_area, "drag-data-received",
        G_CALLBACK(drag_data_received_cb), &allUserData[i * 8 + j]);
      g_signal_connect(drawing_area, "drag-data-get",
        G_CALLBACK(drag_data_get_cb), &allUserData[i * 8 + j]);
      g_signal_connect(drawing_area, "drag-begin", G_CALLBACK(drag_begin_cb),
        &allUserData[i * 8 + j]);
      g_signal_connect(drawing_area, "drag-end", G_CALLBACK(drag_end_cb),
        &allUserData[i * 8 + j]);
      g_signal_connect(drawing_area, "drag-failed", G_CALLBACK(drag_failed_cb),
        &allUserData[i * 8 + j]);

      g_signal_connect(drawing_area2, "drag-motion", G_CALLBACK(drag_motion_cb),
        &allUserData[i * 8 + j]);

      gtk_grid_attach((GtkGrid *) grid, drawing_area, i, j, 1, 1);

      i++;
      gtk_drag_dest_set(drawing_area2, GTK_DEST_DEFAULT_DROP, nullptr, 0,
        GDK_ACTION_COPY);
      gtk_drag_dest_set_target_list(drawing_area2, targetList);
      g_signal_connect(drawing_area2, "draw", G_CALLBACK(draw_cb),
        &allUserData[i * 8 + j]);
      gtk_widget_set_size_request(drawing_area2, 50, 50);
      gtk_grid_attach((GtkGrid *) grid, drawing_area2, i, j, 1, 1);
  /*
    }
  }
  */
  return grid;
}

gboolean
UI::drag_motion_cb(GtkWidget *widget, GdkDragContext *context, gint x,
  gint y, guint time, gpointer userData) {
  widget = widget;
  context = context;
  x = x;
  y = y;
  time = time;
  userData = userData;
  std::cout << "motion : " << x << ", " << y << std::endl;
  gdk_drag_status(context, GDK_ACTION_MOVE, 0);
  return TRUE;
}

gboolean
UI::drag_failed_cb(GtkWidget *widget, GdkDragContext *context,
  GtkDragResult result, gpointer userData) {
  
  widget = widget;
  context = context;
  result = result;
  userData = userData;
  std::cout << "drag failed ! : "
    << result
    << GTK_DRAG_RESULT_SUCCESS
    << GTK_DRAG_RESULT_NO_TARGET
    << GTK_DRAG_RESULT_USER_CANCELLED
    << GTK_DRAG_RESULT_TIMEOUT_EXPIRED
    << GTK_DRAG_RESULT_GRAB_BROKEN
    << GTK_DRAG_RESULT_ERROR << std::endl;
  return FALSE; // nasty animation triggered here !
}

gboolean
UI::drag_drop_cb(GtkWidget *widget, GdkDragContext *context, gint x, gint y,
  guint time, gpointer userData) {
  widget = widget;
  context = context;
  x = x;
  y = y;
  time = time;
  userData = userData;
  std::cout << "Drag Drop received" << std::endl;
  return TRUE;
}

void
UI::drag_data_received_cb(GtkWidget *widget, GdkDragContext *context,
  gint x, gint y, GtkSelectionData *data, guint info, guint time,
  gpointer userData) {
  std::cout << "Data received" << std::endl;
  widget = widget;
  context = context;
  x = x;
  y = y;
  data = data;
  info = info;
  time = time;
  userData = userData;
}

void
UI::drag_data_get_cb(GtkWidget *widget, GdkDragContext *context,
  GtkSelectionData *data, guint info, guint time,
  gpointer userData) {
  std::cout << "Data get" << std::endl;
  widget = widget;
  context = context;
  data = data;
  info = info;
  time = time;
  userData = userData;
}

void
UI::drag_begin_cb(GtkWidget *widget, GdkDragContext *context, gpointer data) {
  struct tileData *tileData = (struct tileData *) data;

  std::cout << "Dragging element at " << tileData->posX << ", "
    << tileData->posY << std::endl;
  widget = widget;
  context = context;
  gtk_widget_queue_draw(widget);
}

/* There must be better ways of doing drag and drop but I'm tired of
** reading the documentation. */
void
UI::drag_end_cb(GtkWidget *widget, GdkDragContext *context, gpointer data) {
  struct tileData *tileData = (struct tileData *) data;
  std::cout << "Ending drag at " << tileData->posX << ", "
    << tileData->posY << std::endl;
  widget = widget;
  context = context;
  data = data;
  gtk_widget_queue_draw(widget);
}

gboolean
UI::draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data) {
  struct tileData *tileData = (struct tileData *) data;

  GdkRGBA color;
  GdkRectangle rect;  
  rect.x = 0;
  rect.y = 0;
  rect.width = 50;
  rect.height = 50;
  
  if ((tileData->posX + tileData->posY) % 2 == 0) {
    color.red = 1;
    color.green = 212.0/255;
    color.blue = 128.00/255;
    color.alpha = 1;
  }
  else {
    color.red = 1;
    color.green = 200.0/255;
    color.blue = 119.00/255;
    color.alpha = 1;
  }

  gdk_cairo_rectangle(cr, &rect);
  gdk_cairo_set_source_rgba(cr, &color);
  cairo_fill(cr);

  widget = widget;
  data = data; 
  return FALSE;
}
