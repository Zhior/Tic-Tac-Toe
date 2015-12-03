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

struct Elementos
{
  GtkWidget *window;
  //Arreglo de botones. Desfasado. (La funcion del boton 0 termina en 1, las del boton 1 termina en 2...)
  //Esto se debe a que el arreglo lugares[] a veces se inicizaliza con basura entonces lo inicializé manualmente con 0s.
  GtkWidget *button[9]; 
  int count;
  int lugares[9];
} elementos;

/* Prototypes */
void ButtonClicked1 ( GtkButton *button, gpointer *data );
void ButtonClicked2 ( GtkButton *button, gpointer *data );
void ButtonClicked3 ( GtkButton *button, gpointer *data );
void ButtonClicked4 ( GtkButton *button, gpointer *data );
void ButtonClicked5 ( GtkButton *button, gpointer *data );
void ButtonClicked6 ( GtkButton *button, gpointer *data );
void ButtonClicked7 ( GtkButton *button, gpointer *data );
void ButtonClicked8 ( GtkButton *button, gpointer *data );
void ButtonClicked9 ( GtkButton *button, gpointer *data );

void checar ( struct Elementos *elementos );
void newGame ( GtkButton *button, gpointer *data );
void newGame2 (struct Elementos *elementos);
void saveGame ( GtkButton *button, gpointer *data );
void loadGame ( GtkButton *button, gpointer *data );

void StopTheApp ( GtkWidget *window, gpointer data );

void printToLog ( char *entry );

/* Main Function */
gint main ( gint argc, gchar *argv[])
{

  /* Declaracion de varibles */
  struct Elementos elementos;
  elementos.count = 0;
  int i;

  for(i=0;i<9;i++)
    elementos.lugares[i] =0;

  /* Widgets */
  /* Boxes */
  GtkWidget *verticalbox;
  GtkWidget *box1, *box2, *box3, *box4;
  GtkWidget *button1, *button2, *button3;
  
  /* Color */
  GdkColor color;
  gdk_color_parse("#ff66cc", &color);

  /* Imagenes */
  GtkWidget *imgNuevo, *imgGuardar, *imgCargar;

 
  /* Initialization */ gtk_init(&argc, &argv);
  /* Window Initialization */
  elementos.window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_position( GTK_WINDOW(elementos.window), GTK_WIN_POS_CENTER );
  gtk_window_set_default_size( GTK_WINDOW(elementos.window), 300, 350 );
  gtk_window_set_title( GTK_WINDOW(elementos.window), "Gato" );
  gtk_container_border_width( GTK_CONTAINER(elementos.window), 0 );
  gtk_widget_modify_bg( elementos.window, GTK_STATE_NORMAL, &color );

  GtkSettings *default_settings = gtk_settings_get_default();
  g_object_set(default_settings, "gtk-button-images", TRUE, NULL); 

  /* Boxes Initialization */
  verticalbox = gtk_vbox_new( FALSE,5 );

  box1 = gtk_hbox_new( TRUE,5 );
  box2 = gtk_hbox_new( TRUE,5 );
  box3 = gtk_hbox_new( TRUE,5 );
  box4 = gtk_hbox_new( TRUE,20 );

  /* Imagenes */
  imgNuevo = gtk_image_new_from_file( "images/x.png" );
  imgGuardar = gtk_image_new_from_file( "images/save.png" );
  imgCargar = gtk_image_new_from_file( "images/open.png" );

  /* Buttons Initialization */
  /* Tablero Gato */
  for ( i=0; i<9; i++ )
    elementos.button[i] = gtk_button_new_with_label("");

  for ( i=0; i<3; i++ )
    gtk_box_pack_start( GTK_BOX(box1), elementos.button[i], FALSE, TRUE, 0 );
  for ( i=3; i<6; i++ )
    gtk_box_pack_start( GTK_BOX(box2), elementos.button[i], FALSE, TRUE, 0 );
  for ( i=6; i<9; i++ )
    gtk_box_pack_start( GTK_BOX(box3), elementos.button[i], FALSE, TRUE, 0 );

  g_signal_connect( GTK_OBJECT(elementos.button[0]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked1), &elementos );
  g_signal_connect( GTK_OBJECT(elementos.button[1]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked2), &elementos );
  g_signal_connect( GTK_OBJECT(elementos.button[2]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked3), &elementos );
  g_signal_connect( GTK_OBJECT(elementos.button[3]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked4), &elementos );
  g_signal_connect( GTK_OBJECT(elementos.button[4]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked5), &elementos );
  g_signal_connect( GTK_OBJECT(elementos.button[5]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked6), &elementos );
  g_signal_connect( GTK_OBJECT(elementos.button[6]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked7), &elementos );
  g_signal_connect( GTK_OBJECT(elementos.button[7]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked8), &elementos );
  g_signal_connect( GTK_OBJECT(elementos.button[8]), "clicked", GTK_SIGNAL_FUNC(ButtonClicked9), &elementos );

  for ( i=0; i<9; i++ )
  gtk_widget_show( elementos.button[i] );
 
  /* Function Buttons */
  button1 = gtk_button_new_with_label( "Nuevo" );
  gtk_button_set_image( GTK_BUTTON(button1), imgNuevo );
  gtk_box_pack_start( GTK_BOX(box4), button1, FALSE, TRUE, 0 );
  g_signal_connect( GTK_OBJECT(button1), "clicked", GTK_SIGNAL_FUNC(newGame), &elementos );
  gtk_widget_show( button1 );

  button2 = gtk_button_new_with_label( "Guardar" );
  gtk_button_set_image( GTK_BUTTON(button2), imgGuardar );
  gtk_box_pack_start( GTK_BOX(box4), button2, FALSE, TRUE, 0 );
  g_signal_connect( GTK_OBJECT(button2), "clicked", GTK_SIGNAL_FUNC(saveGame), &elementos );
  gtk_widget_show( button2 );

  button3 = gtk_button_new_with_label( "Cargar" );
  gtk_button_set_image( GTK_BUTTON(button3), imgCargar );
  gtk_box_pack_start( GTK_BOX(box4), button3, FALSE, TRUE, 0 );
  g_signal_connect( GTK_OBJECT(button3), "clicked", GTK_SIGNAL_FUNC(ButtonClicked1), &elementos );
  gtk_widget_show( button3 );


  /* Packing */
  gtk_box_pack_start( GTK_BOX(verticalbox), box4, TRUE, TRUE, 10 );
  gtk_box_pack_start( GTK_BOX(verticalbox), box1, TRUE, TRUE, 0 );
  gtk_box_pack_start( GTK_BOX(verticalbox), box2, TRUE, TRUE, 0 );
  gtk_box_pack_start( GTK_BOX(verticalbox), box3, TRUE, TRUE, 0 );
  

  g_signal_connect( elementos.window, "destroy", G_CALLBACK(StopTheApp), NULL );
  gtk_container_add( GTK_CONTAINER(elementos.window), verticalbox );
  gtk_widget_show_all( elementos.window );
  gtk_main();
  return 0;

}

