#include <assert.h>
#include "main.h"


Bool tableroCmp(Colour tablero[TAM_TABLERO][TAM_TABLERO], Colour tablero2[TAM_TABLERO][TAM_TABLERO]){
    Bool flag = TRUE;
    for(int i=0; i < TAM_TABLERO;i++){
        for(int j = 0; j < TAM_TABLERO;j++){
            if(tablero[i][j] != tablero2[i][j])
                flag = FALSE;
        }
    }
    return flag;
}

void test_determinarGanador(){

    Colour tableroExample1[][8] = {
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,2,0,0,0},
                                {0,0,0,1,2,1,0,0},
                                {0,0,0,2,2,0,0,0},
                                {0,0,0,0,2,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                        };
    Colour tableroExample2[][8] = {
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,2,0,0,0,0},
                                {0,0,0,2,2,0,0,0},
                                {0,0,1,1,1,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0}
                        };
    Colour tableroExample3[][8] = {
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,1,0,0,0,0},
                                {0,0,0,1,2,0,0,0},
                                {0,0,1,1,1,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0}
                        };

    assert(devolverGanador(tableroExample1)==NEGRO);
    assert(devolverGanador(tableroExample2)==VACIO);
    assert(devolverGanador(tableroExample3)==BLANCO);
}

void test_hayganador(){
    Colour tableroExample1[][8] = {
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,2,0,0,0},
                                {0,0,0,1,2,1,0,0},
                                {0,0,0,2,2,0,0,0},
                                {0,0,0,0,2,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                        };
    Colour tableroExample2[][8] = {
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,2,0,0,0,0},
                                {0,0,0,2,2,0,0,0},
                                {0,0,1,1,1,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0}
                        };
    assert(hayGanador(tableroExample1)==TRUE);
    assert(hayGanador(tableroExample2)==FALSE);
}

void test_cambiarColor(){
    Colour color1 = BLANCO;
    Colour color2 = VACIO;
    Colour color3 = NEGRO;
    assert(cambiarColor(color1)==NEGRO);
    assert(cambiarColor(color2)==VACIO);
    assert(cambiarColor(color3)==BLANCO);
}

void test_posvalida(){
    Celda c;
    c.columna = 0;
    c.fila = -1;
    Celda c2;
    c2.columna = 3;
    c2.fila = 3;
    Celda c3;
    c3.columna = 10;
    c3.fila = 2;
    assert(posvalida(c)==FALSE);
    assert(posvalida(c2)==TRUE);
    assert(posvalida(c3)==FALSE);
}

void test_sonCeldasIguales(){
    Celda c,c2,c3;
    c.columna = 0;
    c.fila = -1;
    c2.columna = 3;
    c2.fila = 3;
    c3.columna = 10;
    c3.fila = 2;

    assert(sonCeldasIguales(c,c2)==FALSE);
    assert(sonCeldasIguales(c,c)==TRUE);
    assert(sonCeldasIguales(c2,c3)==FALSE);
}

void test_createCelda(){
    Celda celda;
    celda.columna = 2;
    celda.fila = 6;
    assert(sonCeldasIguales(createCelda(2,6),celda)==TRUE);
    assert(sonCeldasIguales(createCelda(3,4),celda)==FALSE);
    assert(sonCeldasIguales(createCelda(4,6),celda)==FALSE);
    
}

void test_freeListadoDeCeldas(){
    ListadoDeCeldas list = listaDeCeldasVacia();
   // exit(3);
    insertCeldaninList(&list, createCelda(1,10));
    insertCeldaninList(&list,createCelda(5,2));
    freeListadoDeCeldas(&list);
    assert(list.celdas==NULL);
    assert(list.tamanio == 0);

    freeListadoDeCeldas(&list);
}

