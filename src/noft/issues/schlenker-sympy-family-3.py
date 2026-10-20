from sympy import *
init_printing()
x, y, z, a, b = symbols('x y z a b')
k, m, n = symbols('k m n', integer=True)
f, g, h = symbols('f g h', cls=Function)
#
# Base gradient
#
f=(4*x*(1-x))**1
g=integrate(f,x)
h=(g-g.subs(x,0))/(g.subs(x,1)-g.subs(x,0))
print(h)
print("Func(1/2)                          = ",h.subs(x,1/2))
print("Diff(1/2)                          = ",diff(h,x,1).subs(x,1/2))
#
f=(4*x*(1-x))**2
g=integrate(f,x)
h=(g-g.subs(x,0))/(g.subs(x,1)-g.subs(x,0))
print(h)
print("Func(1/2)                          = ",h.subs(x,1/2))
print("Diff(1/2)                          = ",diff(h,x,1).subs(x,1/2))
#
f=(4*x*(1-x))**3
g=integrate(f,x)
h=(g-g.subs(x,0))/(g.subs(x,1)-g.subs(x,0))
print(h)
print("Func(1/2)                          = ",h.subs(x,1/2))
print("Diff(1/2)                          = ",diff(h,x,1).subs(x,1/2))
#
f=(4*x*(1-x))**4
g=integrate(f,x)
h=(g-g.subs(x,0))/(g.subs(x,1)-g.subs(x,0))
print(h)
print("Func(1/2)                          = ",h.subs(x,1/2))
print("Diff(1/2)                          = ",diff(h,x,1).subs(x,1/2))