/**
*  9 funciones que se llaman se pica uno de los nueve botones del tablero del juego.
*  Dentro de esta función también se llama la función que verifica el ganador.
*  @param *button	El botón que presionó el usuario
*  @param *data		La estructura que contiene todos los botones y la ventana
**/
void ButtonClicked1 ( GtkButton *button, gpointer *data )
{

  struct Elementos *elementos = (struct Elementos *) data;

  if( strcmp( gtk_button_get_label(button), "" ) == 0 )
  {
    elementos->lugares[elementos->count] = 1;

    if ( elementos->count % 2 == 0 )
    {
      gtk_button_set_label(button, "X");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 2" );
      checar(elementos);
    }
    else
    {
      gtk_button_set_label(button, "O");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 1" );
      checar(elementos);
    }
  }

}

void ButtonClicked2 ( GtkButton *button, gpointer *data )
{

  struct Elementos *elementos = (struct Elementos *) data;

  if ( strcmp(gtk_button_get_label(button), "") == 0 )
  {
    elementos->lugares[elementos->count] = 2;

    if ( elementos->count % 2 == 0 )
    {
      gtk_button_set_label(button, "X");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 2" );
      checar(elementos);
    }
    else
    {
      gtk_button_set_label(button, "O");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 1" );
      checar(elementos);
    }
  }

}

void ButtonClicked3 ( GtkButton *button, gpointer *data )
{

  struct Elementos *elementos = (struct Elementos *) data;

  if ( strcmp(gtk_button_get_label(button), "") == 0 )
  {
    elementos->lugares[elementos->count] = 3;

    if ( elementos->count % 2 == 0 )
    {
      gtk_button_set_label(button, "X");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 2" );
      checar(elementos);
    }
    else
    {
      gtk_button_set_label(button, "O");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 1" );
      checar(elementos);
    }
  }

}

