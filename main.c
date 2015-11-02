#include <stdlib.h>
#include "SWI-Prolog.h"
#include <gtk/gtk.h>


GtkWidget *mainWindow;/*creamos la pantalla global*/
GtkWidget *labelJugador;/*será el label que contiene el jugador actual*/
GtkWidget *contenedor; /*contenedor de imagenes*/
/*gyges([f3,f2,f3,f0,f0,f0,f1,f0,f0,f0,f0,f0,f1,f0,f1,f3,f0,f0,f0,f2,f0,f0,f2,f3,f0,f0,f2,f0,f0,f1,f0,f0,f0,f0,f0,f0],X,Actual,Pasada, p2).*/
GtkWidget *matrizImagenes[6][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};/*inicializada en 0*/
int tablero[6][6]  = {{0,0,0,0,0,0},
                      {0,0,0,0,0,0},
                      {0,0,0,0,0,0},
                      {0,0,0,0,0,0},
                      {0,0,0,0,0,0},
                      {0,0,0,0,0,0}
                     };/*inicializada en 0*/

int main (int argc, char *argv[])
{
    printf("Selecciona quien comienza: i (infierno) o c (cielo) \n");
    char turnoInicial[1];
    scanf("%s", &turnoInicial);
    iniciarGtk(argc,argv);
    if(strcmp(turnoInicial,"i") ==0){
        printf("juega infierno\n");
        pantallaPrincipal(0);
    }
    else if(strcmp(turnoInicial,"c") ==0){
        printf("juega cielo\n");
        pantallaPrincipal(1);
    }
    else{
        printf("Opcion incorrecta");
    }
    print_array(tablero);
    return 0;
}
/*si jugador = 0 comienza cielo, si no comienza infierno*/
void pantallaPrincipal(int jugador)
{
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);/*se inicializa*/
    g_signal_connect(mainWindow, "delete-event", G_CALLBACK(gtk_main_quit),NULL);/*evento para poder cerrarla*/
    gtk_window_set_title (GTK_WINDOW (mainWindow), "Gyges");/*le ponemos un titulo*/
    gtk_window_move (mainWindow,0,0);/*la opnemos en la pura esquina superior izquierda*/
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), 775, 600);


    contenedor = gtk_fixed_new ();/*creamos un contenedor donde pondremos todos los widgets*/
    gtk_container_add (GTK_CONTAINER (mainWindow), contenedor);/*lo añadimos a la pantalla*/

    GtkWidget *label;/*creamos un label*/
    label = gtk_label_new ("Gyges");
    gtk_fixed_put (contenedor,label,400,0);/*lo ponemos en el contenedor en la posicion 500 0*/

    /*ponemos la imagen del tablero*/
    GtkWidget *tablero = gtk_image_new ();/*creamos la imagen en blanco*/
    gtk_image_set_from_file (tablero,"Tablero.png");/*la cargamos del filename*/
    gtk_fixed_put (contenedor,tablero,1,40);/*lo ponemos en el contenedor en la posicion*/

    GtkWidget *lblJugadorActual;/*será el label que contiene el jugador actual*/
    lblJugadorActual = gtk_label_new ("Turno del jugador:");
    gtk_fixed_put (contenedor,lblJugadorActual,580,10);/*lo ponemos en el contenedor en la posicion*/



    if(jugador == 1)/*juega cielo*/
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
    juegoPrincipal(jugador);
}

void iniciarGtk(int argc, char *argv[])
{
      /* Initialize GTK+ */
      g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
      gtk_init (&argc, &argv);
      g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

}

