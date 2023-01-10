#ifndef __MAIN__H__
#define __MAIN__H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
void imprimir(char c)
{
    if (isprint(c))
        printf("%c", c);
    else if (c == '\n')
        printf("(\\n)");
    else
        printf("(%d)", c);
    if (c == '\n')
        printf("\n");
}

// Funciones Principales de los tableros:

// constante tamaño del tableroo
#define TAM_TABLERO 8
// definimos el tipo de dato booleano
typedef enum
{
    FALSE, // 0
    TRUE   // 1
} Bool;

// diferentes contenidos de una celda (colores blanco y negro, vacio)
typedef enum
{
    VACIO,  // 0
    BLANCO, // 1
    NEGRO   // 2
} Colour;

// toma una tablero y lo lleva al estado inicial del juego
void transformToTableroInicial(Colour tablero[TAM_TABLERO][TAM_TABLERO])
{

    for (int i = 0; i < TAM_TABLERO; i++)
        for (int j = 0; j < TAM_TABLERO; j++)
            tablero[i][j] = VACIO;
    tablero[3][3] = tablero[4][4] = BLANCO;
    tablero[3][4] = tablero[4][3] = NEGRO;
}

// toma un tabelro, un archivo y guarda el tablero dentro del archivo
void ImprimirTableroInFile(Colour tablero[TAM_TABLERO][TAM_TABLERO], FILE *file)
{
    char celda[] = {'X', 'B', 'N'};
    for (int i = 0; i < TAM_TABLERO; i++)
    {
        for (int j = 0; j < TAM_TABLERO; j++)
        {
            fprintf(file, "%c", celda[tablero[j][i]]);
        }
        fprintf(file, "\n");
    }
}
// toma un tablero y determina si existe algun ganador devolviendo un bool(datatype creado)
Bool hayGanador(Colour tablero[TAM_TABLERO][TAM_TABLERO])
{
    int contadoBlanco = 0, contadornegro = 0;
    for (int i = 0; i < TAM_TABLERO; i++)
        for (int j = 0; j < TAM_TABLERO; j++)
            if (tablero[i][j] == BLANCO)
                contadoBlanco += 1;
            else if (tablero[i][j] == NEGRO)
                contadornegro += 1;
    if (contadoBlanco < contadornegro || contadornegro < contadoBlanco)
        return TRUE;
    else
        return FALSE;
}

// toma un tablero y devuelve quien tiene mas celdas dominadas en el juego actual
Colour devolverGanador(Colour tablero[TAM_TABLERO][TAM_TABLERO])
{
    int contadoBlanco = 0, contadornegro = 0;
    for (int i = 0; i < TAM_TABLERO; i++)
        for (int j = 0; j < TAM_TABLERO; j++)
            if (tablero[i][j] == BLANCO)
                contadoBlanco += 1;
            else if (tablero[i][j] == NEGRO)
                contadornegro += 1;
    if (contadoBlanco < contadornegro || contadornegro < contadoBlanco)
        if (contadoBlanco < contadornegro)
            return NEGRO;
        else
            return BLANCO;
    else
        return VACIO;
}

// toma un color y lo cambia al opuesto (si es blanco -> negro, negro -> blanco y vacio->vacio)
Colour cambiarColor(Colour x)
{
    if (x == BLANCO)
        return NEGRO;
    else if (x == NEGRO)
        return BLANCO;
    return VACIO;
}

// tomando dos tableros copia el segundo en el primero
void cpTablero(Colour tablero1[TAM_TABLERO][TAM_TABLERO], Colour tablero2[TAM_TABLERO][TAM_TABLERO])
{
    for (int i = 0; i < TAM_TABLERO; i++)
        for (int j = 0; j < TAM_TABLERO; j++)
            tablero1[i][j] = tablero2[i][j];
}

// Estructura que representa una celda del tablero como una tupla de enteros;
typedef struct
{
    int fila;
    int columna;
} Celda;

