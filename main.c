#include <stdlib.h>
#include <gtk/gtk.h>


GtkWidget *PantallaPrimerTurno;/*creamos primer pantalla, es global*/

int main (int argc, char *argv[])
{
    iniciarGtk(argc,argv);
    primerPantalla();
    return 0;
}

void pantallaPrincipal(GtkWidget *wid, gpointer data)
{


    GtkWidget *mainWindow;/*creamos primer pantalla*/
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);/*se inicializa*/
    g_signal_connect(mainWindow, "delete-event", G_CALLBACK(gtk_main_quit),NULL);/*evento para poder cerrarla*/
    gtk_window_set_title (GTK_WINDOW (mainWindow), "Gyges");/*le ponemos un titulo*/
    gtk_window_move (mainWindow,0,0);/*la opnemos en la pura esquina superior izquierda*/
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), 775, 600);


    GtkWidget *contenedor = gtk_fixed_new ();/*creamos un contenedor donde pondremos todos los widgets*/
    gtk_container_add (GTK_CONTAINER (mainWindow), contenedor);/*lo añadimos a la pantalla*/

    GtkWidget *label;/*creamos un label*/
    label = gtk_label_new ("Gyges");
    gtk_fixed_put (contenedor,label,400,0);/*lo ponemos en el contenedor en la posicion 500 0*/

    /*ponemos la imagen del tablero*/
    GtkWidget *tablero = gtk_image_new ();/*creamos la imagen en blanco*/
    gtk_image_set_from_file (tablero,"Tablero.png");/*la cargamos del filename*/
    gtk_fixed_put (contenedor,tablero,1,40);/*lo ponemos en el contenedor en la posicion*/

    GtkWidget *label2;/*creamos un label*/
    label2 = gtk_label_new ("Turno del jugador:");
    gtk_fixed_put (contenedor,label2,580,10);/*lo ponemos en el contenedor en la posicion*/



    GtkWidget *buttonInteligencia = gtk_button_new_with_label ("Juega Inteligencia");
    gtk_fixed_put (contenedor,buttonInteligencia,600,50);/*lo ponemos en el contenedor en la posicion*/

    GtkWidget *buttonHumano = gtk_button_new_with_label ("Juega Humano");
    gtk_fixed_put (contenedor,buttonHumano,600,100);/*lo ponemos en el contenedor en la posicion*/

     GtkWidget *buttonSalir = gtk_button_new_with_label ("SALIR");
    gtk_fixed_put (contenedor,buttonSalir,690,590);/*lo ponemos en el contenedor en la posicion*/

    GtkWidget *entrada = gtk_entry_new();
    gtk_fixed_put (contenedor,entrada,600,150);/*lo ponemos en el contenedor en la posicion*/

    GtkWidget  *labelJugador;
    if(((char*) data) == "1")/*juega cielo*/
    {
        labelJugador = gtk_label_new ("Cielo");
    }
    else
    {
        labelJugador = gtk_label_new ("Infierno");
    }
    gtk_fixed_put (contenedor,labelJugador,703,10);/*lo ponemos en el contenedor en la posicion*/

    gtk_widget_show (contenedor);/*mostramos el contenedor con todos los widgets*/
    gtk_widget_show_all (mainWindow);
    gtk_widget_hide(PantallaPrimerTurno);/*la pantallla nunca es borrada, solo escondida"*/
}

void iniciarGtk(int argc, char *argv[])
{
      /* Initialize GTK+ */
      g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
      gtk_init (&argc, &argv);
      g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

}
void primerPantalla()
/*Primer pantalla. Aquí se selecciona si comienza infierno o cielo.*/
{
    PantallaPrimerTurno = gtk_window_new(GTK_WINDOW_TOPLEVEL);/*se inicializa*/
    g_signal_connect(PantallaPrimerTurno, "delete-event", G_CALLBACK(gtk_main_quit),NULL);/*evento para poder cerrarla*/
    gtk_signal_connect (GTK_OBJECT (PantallaPrimerTurno), "destroy",GTK_SIGNAL_FUNC (gtk_exit), NULL);
    gtk_widget_show(PantallaPrimerTurno);/*se muestra*/
    gtk_window_set_title (GTK_WINDOW (PantallaPrimerTurno), "Escoja quien comienza");/*le ponemos un titulo*/
    gtk_window_set_position (GTK_WINDOW (PantallaPrimerTurno), GTK_WIN_POS_CENTER);/* la ponemos en el centro*/


    GtkWidget *buttonCielo = gtk_button_new_with_label ("Juega Cielo");
    GtkWidget *buttonInfierno = gtk_button_new_with_label ("Juega Infierno");
    /*asociamos un boton con una funcion*/
    gtk_signal_connect (GTK_OBJECT (buttonCielo), "clicked",GTK_SIGNAL_FUNC (pantallaPrincipal), (gpointer) "1");
    g_signal_connect (G_OBJECT (buttonInfierno), "clicked", G_CALLBACK (pantallaPrincipal), (gpointer) "2");

    /*creamos un contenedor para los botones*/
    GtkWidget *contenedor = gtk_vbox_new (TRUE, 6);
    gtk_container_add (GTK_CONTAINER (PantallaPrimerTurno), contenedor);

    /*metemos ambos botones en el contenedor*/
    gtk_box_pack_start (GTK_BOX (contenedor), buttonCielo, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (contenedor), buttonInfierno, TRUE, TRUE, 0);

    gtk_widget_show_all (PantallaPrimerTurno);
    gtk_main();
}



