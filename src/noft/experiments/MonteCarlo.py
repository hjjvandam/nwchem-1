import numpy as np
import sys
import os
'''
Monte Carlo optimizer

This code uses the Monte Carlo method to optimize a simple energy expression.
The method guesses steps in a box. When a step is successful (i.e. lowers the
energy) the step sizes are used to update the sides of the box. The update
is such that far from the goal the sides tend to grow. Close to the goal
they tend to shrink. 
Obviously, you could accidentally guess the right answer. In that case
it is very unlikely that a randomly selected step is going to improve the answer.
To deal with this scenario we globally shrink all sides of the box every 10 
consecutively failed attemps.
The algorithm terminates when all the sides of the box are smaller than a given
cutoff.
'''

def E(x):
    '''
    Energy expression

    This expression is simply a sum of parabola
    '''
    en = 0.0
    i = 0
    for xx in x:
       i += 1
       en += i*i * xx*xx
    return en

def rr(n,d):
    '''
    Randomly choose a vector of length n with values between -d and d
    '''
    x = 2*d*np.random.rand(n) - d*np.ones(n)
    return x

def rc(p):
    '''
    Choose a vector of length len(p) filled with random numbers between -p[j] and +p[j]
    '''
    n = len(p)
    x = np.random.rand(n)
    for ii in range(n):
        x[ii] = x[ii]*2.0*p[ii]-p[ii]
    return x

def max(p):
    '''
    Find the maximum value in p
    '''
    return np.max(p)

def update(p,s,a,b,c):
    '''
    Update p based on the step s according to

    p^{i+1} &=& p^i a + [ b (2 s - p^i) + c * p^i ] (1-a)
    '''
    n = len(p)
    pp = np.ones(n)
    for ii in range(n):
        pp[ii] = p[ii]*a + (b*(2.0*abs(s[ii])-p[ii])+c*p[ii])*(1.0-a)
        if pp[ii] < 1.0e-5:
            pp[ii] = 1.0e-5
    return pp

def scale(p,a):
    '''
    Scale p with factor a
    '''
    pp = a*p
    return pp


n = 10
p = np.ones(n)
m = p
x = 1000.0*np.ones(n)+rr(n,100.0)
e_x = E(x)
it = 0
print(str(os.get_terminal_size()))
fp = open("montecarlo_out","w")
text = f"{it:5d}   {e_x:18.8f}  "
for aa in p:
    text += f" {aa:12.6f}"
text += "  "
for aa in x:
    text += f" {aa:10.4f}"
text += "\n"
fp.write(text)
while max(p) > 1.0e-4:
    it += 1
    s = rc(p)
    xs = x + s
    e_xs = E(xs)
    #print(f"{str(it)} {str(e_xs)} {str(x)} {str(s)}")
    itt = 0
    while e_x <= e_xs:
        it += 1
        itt += 1
        s = rc(p)
        xs = x + s
        e_xs = E(xs)
        #print(f"{str(it)} {str(e_x)} {str(p)} {str(x)} {str(s)}")
        if itt % 10 == 0:
            p = scale(p,0.5)
            #print(f"{str(itt)} {str(e_x)} {str(p)} {str(x)} {str(s)}")
    p = update(p,s,0.9,2.0,1.5)
    m = np.maximum(m,p)
    x = xs
    e_x = e_xs
    #print(f"{str(it)}   {str(e_x)}   {str(p)}   {str(x)}   {str(s)}")
    #print(f"{str(it)}   {str(e_x)}   {str(p)}")
    #fp.write(str(it)+"   "+str(e_x)+"   "+str(p)+"\n")
    text = f"{it:5d}   {e_x:18.8f}  "
    for aa in p:
        text += f" {aa:12.6f}"
    text += "  "
    for aa in x:
        text += f" {aa:10.4f}"
    text += "\n"
    fp.write(text)
#print(f"{str(it)}   {str(m)}")
#fp.write(str(it)+"   "+str(m)+"\n")
text = f"{it:5d}   {e_x:18.8f}  "
for aa in m:
    text += f" {aa:12.6f}"
text += "\n"
fp.write(text)
fp.close()