// toma una celda y determina si esta dentro de los limites del tablero;
Bool posvalida(Celda a)
{
    if (0 <= a.fila && a.fila < TAM_TABLERO && 0 <= a.columna && a.columna < TAM_TABLERO)
        return TRUE;
    return FALSE;
}

// toma dos celdas y se comprueba si son iguales(devuelve 1) o si no(devuelve 0);
Bool sonCeldasIguales(Celda a, Celda b)
{
    if (a.fila == b.fila && a.columna == b.columna)
        return TRUE;
    return FALSE;
}

// Estructura q representa una lista de celdas, contiene 3 campos;
typedef struct
{
    Celda *celdas;
    int tamanio;
    int tamanio_maximo;
} ListadoDeCeldas;

// inicializa una lista de celdas en un estado vacio;
ListadoDeCeldas listaDeCeldasVacia()
{
    ListadoDeCeldas l;
    l.tamanio = 0;
    l.celdas = NULL;
    l.tamanio_maximo = 0;

    return l;
}

// toma dos enteros y crea una celda tomando el primero como columna y el segundo como fila;
Celda createCelda(int col, int fil)
{
    Celda c;
    c.columna = col;
    c.fila = fil;
    return c;
}
// toma un puntero a una lista y una celda, e inserta la celda al final de la lista;
void insertCeldaninList(ListadoDeCeldas *list, Celda celda)
{
    Celda *copyplus;
    if (list->tamanio_maximo == list->tamanio)
    {

        if (list->tamanio_maximo == 0)
        {
            copyplus = (Celda *)malloc(sizeof(Celda));
            list->tamanio_maximo += 1;
        }
        else
        {
            list->tamanio_maximo *= 2;
            copyplus = (Celda *)realloc(list->celdas, list->tamanio_maximo * sizeof(Celda));
        }

        if (copyplus == NULL)
        {

            if (list->celdas != NULL)
                free(list->celdas);
            exit(2);
        }
        list->celdas = copyplus;
    }
    //  perror("6\n");
    list->celdas[list->tamanio] = celda;
    list->tamanio += 1;
    //    perror("7");
}
// toma una lista de celdas, libera el espacio pedido para la lista e inicializa los demas campos;
void freeListadoDeCeldas(ListadoDeCeldas *list)
{
    free(list->celdas);
    list->celdas = NULL;
    list->tamanio = 0;
    list->tamanio_maximo = 0;
}

// toma un puntero a lista de celdas, una celda y apunta a la direccion  en la que se encuentra la celda a buscar;
Celda *apuntarCelda(ListadoDeCeldas *list, Celda celda)
{
    int pos;
    for (pos = 0; !((sonCeldasIguales(list->celdas[pos], celda)) == TRUE) && pos < list->tamanio; pos++)
        ;

    if (pos >= list->tamanio)  // si el bucle se detuvo antes del final del listado
        return NULL;           // si llego al final retorno NULL  puesto q no se encontro la celda a apuntar
    return list->celdas + pos; // si no, ajusto y devuelvo la direccino de memoria corrida pos posiciones (aritmetica de punteros)
}

// toma una puntero a lista de celdas, una celda y la elimina de la lista;
void deletearCeldaFromList(ListadoDeCeldas *list, Celda celda)
{
    if (list->tamanio != 1)
    {
        Celda *ptr = apuntarCelda(list, celda);
        if (ptr != NULL)
        {
            for (int pos = ptr - list->celdas; pos < list->tamanio - 1; pos++)
                list->celdas[pos] = list->celdas[pos + 1];
            list->tamanio -= 1;
        }
    }
    else
    {
        freeListadoDeCeldas(list);
    }
}

// Estructura que contine la informacion necesaria para iniciar el juego, posee los nombres de los jugadores
//  la lista de movidas de fichas y quien comienza jugando;
typedef struct
{
    char players[2][100]; // deberia poner la constante no? #def TAM_NAME_PLAYER 100
    Colour whoStart;
    ListadoDeCeldas movidas;
} DataForStartGame;

// toma una archivo y lo recorre hasta llegar al final de una linea o bien terminar de recorrerlo;

Bool esFinDeLinea(char c)
{
    return c == EOF || c == '\n';
}

