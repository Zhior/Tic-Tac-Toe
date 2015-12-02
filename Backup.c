/*  
*   @file   Gato.c
*   @brief  Programa con interfaz grafica para juagr gato.
*           Permite guardar una partida y reiniciarla en cualquier momento.

*   @author Karla Juárez
*           Lucas Comamala
*
*   @date   28/11/2015
*/

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

struct Elementos{
  GtkWidget *window;
  GtkWidget *button[9];
  int count;
}elementos;

/* Prototypes */
void ButtonClicked(GtkButton *button, gpointer *data);
void StopTheApp(GtkWidget *window, gpointer data);

void checar(struct Elementos *elementos);

/* Main Function */
gint main ( gint argc, gchar *argv[])
{

  struct Elementos elementos;
  elementos.count = 1;

  /* Widgets */

  /* Boxes */
  GtkWidget *verticalbox;
  GtkWidget *box1, *box2, *box3, *box4;
  GtkWidget *button10, *button11, *button12;
  
  /* Color */
  GdkColor color;
  gdk_color_parse("#ff66cc", &color);
  
  /* Initialization */
  gtk_init(&argc, &argv);

  /* Window Initialization */
  elementos.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(elementos.window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(elementos.window), 300, 300);
  gtk_window_set_title(GTK_WINDOW(elementos.window), "Gato");
  gtk_container_border_width(GTK_CONTAINER(elementos.window), 0);
  gtk_widget_modify_bg(elementos.window, GTK_STATE_NORMAL, &color);

  /* Boxes Initialization */
  verticalbox = gtk_vbox_new(FALSE,5);

  box1 = gtk_hbox_new(TRUE,5);
  box2 = gtk_hbox_new(TRUE,5);
  box3 = gtk_hbox_new(TRUE,5);
  box4 = gtk_hbox_new(TRUE,20);

  /* Buttons Initialization */
  elementos.button[0] = gtk_button_new_with_label("");
  elementos.button[1] = gtk_button_new_with_label("");
  elementos.button[2] = gtk_button_new_with_label("");
  elementos.button[3] = gtk_button_new_with_label("");
  elementos.button[4] = gtk_button_new_with_label("");
  elementos.button[5] = gtk_button_new_with_label("");
  elementos.button[6] = gtk_button_new_with_label("");
  elementos.button[7] = gtk_button_new_with_label("");
  elementos.button[8] = gtk_button_new_with_label("");

  gtk_box_pack_start(GTK_BOX(box1), elementos.button[0], FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box1), elementos.button[1], FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box1), elementos.button[2], FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box2), elementos.button[3], FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box2), elementos.button[4], FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box2), elementos.button[5], FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box3), elementos.button[6], FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box3), elementos.button[7], FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box3), elementos.button[8], FALSE, TRUE, 0);

  g_signal_connect(GTK_OBJECT(elementos.button[0]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), &elementos);
  g_signal_connect(GTK_OBJECT(elementos.button[1]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), &elementos);
  g_signal_connect(GTK_OBJECT(elementos.button[2]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), &elementos);
  g_signal_connect(GTK_OBJECT(elementos.button[3]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), &elementos);
  g_signal_connect(GTK_OBJECT(elementos.button[4]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), &elementos);
  g_signal_connect(GTK_OBJECT(elementos.button[5]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), &elementos);
  g_signal_connect(GTK_OBJECT(elementos.button[6]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), &elementos);
  g_signal_connect(GTK_OBJECT(elementos.button[7]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), &elementos);
  g_signal_connect(GTK_OBJECT(elementos.button[8]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), &elementos);

  gtk_widget_show(elementos.button[0]);
  gtk_widget_show(elementos.button[1]);
  gtk_widget_show(elementos.button[2]);
  gtk_widget_show(elementos.button[3]);
  gtk_widget_show(elementos.button[4]);
  gtk_widget_show(elementos.button[5]);
  gtk_widget_show(elementos.button[6]);
  gtk_widget_show(elementos.button[7]);
  gtk_widget_show(elementos.button[8]);
 
  button10 = gtk_button_new_with_label("Nuevo");
  gtk_box_pack_start(GTK_BOX(box4), button10, FALSE, TRUE, 0);
  g_signal_connect(GTK_OBJECT(button10), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), NULL);
  gtk_widget_show(button10);

  button11 = gtk_button_new_with_label("Guardar");
  gtk_box_pack_start(GTK_BOX(box4), button11, FALSE, TRUE, 0);
  g_signal_connect(GTK_OBJECT(button11), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), NULL);
  gtk_widget_show(button11);

  button12 = gtk_button_new_with_label("Cargar");
  gtk_box_pack_start(GTK_BOX(box4), button12, FALSE, TRUE, 0);
  g_signal_connect(GTK_OBJECT(button12), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), NULL);
  gtk_widget_show(button12);
  
  /* Packing */
  gtk_box_pack_start(GTK_BOX(verticalbox), box4, TRUE, TRUE, 10);
  gtk_box_pack_start(GTK_BOX(verticalbox), box1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(verticalbox), box2, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(verticalbox), box3, TRUE, TRUE, 0);
  

  g_signal_connect(elementos.window, "destroy", G_CALLBACK(StopTheApp), NULL);

  gtk_container_add(GTK_CONTAINER(elementos.window), verticalbox);
  
  gtk_widget_show_all(elementos.window);
  
  gtk_main();

  return 0;

}

