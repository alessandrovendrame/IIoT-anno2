A = [[1,2],[7,5],[8,3],[1,5],[8,2]]
B = [1,2,5,14,24,54,32,8,6,7]
C = []

for element in A:
    if element[0] not in B:
        C.append([element[0],1])
    else:
        C[C.index(element[0])][1] += 1