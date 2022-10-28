#!/usr/bin/env python3
import argparse
import math

class Atom:
    """
    A simple atom class to deal with XYZ files

    An atom is an element at a particular position. So the class just
    needs space to store the chemical symbol and the Cartesian
    coordinates of the atom position.
    """
    symbol = ""
    x = 0.0
    y = 0.0
    z = 0.0

    def __init__(self,tuple):
        """
        A tuple containing atom information

        The tuple is expected to contain:
        - the chemical symbol
        - x-coordinate
        - y-coordinate
        - z-coordinate
        """
        (symbol,x,y,z) = tuple
        self.symbol = str(symbol)
        self.x = float(x)
        self.y = float(y)
        self.z = float(z)

def distance(a,b):
     """
     Calculate the distance between atoms A and B

     :param a: the first atom
     :type  a: Atom
     :param b: the second atom
     :type  b: Atom
     :return: The distance between atoms A and B
     """
     dx = a.x - b.x
     dy = a.y - b.y
     dz = a.z - b.z
     d2 = dx*dx + dy*dy + dz*dz
     return math.sqrt(d2)

def read_xyz(file):
    """
    Read an XYZ file just returning the molecular structure

    An XYZ file has the following structure:
    - the first line gives the number of atoms natom
    - the second line is a comment
    - the following natom lines specify elements and atomic positions
    This function reads the XYZ file and just return a list of natom
    line specifying the atomic positions.

    :param file: a string containing the XYZ file filename.
    :return: the list of atoms contained in the XYZ file.
    """
    f = open(file)
    atoms = []
    line = f.readline()
    natoms = int(line.split()[0])
    line = f.readline()
    for ii in range(0, natoms):
        line = f.readline()
        fields = line.split()
        symbol = fields[0]
        x = float(fields[1])
        y = float(fields[2])
        z = float(fields[3])
        atoms.append(Atom((symbol,x,y,z)))
    f.close()
    return atoms

def write_xyz(file,atoms):
    """
    Write an XYZ file for the given atoms

    :param file: the name of the XYZ file
    :type  file: string
    :param atoms: the list of atoms
    :type  atoms: list of Atom
    """
    f = open(file,"w")
    natoms = len(atoms)
    f.write(f"{natoms}\n\n")
    for atom in atoms:
        symbol = atom.symbol
        x = atom.x
        y = atom.y
        z = atom.z
        f.write(f"{symbol} {x} {y} {z}\n")
    f.close()
    
def select_near_atoms(atom_list,position,cutoff):
    """
    Select the atoms near a specified point

    Loop of the list of atoms and copy all atoms within the distance
    cutoff from the atom specified in position to the result list.
    The result list is returned.

    :param atom_list: The list of atoms from the XYZ file
    :type  atom_list: list of Atom
    :param position:  The reference position specified as an Atom object
    :type  position:  Atom
    :param cutoff: The distance cutoff for selecting atoms
    :type  cutoff: float
    """
    outlist = []
    for atom in atom_list:
        dist = distance(atom,position)
        if (dist < cutoff):
            outlist.append(atom)
    return outlist

def ref_position(textin):
    """
    Take the reference position given as text and return an Atom
    """
    text = textin.split()
    if len(text) != 3:
        raise Exception("Three coordinates are needed to specify a position")
    x = float(text[0])
    y = float(text[1])
    z = float(text[2])
    return Atom(("",x,y,z))

def commandline():
    parser = argparse.ArgumentParser(
        description="Select atoms from an XYZ file based on a distance criterion",
        prog="select-atoms.py",
        epilog="big things have small beginnings")
    parser.add_argument('--infile',dest="file_in",help="the input XYZ file")
    parser.add_argument('--outfile',dest="file_out",help="the resulting XYZ file")
    parser.add_argument('--distance',dest="distance",help="the distance cutoff",type=float)
    parser.add_argument('--position',dest="refpos",help="the reference position given as \"x y z\"")
    return parser.parse_args()

if __name__ == "__main__":
    args = commandline()
    position = ref_position(args.refpos)
    inlist = read_xyz(args.file_in)
    outlist = select_near_atoms(inlist,position,args.distance)
    write_xyz(args.file_out,outlist)