void terminarLinea(FILE *file)
{
    while(!esFinDeLinea(fgetc(file)))

    ;
}

// toma un archivo abierto y el nombre del jugador, guarda el nombre escrito en el archivo en el nombre del jugador
Colour extractNamePlayer(FILE *file, char *name)
{
    Colour color_jugador = VACIO; // el id del jugador lo inicializas en vacio
    Bool flag = FALSE;            // esta bandera se usa para verificar q el nombre del jugador no exceda el limite (puesto en 99);

    int largo_del_nombre = 0;
    for (char c = '\0'; !esFinDeLinea(c);)
    {
        c = fgetc(file);
      //  imprimir(c);
        if (c == ',')
        {
            c = fgetc(file);
           // imprimir(c);
            // printf("El color actual es %c\n",c);
            if (c == 'N')
            {
                //    printf("el color es igual :)\n");
                color_jugador = NEGRO;
            }
            else if (c == 'B')
                color_jugador = BLANCO; // vease que si no entra en ninguno de esto condicionales, el color queda en vacio;

            // printf("el color actual es: %d\n", color_jugador);

            if (color_jugador != VACIO)
            {
                c = fgetc(file);
              //  imprimir(c);
                if(c == 13){
                    c = fgetc(file);
                }
                // printf("entrooo\n");
                if (!esFinDeLinea(c))
                {
                    color_jugador = VACIO;
                    terminarLinea(file);
                }
            }
            c = '\n';
        }
        else
        {
            if (!flag)
            {
                if (largo_del_nombre < 99)
                    name[largo_del_nombre++] = c;
                else
                {
                    name[largo_del_nombre] = '\0';
                    printf("%s", name);
                    flag = TRUE;
                    putchar(c);
                }
            }
            else
            {
                putchar(c);
            }
        }
    }

    name[largo_del_nombre] = '\0';
    if (flag)
        printf("El nombre recibido del arvhivos excede el limite de caracteres, el nombre sera %s\n", name);

    return color_jugador; // el color recibido se utiliza para guardar el nombre de cada jugador
                          // diferenciandolos por colores (Blanco == 1 y Negro == 2);
                          /* char c;
                           Colour color;
                           int largo_del_nombre=0;
                           for(c='\0';!(c==EOF || c == '\n');){
                               c=fgetc(file);
                               if(c==','){
                                   c = fgetc(file);
                                   if(c=='B')
                                       color = BLANCO;
                                   else if(c=='N')
                                       color = NEGRO;
                                   else
                                       color = VACIO;
                                   c=fgetc(file);
                               }
                               else{
                                   name[largo_del_nombre]=c;
                                   largo_del_nombre+=1;
                               }
                      
                           }
                           return color;*/
}

// toma dos punteros a entero y cambia el valor hallado en el lugar de memoria
// para ser representados como coordenadas
void toocords(int *c, int *f)
{
    *c -= 'A';
    *f -= 1;
}

void totable(int *c, int *f)
{
    *c += 'A';
    *f += 1;
}

