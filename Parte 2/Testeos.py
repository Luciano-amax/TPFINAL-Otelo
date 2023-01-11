from main import *

def transformTablero(tablero: list[list[int]]) -> dict[tuple[int,int]]:
    dict_tablero = {}
    if(tablero == []):
        return tablero
    for i in range(len(tablero)):
        for j in range(len(tablero[0])):
            dict_tablero[(i,j)] = tablero[i][j]
    return dict_tablero


def test_transformTablero():
    assert(transformTablero([
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,1,2,0,0,0],
                                [0,0,0,2,1,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0]
                            ]) 
                            
                            == 

                            { 
                                (0,0):0,(0,1):0,(0,2):0,(0,3):0,(0,4):0,(0,5):0,(0,6):0,(0,7):0,
                                (1,0):0,(1,1):0,(1,2):0,(1,3):0,(1,4):0,(1,5):0,(1,6):0,(1,7):0,
                                (2,0):0,(2,1):0,(2,2):0,(2,3):0,(2,4):0,(2,5):0,(2,6):0,(2,7):0,
                                (3,0):0,(3,1):0,(3,2):0,(3,3):1,(3,4):2,(3,5):0,(3,6):0,(3,7):0,
                                (4,0):0,(4,1):0,(4,2):0,(4,3):2,(4,4):1,(4,5):0,(4,6):0,(4,7):0,
                                (5,0):0,(5,1):0,(5,2):0,(5,3):0,(5,4):0,(5,5):0,(5,6):0,(5,7):0,
                                (6,0):0,(6,1):0,(6,2):0,(6,3):0,(6,4):0,(6,5):0,(6,6):0,(6,7):0,
                                (7,0):0,(7,1):0,(7,2):0,(7,3):0,(7,4):0,(7,5):0,(7,6):0,(7,7):0
                            })
    
    assert(transformTablero([
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,1,1,1,0,0],
                                [0,0,0,2,2,0,0,0],
                                [0,0,0,0,2,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                            ]) 
                            
                            == 
                            
                            {   
                                (0,0):0,(0,1):0,(0,2):0,(0,3):0,(0,4):0,(0,5):0,(0,6):0,(0,7):0,
                                (1,0):0,(1,1):0,(1,2):0,(1,3):0,(1,4):0,(1,5):0,(1,6):0,(1,7):0,
                                (2,0):0,(2,1):0,(2,2):0,(2,3):0,(2,4):0,(2,5):0,(2,6):0,(2,7):0,
                                (3,0):0,(3,1):0,(3,2):0,(3,3):1,(3,4):1,(3,5):1,(3,6):0,(3,7):0,
                                (4,0):0,(4,1):0,(4,2):0,(4,3):2,(4,4):2,(4,5):0,(4,6):0,(4,7):0,
                                (5,0):0,(5,1):0,(5,2):0,(5,3):0,(5,4):2,(5,5):0,(5,6):0,(5,7):0,
                                (6,0):0,(6,1):0,(6,2):0,(6,3):0,(6,4):0,(6,5):0,(6,6):0,(6,7):0,
                                (7,0):0,(7,1):0,(7,2):0,(7,3):0,(7,4):0,(7,5):0,(7,6):0,(7,7):0
                            })

    assert(transformTablero([
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,2,0,0,0,0],
                                [0,0,0,2,2,0,0,0],
                                [0,0,0,2,1,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0]
                            ]) 
                            
                            == 
                            
                            {
                                (0,0):0,(0,1):0,(0,2):0,(0,3):0,(0,4):0,(0,5):0,(0,6):0,(0,7):0,
                                (1,0):0,(1,1):0,(1,2):0,(1,3):0,(1,4):0,(1,5):0,(1,6):0,(1,7):0,
                                (2,0):0,(2,1):0,(2,2):0,(2,3):2,(2,4):0,(2,5):0,(2,6):0,(2,7):0,
                                (3,0):0,(3,1):0,(3,2):0,(3,3):2,(3,4):2,(3,5):0,(3,6):0,(3,7):0,
                                (4,0):0,(4,1):0,(4,2):0,(4,3):2,(4,4):1,(4,5):0,(4,6):0,(4,7):0,
                                (5,0):0,(5,1):0,(5,2):0,(5,3):0,(5,4):0,(5,5):0,(5,6):0,(5,7):0,
                                (6,0):0,(6,1):0,(6,2):0,(6,3):0,(6,4):0,(6,5):0,(6,6):0,(6,7):0,
                                (7,0):0,(7,1):0,(7,2):0,(7,3):0,(7,4):0,(7,5):0,(7,6):0,(7,7):0
                            })

# pos :: tuple -> Boolean
def test_posvalida():
    tupla = (9,0)
    tupla2 = (10, 5)
    tupla3 = (0,0)
    assert(esPosValida(tupla)== False)
    assert(esPosValida(tupla2)== False)
    assert(esPosValida(tupla3) == True)

