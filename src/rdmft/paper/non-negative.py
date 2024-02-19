#!/usr/bin/env python

def akk(n):
    return n

def all(m):
    return m

def akl(n,m,c,x):
    return c*((n*(1.0-n)*m*(1.0-m))**x)

def b(n,m,c,x):
    return (all(m)-akk(n))/(2.0*akl(n,m,c,x))

def sign(x):
    if   x < 0:
        return -1
    elif x > 0:
        return  1
    else:
        return  0

def t(n,m,c,x):
    v = b(n,m,c,x)
    return sign(v)/(abs(v)+(v*v+1.0)**0.5)

def bkk_ll(n,m,c,x):
    vv = t(n,m,c,x)*akl(n,m,c,x)
    return (akk(n) - vv, all(m) + vv)

val = [0.0001, 0.001, 0.01, 0.1, 0.4, 0.49, 0.499, 0.5, 0.9, 0.99, 0.999]
vals = []
num = len(val)
for ii in range(0, num):
    for jj in range(0, ii+1):
        n = val[ii]
        m = val[jj]
        vals.append((n,m))

for ii in vals:
    n, m = ii
    #
    # Just change x at c=1
    bn, bm = bkk_ll(n,m,1.0,0.5)
    #bn, bm = bkk_ll(n,m,1.0,0.49975)
    #bn, bm = bkk_ll(n,m,1.0,0.49951)
    #bn, bm = bkk_ll(n,m,1.0,0.49902)
    #bn, bm = bkk_ll(n,m,1.0,0.49804)
    #bn, bm = bkk_ll(n,m,1.0,0.49609)
    #bn, bm = bkk_ll(n,m,1.0,0.49218)
    #bn, bm = bkk_ll(n,m,1.0,0.48437)
    #bn, bm = bkk_ll(n,m,1.0,0.46875)
    #bn, bm = bkk_ll(n,m,1.0,0.4370)
    #bn, bm = bkk_ll(n,m,1.0,0.375)
    #bn, bm = bkk_ll(n,m,1.0,0.25)
    #
    # Just change c at x=1/2
    bn, bm = bkk_ll(n,m,1.0,0.5)
    #bn, bm = bkk_ll(n,m,1.01562,0.5)
    #bn, bm = bkk_ll(n,m,1.03125,0.5)
    #bn, bm = bkk_ll(n,m,1.0625,0.5)
    #bn, bm = bkk_ll(n,m,1.125,0.5)
    #bn, bm = bkk_ll(n,m,1.25,0.5)
    #bn, bm = bkk_ll(n,m,1.5,0.5)
    #bn, bm = bkk_ll(n,m,2.0,0.5)
    #
    # Conclusion of the above two experiments:
    # - The density matrix is only non-negative if
    #   x >= 0.5 and c <= 1
    #
    # Try if at x=0.25 we can make the density matrix
    # non-negative by lowering c.
    #bn, bm = bkk_ll(n,m,1.0,0.25)
    #bn, bm = bkk_ll(n,m,0.1,0.25)
    #bn, bm = bkk_ll(n,m,0.055,0.25)
    #bn, bm = bkk_ll(n,m,0.0325,0.25)
    #bn, bm = bkk_ll(n,m,0.02125,0.25)
    #bn, bm = bkk_ll(n,m,0.01843,0.25)
    #bn, bm = bkk_ll(n,m,0.01807,0.25)
    #bn, bm = bkk_ll(n,m,0.01789,0.25)
    #bn, bm = bkk_ll(n,m,0.01780,0.25)
    bn, bm = bkk_ll(n,m,0.01776,0.25)
    #bn, bm = bkk_ll(n,m,0.01772,0.25)
    #bn, bm = bkk_ll(n,m,0.01702,0.25)
    #bn, bm = bkk_ll(n,m,0.01562,0.25)
    #bn, bm = bkk_ll(n,m,0.01,0.25)
    #
    # Conclusion of the above experiment:
    # - If x=0.25 then the density matrix is non-negative
    #   if c <= 0.01776
    #
    # Try if at x=0.75 we can keep the density matrix
    # non-negative while increasing c.
    #bn, bm = bkk_ll(n,m,4.0,0.75)
    #bn, bm = bkk_ll(n,m,3.75,0.75)
    #bn, bm = bkk_ll(n,m,3.625,0.75)
    #bn, bm = bkk_ll(n,m,3.5625,0.75)
    #bn, bm = bkk_ll(n,m,3.55468,0.75)
    #bn, bm = bkk_ll(n,m,3.55077,0.75)
    #bn, bm = bkk_ll(n,m,3.54979,0.75)
    #bn, bm = bkk_ll(n,m,3.54972,0.75)
    #bn, bm = bkk_ll(n,m,3.54969,0.75)
    bn, bm = bkk_ll(n,m,3.54967,0.75)
    #bn, bm = bkk_ll(n,m,3.54966,0.75)
    #bn, bm = bkk_ll(n,m,3.54954,0.75)
    #bn, bm = bkk_ll(n,m,3.54930,0.75)
    #bn, bm = bkk_ll(n,m,3.54882,0.75)
    #bn, bm = bkk_ll(n,m,3.54687,0.75)
    #bn, bm = bkk_ll(n,m,3.53125,0.75)
    #bn, bm = bkk_ll(n,m,3.5,0.75)
    #bn, bm = bkk_ll(n,m,3.0,0.75)
    #bn, bm = bkk_ll(n,m,2.0,0.75)
    #bn, bm = bkk_ll(n,m,1.0,0.75)
    #
    # Conclusion: if x=0.75 then c should be
    # c <= 3.54967 for the density matrix to be 
    # non-negative
    #
    # Try if at x=1.00 we can keep the density matrix
    # non-negative while increasing c.
    #bn, bm = bkk_ll(n,m,14.0,1.00)
    #bn, bm = bkk_ll(n,m,10.5,1.00)
    #bn, bm = bkk_ll(n,m,8.75,1.00)
    #bn, bm = bkk_ll(n,m,7.875,1.00)
    #bn, bm = bkk_ll(n,m,7.4375,1.00)
    #bn, bm = bkk_ll(n,m,7.38281,1.00)
    #bn, bm = bkk_ll(n,m,7.38195,1.00)
    #bn, bm = bkk_ll(n,m,7.38173,1.00)
    #bn, bm = bkk_ll(n,m,7.38162,1.00)
    bn, bm = bkk_ll(n,m,7.38157,1.00)
    #bn, bm = bkk_ll(n,m,7.38152,1.00)
    #bn, bm = bkk_ll(n,m,7.38110,1.00)
    #bn, bm = bkk_ll(n,m,7.37939,1.00)
    #bn, bm = bkk_ll(n,m,7.37597,1.00)
    #bn, bm = bkk_ll(n,m,7.36913,1.00)
    #bn, bm = bkk_ll(n,m,7.35546,1.00)
    #bn, bm = bkk_ll(n,m,7.32812,1.00)
    #bn, bm = bkk_ll(n,m,7.21875,1.00)
    #bn, bm = bkk_ll(n,m,7.0,1.00)
    #bn, bm = bkk_ll(n,m,3.5,1.00)
    #
    # Conclusion: if x=1.0 then c<=7.38157 for the density
    # matrix to be non-negative
    
    print(f'{n:.4f} {m:.4f}   {bn:.6f} {bm:.6f}')