int getInfo(char *file, DataForStartGame *info)
{

    Bool flag = FALSE;
    FILE *arch = fopen(file, "r");
    if (arch == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", file);
        return -1;
    }
    char name[100];
    for (int i = 0; i < 2; i++)
    {
        Colour color_jugador;
        color_jugador = extractNamePlayer(arch, name);

        if (color_jugador == VACIO)
        {
            printf("No se ingreso un color valido para %s\n", name);
            for (int k = 0; k < 2; k++)
                info->players[k][0] = '\0';
            flag = TRUE;
        }
        else
        {
            strcpy(info->players[color_jugador - 1], name);
        }
    }

    char col = fgetc(arch);
   // imprimir(col);
    switch (col)
    {
    case 'N':
        info->whoStart = NEGRO;
        //printf("el color inicial es blanco :)");
        break;
    case 'B':
        info->whoStart = BLANCO;
        break;
    default:
        info->whoStart = VACIO;
    }
    if(info->whoStart == VACIO){
        printf("El color de jugador inicial no es valido \n");
        flag = TRUE;
    }
    char c = fgetc(arch);
    if(c == 13)
        c = fgetc(arch);
    if (!esFinDeLinea(c))
    {
        printf("\nel valor del caracter es:");
        //imprimir(c);
        printf("El color no es unica letra, color inicial invalido\n");
        terminarLinea(arch);
        flag = TRUE;
    }
    
    info->movidas = listaDeCeldasVacia();
    Celda jugada = createCelda(0, 0);
    //printf("\n");
    while ((jugada.columna = fgetc(arch)) != EOF)
    {
        if(jugada.columna == 13){
            jugada.columna = fgetc(arch);
            }
       // imprimir(jugada.columna);
       // printf(" Jugada leida :)");
        //printf("\n");
        if (jugada.columna == '\n'){
            jugada = createCelda(-1, -1); // id salto de linea;
         //   printf("SALTO DE LINEA \n");
            //printf("La columna es %d y la fila es %d",jugada.columna, jugada.fila);
            }
        else
        {
            if ('A'<=jugada.columna && jugada.columna <= 'H'){
                jugada.fila = fgetc(arch);
                jugada.fila -= '1';
                jugada.columna -= 'A';
            }
            else   printf("ALGUNA CELDA ESTA MAL LEIDA :");
            //if(jugada.columna == 'F')
                //printf("la columna es efe \n");

              //  jugada.fila -= '1';
                //printf("la columna es %d\n",jugada.fila);jauga
            //printf("entro en el else \n");
            //jugada.fila = fgetc(arch);
            //jugada.fila -= 1;
            //printf("la fila tomada es %c",jugada.fila);
            //printf("la fila leida es: %d\n",jugada.fila);
            //printf("la columna es: %d\n",jugada.columna);

            //printf("la columna es: %c\n",jugada.columna);
            //printf("la fila es: %d\n",jugada.fila);

            char s = fgetc(arch);
            if(s == 13)
                s = fgetc(arch);
            else if(s==-1)
                s = fgetc(arch);
            else {
                if(!esFinDeLinea(s))
                    terminarLinea(arch);
                
                //printf("la fila leida es: %d\n",jugada.fila);
                if(esFinDeLinea(jugada.fila))
                    printf("la fila es final de linea \n");
                //printf("la columna es: %d\n",jugada.columna);
                //printf("la linea otra es:%c\n",s);
                //printf("la linea es: %d\n",s);
                //if(esFinDeLinea(s))
                  //  printf("llego al final de la linea; \n");
                if(!esFinDeLinea(s) || !posvalida(jugada)){
                    if(!esFinDeLinea(s))
                        printf("la jugada no es valida niopsho\n");
                    jugada = createCelda(-10,-10);
                }
            }
           // printf("la columna es: %c\n",jugada.columna);
            //printf("la fila es: %d\n",jugada.fila);
        }
       // printf("la columna es: %c\n",jugada.columna);
       // printf("la fila es: %d\n",jugada.fila);
    //printf("La columna es %d y la fila es %d\n",jugada.columna, jugada.fila);
        insertCeldaninList(&(info->movidas), jugada);
    }
    fclose(arch);
    if (flag)
        return 1;
    else
        return 0;
}

// SOLO PARA EL JUEGO:
// Direcciones:
/*
(1,0) derecha
(-1,0) izquierda
(0,1) arriba
(0,-1) abajo
(1,1) arriba derecha
(1,-1) abajo derecha
(-1,1) arriba izquierda
(-1,-1) abajo izquierda

typedef struct
{
    int x[] = {1,-1,0,0,1,1,-1,-1};
    int y[] = {0,0,1,-1,1,-1,1,-1};
}Direcciones;
*/
Bool isCeldaInList(ListadoDeCeldas list, Celda celda)
{
    Bool flag = FALSE;
    for (int i = 0; i < list.tamanio && !flag; i++)
    {
        if (sonCeldasIguales(list.celdas[i], celda))
            flag = TRUE;
    }
    return flag;
}

