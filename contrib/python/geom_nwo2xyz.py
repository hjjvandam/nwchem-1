'''
Script to convert geometries as printed in the NWChem output
to the XYZ format.

For example for water it will convert (filename "h2o.nwo"):

    1 O                    8.0000     0.00000000     0.00000000     0.22140000
    2 H                    1.0000    -1.43000000     0.00000000    -0.88560000
    3 H                    1.0000     1.43000000     0.00000000    -0.88560000

Into (filename "h2o.xyz"):

    3

    O      0.00000000     0.00000000     0.22140000
    H     -1.43000000     0.00000000    -0.88560000
    H      1.43000000     0.00000000    -0.88560000

by running

	python3 geom_nwo2xyz.py h2o.nwo h2o.xyz
'''
import argparse

def parseargs():
    '''
    Parse the commandline arguments and return them
    '''
    parser = argparse.ArgumentParser(description="Convert NWChem output coordinates into an XYZ file")
    parser.add_argument("nwo_filename",help="The file with atomic coordinates in the NWChem output format")
    parser.add_argument("xyz_filename",help="The XYZ file")
    args = parser.parse_args()
    return args

def read_geom_nwo(filename):
    '''
    Read the entire NWChem coordinates file and return contents as a list of strings
    '''
    f = open(filename,"r")
    lines = f.readlines()
    f.close()
    return lines

def write_geom_xyz(filename,xyz_contents):
    '''
    Write the contents of the XYZ coordinates data
    '''
    f = open(filename,"w")
    f.writelines(xyz_contents)
    f.close()

def convert_coords(nwo_coords):
    '''
    Take the coordinates in the NWChem output format and return the contents of the corresponding XYZ file
    '''
    xyz_coords = []
    num_atoms = len(nwo_coords)
    line = f"{num_atoms}\n"
    xyz_coords.append(line)
    line = "\n"
    xyz_coords.append(line)
    for atom in nwo_coords:
        pieces = atom.split()
        #DEBUG
        print(pieces)
        #DEBUG
        line = f"{pieces[1]}  {pieces[3]}  {pieces[4]}  {pieces[5]}\n"
        xyz_coords.append(line)
    return xyz_coords

def convert(args):
    '''
    Do the conversion

    This action proceeds in 3 steps:
    - read the file with the structure in the NWChem output format
    - convert the lines
    - write the XYZ file
    '''
    nwo_coords = read_geom_nwo(args.nwo_filename)
    xyz_coords = convert_coords(nwo_coords)
    write_geom_xyz(args.xyz_filename,xyz_coords)

if __name__ == "__main__":
    args = parseargs()
    convert(args)
