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
  int i;

  /* Widgets */

  /* Boxes */
  GtkWidget *verticalbox;
  GtkWidget *box1, *box2, *box3, *box4;
  GtkWidget *button1, *button2, *button3;
  
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
  
  /* Tablero de Gato */
  for( i=0; i<9; i++ )
    elementos.button[i] = gtk_button_new_with_label("");

  for( i=0; i<3; i++ )
    gtk_box_pack_start(GTK_BOX(box1), elementos.button[i], FALSE, TRUE, 0);
  for( i=3; i<6; i++ )
    gtk_box_pack_start(GTK_BOX(box2), elementos.button[i], FALSE, TRUE, 0);
  for( i=6; i<9; i++ )
    gtk_box_pack_start(GTK_BOX(box3), elementos.button[i], FALSE, TRUE, 0);

  for( i=0; i<9; i++ )
    g_signal_connect(GTK_OBJECT(elementos.button[9]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), &elementos);

  for( i=0; i<9; i++ )
    gtk_widget_show(elementos.button[i]);
 
  /* Function Buttons */
  button1 = gtk_button_new_with_label("Nuevo");
  gtk_box_pack_start(GTK_BOX(box4), button1, FALSE, TRUE, 0);
  g_signal_connect(GTK_OBJECT(button1), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), NULL);
  gtk_widget_show(button1);

  button2 = gtk_button_new_with_label("Guardar");
  gtk_box_pack_start(GTK_BOX(box4), button2, FALSE, TRUE, 0);
  g_signal_connect(GTK_OBJECT(button2), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), NULL);
  gtk_widget_show(button2);

  button3 = gtk_button_new_with_label("Cargar");
  gtk_box_pack_start(GTK_BOX(box4), button3, FALSE, TRUE, 0);
  g_signal_connect(GTK_OBJECT(button3), "clicked", GTK_SIGNAL_FUNC(ButtonClicked), NULL);
  gtk_widget_show(button3);
  
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

/**
*  Esta función se llama cuando se pica una de los nueve botones del tablero del juego.
*  Dentro de esta función también se llama la función que verifica el ganador.
*  @param *button	El botón que presionó el usuario
*  @param *data		La estructura que contiene todos los botones y la ventana
**/
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

/**
*  Función que verifica el ganador del juego.
*  @param *elementos	La estructura que contiene todos los botones y la ventana
**/
void checar(struct Elementos *elementos)
{
  GtkWidget *dialog, *label, *content_area;

  /* if() feo que comprueba si hay hay un ganador */
  if (
     ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[1]))) == 0) && 
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[2]))) == 0) &&
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[1])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), "") != 0))

     ||

     ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[3])), gtk_button_get_label(GTK_BUTTON(elementos->button[4]))) == 0) && 
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[3])), gtk_button_get_label(GTK_BUTTON(elementos->button[5]))) == 0) &&
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[3])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[4])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[5])), "") != 0))

     ||

     ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[6])), gtk_button_get_label(GTK_BUTTON(elementos->button[7]))) == 0) && 
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[6])), gtk_button_get_label(GTK_BUTTON(elementos->button[8]))) == 0) &&
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[6])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[7])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[8])), "") != 0))

     ||

     ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[3]))) == 0) && 
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[6]))) == 0) &&
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[3])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[6])), "") != 0))

     ||

     ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[1])), gtk_button_get_label(GTK_BUTTON(elementos->button[4]))) == 0) && 
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[1])), gtk_button_get_label(GTK_BUTTON(elementos->button[7]))) == 0) &&
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[1])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[4])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[7])), "") != 0))

     ||

     ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), gtk_button_get_label(GTK_BUTTON(elementos->button[5]))) == 0) && 
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), gtk_button_get_label(GTK_BUTTON(elementos->button[8]))) == 0) &&
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[5])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[8])), "") != 0))

     ||

     ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[4]))) == 0) && 
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), gtk_button_get_label(GTK_BUTTON(elementos->button[8]))) == 0) &&
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[4])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[8])), "") != 0))
	 
     ||

     ((strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), gtk_button_get_label(GTK_BUTTON(elementos->button[4]))) == 0) && 
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), gtk_button_get_label(GTK_BUTTON(elementos->button[6]))) == 0) &&
      (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[4])), "") != 0) && 
	  (strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[6])), "") != 0))
    )
    {
	  /* Si el judaor 1 ganó */
      if (elementos->count % 2 != 0)
      {
        dialog = gtk_dialog_new_with_buttons ("Gato", GTK_WINDOW(elementos->window), GTK_DIALOG_DESTROY_WITH_PARENT, "Salir", GTK_RESPONSE_NONE,
                                              NULL);

         content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
         label = gtk_label_new ("Jugador 2 ganó!");
  
         g_signal_connect_swapped (dialog,
                                   "response",
                                   G_CALLBACK (StopTheApp),
                                   dialog);

         gtk_container_add (GTK_CONTAINER (content_area), label);
         gtk_widget_show_all (dialog);
       }
	   /* Si el judaor 2 ganó */
       else
       {
          dialog = gtk_dialog_new_with_buttons ("Gato", GTK_WINDOW(elementos->window), GTK_DIALOG_DESTROY_WITH_PARENT, "Salir", GTK_RESPONSE_NONE, NULL);

           content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
           label = gtk_label_new ("Jugador 1 ganó!");
   
           g_signal_connect_swapped (dialog,
                                     "response",
                                     G_CALLBACK (StopTheApp),
                                     dialog);

           gtk_container_add (GTK_CONTAINER (content_area), label);
           gtk_widget_show_all (dialog);
       }
	   
    }

}

/**
*  Función para desturi el programa
**/
void StopTheApp(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}


