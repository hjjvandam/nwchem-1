from sympy import *
init_printing()
x, y, z, a = symbols('x y z a')
k, m, n = symbols('k m n', integer=True)
f, g, h = symbols('f g h', cls=Function)
#
# We define the gradient which we want to be positive.
# Because we work on the domain x=[0,1] and the relevant
# points are x=0, x=1/2, x=1 we can choose low order functions.
# All the relevant positive factors are x, (x-1/2)**2, and 1-x
#
# Stationary point at x=1/2
#
print("Stationary point at x=1/2          : ",end="")
f=(x-1/2)**2
g=integrate(f,x)
h=(g-g.subs(x,0))/(g.subs(x,1)-g.subs(x,0))
print(h)
print("Func(1/2)                          = ",h.subs(x,1/2))
print("Diff(1/2)                          = ",diff(h,x,1).subs(x,1/2))
print("Diff2(1/2)                         = ",diff(h,x,2).subs(x,1/2))
print()
#
# Stationary point at x=0, x=1/2
#
print("Stationary point at x=0, x=1/2     : ",end="")
f=x*(x-1/2)**2
g=integrate(f,x)
h=(g-g.subs(x,0))/(g.subs(x,1)-g.subs(x,0))
print(h)
print("Func(1/2)                          = ",h.subs(x,1/2))
print("Diff(1/2)                          = ",diff(h,x,1).subs(x,1/2))
print("Diff2(1/2)                         = ",diff(h,x,2).subs(x,1/2))
print()
#
# Stationary point at x=1/2, x=1
#
print("Stationary point at x=1/2, x=1     : ",end="")
f=(x-1/2)**2*(1-x)
g=integrate(f,x)
h=(g-g.subs(x,0))/(g.subs(x,1)-g.subs(x,0))
print(h)
print("Func(1/2)                          = ",h.subs(x,1/2))
print("Diff(1/2)                          = ",diff(h,x,1).subs(x,1/2))
print("Diff2(1/2)                         = ",diff(h,x,2).subs(x,1/2))
print()
#
# Stationary point at x=0, x=1/2, x=1
#
print("Stationary point at x=0, x=1/2, x=1: ",end="")
f=x*(x-1/2)**2*(1-x)
g=integrate(f,x)
h=(g-g.subs(x,0))/(g.subs(x,1)-g.subs(x,0))
print(h)
print("Func(1/2)                          = ",h.subs(x,1/2))
print("Diff(1/2)                          = ",diff(h,x,1).subs(x,1/2))
print("Diff2(1/2)                         = ",diff(h,x,2).subs(x,1/2))
#
# So far we have assumed that a stationary point at x=1/2 would really help.
# The results show real improvements in just one case. Even then there is clearly
# something missing. This leads to the question: What if we maximize the gradient
# at x=1/2 instead?
#
# Stationary point at x=0, and x=1
#
print("Stationary point at x=0, x=1       : ",end="")
f=x*(1-x)
g=integrate(f,x)
h=(g-g.subs(x,0))/(g.subs(x,1)-g.subs(x,0))
print(h)
print("Func(1/2)                          = ",h.subs(x,1/2))
print("Diff(1/2)                          = ",diff(h,x,1).subs(x,1/2))
print("Diff2(1/2)                         = ",diff(h,x,2).subs(x,1/2))
#
# Stationary point at x=0
#
print("Stationary point at x=0            : ",end="")
f=x+3*x*(1-x)
g=integrate(f,x)
h=(g-g.subs(x,0))/(g.subs(x,1)-g.subs(x,0))
print(h)
print("Func(1/2)                          = ",h.subs(x,1/2))
print("Diff(1/2)                          = ",diff(h,x,1).subs(x,1/2))
print("Diff2(1/2)                         = ",diff(h,x,2).subs(x,1/2))
#
# Stationary point at x=1
#
print("Stationary point at x=1            : ",end="")
f=(1-x)+3*x*(1-x)
g=integrate(f,x)
h=(g-g.subs(x,0))/(g.subs(x,1)-g.subs(x,0))
print(h)
print("Func(1/2)                          = ",h.subs(x,1/2))
print("Diff(1/2)                          = ",diff(h,x,1).subs(x,1/2))
print("Diff2(1/2)                         = ",diff(h,x,2).subs(x,1/2))
