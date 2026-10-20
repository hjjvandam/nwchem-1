from sympy import *
init_printing()
ra, rb, c, a = symbols('ra rb c a', positive=True)
k, m, n = symbols('k m n', integer=True)
f, g, h = symbols('f g h', cls=Function)
#
# For the restricted open-shell case we want a functional
# that is sensible when ra != rb. In particular the
# functional should go to 0 if either ra == 0,
# rb == 0.
#
# We model this functional after exchange functionals where
# for the closed shell scenario r=2*ra=2*rb and therefore
# Ex(ra,rb)=0.5*(Ex(2*ra)+Ex(2*rb))
#
f=c*sqrt((2*ra)*(2*rb))**a
print("Slater functional")
print("f(ra=rb) = ",simplify(f.subs(rb,ra)))
print("Functional = ",f)
print("Diff(ra)   = ",diff(f,ra))
print("Diff(rb)   = ",diff(f,rb))
#print("Diff(ra)   = ",simplify(diff(f,ra).subs(rb,ra)))
#
# Exchange functional
#
g=(c/2)*((2*ra)**a+(2*rb)**a)
print("")
print("Slater exchange functional")
print("g(ra=rb) = ",simplify(g.subs(rb,ra)))
print("Functional = ",g)
print("Diff(ra)   = ",diff(g,ra))
print("Diff(rb)   = ",diff(g,rb))

#print(simplify(simplify(g.subs(rb,ra)) - simplify(f.subs(rb,ra))))
#print(simplify(diff(g,ra) - diff(f,ra).subs(rb,ra)))
