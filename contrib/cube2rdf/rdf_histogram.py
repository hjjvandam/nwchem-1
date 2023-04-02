#!/bin/env python3
'''
A script to generate a histogram of RDF data

The radial distribution function (RDF) data lives in a file
and consists of two columns. The first column lists the
distance, and the second column lists a function value at
that distance. 

This script generates a histogram by binning the distance 
values and calculating the bar height as a sum of function
values in that bin.
'''
import numpy
import matplotlib
import matplotlib.pyplot

def parse_arguments():
    '''
    Parse the command line arguments.

    The only command line argument for this script is the
    filename for the RDF data.
    '''
    from argparse import ArgumentParser
    prs = ArgumentParser()
    prs.add_argument("rdffn",help="The name of the radial distribution function data file")
    args = prs.parse_args()
    return args 

def read_rdffile(rdffn):
    '''
    Read the RDF file and return a tuple of lists.

    The return value consist of a tuple of lists (R,F).
    The list R contains the values for distance.
    The list F contains function values such that F[i] == f(R[i])
    for some function f. 
    Strictly speak f is not a function because the original function
    is f(x,y,z) which has been mapped to a distance metric f(r). As
    a result it is possible to have multiple values of f for the same r,
    which strictly speaking makes that f is not a function.
    '''
    R = []
    F = []
    with open(rdffn,'r') as file:
        for line in file:
            ln_list = line.split()
            R.append(float(ln_list[0]))
            F.append(float(ln_list[1]))
    return (R,F)

def draw_histogram(R,F):
    '''
    Given a list of radii and corresponding weights generate and draw a
    histogram.

    To generate and draw the histogram Numpy and Matplotlib are used.
    '''
    npr = numpy.array(R)
    npf = numpy.array(F)
    matplotlib.pyplot.hist(npr,200,weights=npf)
    matplotlib.pyplot.show()

if __name__ == "__main__":
    args = parse_arguments()
    (R,F) = read_rdffile(args.rdffn)
    draw_histogram(R,F)
