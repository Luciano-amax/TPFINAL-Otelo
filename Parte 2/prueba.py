A = set[(1,1),(2,2)]
B = set[(2,2),(1,1)]

def sonConjuntosIguales(A: set[tuple[int,int]],B: set[tuple[int,int]]) -> bool:
    flag = False
    if(len(A) == len(B)):
        for elemA in A:
            for elemB in B:
                if(elemA == elemB):
                    flag = True
    return flag