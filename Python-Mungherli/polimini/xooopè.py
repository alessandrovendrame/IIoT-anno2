import numpy as np

v=[(0,1),(0,2),(0,3)]
v1=[(0,1),(2,3)]
v2 = [v,v1]

c = np.rot90(v)
d = np.rot90(c)

print("C: " , c)
print("D: " , d)

if v==v1:
    print("VERO!")

if v in v2:
    print("Sono dentro")