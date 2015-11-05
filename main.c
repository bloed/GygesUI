#include <stdlib.h>
#include <SWI-Prolog.h>
#include <gtk/gtk.h>
/*
%Instituto Tecnológico Costa Rica
%Escuela de Computación - Carrera Ingienría de computacion
%Lenguajes de programacion
%Grupo 01
%Tarea corta  C
%Estudiante: Josué Arrieta Salas
%Carne: 2014008153
%Profesor: Kirstein Gätjens Soto
%Fecha: 16/10/2015
%Funcion: Crear una interfaz para el juego gyges


Manual de USO: Seguir las reglas de que están en : Manual para compilar.pdf
Una vez compilado el programa:
Todas las inttrucciones serán por la consola:
0 salir
1 para jugar IA (es automático)
2 para jugar persona. Si es en fase de poner fichas se utiliza el siguiente formato:
A) posicionCasilla_Tipo de de ficha. EJ:a0_3 donde en la casilla a3 se pondrá una ficha de 3
Si es en la fase ya de juego sería:
B) casillaOrigen_casillaDestino. Ej a0_b0. Esto sería mover lo que este en la casilla a0 a la b0.
Si se quiere ganar sería a0_w0

NOTA: hay validacion de formato y de movimientos




%ANALISIS DE RESULTADOS (A):
%_______________________________________________________________________________________________
%                    FUNCIONALIDAD                                     |  CRITERO DE ÉXITO     |
%______________________________________________________________________|_______________________|
%-Movimientos válidos por todo el tablero                              | A completado con éxito|
%-Puede jugar tanto IA como persona                                    | A completado con éxito|
%-Se realiza una hermosa interfaz                                      | A completado con éxito|
%-Se puede indicar quien comienza                                      | A completado con éxito|
%-Se simula una partida de Gyges sin problema                          | A completado con éxito|
%-Se crea y se escribe en la bitacor___________________________________| A completado con éxito|



*/

/*PROTOTIPOS*/
int mapeo (char);
int verificaEntrada(int, int, int);
int verificaEntrada2(int, int, int, int);
char* intToF(int);
char mapeoAlReves (int);


GtkWidget *mainWindow;/*creamos la pantalla global*/
GtkWidget *labelJugador;/*será el label que contiene el jugador actual*/
GtkWidget *contenedor; /*contenedor de imagenes*/
char tableroAdrian[6][6][3];/*es de 3 dimensiones, las 2 normales, + el string*/

char* actual;
char* newMove;
char actualU[3];
char newMoveU[3];
char message[35];

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
    PL_initialise(argc, argv);
    jugadaAi();
    escribeBitacora("------Nuevo Juego------");
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
    imprimeTableroAdrian();
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

void jugadaAi(int jugador){
    toArrayAdrian(tablero);
    predicate_t p_consult = PL_predicate("gyges", 4, "user");
    term_t t = PL_new_term_refs(4);
    term_t h = PL_new_term_ref();
    PL_put_nil(t);
    int i, j;
    for(i=5; i>=0; --i){
        for(j=5;j>=0;--j){
            PL_put_atom_chars(h,tableroAdrian[i][j]);
            PL_cons_list(t,h,t);
        }
    }
    PL_put_variable(t+1);
    PL_put_variable(t+2);
    PL_put_integer(t+3,jugador);

    qid_t query = PL_open_query(NULL, PL_Q_NORMAL, p_consult, t);
    int result = PL_next_solution(query);
    if(result){
        PL_get_atom_chars(t+1, &actual);
        PL_get_atom_chars(t+2, &newMove);
        printf("Casilla actual %s.\n", actual);
        printf("Nueva casilla %s.\n", newMove);
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "Se movio de la casilla %s, a la casilla %s", actual, newMove);
        char* p = &buffer[0];
        muestraMensaje(mainWindow,p);/*mandamos un puntero al comienzo del array*/
    }
    PL_close_query(query);
}