void test_insertCeldaninList(){
  //  exit(3);
    ListadoDeCeldas list = listaDeCeldasVacia();
    insertCeldaninList(&list,createCelda(1,1));
    insertCeldaninList(&list,createCelda(4,0));
    insertCeldaninList(&list, createCelda(7,2));
  //  exit(3);
    assert(sonCeldasIguales(list.celdas[0], createCelda(1,1))==TRUE);
    assert(sonCeldasIguales(list.celdas[1], createCelda(4,0))==TRUE);
    assert(sonCeldasIguales(list.celdas[2],createCelda(7,2))==TRUE);
    assert(list.tamanio == 3);
    assert(list.tamanio_maximo == 4);
    freeListadoDeCeldas(&list);

   // perror("tatodojoya\n");

}

void test_apuntarCelda(){
    ListadoDeCeldas list = listaDeCeldasVacia();
    insertCeldaninList(&list, createCelda(1,1));
    insertCeldaninList(&list,createCelda(4,2));
    insertCeldaninList(&list,createCelda(5,5));
    assert(apuntarCelda(&list, createCelda(5,5))== list.celdas+2);
    assert(apuntarCelda(&list,createCelda(0,0))==NULL);
    assert(apuntarCelda(&list,createCelda(4,2))== list.celdas+1);
    freeListadoDeCeldas(&list);
}


Bool sonListasIguales(ListadoDeCeldas list1, ListadoDeCeldas list2){
    Bool flag = TRUE;
    if(list1.tamanio != list2.tamanio){
        flag = FALSE;
        return flag;
    }
    else{
    for(int i = 0; i <list1.tamanio ; i++){
        if(!sonCeldasIguales(list1.celdas[i],list2.celdas[i]))
            flag = FALSE;
    }
    }
    return flag;

}

void test_deletearCeldaFromList(){
    ListadoDeCeldas list = listaDeCeldasVacia();
    ListadoDeCeldas listcmp = listaDeCeldasVacia();
    insertCeldaninList(&list,createCelda(1,1));
    insertCeldaninList(&list,createCelda(4,2));
    insertCeldaninList(&list,createCelda(7,4));

    insertCeldaninList(&listcmp,createCelda(4,2));
    insertCeldaninList(&listcmp,createCelda(7,4));

    deletearCeldaFromList(&list,createCelda(1,1));
    assert(sonListasIguales(list,listcmp));
    freeListadoDeCeldas(&list);
    freeListadoDeCeldas(&listcmp);
}

void test_tocoords(){
    int col = 'A';
    int fil = 1;
    toocords(&col,&fil);
    assert(col == 0);
    assert(fil == 0);
}

void test_totable(){
    int col = 0;
    int fil = 0;
    totable(&col,&fil);
    assert(col == 'A');
    assert(fil == 1);
}

void test_isCeldaInList(){
    ListadoDeCeldas list = listaDeCeldasVacia();
    insertCeldaninList(&list,createCelda(1,1));
    insertCeldaninList(&list,createCelda(3,2));
    insertCeldaninList(&list,createCelda(3,3));


    assert(isCeldaInList(list,createCelda(1,1))==TRUE);
    assert(isCeldaInList(list,createCelda(0,0))==FALSE);
    assert(isCeldaInList(list,createCelda(3,3))==TRUE);
    assert(isCeldaInList(list,createCelda(4,6))==FALSE);

    freeListadoDeCeldas(&list);
}

void test_direccion_cumple_regla1(){
    Colour tablero[TAM_TABLERO][TAM_TABLERO];
    transformToTableroInicial(tablero);
    Celda celda = createCelda(4,4);
    assert(direccion_cumple_regla1(tablero,celda,NEGRO,0,-1) == FALSE);
    assert(direccion_cumple_regla1(tablero,celda,BLANCO,-1,0) == TRUE);
    assert(direccion_cumple_regla1(tablero,celda,BLANCO,-1,-1) == FALSE);
    
}

//void test_sonListasIguales(){

//}

/*void printListadeCeldas(ListadoDeCeldas lista){
    if(lista.tamanio == 0){
        printf("La lista esta vacia \n");
        return ;
    }else
    for(int i = 0; i < lista.tamanio;i++){
        printf("La %d° celda es: ",i);
        printf("%d %d \n",lista.celdas[i].columna,lista.celdas[i].fila);
    }
}*/

