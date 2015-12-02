/*  
*   @file   Gato.c
*   @brief  Programa con interfaz grafica para juagr gato.
*           Permite guardar una partida y reiniciarla en cualquier momento.

*   @author Carla Juarez
*           Lucas Comamala
*
*   @date   28/11/2015
*/

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

/* Turn number */
int count=1;
GtkWidget *window;

/* Prototypes */
void ButtonClicked(GtkButton *button, gpointer data);
void StopTheApp(GtkWidget *window, gpointer data);

GtkWidget *AddButton(GtkWidget *theBox, GtkWidget *EntryBox);

void checar(void);

/* Main Function */
gint main ( gint argc, gchar *argv[])
{

  /* Widgets */


  GtkWidget *menubar;
  GtkWidget *fileMenu;
  GtkWidget *fileMi;
  GtkWidget *quitMi;


  /* Boxes */
  GtkWidget *verticalbox;
  GtkWidget *box1, *box2, *box3;

  /* Buttons */
  GtkWidget *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8, *button9;
  
  /* Color */
  GdkColor color;
  gdk_color_parse("#ff66cc", &color);
  
  /* Initialization */
  gtk_init(&argc, &argv);

  /* Window Initialization */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
  gtk_window_set_title(GTK_WINDOW(window), "Gato");
  gtk_container_border_width(GTK_CONTAINER(window), 0);
  //gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);

  /* Boxes Initialization */
  verticalbox = gtk_vbox_new(FALSE,5);

  box1 = gtk_hbox_new(TRUE,5);
  box2 = gtk_hbox_new(TRUE,5);
  box3 = gtk_hbox_new(TRUE,5);

  /* Buttons Initialization */
  button1 = AddButton(box1, NULL);
  gtk_widget_show(button1);
  button2 = AddButton(box1, NULL);
  gtk_widget_show(button2);
  button3 = AddButton(box1, NULL);
  gtk_widget_show(button3);

  button4 = AddButton(box2, NULL);
  gtk_widget_show(button4);
  button5 = AddButton(box2, NULL);
  gtk_widget_show(button5);
  button6 = AddButton(box2, NULL);
  gtk_widget_show(button6);

  button7 = AddButton(box3, NULL);
  gtk_widget_show(button7);
  button8 = AddButton(box3, NULL);
  gtk_widget_show(button8);
  button9 = AddButton(box3, NULL);
  gtk_widget_show(button9);

  menubar = gtk_menu_bar_new();
  fileMenu = gtk_menu_new();

  fileMi = gtk_menu_item_new_with_label("File");
  quitMi = gtk_menu_item_new_with_label("Quit");

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
  gtk_box_pack_start(GTK_BOX(verticalbox), menubar, FALSE, FALSE, 0);
  
  /* Packing */
  gtk_box_pack_start(GTK_BOX(verticalbox), box1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(verticalbox), box2, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(verticalbox), box3, TRUE, TRUE, 0);

  

  g_signal_connect(window, "destroy", G_CALLBACK(StopTheApp), NULL);

  gtk_container_add(GTK_CONTAINER(window), verticalbox);
  
  gtk_widget_show_all(window);
  
  gtk_main();

  return 0;

}

/* Add Button Function */
GtkWidget *AddButton(GtkWidget *theBox, GtkWidget *EntryBox)
{
    GtkWidget *button;
    button = gtk_button_new_with_label("");
    gtk_box_pack_start(GTK_BOX(theBox), button, FALSE, TRUE, 0);
    g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), EntryBox);
    return button;
}

/* Click Button Function */
void ButtonClicked(GtkButton *button, gpointer data)
{

  if (strcmp(gtk_button_get_label(button), "") == 0)
  {
    if (count % 2 != 0)
    {
      gtk_button_set_label(button, "X");
      //checar();
      gtk_window_set_title(GTK_WINDOW(window), "Turno: Jugador 2");
    }
    else
    {
      gtk_button_set_label(button, "O");
      //checar();
      gtk_window_set_title(GTK_WINDOW(window), "Turno: Jugador 1");
    }

    
    count++;
  }
}

/*void checar(void)
{
if (
    ((strcmp(gtk_button_get_label(button1), gtk_button_get_label(button2)) == 0) && 
    (strcmp(gtk_button_get_label(button1), gtk_button_get_label(button3)) == 0)) ||

    ((strcmp(gtk_button_get_label(button4), gtk_button_get_label(button5)) == 0) && 
    (strcmp(gtk_button_get_label(button4), gtk_button_get_label(button6)) == 0)) ||

    ((strcmp(gtk_button_get_label(button7), gtk_button_get_label(button8)) == 0) && 
    (strcmp(gtk_button_get_label(button7), gtk_button_get_label(button9)) == 0)) ||

    ((strcmp(gtk_button_get_label(button1), gtk_button_get_label(button4)) == 0) && 
    (strcmp(gtk_button_get_label(button1), gtk_button_get_label(button7)) == 0)) ||

    ((strcmp(gtk_button_get_label(button2), gtk_button_get_label(button5)) == 0) && 
    (strcmp(gtk_button_get_label(button2), gtk_button_get_label(button8)) == 0)) ||

    ((strcmp(gtk_button_get_label(button3), gtk_button_get_label(button6)) == 0) && 
    (strcmp(gtk_button_get_label(button3), gtk_button_get_label(button9)) == 0)) ||

    ((strcmp(gtk_button_get_label(button1), gtk_button_get_label(button5)) == 0) && 
    (strcmp(gtk_button_get_label(button1), gtk_button_get_label(button9)) == 0)) ||

    ((strcmp(gtk_button_get_label(button3), gtk_button_get_label(button5)) == 0) && 
    (strcmp(gtk_button_get_label(button3), gtk_button_get_label(button7)) == 0)) ||
    )
    {
      g_print("%s", gtk_window_get_title());

    }

}*/

/* StopTheApp */
void StopTheApp(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}


