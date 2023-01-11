import random

def tamTablero() -> int:
    return 8

def GetInfoFromFile(path_to_archivo) -> tuple[dict[tuple[int,int]],str]:
    tablero = {}
    arch = open(path_to_archivo)
    for i in range (tamTablero()):
        for k in range (tamTablero()):
            tablero[(i,k)] = 0
    for i in range (tamTablero()):
        line = arch.readline().replace('\n','')
        for k in range (tamTablero()):
            if(line[k] != 'X'):
                if(line[k] == 'B'):
                    tablero[(k,i)] = 1
                else:
                    tablero[(k,i)] = 2

    if(arch.readline()[0] == 'B'):
        whoStart = 1
    else:
        whoStart = 2
    return tablero,whoStart

def esPosValida(pos:tuple[int,int]) -> bool:
    x=pos[0]
    y=pos[1]
    if(0 <= x and x < tamTablero() and 0 <= y and y < tamTablero()):
        return True
    else:
        return False

def printTablero(tablero: dict[tuple[int,int]]) -> None:
    get_color = {
        0: ' ',
        1: "B",
        2: "N",
        3: 'X'
    }
 
    linea = lambda : print('  '+'-'*33)
 
    print('  ',end='')
    for i in range(8):
        print('  '+chr(65+i),end=' ')
    print()
    linea()
    for i in range(8):
        print(i+1,end=' ')
        for j in range(8):
            print('| '+get_color[tablero[(j,i)]],end=' ')
        print('|')
        linea()

def toCoords(letras: str) -> tuple[int,int]:
    # Las jugadas son una palabra de 2 letras, si una jugada no tiene 2 letras, entonces se devuelve una coordenada no valida
    if(len(letras)!=2):
        return (-1,-1)
    return (ord(letras[0])-ord('A'),int(letras[1])-1)

def sumaTupla(t1: tuple,t2: tuple) -> tuple:
    return (t1[0]+t2[0],t1[1]+t2[1])

def casillasEnDireccion(pos: tuple[int,int],direccion: tuple[int,int]) -> list[tuple[int,int]]:
    casillas = []
    pos = sumaTupla(pos,direccion)
    while(esPosValida(pos)):
        casillas.append(pos)
        pos=sumaTupla(pos,direccion)
    return casillas

def alternarColor(color: int) -> int:
    if color == 1:
        return 2
    if color == 2:
        return 1
    return color

# Dada un tablero, una posicion de origen, una direccion y un color, devuelve True si y solo si en la celda adyacente origen en dicha direccion hay una ficha del color contrario
def direccionCumpleRegla1(tablero: dict[tuple[int,int]],pos: tuple[int,int],direccion: tuple[int,int],color: int) -> bool:
    new_pos = sumaTupla(pos,direccion)
    return esPosValida(new_pos) and tablero[new_pos]==alternarColor(color)

def getFichasFromDireccion(tablero: dict[tuple[int,int]],origen: tuple[int,int],direccion: tuple[int,int],color_jugador: int) -> list[tuple[int,int]]:
    casillas = casillasEnDireccion(origen,direccion)
 
    colores = list(map(lambda pos: tablero[pos],casillas))
 
    try:
        limit = colores.index(color_jugador)
    except ValueError:
        limit=0

    try:
        limit_vacio = colores.index(0)
        if limit_vacio < limit:
            limit=0
    except ValueError:
        pass
    
    return casillas[:limit]

def actualizarPosiciones(tablero: dict[tuple[int,int]],posiciones:set[tuple[int,int]],pos: tuple[int,int]):
    direcciones = [
        (-1,-1),    # Arriba Izquierda
        (-1,0),     # Izquierda
        (-1,1),     # Arriba Derecha
        (0,-1),     # Izquierda
        (0,1),      # Derecha
        (1,-1),     # Abajo Izquierda
        (1,0),      # Abajo
        (1,1)       # Abajo Derecha
    ]
 
    posiciones.remove(pos)
 
    for direccion in direcciones:
        posison = sumaTupla(pos,direccion)
        if(esPosValida(posison) and tablero[posison]==0):
            posiciones.add(posison)

# Genera un nuevo tablero con la configuracion inicial
def nuevoTablero() -> dict[tuple[int,int]]:
    tablero = {}

    for i in range(tamTablero()):
        for j in range(tamTablero()):
            tablero[(i,j)]=0
 
    tablero[(3,3)]=tablero[(4,4)]=1
    tablero[(3,4)]=tablero[(4,3)]=2
    
    return tablero

# Dado un tablero de juego, devuelve el jugador que lleva la delantera, devuelve 0 si hay un empate
def determinarGanador(tablero: dict[tuple[int,int]]) -> int:
    count_fichas = {1: 0, 2:0}
    for pos in tablero:
        if(tablero[pos]!=0):
            count_fichas[tablero[pos]]+=1

    if count_fichas[1] > count_fichas[2]:
        return 1
    if count_fichas[1] < count_fichas[2]:
        return 2
    return 0

def simularJugada(tablero: dict[tuple[int,int]],origen: tuple[int,int],color_jugador: int) -> int:
    direcciones = [
        (-1,-1),    # Arriba Izquierda
        (-1,0),     # Izquierda
        (-1,1),     # Arriba Derecha
        (0,-1),     # Izquierda
        (0,1),      # Derecha
        (1,-1),     # Abajo Izquierda
        (1,0),      # Abajo
        (1,1)       # Abajo Derecha
    ]

    # De todas las direcciones posibles, me quedo con aquellas en donde hay una ficha adyacente del color contrario
    direcciones_validas = [direccion for direccion in direcciones if direccionCumpleRegla1(tablero,origen,direccion,color_jugador)]
 
    if(direcciones_validas == []):
        # Esta posicion no cumple la regla 1
        return -1

    fichas_cambiadas = 0
 
    for direccion in direcciones_validas:
        # Convierte las fichas afectadas al color del jugador
        for casilla in getFichasFromDireccion(tablero,origen,direccion,color_jugador):
            tablero[casilla] = color_jugador
            fichas_cambiadas +=1
    if(fichas_cambiadas > 0):
        tablero[origen] = color_jugador

    return fichas_cambiadas