void test_listar_Celdas_en_direccion(){

    Colour tableroExample2[][8] = {
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,2,0,0,0,0},
                                {0,0,0,2,2,0,0,0},
                                {0,0,1,1,2,2,2,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0}
                        };
    Celda origen = createCelda(4,7);
    ListadoDeCeldas list = listaDeCeldasVacia();
    list = listar_Celdas_en_direccion(tableroExample2,origen,BLANCO,0,-1);
    ListadoDeCeldas devuelve1 = listaDeCeldasVacia();
    insertCeldaninList(&devuelve1,createCelda(4,6));
    insertCeldaninList(&devuelve1,createCelda(4,5));
    insertCeldaninList(&devuelve1,createCelda(4,4));

    assert(sonListasIguales(list,devuelve1));

    Celda origen2 = createCelda(1,3);
    ListadoDeCeldas list2 = listaDeCeldasVacia();
    list2 = listar_Celdas_en_direccion(tableroExample2,origen2,BLANCO,1,0);
    ListadoDeCeldas devuelve2 = listaDeCeldasVacia();
    insertCeldaninList(&devuelve2,createCelda(2,3));
    insertCeldaninList(&devuelve2,createCelda(3,3));

    assert(sonListasIguales(list2,devuelve2));

    freeListadoDeCeldas(&list);
    freeListadoDeCeldas(&devuelve1);
    freeListadoDeCeldas(&list2);
    freeListadoDeCeldas(&devuelve2);
    //printf("todojoya");

}

void test_jugadaValida(){
    Colour tablero[TAM_TABLERO][TAM_TABLERO];
    transformToTableroInicial(tablero);

    Colour tableroExample[][8] = {
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,1,2,0,0,0},
                                {0,0,0,2,1,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                        };

    //printListadeCeldas(listar_Celdas_en_direccion(tableroExample,createCelda(5,3),BLANCO,-1,0));

    Colour tableroExample1[][8] = {
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,2,0,0,0},
                                {0,0,0,1,2,1,0,0},
                                {0,0,0,2,2,0,0,0},
                                {0,0,0,0,2,0,0,0},
                                {0,0,0,0,1,0,0,0},
                                {0,0,0,0,0,0,0,0},
                        };
    
    Colour tableroExample2[][8] = {
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,2,0,0,0,0},
                                {0,0,0,2,2,0,0,0},
                                {0,0,1,1,1,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0}
                        };

    Celda cel;
    cel = createCelda(1,4);
    Colour jugador = BLANCO; // devuelve 1;(usando tablero)
    
    int result = jugadaValida(tableroExample1,cel,jugador);
    assert(result == 4);

    Celda cel2 = createCelda(2,3);
    Colour jugador2 = NEGRO;
    int result2 = jugadaValida(tableroExample,cel2,jugador2);
   // printf("la jugada cambio %d",result2);
    assert(result2 == 1);

    Celda cel3 = createCelda(3,2);
    Colour jugador3 = BLANCO;
    int result3 = jugadaValida(tableroExample2,cel3,jugador3);
    //printf("la jugada cambio %d",result3);
    assert(result3 == 0);

}


Bool sonTableroIguales(Colour tablero[TAM_TABLERO][TAM_TABLERO], Colour tablero2[TAM_TABLERO][TAM_TABLERO]){
    Bool flag  = TRUE;
    for(int i=0; i< TAM_TABLERO ; i++)
        for(int j = 0; j<TAM_TABLERO;j++){
            if(tablero2[i][j] != tablero[i][j])
                flag = FALSE;
        }
    return flag;
}

void printTablero(Colour tablero[TAM_TABLERO][TAM_TABLERO]){
    for(int i= 0; i < TAM_TABLERO; i++){
        for(int j = 0; j < TAM_TABLERO; j++)
            if(tablero[i][j] == VACIO)
                printf("0");
            else if(tablero[i][j] == BLANCO)
                printf("1");
            else printf("2");
        printf("\n");
        }
}