void actualizarPosicionesJugables(Colour tablero[TAM_TABLERO][TAM_TABLERO], Celda jugada, ListadoDeCeldas *posibles_celdas_a_jugar)
{
    // Direcciones dir; -> xq no funciona?
    int x[] = {1, -1, 0, 0, 1, 1, -1, -1};
    int y[] = {0, 0, 1, -1, 1, -1, 1, -1};

    // Lo primero es borrar la celda que se jugó de la lista de posibles_celdasa_jugar
    Celda *ptr = apuntarCelda(posibles_celdas_a_jugar, jugada);
    if (ptr != NULL)
    {                                                         // si la lista de posibles jugadas no esta vacia, borro la celda ya ocupada x jugada
        deletearCeldaFromList(posibles_celdas_a_jugar, *ptr); // saco *ptr de la lista donde ptr apunta a la celda ya jugada
        for (int i = 0; i < 8; i++)
        {
            Celda temp;
            int varX = jugada.columna + x[i];
            int varY = jugada.fila + y[i];
            temp.columna = varX;
            temp.fila = varY;
            if (tablero[temp.columna][temp.fila] == VACIO && !isCeldaInList(*posibles_celdas_a_jugar, temp) && posvalida(temp))
                insertCeldaninList(posibles_celdas_a_jugar, temp);
        }
    }
}
Bool direccion_cumple_regla1(Colour tablero[TAM_TABLERO][TAM_TABLERO], Celda origen, Colour jugador_actual, int x, int y)
{
    origen.fila += y;
    origen.columna += x;
    return (tablero[origen.columna][origen.fila] == cambiarColor(jugador_actual) && posvalida(origen));
}
void printListadeCeldas(ListadoDeCeldas lista)
{
    if (lista.tamanio == 0)
    {
        printf("La lista esta vacia \n");
        return;
    }
    else
        for (int i = 0; i < lista.tamanio; i++)
        {
            printf("La %d° celda es: ", i);
            printf("%d %d \n", lista.celdas[i].columna, lista.celdas[i].fila);
        }
}

void printCelda(Colour tablero[TAM_TABLERO][TAM_TABLERO], Celda posisom)
{
    if (tablero[posisom.columna][posisom.fila] == NEGRO)
        printf("La celda es negra\n");
    else if (tablero[posisom.columna][posisom.fila] == BLANCO)
        printf("la celda es blanca\n");
    else
        printf("celda vacia\n");
}

ListadoDeCeldas listar_Celdas_en_direccion(Colour tablero[TAM_TABLERO][TAM_TABLERO], Celda origen, Colour jugador_actual, const int x, const int y)
{
    // perror("4");
    ListadoDeCeldas list = listaDeCeldasVacia();
    Celda celda = origen;
    celda.columna += x;
    // printf("la column es: %d\n",celda.columna);
    celda.fila += y;
    // printf("la fila es: %d\n",celda.fila);
    for (; tablero[celda.columna][celda.fila] == cambiarColor(jugador_actual) && posvalida(celda); celda.columna += x, celda.fila += y)
    {
        //  printf("la column es: %d\n",celda.columna);
        // printf("la fila es: %d\n",celda.fila);
        insertCeldaninList(&list, celda);
    }
    // for(int i = 0; i < list.tamanio; i++)
    //   printCelda(tablero,list.celdas[i]);
    // perror("2");
    // Veamos porque se corto el bucle:
    // printCelda(tablero,celda);
    // printf("la column es: %d\n",celda.columna);
    // printf("la fila es: %d\n",celda.fila);
    /*f(!posvalida(celda))
        printf("aca no esta el error\n");
    if(tablero[celda.columna][celda.fila] != jugador_actual)
        printf("el error tampoco aca\n");
*/
    if (!posvalida(celda) || tablero[celda.columna][celda.fila] != jugador_actual)
        freeListadoDeCeldas(&list);

    // printListadeCeldas(list);
    return list;
}
int jugadaValida(Colour tablero[TAM_TABLERO][TAM_TABLERO], Celda juagada, Colour jugador_actual)
{
    // Direcciones dir; -> xq no funciona??
    int x[] = {1, -1, 0, 0, 1, 1, -1, -1}; // -> xq no funciona?
    int y[] = {0, 0, 1, -1, 1, -1, 1, -1};
    Bool flag = FALSE;
    int contador_de_fichas_cambiadas_de_color = 0;
    // printf("la celda es: %c %d\n",juagada.columna+'A',juagada.fila+1);
    for (int i = 0; i < TAM_TABLERO; i++)
    {
        if (direccion_cumple_regla1(tablero, juagada, jugador_actual, x[i], y[i]))
        {
            flag = TRUE;
            ListadoDeCeldas cambiar;
            cambiar = listar_Celdas_en_direccion(tablero, juagada, jugador_actual, x[i], y[i]);
            for (int k = 0; k < cambiar.tamanio; k++)
            {
                tablero[cambiar.celdas[k].columna][cambiar.celdas[k].fila] = jugador_actual;
                contador_de_fichas_cambiadas_de_color += 1;
            }
            freeListadoDeCeldas(&cambiar);
        }
    }
    if (contador_de_fichas_cambiadas_de_color > 0)
        tablero[juagada.columna][juagada.fila] = jugador_actual;
    if (flag)
    {
        return contador_de_fichas_cambiadas_de_color;
    }
    else
        return -10;
}