def existeJugadaValida(tablero : dict[tuple[int,int]],jugadas_posibles: set[tuple[int,int]]):
    flag = False
    for posison in jugadas_posibles:
        cont_blanco = simularJugada(tablero.copy(),posison,1)
        cont_negro = simularJugada(tablero.copy(),posison,2)
        if(cont_negro > 0 or cont_blanco > 0):
            flag = True
    return flag

def estaEnLista(lista: list, pos: int):
    flag = False
    for i in range (len(lista)):
        if(pos == lista[i]):
            flag = True
    return flag

def ingresarJugada_IA_(tablero: dict[tuple[int,int]], nivel: int, color_IA: int, jugadas_posibles: set[tuple[int,int]]):
    movimineto = None
    if(nivel == 0):
        flag_jugada = False

        lista_mezclada = []
        temp = list(jugadas_posibles.copy())
        cont = 0
        while(cont < len(temp)):
            j = random.randrange(0,len(temp),1)
            if(not estaEnLista(lista_mezclada,temp[j])):
                lista_mezclada.append(temp[j])
                cont+=1
        i = 0
        while(not flag_jugada and i < len(lista_mezclada)):
            contador = simularJugada(tablero.copy(),lista_mezclada[i],color_IA)
            if(contador > 0):
                flag_jugada = True
                movimineto = lista_mezclada[i]
            i+=1
    else:
        contMaximo = 0
        i = 0
        for celda in jugadas_posibles:
            contador = simularJugada(tablero.copy(),celda,color_IA)
            if(contador > contMaximo):
                contMaximo = contador
                movimineto = celda

    if(movimineto == None):
        print("La IA no posee movimientos posibles, salta su turno ")
    else:
        print("La IA puso su ficha en {}{}".format(chr(ord('A')+ movimineto[0]),movimineto[1]+1))
        simularJugada(tablero,movimineto,color_IA)
        actualizarPosiciones(tablero,jugadas_posibles,movimineto)  
    return movimineto

def ingresaJugadaH(tablero: dict[tuple[int,int]], jugador_actual: int, jugadas: set[tuple[int,int]]):
    flag = False
    print("Por favor ingrese una celda: ",end='')
    while(not flag):
        jugada = input()
        celda = toCoords(jugada)
        if(esPosValida(celda) and tablero[celda] == 0):
            cont_player = simularJugada(tablero,celda,jugador_actual)
            if(cont_player > 0):
                flag = True
                actualizarPosiciones(tablero,jugadas,celda)
        if(jugada == '' and not(existeJugadaValida(tablero,jugadas))):
            flag = True
        if(not flag):
            print("No se ingreso un jugada valida, por favor ingrese otra celda: ",end='')

def setJugadasPosibles(tablero: dict[tuple[int,int]])-> set[tuple[int,int]]:
    direcciones = [
        (-1,-1),    # Arriba Izquierda
        (-1,0),     # Izquierda
        (-1,1),     # Arriba Derecha
        (0,-1),     # Izquierda
        (0,1),      # Derecha
        (1,-1),     # Abajo Izquierda
        (1,0),      # Abajo
        (1,1)       # Abajo Derecha
    ]
    Jugadas_posibles  = set()

    for celda in tablero.keys():
        #print(celda)
        celda_posibles = False
        if(tablero[celda] == 0):
            for dir in direcciones:
                temp = sumaTupla(celda,dir)
                #print("LA CELDA A REVISAR QUEDA EN: ")
                #print(temp)
                if(esPosValida(temp) and tablero[temp] != 0 ):
                    celda_posibles = True
        if(celda_posibles):
            Jugadas_posibles.add(celda)

    return Jugadas_posibles

def main(path_to_archivo, colorPlayer, nivel):
    tablero,WhoStart = GetInfoFromFile(path_to_archivo)
    #print(tablero)
    jugadas_posibles_iniciales = setJugadasPosibles(tablero)
    jugador_actual = WhoStart
    #print(jugadas_posibles_iniciales)
    printTablero(tablero)
    while(existeJugadaValida(tablero,jugadas_posibles_iniciales)):
        if(jugador_actual != colorPlayer):
            ingresarJugada_IA_(tablero,nivel,jugador_actual,jugadas_posibles_iniciales)
            #print(tablero,end='')
            printTablero(tablero)
        else:
            ingresaJugadaH(tablero,jugador_actual,jugadas_posibles_iniciales)
            #print(tablero,end='')
            printTablero(tablero)
        #print("ENTRA ACA EL JUGADOR ACTUAL ES: ")
        #print(jugador_actual)
        jugador_actual = alternarColor(jugador_actual)
        #print(jugador_actual)
    winner = determinarGanador(tablero)
    if(winner == 0):
        print("EL JUEGO FINALIZO EN EMPATE ")
    else:
        if(winner == 1):
            print("EL JUEGO FINALIZO, EL JUGADOR BLANCO SE CONSAGRO GANADOR ")
        else:
            print("EL JUEGO FINALIZO, EL JUGADOR NEGRO SE CONSAGRO GANADOR ")