# sumaTupla :: tuple, tuple -> tuple 
def test_sumaTupla():
    tupla = (9,0)
    tupla2 = (10, 5)
    tupla3 = (0,0)
    assert(sumaTupla(tupla,tupla2)== (19,5))
    assert(sumaTupla(tupla3,tupla2)== (10,5))
    assert(sumaTupla(tupla3,tupla)== (9,0))
    
# printTablero :: tablero:dict -> None
def tablero_inicial(): return transformTablero([
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,1,2,0,0,0],
                                [0,0,0,2,1,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0]
                            ]) 



def tablero_de_prueba(): return transformTablero([
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,1,1,1,0,0],
                                [0,0,0,2,2,0,0,0],
                                [0,0,0,0,2,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                            ]) 

def tablero_de_prueba2(): return transformTablero([
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,2,0,0,0,0],
                                [0,0,0,2,2,0,0,0],
                                [0,0,0,2,1,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0,0]
                            ]) 

# printTablero :: dict[tuple[int,int]] -> None
def test_printTablero():
    assert(printTablero(tablero_inicial())==None)
   #assert(printTablero(tablero56)==None)
   #assert(printTablero(tablero34)==None)
   
# casillasEnDireccion :: tuple[int,int], tuple[int,int] -> list[tuple[int,int]]
def test_casillasEnDireccion():
    assert(casillasEnDireccion((3,3),(0,-1)) == [(3,2),(3,1),(3,0)])
    assert(casillasEnDireccion((0,0),(1,1)) == [(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7)]) 
    assert(casillasEnDireccion((7,7),(1,1)) == [])   

#alternarColor :: int -> int
def test_alternarColor():
    assert(alternarColor(1)==2)
    assert(alternarColor(2)==1)
    assert(alternarColor(0)==0)
    
def test_direccionCumpleRegla1():
    assert(direccionCumpleRegla1(tablero_inicial(),(3,3),(0,-1),1) == False)
    assert(direccionCumpleRegla1(tablero_inicial(),(3,3),(1,0),1) == True)
    assert(direccionCumpleRegla1(tablero_inicial(),(3,3),(1,0),2) == False)


#getFichasFromDireccion :: dict[tuple[int,int]], tuple, tuple -> list[tuple[int,int]]
def test_getFichasFromDireccion():
    assert(getFichasFromDireccion(tablero_de_prueba(),(3,3),(1,1),1) == [])
    assert(getFichasFromDireccion(tablero_de_prueba(),(6,4),(-1,0),1) == [(5,4),(4,4)])
    assert(getFichasFromDireccion(tablero_de_prueba(),(2,5),(1,-1),2) == [(3,4)])

#simularJugada :: dict[tuple[int,int]], tuple, int -> int
def test_simularJugada():
    assert(simularJugada(tablero_de_prueba(), (2,3), 1) == -1)
    assert(simularJugada(tablero_de_prueba(), (2,6), 2) == 1)
    assert(simularJugada(tablero_de_prueba(), (6,4), 1) == 2)

#toCoords :: str -> tuple[int,int]
def test_toCoords():
    assert(toCoords('A9') == (0,8)) # aunque sea invalida
    assert(toCoords('B4') == (1,3))
    assert(toCoords('F6') == (5,5))

#actualizarPosiciones :: dict[tuple[int,int]], set[tuple[int,int]], tuple[int,int] -> None
    assert (actualizarPosiciones(tablero_inicial(),set([(2,2),(2,3),(2,4),(2,5),(3,2),(3,5),(4,2),(4,5),(5,2),(5,3),(5,4),(5,5)]), (3,2)) == None)
    
#nuevoTablero :: -> dict[tuple[int,int]]
def test_nuevoTablero():
    assert(nuevoTablero() == tablero_inicial())

#determinarGanador :: dict[tuple[int,int]] -> int
    assert(determinarGanador(tablero_de_prueba()) == 0)
    assert(determinarGanador(tablero_inicial()) == 0)
    assert(determinarGanador(tablero_de_prueba2()) == 2)

def test_setJugadasPosibles():
    assert(setJugadasPosibles(tablero_inicial()) == set([(2,2),(2,3),(2,4),(2,5),(3,2),(3,5),(4,2),(4,5),(5,2),(5,3),(5,4),(5,5)]))    
    assert(setJugadasPosibles(tablero_de_prueba()) == set([(2,2),(2,3),(2,4),(2,5),(2,6),(3,2),(3,6),(4,2),(4,5),(4,6),(5,2),(5,3),(5,5),(6,3),(6,4),(6,5)]))
    assert(setJugadasPosibles(tablero_de_prueba2()) == set([(1,2),(1,3),(1,4),(2,2),(2,4),(2,5),(3,2),(3,5),(4,2),(4,5),(5,2),(5,3),(5,4),(5,5)]))