Bool existeJugadasValidas(Colour tablero[TAM_TABLERO][TAM_TABLERO], Colour jugador_actual, ListadoDeCeldas jugadas_posibles)
{
    Bool flag = FALSE;
    Colour temp_tablero[TAM_TABLERO][TAM_TABLERO];
    cpTablero(temp_tablero, tablero);

    for (int i = 0; i < jugadas_posibles.tamanio && !flag; i++)
    {
        if (posvalida(jugadas_posibles.celdas[i]))
        {
            int contador = jugadaValida(temp_tablero, jugadas_posibles.celdas[i], jugador_actual);
            if (contador > 0)
                flag = TRUE;
        }
    }
    return flag;
}
ListadoDeCeldas Posiciones_Posibles_Iniciales()
{ // se puede poner dentro de un bucle :)
    ListadoDeCeldas lista = listaDeCeldasVacia();
    Celda celda1;
    celda1.columna = 2;
    celda1.fila = 2;
    Celda celda2;
    celda2.columna = 3;
    celda2.fila = 2;
    Celda celda3;
    celda3.columna = 4;
    celda3.fila = 2;
    Celda celda4;
    celda4.columna = 5;
    celda4.fila = 2;
    Celda celda5;
    celda5.columna = 2;
    celda5.fila = 3;
    Celda celda6;
    celda6.columna = 2;
    celda6.fila = 4;
    Celda celda7;
    celda7.columna = 2;
    celda7.fila = 5;
    Celda celda8;
    celda8.columna = 3;
    celda8.fila = 5;
    Celda celda9;
    celda9.columna = 4;
    celda9.fila = 5;
    Celda celda10;
    celda10.columna = 5;
    celda10.fila = 5;
    Celda celda11;
    celda11.columna = 5;
    celda11.fila = 4;
    Celda celda12;
    celda12.columna = 5;
    celda12.fila = 4;
    // INSERTAR:
    insertCeldaninList(&lista, celda1);
    insertCeldaninList(&lista, celda2);
    insertCeldaninList(&lista, celda3);
    insertCeldaninList(&lista, celda4);
    insertCeldaninList(&lista, celda5);
    insertCeldaninList(&lista, celda6);
    insertCeldaninList(&lista, celda7);
    insertCeldaninList(&lista, celda8);
    insertCeldaninList(&lista, celda9);
    insertCeldaninList(&lista, celda10);
    insertCeldaninList(&lista, celda11);
    insertCeldaninList(&lista, celda12);

    return lista;
}