void juegoPrincipal(int jugadorActual){
    int control = 0;
    char desicion[20],movimiento[20];
    int contador = 0;

    while (control == 0) {
        while ( gtk_events_pending() ) gtk_main_iteration();
        printf("\nSelecciona una opción: \n 0. Salir \n 1. Juega IA \n 2. Juega Persona\n");
        scanf("%s", &desicion);
        if(strcmp(desicion,"0") ==0){
            printf("Nos vemos!");
            control = 1;
        }
        else if(strcmp(desicion,"1") ==0){/*juega IA*/
            if(contador <12){/*estamos en etapas iniciales*/
                /*se pone pieza en tablero*/
                /*putImagen(fil,col,ficha)*/
                contador++;
            }
            else{
                /*tiene que hacer ya movimientos tuanis*/
                /*moveImagen(filOrigen, colOrigen, filDestino, colDestino);*/
            }
            siguienteTurno();
        }
        else if(strcmp(desicion,"2") ==0){/*juega Humano*/
            /*ahora hay que ver si es un moviiento valido, si si se meuve, si no no pasa nada*/
            /*muestraMensaje(mainWindow,"Movimiento ilegal. Juegue bien!");*/
            if(contador <12){/*estamos en etapas iniciales*/
                /*se pone pieza en tablero,basado en lo que el usuario escribio*/
                /*putImagen(fil,col,ficha)*/
                printf("Que ficha y dónde la quiere poner: \n");
                scanf("%s", &movimiento);
                contador++;
            }
            else{
                printf("Qué ficha y a donde la quiere mover: \n");
                scanf("%s", &movimiento);
                /*tiene que hacer ya movimientos tuanis, basado en lo que el usuario escribio*/
                /*moveImagen(filOrigen, colOrigen, filDestino, colDestino);*/
            }
            siguienteTurno();
        }
        else
        {
            muestraMensaje(mainWindow,"Opcion incorrecta. Solo existen 3 opciones: 0 ,1 y 2.");
        }
    }
}

/*metodo que invierte los labels de la pantalla*/
void siguienteTurno(){
    if (strcmp(gtk_label_get_text (labelJugador), "Cielo")==0)/*le tocará jugar a infierno*/
    {
        gtk_label_set_text (labelJugador,"Infierno");
    }
    else{/*le tocará jugar a cielo*/
        gtk_label_set_text (labelJugador,"Cielo");
    }
}

/*muestra en pantalla un mensaje de error de jugada incorrecta*/
/*recibe una pantalla padre, y un mensaje*/
void muestraMensaje(GtkWidget *pantallaPadre, char* mensaje)
{
     GtkWidget *pantallita = NULL;
     pantallita = gtk_message_dialog_new (GTK_WINDOW (pantallaPadre), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, mensaje);
     gtk_window_set_position (GTK_WINDOW (pantallita), GTK_WIN_POS_CENTER);
     gtk_dialog_run (GTK_DIALOG (pantallita));
     gtk_widget_destroy (pantallita);
}

/*pone una imagen en pantalla en fila y columna dada. Ficha debe ser 1,2,3*/
putImagen(int fil, int col, int ficha){
    char fichac[15];
    sprintf(fichac, "%d.png", ficha);
    int x = 162 + (col*48);
    int y = 202 + (fil*48);
    GtkWidget *fichaImagen = gtk_image_new ();/*creamos la imagen en blanco*/
    gtk_image_set_from_file (fichaImagen,fichac);/*la cargamos del filename*/
    gtk_fixed_put (contenedor,fichaImagen,x,y);/*lo ponemos en el contenedor en la posicion*/
    gtk_widget_show (contenedor);/*mostramos el contenedor con todos los widgets*/
    gtk_widget_show_all (mainWindow);
    matrizImagenes[fil][col] = fichaImagen;/*ponemos el puntero de la imagen en su determinada posicion*/
    tablero[fil][col] = ficha;/*actualizamos tambien la matriz lógica*/
}

/*mueve una imagen en el tablero, dada una coordenada a otra*/
moveImagen(int filOrigen, int colOrigen, int filDestino, int colDestino){
    int x = 162 + (colDestino*48);
    int y = 202 + (filDestino*48);
    GtkWidget *fichaImagen = matrizImagenes[filOrigen][colOrigen];/*agarramos el puntero de imagen a esa zona*/
    gtk_fixed_put (contenedor,fichaImagen,x,y);/*lo ponemos en el contenedor en la posicion*/
    matrizImagenes[filOrigen][colOrigen] = 0;/*ahora en esa zona de memoria no hay "nada"*/
    tablero[filOrigen][colOrigen] = 0;/*ahora en esa zona de memoria no hay "nada"*/
}


/*solo para debug*/
void print_array(int a[6][6]) {
   int i, j;
   /* print each row of the array */
   for (i = 0; i < 6; i++) {
      for (j = 0; j < 6; j++)
         printf("%6i ", a[i][j]);
          /* must add newline at end */
      printf("\n");
   }
   printf("\n");
}