/* Add Button Function */
GtkWidget *AddButton(GtkWidget *theBox, GtkWidget *EntryBox)
{
    GtkWidget *button;
    button = gtk_button_new_with_label("");
    gtk_box_pack_start(GTK_BOX(theBox), button, FALSE, TRUE, 0);
    g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), NULL);
    return button;
}


/* Click Button Function */
void ButtonClicked(GtkButton *button, gpointer *data)
{
  struct Elementos *elementos = (struct Elementos *) data;

  if (strcmp(gtk_button_get_label(button), "") == 0)
  {
    if (elementos->count % 2 != 0)
    {
      gtk_button_set_label(button, "X");
      checar(elementos);
      gtk_window_set_title(GTK_WINDOW(elementos->window), "Turno: Jugador 2");
    }
    else
    {
      gtk_button_set_label(button, "O");
      checar(elementos);
      gtk_window_set_title(GTK_WINDOW(elementos->window), "Turno: Jugador 1");
    }

    
    elementos->count++;
  }
}

void checar(struct Elementos *elementos)
{
  GtkWidget *dialog, *label, *content_area;

  if (
    ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[1]))) == 0) && 
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[2]))) == 0) &&
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[1])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), "") != 0))

    ||

    ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[3])), gtk_button_get_label(GTK_BUTTON(elementos->button[4]))) == 0) && 
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[3])), gtk_button_get_label(GTK_BUTTON(elementos->button[5]))) == 0) &&
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[3])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[4])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[5])), "") != 0))

    ||

    ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[6])), gtk_button_get_label(GTK_BUTTON(elementos->button[7]))) == 0) && 
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[6])), gtk_button_get_label(GTK_BUTTON(elementos->button[8]))) == 0) &&
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[6])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[7])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[8])), "") != 0))

    ||

    ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[3]))) == 0) && 
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[6]))) == 0) &&
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[3])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[6])), "") != 0))

    ||

    ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[1])), gtk_button_get_label(GTK_BUTTON(elementos->button[4]))) == 0) && 
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[1])), gtk_button_get_label(GTK_BUTTON(elementos->button[7]))) == 0) &&
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[1])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[4])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[7])), "") != 0))

    ||

    ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), gtk_button_get_label(GTK_BUTTON(elementos->button[5]))) == 0) && 
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), gtk_button_get_label(GTK_BUTTON(elementos->button[8]))) == 0) &&
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[5])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[8])), "") != 0))

    ||

    ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[4]))) == 0) && 
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[8]))) == 0) &&
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[4])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[8])), "") != 0))
    ||

    ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), gtk_button_get_label(GTK_BUTTON(elementos->button[4]))) == 0) && 
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), gtk_button_get_label(GTK_BUTTON(elementos->button[6]))) == 0) &&
    (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[4])), "") != 0) && (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[6])), "") != 0))
    )
    {
      if (elementos->count % 2 != 0)
      {
        dialog = gtk_dialog_new_with_buttons ("Gato", GTK_WINDOW(elementos->window), GTK_DIALOG_DESTROY_WITH_PARENT, "Salir", GTK_RESPONSE_NONE,
                                              NULL);

         content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
         label = gtk_label_new ("Ganador: jugador 2!");
  
         g_signal_connect_swapped (dialog,
                                   "response",
                                   G_CALLBACK (StopTheApp),
                                   dialog);

         gtk_container_add (GTK_CONTAINER (content_area), label);
         gtk_widget_show_all (dialog);
       }
       else
       {
          dialog = gtk_dialog_new_with_buttons ("Gato", GTK_WINDOW(elementos->window), GTK_DIALOG_DESTROY_WITH_PARENT, "Salir", GTK_RESPONSE_NONE,
                                                NULL);

           content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
           label = gtk_label_new ("Ganador: jugador 1!");
   
           g_signal_connect_swapped (dialog,
                                     "response",
                                     G_CALLBACK (StopTheApp),
                                     dialog);

           gtk_container_add (GTK_CONTAINER (content_area), label);
           gtk_widget_show_all (dialog);
       }
    }

}

/* StopTheApp */
void StopTheApp(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}