typedef enum
{
    JUEGO_COMPLETO,           // se realizaron todas las jugadas posibles y no se puede seguir colocando fichas correctamente
    JUEGO_CONTINUA,           // no ocurrio ningun imprevisto y el juego debe continuar
    CELDA_OCUPADA,            // un jugador puso una ficha en una celda ocupada
    CELDA_FUERA_DE_LIMITES,    // un jugador puso una ficha fuera de los limites establecidos
    JUGADA_INCORRECTA_REGLA1, // un jugador relizo una jugada q no cumple regla 1)
    JUGADA_INCORRECTA_REGLA2, // un jugador realizo una jugada q no produjo cambios en el tablero
    SALTO_INCORRECTO         // un jugador decidio saltar cuando tenia alguna jugada posible
} Situacion_del_juego;

typedef struct
{
    Colour WhoendGame;
    Colour tablero[TAM_TABLERO][TAM_TABLERO];
    Situacion_del_juego status;
} DataForEndGame;

void mostrarMensajeSituacion(char jugadores[2][100], DataForEndGame info_final)
{
    Colour player_a_mostrar = cambiarColor(info_final.WhoendGame);
    //Colour temp = cambiarColor(player_a_mostrar);
    
    switch(info_final.status){
        case 0:
            printf("EL JUEGO TERMINO ");
            if(hayGanador(info_final.tablero)){
                Colour winner = devolverGanador(info_final.tablero);
                printf("CON VICTORIA DE %s",jugadores[winner - 1]);
            }
            else printf("EN EMPATE");
            break;
        case 1:
            printf("EL JUEGO CONTINUA, LE TOCA JUGAR A %s",jugadores[player_a_mostrar-1]);
            break;
        case 2:
            printf("%s PUSO UNA FICHA EN UNA CASILLA OCUPADA", jugadores[info_final.WhoendGame -1]);
            break;
        case 3:
            printf("%s NO PUSO UNA FICHA EN UNA CASILLA VALIDA",jugadores[info_final.WhoendGame - 1]);
            break;
        case 4:
            printf("%s PUSO UNA FICHA EN UNA CASILLA QUE NO CUMPLE LA REGLA 1",jugadores[info_final.WhoendGame-1]);
            break;
        case 5:
            printf("%s PUSO UNA FICHA EN UNA CASILLA QUE NO CREA CAMBIOS EN EL TABLERO",jugadores[info_final.WhoendGame-1]);
            break;
        case 6:
            printf("%s SALTO SU TURNO CUANDO AUN TENIA JUGADAS POSIBLES",jugadores[info_final.WhoendGame-1]);
            break;
        case -1:
            printf("NO SE HAN INGRESADO JUGADAS");
            break;
        default:
            printf("ESTADO INVALIDO");
            break;
    }
    if(info_final.status != 1){
        printf("\nNO SE HA GENERADO EL ARCHIVO DEL TABLERO FINAL");
    }
    else printf("\nSE HA GENERADO EL TABLERO, A SEGUIR JUGANDO ");
}

int writeTableroinFile(char *file, DataForEndGame info)
{
    FILE *arch = fopen("salida.txt", "w");
    if (arch == NULL)
    {
        printf("no se pudo guardar el tablero de juego\n");
        return 1;
    }
   // printf("El color obtenido fue: %d\n",info.WhoendGame);
    ImprimirTableroInFile(info.tablero, arch);
    if (info.WhoendGame == BLANCO)
        fprintf(arch, "N");
    else
        fprintf(arch, "B");
    fclose(arch);
    return 0;
}