void ButtonClicked4 ( GtkButton *button, gpointer *data )
{

  struct Elementos *elementos = (struct Elementos *) data;

  if ( strcmp(gtk_button_get_label(button), "") == 0 )
  {
    elementos->lugares[elementos->count] = 4;

    if ( elementos->count % 2 == 0 )
    {
      gtk_button_set_label(button, "X");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 2" );
      checar(elementos);
    }
    else
    {
      gtk_button_set_label(button, "O");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 1" );
      checar(elementos);
    }
  }

}

void ButtonClicked5 ( GtkButton *button, gpointer *data)
{

  struct Elementos *elementos = (struct Elementos *) data;

  if (strcmp(gtk_button_get_label(button), "") == 0)
  {
    elementos->lugares[elementos->count] = 5;

    if ( elementos->count % 2 == 0 )
    {
      gtk_button_set_label(button, "X");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 2" );
      checar(elementos);
    }
    else
    {
      gtk_button_set_label(button, "O");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 1" );
      checar(elementos);
    }
  }

}

void ButtonClicked6 ( GtkButton *button, gpointer *data )
{

  struct Elementos *elementos = (struct Elementos *) data;

  if ( strcmp(gtk_button_get_label(button), "") == 0 )
  {
    elementos->lugares[elementos->count] = 6;

    if ( elementos->count % 2 == 0 )
    {
      gtk_button_set_label(button, "X");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 2" );
      checar(elementos);
    }
    else
    {
      gtk_button_set_label(button, "O");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 1" );
      checar(elementos);
    }
  }

}

void ButtonClicked7 ( GtkButton *button, gpointer *data )
{

  struct Elementos *elementos = (struct Elementos *) data;

  if ( strcmp(gtk_button_get_label(button), "") == 0 )
  {
    elementos->lugares[elementos->count] = 7;

    if ( elementos->count % 2 == 0 )
    {
      gtk_button_set_label(button, "X");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 2" );
      checar(elementos);
    }
    else
    {
      gtk_button_set_label(button, "O");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 1" );
      checar(elementos);
    }
  }

}

void ButtonClicked8 ( GtkButton *button, gpointer *data )
{

  struct Elementos *elementos = (struct Elementos *) data;

  if ( strcmp(gtk_button_get_label(button), "" ) == 0)
  {
    elementos->lugares[elementos->count] = 8;

    if ( elementos->count % 2 == 0 )
    {
      gtk_button_set_label(button, "X");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 2" );
      checar(elementos);
    }
    else
    {
      gtk_button_set_label(button, "O");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 1" );
      checar(elementos);
    }
  }

}

void ButtonClicked9 ( GtkButton *button, gpointer *data )
{

  struct Elementos *elementos = (struct Elementos *) data;

  if ( strcmp(gtk_button_get_label(button), "") == 0 )
  {
    elementos->lugares[elementos->count] = 9;

    if (elementos->count % 2 == 0)
    {
      gtk_button_set_label(button, "X");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 2" );
      checar(elementos);
    }
    else
    {
      gtk_button_set_label(button, "O");
      elementos->count++;
      gtk_window_set_title( GTK_WINDOW(elementos->window), "Turno: Jugador 1" );
      checar(elementos);
    }
  }

}

/**
*  Función para reiniciar el juego.
*  Se llama con el botón de la pantalla principal.
*  @param *button	El botón que presionó el usuario (nuevo).
*  @param *data		La estructura que contiene todos los botones y la ventana.
**/
void newGame(GtkButton *button, gpointer *data)
{

  struct Elementos *elementos = (struct Elementos *) data;
  int i;

  printToLog("Intentando reiniciar el juego...\n");

  for( i=0; i<9; i++ )
    gtk_button_set_label(GTK_BUTTON(elementos->button[i]), "");

  for( i=0; i<9; i++ )
    elementos->lugares[i] = 0;

  gtk_window_set_title(GTK_WINDOW(elementos->window), "Turno: Jugador 1");

  elementos->count = 0;

  printToLog("Juego reiniciado.\n");

}

