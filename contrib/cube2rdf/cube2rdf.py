#!/bin/env python3
'''
Convert a .cube file to a charge vs. distance table

This script takes a .cube file, a position in space, and
an output file name. From the cube file the grid point positions
are generated and the charge at point is read. The distance 
between the grid point and the input position is calculated. 
A table of distance and charge is written to the output file.

This table can be used, for example, to generate a histogram
of charge vs distance, or a radial distribution function
of the charge.
'''

def parse_arguments():
    '''
    Parse the command line arguments

    Details on the actual command line arguments are on the line
    that defines the argument.
    '''
    from argparse import ArgumentParser
    prs = ArgumentParser()
    prs.add_argument("cubefn",help="The name of the cube file")
    prs.add_argument("position",help="The position of the reference point, e.g. \"0.0,0.0,0.0\"")
    prs.add_argument("rdffn",help="The name of the output file")
    args = prs.parse_args()
    return args

def read_cubefile(cubefn):
    '''
    Read a cube file and return a list of points and corresponding values.

    A cube file consists of the following data (http://paulbourke.net/dataformats/cube/):
    - two comment lines
    - a line with the number of atoms followed by the origin of the volumetric data
    - three lines each with the following information:
      - a number of grid points for a direction followed by a vector that specifies the direction
      - the sign of the number of grid points specifies the unit of distance
        - negative for Angstroms
        - positive for Bohr
    - the list of atoms with on each line:
      - the atom number
      - the atom charge
      - the atom position
    - the volumetric data looping fastest over Z, then Y, and finally X
    '''
    fp = open(cubefn,"r")
    # Skip comment lines
    fp.readline()
    fp.readline()
    line = fp.readline()
    list_ln = line.split()
    natom = int(list_ln[0])
    # fetch the origin
    o_x = float(list_ln[1])
    o_y = float(list_ln[2])
    o_z = float(list_ln[3])
    # get the number of grid points and the coordinate axes
    line = fp.readline()
    list_ln = line.split()
    nx = int(list_ln[0])
    vx_x = float(list_ln[1])
    vx_y = float(list_ln[2])
    vx_z = float(list_ln[3])
    line = fp.readline()
    list_ln = line.split()
    ny = int(list_ln[0])
    vy_x = float(list_ln[1])
    vy_y = float(list_ln[2])
    vy_z = float(list_ln[3])
    line = fp.readline()
    list_ln = line.split()
    nz = int(list_ln[0])
    vz_x = float(list_ln[1])
    vz_y = float(list_ln[2])
    vz_z = float(list_ln[3])
    # skip the atom data
    for iatom in range(0,natom):
        fp.readline()
    npts = nx*ny*nz
    nline = int((nz+5)/6)*ny*nz
    data = []
    for ii in range(0,nline):
        line = fp.readline()
        list_ln = line.split()
        for xt in list_ln:
            data.append(float(xt))
    lendata = len(data)
    if lendata != npts:
        print("# points: ",npts," # data: ",lendata,"?")
    result = []
    for ix in range(0,nx):
        for iy in range(0,ny):
            for iz in range(0,nz):
                px = o_x + ix*vx_x + iy*vy_x + iz*vz_x
                py = o_y + ix*vx_y + iy*vy_y + iz*vz_y
                pz = o_z + ix*vx_z + iy*vy_z + iz*vz_z
                ii = ix*ny*nz + iy*nz + iz
                pd = data[ii]
                result.append((px,py,pz,pd))
    fp.close()
    return result

def get_position(pos_str):
    '''
    Convert a position encoded in a string to a tuple
    '''
    pos_list = pos_str.split(',')
    px = float(pos_list[0])
    py = float(pos_list[1])
    pz = float(pos_list[2])
    return (px,py,pz)

def compute_rdf(position,cubedata):
    '''
    Take the cube data and the reference position, and return a list of distance and value
    '''
    import math
    rdf = []
    (px,py,pz) = position
    for ii in cubedata:
        (dx,dy,dz,dq) = ii
        rr = math.sqrt((px-dx)*(px-dx)+(py-dy)*(py-dy)+(pz-dz)*(pz-dz))
        rdf.append((rr,dq))
    return rdf

def write_rdffile(rdffile,data):
    '''
    Write the RDF data to a file
    '''
    fp = open(rdffile,'w')
    for ii in data:
        (rr,dq) = ii
        fp.write(f'{rr} {dq}\n')
    fp.close()

def execute_with_arguments(args):
    '''
    Execute the function of the script with the arguments provided.
    '''
    cubefile = args.cubefn
    position = args.position
    rdffile  = args.rdffn
    position = get_position(position)
    cubedata = read_cubefile(cubefile)
    rdfdata  = compute_rdf(position,cubedata)
    write_rdffile(rdffile,rdfdata)

def main():
    '''
    The main function
    '''
    execute_with_arguments(parse_arguments())

if __name__ == "__main__":
    main()