void test_SimularJuego(){
    DataForStartGame info_inicial;
        info_inicial.movidas = listaDeCeldasVacia();
        insertCeldaninList((&info_inicial.movidas), createCelda(0,0));
        insertCeldaninList((&info_inicial.movidas), createCelda(3,4));
        insertCeldaninList((&info_inicial.movidas), createCelda(4,1));
        info_inicial.whoStart = NEGRO;

    DataForEndGame info_final;
        transformToTableroInicial(info_final.tablero);
        //printTablero(info_final.tablero);
        info_final.status = JUGADA_INCORRECTA_REGLA1;
        info_final.WhoendGame = NEGRO;

    Colour test[TAM_TABLERO][TAM_TABLERO];
    transformToTableroInicial(test);

    DataForEndGame result = SimularJuego(info_inicial);
    assert(sonTableroIguales(info_final.tablero,result.tablero));
    assert(info_final.status==result.status);
    assert(result.WhoendGame == info_final.WhoendGame);

    DataForStartGame inicio;
        inicio.movidas = listaDeCeldasVacia();
        insertCeldaninList((&inicio.movidas),createCelda(4,4));
        //insertCeldaninList((&inicio.movidas),createCelda(,));
        //insertCeldaninList((&inicio.movidas),createCelda(,));
        inicio.whoStart = BLANCO;
    DataForEndGame fin;
        transformToTableroInicial(fin.tablero);
        fin.status = CELDA_OCUPADA;
        fin.WhoendGame = BLANCO;
    
    DataForEndGame result2 = SimularJuego(inicio);

    assert(sonTableroIguales(fin.tablero,result2.tablero));
    assert(fin.status == result2.status);
    assert(fin.WhoendGame == result2.WhoendGame);

    //printTablero(result2.tablero);

    Colour tableroExample1[][8] = {
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,1,1,1,0,0},
                                {0,0,0,2,1,1,0,0},
                                {0,0,0,0,0,1,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                        };
        //printTablero(tableroExample1);
    printTablero(tableroExample1);
    printf("\n");

    DataForStartGame start;
        start.movidas = listaDeCeldasVacia();
        start.whoStart = BLANCO;
        insertCeldaninList((&start.movidas),createCelda(3,5));
        insertCeldaninList((&start.movidas),createCelda(4,5));
        insertCeldaninList((&start.movidas),createCelda(5,5));
    DataForEndGame end;
        end.status = JUEGO_CONTINUA;
        cpTablero(end.tablero,tableroExample1);
        end.WhoendGame = BLANCO;

    DataForEndGame resultado = SimularJuego(start);
    //printTablero(resultado.tablero);
    //printTablero(resultado.tablero);
    
    assert(sonTableroIguales(end.tablero,resultado.tablero));
    assert(end.status == resultado.status);
    assert(end.WhoendGame == resultado.WhoendGame);

    Colour tableroExample3[][8] = {
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,2,0,0,0,0},
                                {0,0,0,2,2,0,0,0},
                                {0,0,0,2,1,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                        };
    DataForStartGame i;
    i.movidas = listaDeCeldasVacia();
    i.whoStart = NEGRO;
    insertCeldaninList(&i.movidas,createCelda(2,3));

    DataForEndGame f;
    f.status = JUEGO_CONTINUA;
    cpTablero(f.tablero,tableroExample3);
    f.WhoendGame = NEGRO;

    DataForEndGame r = SimularJuego(i);

    assert(sonTableroIguales(r.tablero,f.tablero));
    assert(r.status == f.status);
    assert(r.WhoendGame == f.WhoendGame);



    printf("anda todo bien\n");
}
//echo Exit Code is %errorlevel%

int main(){
    test_determinarGanador();
    test_hayganador();
    test_cambiarColor();
    test_posvalida();
    test_sonCeldasIguales();
    test_createCelda();
    test_freeListadoDeCeldas();
    test_insertCeldaninList();
    test_apuntarCelda();
    test_deletearCeldaFromList();
    test_tocoords();
    test_totable();
    test_isCeldaInList();
    test_direccion_cumple_regla1();
    test_listar_Celdas_en_direccion();
    test_jugadaValida();
    test_SimularJuego();
    return 0;
}