/**
*  Función para reiniciar el juego con diferentes argumentos.
*  Se llama desde el dialogo cuando se termina un juego.
*  @param *button	El botón que presionó el usuario (nuevo).
*  @param *data		La estructura que contiene todos los botones y la ventana.
**/
void newGame2(struct Elementos *elementos)
{

  int i;

  printToLog("Intentando reiniciar el juego...\n");

  for( i=0; i<9; i++ )
    gtk_button_set_label(GTK_BUTTON(elementos->button[i]), "");

  for( i=0; i<9; i++ )
    elementos->lugares[i] = 0;

  gtk_window_set_title(GTK_WINDOW(elementos->window), "Turno: Jugador 1");

  elementos->count = 0;

  printToLog("Juego reiniciado.\n");

}

/**
*  Función que guarda el juego actual.
*  @param *button	El botón que presionó el usuario (guardar).
*  @param *data		La estructura que contiene todos los botones y la ventana.
**/
void saveGame(GtkButton *button, gpointer *data)
{

  struct Elementos *elementos = (struct Elementos *) data;
  
  int i;
  char nombre[22];

  time_t rawtime;
  struct tm *infom;

  FILE *archivo;

  printToLog("Intentando guardar...\n");

  /* Utiliza la fecha y hor actual para crear el nombre del archivo */
  time(&rawtime);
  infom = localtime(&rawtime);
  strftime(nombre, 80, "%x_%H:%M", infom);
  
  for ( i=0; i<22; i++ )
    if ( nombre[i]  == '/' )
      nombre[i] = '-';

  archivo = fopen(nombre, "wt");

  /* Sin memoria error */
  if ( archivo == NULL )
  {
    printToLog("Falta de memoria.\n");
    exit(1);
  }
	
  /* Popula el archivo de texto con los movimientos en orden */
  for ( i=0; i<9; i++ )
    if( elementos->lugares[i] == 0 )
      break;
    else
      fprintf(archivo, "%i\n", elementos->lugares[i]);

  /* DEBUG 
     DELETE ME!!!!!! */
  for(i=0;i<9;i++)
    g_print("%i\n", elementos->lugares[i]);


  fclose(archivo);

  printToLog("Archivo guardado exitosamente con el nombre: ");
  printToLog(nombre);
  printToLog("\n");

}