void juegoPrincipal(int jugadorActual){
    int control = 0;
    char desicion[20],movimiento[20];
    int contador = 0;

    int columna;
    int fila;
    int pieza;
    int fila2;
    int columna2;
    int ficha_init = 1;

    while (control == 0) {
        while ( gtk_events_pending() ) gtk_main_iteration();
        printf("\nSelecciona una opción: \n 0. Salir \n 1. Juega IA \n 2. Juega Persona\n");
        scanf("%s", &desicion);
        if(strcmp(desicion,"0") ==0){
            printf("Nos vemos!");
            scanf("%s", &movimiento);
            control = 1;
        }
        else if(strcmp(desicion,"1") ==0){/*juega IA*/
            if(contador <12){/*estamos en etapas iniciales*/
                int val=0;
                while(val==0){
                    int r =rand_lim(5);
                    if(jugadorActual == 0 && tablero[5][r]==0){
                        tablero[5][r] = ficha_init;
                        val = 1;
                        strcpy(message,"Se puso la ficha inicial en: ");
                        message[28] = 'f';
                        message[29] = r+ 48;
                        message[30] = 0;
                        muestraMensaje(mainWindow,message);
                        putImagen(5,r,ficha_init);
                    }
                    if(jugadorActual == 1 && tablero[0][r]==0){
                        tablero[0][r] = ficha_init;
                        val = 1;
                        strcpy(message,"Se puso la ficha inicial en: ");
                        message[28] = 'a';
                        message[29] = r+ 48;
                        message[30] = 0;
                        muestraMensaje(mainWindow,message);
                        putImagen(0,r,ficha_init);
                    }
                }

                ficha_init++;
                if(ficha_init == 4){
                    ficha_init = 1;
                }

                contador++;
                siguienteTurno();
                if(jugadorActual ==0)
                    jugadorActual =1;
                else{
                    jugadorActual =0;
                }
            }
            else{
                /*tiene que hacer ya movimientos tuanis*/

                jugadaAi(jugadorActual);
                fila = mapeo(actual[0]);
                columna = (int)actual[1] - '0';
                fila2 = mapeo (newMove[0]);
                columna2 = (int)newMove[1] - '0';

                if(newMove[0]=='w'){
                     strcpy(message,"La AI ha ganado! Con la ficha: ");
                     message[31] = actual[0];
                     message[32] = actual[1];
                     message[33] = 0;
                     muestraMensaje(mainWindow,message);
                }else{
                    moveImagen(fila, columna, fila2, columna2);
                    siguienteTurno();
                    if(jugadorActual ==0)
                        jugadorActual =1;
                    else{
                        jugadorActual =0;
                    }
                }
            }
        }
        else if(strcmp(desicion,"2") ==0){/*juega Humano*/
            /*ahora hay que ver si es un moviiento valido, si si se meuve, si no no pasa nada*/
            /*muestraMensaje(mainWindow,"Movimiento ilegal. Juegue bien!");*/
            if(contador <12){/*estamos en etapas iniciales*/
                /*se pone pieza en tablero,basado en lo que el usuario escribio*/
                printf("Que ficha y dónde la quiere poner: (Ejemplo: a1_2   en la posición a1 poner una pieza de 2).\n");
                scanf("%s", &movimiento);
                pieza = (int)movimiento[3]- '0';
                columna = (int)movimiento[1] - '0';
                fila = mapeo (movimiento[0]);
                if (verificaEntrada(fila, columna, pieza) == 1 && init_valido(fila,columna,pieza,jugadorActual) == 1){/*Verificamos formato*/
                    putImagen(fila,columna,pieza);/*ponemos imagen*/
                    contador++;
                    siguienteTurno();/*siguiente del jugador*/
                    if(jugadorActual ==0)
                        jugadorActual =1;
                    else{
                        jugadorActual =0;
                    }
                }
                else{
                    muestraMensaje(mainWindow,"Entrada de datos incorrecta. Siga el ejemplo: a1_2.");
                }
            }
            else{
                printf("Qué ficha y a donde la quiere mover:(Ejemplo: a0_f3   esto es mover la pieza en la casilla a0 a f3, para ganar ponga como ultima ficha w0). \n");
                scanf("%s", &movimiento);
                /*tiene que hacer ya movimientos tuanis, basado en lo que el usuario escribio*/
                fila = mapeo(movimiento[0]);
                columna = (int)movimiento[1] - '0';
                fila2 = mapeo (movimiento[3]);
                columna2 = (int)movimiento[4] - '0';
                actualU[0] = movimiento[0];
                actualU[1] = movimiento[1];
                actualU[2] =  0;
                newMoveU[0] = movimiento[3];
                newMoveU[1] = movimiento[4];
                newMoveU[2] = 0;

                if (movimiento[3] =='w'){
                    if(validarMov(jugadorActual)){
                        muestraMensaje(mainWindow,"El usuario acaba de declarar que ha ganado! Felicidades!");
                    }else{
                        printf("El movimiento que realizo no se considera valido. Digite 1 para aceptar el movimiento o 2 para cancelarlo. \n");
                        scanf("%s", &desicion);
                        if(strcmp(desicion,"1") == 0){
                            muestraMensaje(mainWindow,"El usuario acaba de declarar que ha ganado! Felicidades!");
                        }
                    }
                }
                else{
                    if(verificaEntrada2(fila, columna, fila2, columna2)==1){/*verificamos formato*/
                        if(validarMov(jugadorActual)){
                            moveImagen(fila, columna, fila2, columna2);/*movemos ficha*/
                            siguienteTurno();/*turno del siguiente jugador*/
                            if(jugadorActual ==0)
                                jugadorActual =1;
                            else{
                                jugadorActual =0;
                            }
                        }else{
                            printf("El movimiento que realizo no se considera valido. Digite 1 para aceptar el movimiento o 2 para cancelarlo. \n");
                            scanf("%s", &desicion);
                            if(strcmp(desicion,"1") == 0){
                                moveImagen(fila, columna, fila2, columna2);/*movemos ficha*/
                                siguienteTurno();/*turno del siguiente jugador*/
                                if(jugadorActual ==0)
                                    jugadorActual =1;
                                else{
                                    jugadorActual =0;
                                }
                            }
                        }
                    }
                    else{
                    muestraMensaje(mainWindow,"Entrada de datos incorrecta. Siga el ejemplo: a0_f3.");
                    }
                }
            }
        }
        else
        {
            muestraMensaje(mainWindow,"Opcion incorrecta. Solo existen 3 opciones: 0 ,1 y 2.");
        }
    }
}