DataForEndGame SimularJuego(DataForStartGame info_inicial)
{
    Colour casilla_ocupada;
    Celda *jugadas = info_inicial.movidas.celdas;
    DataForEndGame info_final;
    transformToTableroInicial(info_final.tablero);
    // inicializamos la lista de posibles_jugadas
    ListadoDeCeldas jugadas_posibles = listaDeCeldasVacia();
    Bool flag = TRUE;

//volver aca;
    //printf("EL JUGADOR RECIBIDO FUE :%d",info_inicial.whoStart);

    for (int i = TAM_TABLERO / 2 - 2; i < TAM_TABLERO; i++)
        for (int j = TAM_TABLERO / 2 - 2; j < TAM_TABLERO; j++)
            if (info_final.tablero[i][j] == VACIO)
            {
                Celda celda;
                celda.columna = j;
                celda.fila = i;
                insertCeldaninList(&jugadas_posibles, celda);
            }

    info_final.status = JUEGO_CONTINUA;
    int i;
    Colour jugador_actual = info_inicial.whoStart;
    //printf("La cantidad de jugadas es %d\n",info_inicial.movidas.tamanio);
    //printf("El jugador que inicia jugando es %s\n",(info_inicial.whoStart == 1) ? "BLANCO" : "NEGRO");
    for (i = 0;  info_final.status == JUEGO_CONTINUA && i < info_inicial.movidas.tamanio; i++)
    {
       // printListadeCeldas(jugadas_posibles);
        //printf("\n");

        if (jugadas[i].columna == -1 && jugadas[i].fila == -1)
        {
          //  printf("se introdujo un salto de linea: ");
            if (existeJugadasValidas(info_final.tablero, jugador_actual, jugadas_posibles))
            {
               // printf("el estado no entro aca");
                info_final.status = SALTO_INCORRECTO;
            }
        }
        else if (!posvalida(jugadas[i]))
            info_final.status = CELDA_FUERA_DE_LIMITES;
        else if (info_final.tablero[jugadas[i].columna][jugadas[i].fila] != VACIO){
            casilla_ocupada = jugador_actual;
            printf("SE INGRESO MAL LA CELDA %c %d\n",jugadas[i].columna+'A',jugadas[i].fila+1);
            info_final.status = CELDA_OCUPADA;
            }
        else
        {
            int cambiar = jugadaValida(info_final.tablero, jugadas[i], jugador_actual);
            //printf("EL JUGADOR ACTUAL ES :%d\n",jugador_actual);
            switch (cambiar)
            {
            case -10:
                info_final.status = JUGADA_INCORRECTA_REGLA1;
                break;
            case 0:
                info_final.status = JUGADA_INCORRECTA_REGLA2;
                printf("%c%d\n", jugadas[i].columna + 'A', jugadas[i].fila + 1);
                break;
            default:
                actualizarPosicionesJugables(info_final.tablero, jugadas[i], &jugadas_posibles);
                break;
            }
           // printf("EL JUGADOR ACTUAL ES :%d\n",jugador_actual); // 2
        }
      //  printf("EL JUGADOR ACTUAL ES :%d\n",jugador_actual); // 2
       // printf("el iterador esta en %d\n",i);
        if((i+1) < info_inicial.movidas.tamanio && info_final.status == JUEGO_CONTINUA){
            jugador_actual = cambiarColor(jugador_actual);
          //  printf("esta mal");
        }
        //printf("El jugador que termino jugando es %s\n",(jugador_actual == 1) ? "BLANCO" : "NEGRO");

       // printf("EL JUGADOR ACTUAL ES :%d\n",jugador_actual); // 2
      
        
    }

    //printf("LAS JUGADAS QUE SE REALIARON FUERON %d",i);
    //printf("EL JUGADOR ACTUAL ES :%d\n",jugador_actual);
    if (info_final.status == JUEGO_CONTINUA)
        info_final.status = (existeJugadasValidas(info_final.tablero, jugador_actual, jugadas_posibles)) ? JUEGO_CONTINUA : JUEGO_COMPLETO;
    
    //printf("EL JUGADOR ACTUAL ES :%d\n",jugador_actual);
    
    if(info_inicial.movidas.tamanio == 0)
        info_final.status = -1;
   // printf("cantidad de jugadas %d",info_inicial.movidas.tamanio);
    
   // printf("El jugador a guardar es: %s\n",(jugador_actual == 1) ? "BLANCO" : "NEGRO");
    info_final.WhoendGame = jugador_actual;
    if(info_final.status == 2)
        info_final.WhoendGame = casilla_ocupada;
    //printf("EL JUGADOR ACTUAL ES :%d\n",jugador_actual);
    freeListadoDeCeldas(&jugadas_posibles);


    //printf("EL ESTADO FINAL ES: %d",info_final.status);
    return info_final;
}

#endif