/**
*  Función que verifica el ganador del juego.
*  @param *elementos	La estructura que contiene todos los botones y la ventana.
**/
void checar ( struct Elementos *elementos )
{

  /* Crea una nueva ventana para el mensaje de ganador/empate */
  GtkWidget *dialog, *label, *content_area;
  gint result;

  // Ventana
  dialog = gtk_dialog_new ();
  gtk_window_set_title( GTK_WINDOW(dialog), "Gato" );
  gtk_container_border_width( GTK_CONTAINER(dialog), 5 );
  gtk_window_set_default_size( GTK_WINDOW(dialog), 150, 90 );

  // Botones
  gtk_dialog_add_buttons (GTK_DIALOG(dialog), GTK_STOCK_NEW, 1, GTK_STOCK_QUIT, 2, NULL);

  // Label
  content_area = gtk_dialog_get_content_area( GTK_DIALOG (dialog) );


  /* if() que comprueba si hay hay un ganador */
  if (
     (( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[0]) ), gtk_button_get_label( GTK_BUTTON(elementos->button[1]) )) == 0 ) && 
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[0]) ), gtk_button_get_label( GTK_BUTTON(elementos->button[2]) )) == 0 ) &&
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[0]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[1]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[2]) ), "") != 0 ))

     ||

     (( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[3]) ), gtk_button_get_label( GTK_BUTTON(elementos->button[4]) )) == 0 ) && 
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[3]) ), gtk_button_get_label( GTK_BUTTON(elementos->button[5]) )) == 0 ) &&
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[3]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[4]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[5]) ), "") != 0 ))

     ||

     (( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[6]) ), gtk_button_get_label( GTK_BUTTON(elementos->button[7]) )) == 0 ) && 
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[6]) ), gtk_button_get_label( GTK_BUTTON(elementos->button[8]) )) == 0 ) &&
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[6]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[7]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label( GTK_BUTTON(elementos->button[8]) ), "") != 0 ))

     ||

     (( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0]) ), gtk_button_get_label(GTK_BUTTON(elementos->button[3]) )) == 0 ) && 
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0]) ), gtk_button_get_label(GTK_BUTTON(elementos->button[6]) )) == 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[3]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[6]) ), "") != 0 ))

     ||

     (( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[1]) ), gtk_button_get_label( GTK_BUTTON(elementos->button[4]) )) == 0 ) && 
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[1]) ), gtk_button_get_label( GTK_BUTTON(elementos->button[7]) )) == 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[1]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[4]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[7]) ), "") != 0 ))

     ||

     (( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2]) ), gtk_button_get_label( GTK_BUTTON(elementos->button[5]) )) == 0 ) && 
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2]) ), gtk_button_get_label( GTK_BUTTON(elementos->button[8]) )) == 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[2]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[5]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[8]) ), "") != 0 ))

     ||

     (( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0]) ), gtk_button_get_label(GTK_BUTTON(elementos->button[4]) )) == 0 ) && 
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0]) ), gtk_button_get_label(GTK_BUTTON(elementos->button[8]) )) == 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[0]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[4]) ), "") != 0 ) &&
      ( strcmp(gtk_button_get_label(GTK_BUTTON(elementos->button[8]) ), "") != 0 ))
	 
     ||

     ((strcmp( gtk_button_get_label(GTK_BUTTON(elementos->button[2]) ), gtk_button_get_label(GTK_BUTTON(elementos->button[4]) )) == 0 ) && 
      (strcmp( gtk_button_get_label(GTK_BUTTON(elementos->button[2]) ), gtk_button_get_label(GTK_BUTTON(elementos->button[6]) )) == 0 ) &&
      (strcmp( gtk_button_get_label(GTK_BUTTON(elementos->button[2]) ), "") != 0 ) &&
      (strcmp( gtk_button_get_label(GTK_BUTTON(elementos->button[4]) ), "") != 0 ) &&
      (strcmp( gtk_button_get_label(GTK_BUTTON(elementos->button[6]) ), "") != 0 ))
    ) //End condition
    {

      /* Si el jugador 1 ganó */
      if (elementos->count % 2 != 0)
      {
        printToLog( "Ganador: Jugador 1.\n" );
        gtk_window_set_title( GTK_WINDOW(elementos->window), "Ganador: Jugador 1!" );
        label = gtk_label_new( "Jugador 1 ganó!" );

        //g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog);

        gtk_container_add( GTK_CONTAINER (content_area), label );
        gtk_widget_show(label);

        result = gtk_dialog_run ( GTK_DIALOG (dialog) );
        switch (result)
        {
          case 1:
            newGame2(elementos);
            break;
          default:
            printToLog("Terminando programa...\n");
            gtk_main_quit();
            break;
        }
      gtk_widget_destroy (dialog);

      }
      /* Si el jugador 2 ganó */
      else
      {

        printToLog( "Ganador: Jugador 2.\n" );
        gtk_window_set_title( GTK_WINDOW(elementos->window), "Ganador: Jugador 2!" );
        label = gtk_label_new( "Jugador 2 ganó!" );

        gtk_container_add(GTK_CONTAINER (content_area), label);
        gtk_widget_show(label);

        result = gtk_dialog_run( GTK_DIALOG (dialog) );
        switch (result)
        {
          case 1:
            newGame2(elementos);
            break;
          default:
            printToLog("Terminando programa...\n");
            gtk_main_quit();
            break;
        }
        gtk_widget_destroy (dialog);

      }

    } //End if

    /* Si empatan */
    else if( elementos->count > 8 )
    {
      printToLog("Juego empatado.\n");
      gtk_window_set_title(GTK_WINDOW(elementos->window), "GATO!!!");
      label = gtk_label_new ("Empate!");

      gtk_container_add(GTK_CONTAINER (content_area), label);
      gtk_widget_show(label);

      result = gtk_dialog_run( GTK_DIALOG (dialog) );
      switch (result)
      {
        case 1:
          newGame2(elementos);
          break;
        default:
          printToLog("Terminando programa...\n");
          gtk_main_quit();
          break;
      }
      gtk_widget_destroy (dialog);
    } //End else if
}

/**
*  Función que imprime a la consola para hacer pruebas o debug
*  @param	entry lo que se piensa imprimir
*/
void printToLog(char *entry)
{
  g_print("%s", entry);
}


/**
*  Función para destuir el programa
**/
void StopTheApp(GtkWidget *window, gpointer data)
{
  printToLog("Terminando programa...\n");
  gtk_main_quit();
}