int rand_lim(int limit) {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do {
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

int init_valido(int fil, int col, int ficha, int turno){
    if(turno == 1 && fil ==0 && tablero[fil][col]==0){
        int i;
        int counter = 0;
        for(i=0;i<6;i++){
            if(tablero[0][i] == ficha){
                counter++;
            }
        }
        if(counter > 1){
            return 0;
        }else{
            return 1;
        }
    }
    if(turno == 0 && fil ==5 && tablero[fil][col]==0){
        int i;
        int counter = 0;
        for(i=0;i<6;i++){
            if(tablero[5][i] == ficha){
                counter++;
            }
        }
        if(counter > 1){
            return 0;
        }else{
            return 1;
        }
    }
    return 0;
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
    gtk_fixed_put (contenedor,fichaImagen,x,y);/*lo ponemos en el contenedor en la posicion.*/
    gtk_widget_show (contenedor);/*mostramos el contenedor con todos los widgets*/
    gtk_widget_show_all (mainWindow);
    matrizImagenes[fil][col] = fichaImagen;/*ponemos el puntero de la imagen en su determinada posicion*/
    tablero[fil][col] = ficha;/*actualizamos tambien la matriz lógica*/
    escribeBitacora1(fil, col, ficha, gtk_label_get_text (labelJugador));
}

/*mueve una imagen en el tablero, dada una coordenada a otra*/
moveImagen(int filOrigen, int colOrigen, int filDestino, int colDestino){
    int x = 162 + (colDestino*48);
    int y = 202 + (filDestino*48);
    GtkWidget *fichaImagen = matrizImagenes[filOrigen][colOrigen];/*agarramos el puntero de imagen a esa zona*/


    int pieza = tablero[filOrigen][colOrigen];/*guardamos la pieza para no perderla para escribir la bitacora*/

    char fichac[15];
    sprintf(fichac, "%d.png", pieza);
    GtkWidget *nuevaImagen = gtk_image_new ();/*creamos la imagen en blanco*/
    gtk_image_set_from_file (nuevaImagen,fichac);/*la cargamos del filename*/
    gtk_image_clear(fichaImagen);

    gtk_fixed_put (contenedor,nuevaImagen,x,y);/*lo ponemos en el contenedor en la posicion.*/
    gtk_widget_show (contenedor);/*mostramos el contenedor con todos los widgets*/
    gtk_widget_show_all (mainWindow);

    matrizImagenes[filDestino][colDestino] = nuevaImagen;/*ponemos el puntero de la imagen en su determinada posicion*/
    matrizImagenes[filOrigen][colOrigen] = 0;/*ahora en esa zona de memoria no hay "nada"*/
    tablero[filOrigen][colOrigen] = 0;/*ahora en esa zona de memoria no hay "nada"*/
    tablero[filDestino][colDestino] = pieza;
    escribeBitacora2(filOrigen, colOrigen, filDestino , colDestino, pieza, gtk_label_get_text (labelJugador));
}


/*escribe en la bitacora un string x*/
void escribeBitacora(char* string){
    FILE *archivo = fopen("Bitacora.txt", "a");
    if (archivo == NULL)
    {
        printf("Error opening file!\n");
    }
    else{
       fprintf(archivo, "%s\n", string);
       fclose(archivo);
    }
}

/*escribe en la bitacora, si se puso una pieza*/
void escribeBitacora1(int fil, int col, int pieza, char* jugador){
    FILE *archivo = fopen("Bitacora.txt", "a");
    char filac = mapeoAlReves(fil);
    if (archivo == NULL)
    {
        printf("Error!\n");
    }
    else{
       fprintf(archivo, "%s puso una pieza en la casilla %c%d, la pieza era de tipo %d.\n", jugador,filac,col,pieza);
       fclose(archivo);
    }
}

void escribeBitacora2(int fil, int col,int fil1,int col2, int pieza, char* jugador){
    FILE *archivo = fopen("Bitacora.txt", "a");
    char fil1c = mapeoAlReves(fil1);
    char filc = mapeoAlReves(fil);
    if (archivo == NULL)
    {
        printf("Error!\n");
    }
    else{
       fprintf(archivo, "%s movio una ficha en la casilla %c%d una pieza de tipo %d, a la casilla %c%d.\n", jugador,filc,col,pieza,fil1c,col2);
       fclose(archivo);
    }
}

int validarMov(int jugador){
    toArrayAdrian(tablero);
    predicate_t p_consult = PL_predicate("gygesVerify", 5, "user");
    term_t t = PL_new_term_refs(5);
    term_t h = PL_new_term_ref();
    PL_put_nil(t);
    int i, j;
    for(i=5; i>=0; --i){
        for(j=5;j>=0;--j){
            PL_put_atom_chars(h,tableroAdrian[i][j]);
            PL_cons_list(t,h,t);
        }
    }
    PL_put_atom_chars(t+1, actualU);
    PL_put_atom_chars(t+2, newMoveU);
    PL_put_integer(t+3,jugador);
    PL_put_variable(t+4);

    qid_t query = PL_open_query(NULL, PL_Q_NORMAL, p_consult, t);
    int result = PL_next_solution(query);
    int boolean = 0;
    if(result){
        PL_get_integer(t+4, &boolean);

    }
    PL_close_query(query);
    return boolean;
}

/*recibe una letra y le haremos un mapeo*/
int mapeo (char letra)
{
    if(letra == 'a'){
        return 0;
    }
    else if(letra == 'b'){
        return 1;
    }
    else if(letra == 'c'){
        return 2;
    }
    else if(letra == 'd'){
        return 3;
    }
    else if(letra == 'e'){
        return 4;
    }
    else if(letra == 'f'){
        return 5;
    }
    /*invalido*/
    return 6;
}

/*recibe una entero  le haremos mapeo*/
char mapeoAlReves (int letra)
{
    if(letra == 0){
        return 'a';
    }
    else if(letra == 1){
        return 'b';
    }
    else if(letra == 2){
        return 'c';
    }
    else if(letra == 3){
        return 'd';
    }
    else if(letra == 4){
        return 'e';
    }
    else if(letra == 5){
        return 'f';
    }
    /*invalido*/
    return 'z';
}

/*Verifica que una entrada sea valida*/
int verificaEntrada(int fil, int col, int pieza){
    /*hay que verificar que etanto fila, columna son numeros entre 5 y 0, y la pieza entre 1 y 3*/
    if((fil>=0 && fil<=5)&&(col>=0 && col<=5)&&(pieza>=1 && pieza<=3)){
        return 1;/*movimiento valido*/
    }
    else{
        return 2;
    }
}

int verificaEntrada2(int fil, int col, int fil2, int col2){
    /*hay que verificar que etanto filas, columnas son numeros entre 5 y 0,*/

    if((fil>=0 && fil<=5)&&(col>=0 && col<=5)&&(fil2>=0 && fil2<=5)&&(col2>=0 && col2<=5)){
        return 1;/*movimiento valido*/
    }
    else{
        return 2;
    }
}

/*Psamos un entero 2 a la forma "f2"*/
char* intToF(int entero){
    char resultado[3];
    sprintf(resultado, "f%d", entero);
    printf("%s", resultado);
    return resultado;
}

/*pasamos un tablero de arreglos de enteros, a uno especializado*/
void toArrayAdrian(int tablero[6][6]){
   int i, j;
   int k = 0;
   char stringTemporal[3];
   for (i = 0; i < 6; i++) {
       for (j = 0; j < 6; j++){
           sprintf(stringTemporal, "f%d", tablero[i][j]);/*agarramos el entero, y le metemos un f adelante de este*/
           tableroAdrian[i][j][0] = stringTemporal[0];
           tableroAdrian[i][j][1] = stringTemporal[1];
           tableroAdrian[i][j][2] = stringTemporal[2];
       }
   }
}

/*proposito de debug, imprime el tablero especializado f0,f1,.. en pantalla*/
void imprimeTableroAdrian(){
    toArrayAdrian(tablero);
    int i,j;
    for (i = 0; i < 6; i++) {
       for (j = 0; j < 6; j++){
           printf("%s ",tableroAdrian[i][j]);
       }
       printf("\n");
   }
   printf("\n");
}

