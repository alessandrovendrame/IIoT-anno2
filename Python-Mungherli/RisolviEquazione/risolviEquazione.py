import sympy as sym
sym.init_printing()
x,y,z = sym.symbols('x,y,z')

f = sym.Eq((x/y+z) + (y/x+z) + (z/x+y),4)

print(sym.solve([f], [x, y, z]))