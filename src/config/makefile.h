# $Id: makefile.h,v 1.219 1997-03-14 21:13:09 d3e129 Exp $

# Common definitions for all makefiles ... these can be overridden
# either in each makefile by putting additional definitions below the
# include statement, or on the command line

#
# TOPDIR points to your top-level directory that contains 
# src, lib, config, ... (SRCDIR, etc., are derived from TOPDIR)
# Do a setenv for NWCHEM_TOP to be the top level directory
#

ifndef NWCHEM_TOP
error1:
	@echo You must define NWCHEM_TOP in your environment to be the path
	@echo of the top level nwchem directory ... something like
	@echo     setenv NWCHEM_TOP /msrc/home/elvis/nwchem
	@exit 1
endif

#
# Do a setenv for NWCHEM_TARGET to be the machine you wish to build for
# (one of SUN, DELTA, IBM, KSR, PARAGON, CRAY-T3D, DECOSF)
#

ifndef NWCHEM_TARGET
error2:
	@echo You must define NWCHEM_TARGET in your environment to be the name
	@echo of the machine you wish to build for ... for example
	@echo     setenv NWCHEM_TARGET SUN
	@echo Known targets are SUN, DELTA, ...
	@exit 1
endif

     TARGET = $(NWCHEM_TARGET)
     TOPDIR = $(NWCHEM_TOP)

     SRCDIR = $(TOPDIR)/src
     LIBDIR = $(TOPDIR)/lib/$(TARGET)
     BINDIR = $(TOPDIR)/bin/$(TARGET)
     INCDIR = $(TOPDIR)/src/include
     CNFDIR = $(TOPDIR)/src/config

#
# Define LIBPATH to be paths for libraries that you are linking in
# from precompiled sources and are not building now. These libraries
# will be searched AFTER anything you are building now.
# e.g. LIBPATH = -L/msrc/proj/mss/lib
#
    LIBPATH = 

#
# Define INCPATH to be directories to get includes for
# libraries that you are not building now.  These directories
# will be searched AFTER anything you are building now.
#
    INCPATH = 

# These subdirectories will build the core, or supporting libraries
# that are required by all NWChem modules.  The include directory is
# first to insure that all include files will be properly installed
# prior to trying to compile anything.
#
# The core libraries are usually rather platform-dependent and are
# specified below.  Use of MPI requires substituting the tcgmsg-mpi
# wrapper for the normal tcgmsg library.

ifdef USE_MPI
NW_CORE_SUBDIRS = include basis geom global inp input chemio \
	ma pstat rtdb tcgmsg-mpi task symmetry util $(CORE_SUBDIRS_EXTRA)
else
NW_CORE_SUBDIRS = include basis geom global inp input chemio \
	ma pstat rtdb tcgmsg task symmetry util $(CORE_SUBDIRS_EXTRA)
endif

# Include the modules to build defined by 'make nwchem_config' at top level


include $(CNFDIR)/nwchem_config.h

# Finally, we can set the full list of interesting directories, which
# is what most makefile will care about.

NWSUBDIRS = $(NW_CORE_SUBDIRS) $(NW_MODULE_SUBDIRS)

##########################################################
#                                                        #
# Should NOT need to modify below here unless porting to #
# a new machine or changing compiler options             #
#                                                        #
##########################################################

# Only the SUN, SGI, KSR, PARAGON, DELTA and IBM versions are up to date

# Each machine dependent section should define the following as necessary.
# (defaults if any in parentheses)
#
#         FC = path to Fortran compiler (f77)
#         CC = path to ANSI C compiler (cc)
#         AS = path to the assembler (as)
#         AR = path to archive builder (ar)
#        CPP = path to ANSI-like C preprocessor (cpp)
#     RANLIB = path to ranlib or something harmless if not required
#      SHELL = path to the Bourne Shell
#       MAKE = DON'T define this ... it will break the passing of command
#              arguments.  Simply use the correct path to GNU make on the 
#              command line and all will work just dandy.
#  MAKEFLAGS = options to GNU make ... -j controls no. of threads used
#              for parallel builds. --no-print-directory says be quiet about
#              changing directory.
#    INSTALL = command to install an executable when it is built
#    
# C/FOPTIONS = essential compiler options independent of optimization level
#              C/FOPTIONS should not usually be overridden on the command line
#   C/FDEBUG = compiler flags to enable enable debugging and used for
#              all routines not vital for performance (OBJ in makelib.h)
#C/FOPTIMIZE = compiler flags to enable optimization for important routines.
#              (OBJ_OPTIMIZE in makelib.h)
#
#              C/FDEBUG and C/FOPTIMIZE can be overridden on the command 
#              line to change the optimization level for routines normally 
#              compiled with them.
#
#  EXPLICITF = undefined if the Fortran compiler runs .F files thru .f
#              Otherwise set it to anything and define FCONVERT to be a 
#              command to make $< (which will be a .F file) into $*.f
#
#   FCONVERT = command to convert a .F into a .f 
#
#  LDOPTIONS = additional options to be passed to the linker (LDFLAGS is
#              built from this and the library path info).  LDOPTIONS is
#              the best way to add to the link command.
#
#    ARFLAGS = options for AR (ru)
#
#    DEFINES = C preprocessor defines for both C and Fortran
#
#  CORE_LIBS = List of libraries and paths for libraries in addition 
#              to the LIBDIR and LIBPATH options.
#
# CORE_SUBDIRS_EXTRA = List of additional directories (e.g., BLAS) that
#                 are needed on this machine.
# MODULE_SUBDIRS_EXTRA = List of additional directories (e.g., stepper) that
#                 are needed for top-level modules on this machine.
#		  (Should not normally be used)
#
# SCRATCH_DEF_DIR = Site specific default directory for scratch files
# PERM__DEF_DIR   = Site specific default directory for permanent files
#
# The following are defined for all machines at the bottom of this file
#
#   C/FFLAGS = all options to the C/Fortran compilers (note CPPFLAGS are 
#              separate).  These comprise C/FOPTIONS and C/FOPT.
#   INCLUDES = C preprocessor include paths for both C and Fortran.
#              In princpile this could be machine dependent but is not yet.
#   CPPFLAGS = options to C preprocessor that both C and Fortran will use.
#              This comprises the includes and defines.
#    LDFLAGS = options for the linker.  Currently paths from LIBDIR and
#              LIBPATH.
#
# NWCHEM_TARGET_CPU environment variable is used to select optimal compiler flag
# values R10000 and R8000 are currently recognized under SGITFP and SGI_N32 (JN)
#


#
# Establish some required defaults which may need overriding
# for some machines

           SHELL = /bin/sh
         ARFLAGS = r
          FDEBUG = -g
          CDEBUG = -g
              AR = ar

ifndef SCRATCH_DEF_DIR
 SCRATCH_DEF_DIR = "'.'"
endif
ifndef PERM_DEF_DIR
 PERM_DEF_DIR   = "'.'"
endif

#
# Machine specific stuff
#

ifeq ($(TARGET),SUN)
#
# Sun running SunOS
#

       NICE = nice
      SHELL := $(NICE) /bin/sh
    CORE_SUBDIRS_EXTRA = blas lapack
         CC = gcc
     RANLIB = ranlib
  MAKEFLAGS = -j 1 --no-print-directory
    INSTALL = @echo $@ is built

   FOPTIONS = -Nl199 -fast -dalign
   COPTIONS = -Wall
# -O4 breaks at least inp_* and seems no faster than -O3
  FOPTIMIZE = -O3
  COPTIMIZE = -g -O2

    DEFINES = -DSUN

       CORE_LIBS =  -lutil -lchemio -lglobal -llapack -lblas
endif

ifeq ($(TARGET),SOLARIS)
#
# Sun runningS olaris 2.4 or later
# if you want to use purecoverage tool you must
#
# setenv PURECOV 1
# FLINT = 1
#
      SHELL := $(NICE) /bin/sh
    CORE_SUBDIRS_EXTRA = blas lapack
	CPP = /usr/ccs/lib/cpp
         CC = gcc
     RANLIB = echo
  MAKEFLAGS = -j 2 --no-print-directory
    INSTALL = echo $@ is built
# -fast introduces many options that must be applied to all files
# -stackvar puts locals on the stack which seems a good thing
#     but may need to increase the stacksize at runtime using limit
# -xs allows debugging without .o files
   FOPTIONS = -Nl199 -fast -dalign -stackvar
   COPTIONS = -Wall
# Under Solaris -O3 is the default with -fast (was -O2 with SUNOS)
# -fsimple=2 enables more rearranging of floating point expressions
# -depend enables more loop restructuring
  FOPTIMIZE = -O3 -fsimple=2 -depend 
# Under Solaris -g no longer disables optimization ... -O2 seems solid
# but is slow and impairs debug ... use -O1 for speed and debugability
     FDEBUG = -g -O1
  COPTIMIZE = -g -O2
   LIBPATH += -L/usr/ucblib
    DEFINES = -DSOLARIS

  LDOPTIONS = -xildoff

       CORE_LIBS = -lutil -lchemio -lglobal -llapack -lblas
# First four needed for parallel stuff, last for linking with profiling
      EXTRA_LIBS = -lsocket -lrpcsvc -lnsl -lucb -ldl

ifdef PURECOV
#
# Sun running Solaris 2.4 or later
#
      SHELL := $(NICE) /bin/sh
    CORE_SUBDIRS_EXTRA = blas lapack
         CC = purecov gcc
         FC = purecov f77
     RANLIB = echo
  MAKEFLAGS = -j 2 --no-print-directory
    INSTALL = echo $@ is built
# -fast introduces many options that must be applied to all files
# -stackvar puts locals on t
# the stack which seems a good thing
#     but may need to increase the stacksize at runtime using limit
# -xs allows debugging without .o files
   FOPTIONS = -Nl199 -fast -dalign -stackvar
   COPTIONS = -Wall
# Under Solaris -O3 is the default with -fast (was -O2 with SUNOS)
# -fsimple=2 enables more rearranging of floating point expressions
# -depend enables more loop restructuring
  FOPTIMIZE = -O3 -fsimple=2 -depend 
# Under Solaris -g no longer disables optimization ... -O2 seems solid
# but is slow and impairs debug ... use -O1 for speed and debugability
     FDEBUG = -g -O1
  COPTIMIZE = -g -O1
   LIBPATH += -L/usr/ucblib
   LIBPATH += -L/afs/msrc/sun4m_54/apps/purecov
   DEFINES = -DSOLARIS
   OPTIONS = -xildoff -Bstatic
   CORE_LIBS = -lutil -lglobal -llapack -lblas
# First four needed for parallel stuff, last for linking with profiling
	   EXTRA_LIBS = -lsocket -lrpcsvc -lnsl -lucb -lintl -lc -lc -lpurecov_stubs

#end of purecov
endif


#end of solaris
endif


ifeq ($(TARGET),CRAY-T3D)
#
# CRAY-T3D cross-compiled on YMP (atw)
#
   CORE_SUBDIRS_EXTRA =	blas lapack # Only a couple of routines not in scilib
               RANLIB = echo
            MAKEFLAGS = -j 4 --no-print-directory
              INSTALL = @echo $@ is built
        OUTPUT_OPTION = 

                   FC = cf77 
                  CPP = cpp -P  -N
#                   FC = /mpp/bin/cf77 
#                  CPP = /mpp/lib/cpp -P  -N
# gpp does not eat elif
#                 CPP = /usr/lib/gpp -P  -F
# need jump since with all modules code is too big for branches
# noieeedivide seems safe and should be faster
             FOPTIONS = -dp -Ccray-t3d 
             COPTIONS = -Tcray-t3d -hjump
# To make executable smaller use scalar optimization and no -g on all code.
# symmetry/(dosymops.F,sym_movecs_apply_op) break with scalar
# (it is handled separately in symmetry/makefile)
# !! Note that -O option disables any -Wf"-o options" but we need
# !! jump so cannot use -O.
               FDEBUG = -Wf"-o scalar,jump,noieeedivide"
# Not sure yet if these are fully safe ... aggress,unroll
            FOPTIMIZE = -Wf"-o scalar,jump,noieeedivide,aggress,unroll"
               CDEBUG = -O 1
            COPTIMIZE = -O
# -s eliminates symbol tables to make executable smaller (remove -s
# if you want to debug) ... the T3 does load the symbol table (stupid!)
# No need for forcing of block data here as long as each one is
# referenced by an external statement in the code.
            LDOPTIONS = -s -Drdahead=on -L$(LIBDIR) 

# Compilation also depends on compilers defining CRAY
              DEFINES = -DCRAY_T3D -DPARALLEL_DIAG

#               LINK.f = /mpp/bin/mppldr $(LDOPTIONS)
               LINK.f = mppldr $(LDOPTIONS)

            CORE_LIBS =  -lutil -lchemio -lglobal -lpeigs -llapack -lblas

      EXPLICITF     = TRUE
      FCONVERT      = $(CPP) $(CPPFLAGS)  $< | sed '/^\#/D'  > $*.f
endif


ifeq ($(TARGET),CRAY-T3E)
#
#
   CORE_SUBDIRS_EXTRA =	blas lapack # Only a couple of routines not in scilib
               RANLIB = echo
            MAKEFLAGS = -j 1 --no-print-directory
              INSTALL = @echo $@ is built
        OUTPUT_OPTION = 

                   FC = f90 
                  CPP = cpp -P  -N
             FOPTIONS = -d p -F  
             COPTIONS = 
               FDEBUG = -O scalar1
            FOPTIMIZE = -O scalar3,aggress,unroll2
               CDEBUG = -O 1
            COPTIMIZE = -O
            LDOPTIONS = -L$(LIBDIR) 

              DEFINES = -DCRAY_T3E -DCRAY_T3D -D__F90__

               LINK.f = f90 $(LDOPTIONS)

            CORE_LIBS = -lutil -lchemio -lglobal -llapack -lblas

      FCONVERT      = $(CPP) $(CPPFLAGS)  $< | sed '/^\#/D'  > $*.f
      EXPLICITF     = TRUE
endif

ifeq ($(TARGET),KSR)
#
# KSR running OSF
#
# JN 96/10/02:
# Replaced -DLongInteger with -DEXT_INT for consistency with GA, DRA, PEIGS ...

    CORE_SUBDIRS_EXTRA = blas
     RANLIB = echo
  MAKEFLAGS = -j 10 --no-print-directory
    INSTALL = @echo $@ is built

   FOPTIONS = -r8
   COPTIONS = 
  FOPTIMIZE = -xfpu3 -O1
  COPTIMIZE = -xfpu3 -O1

    DEFINES = -DKSR -DPARALLEL_DIAG -DEXT_INT

#       LIBPATH += -L/home/d3g681/TCGMSG_DISTRIB
        LIBPATH += -L/home2/d3g270/peigs1.1.1 -L/home/d3g681/TCGMSG_DISTRIB
       CORE_LIBS = -lglobal -lutil -lchemio -lpeigs \
                   -lksrlapk -lksrblas -llapack2 -lblas2  
      EXTRA_LIBS = -para -lrpc
endif

ifeq ($(TARGET),PARAGON)
#
# Intel Paragon running OSF
# (native build, or cross-compiled -- the latter is faster in most cases)
#
    CORE_SUBDIRS_EXTRA = lapack

         FC = if77
         CC = icc
         AR = ar860
     RANLIB = echo

  MAKEFLAGS = -j 4  --no-print-directory
    INSTALL = @echo $@ is built

  FOPTIONS = -Knoieee
  COPTIONS = -Knoieee
 FOPTIMIZE = -O2 -Minline=1000
FVECTORIZE = -O2 -Minline=1000 # -Mvect
 COPTIMIZE = -O2

#
# __PARAGON__ is defined by the PGI cpp, but NOT when it is invoked by
# the f77 comiler!!!
#
# Do NOT define -DNX or -DIPSC for paragon -- they get into some code for
# real iPSC and Delta that is not applicable to the paragon, which is more
# unixy since it runs OSF/1.
#
    DEFINES = -D__PARAGON__ -DPARALLEL_DIAG
    ARFLAGS = ru

# CAUTION: PGI's linker thinks of -L as adding to the _beginning_ of the
# search path -- contrary to usual unix usage!!!!!
       LIBPATH  += -L/home/delilah11/gifann/lib
       CORE_LIBS = -lglobal -lchemio -lutil \
	           -lpeigs_paragon -llapack $(LIBDIR)/liblapack.a -lkmath 
      EXTRA_LIBS = -nx
endif

ifeq ($(TARGET),DELTA)
#
# DELTA/IPSC running NX
#
    CORE_SUBDIRS_EXTRA = lapack blas # -lkamth not reliable
# blas
        FC = if77
        CC = icc
       CPP = /usr/lib/cpp
        AR = ar860
    RANLIB = echo

   INSTALL = "strip860 $(BINDIR)/nwchem; rcp $(BINDIR)/nwchem delta1:"
 MAKEFLAGS = -j 2  --no-print-directory

  FOPTIONS = -Knoieee
  COPTIONS = -Knoieee
 FOPTIMIZE = -O2 		# -Minline=1000 ## Inlining bombs for dtrtri.f
FVECTORIZE = -O4 		# -Mvect corrupts lapack for large vectors
 COPTIMIZE = -O2

   DEFINES = -DNX -DDELTA -DIPSC -DNO_BCOPY  -D__IPSC__ -DPARALLEL_DIAG
        LIBPATH += -L/home/delilah11/gifann/lib
       CORE_LIBS = -lglobal -lutil -lchemio -lglobal -lpeigs_delta \
		   $(LIBDIR)/liblapack.a -llapack -lblas
      EXTRA_LIBS = -node
endif


ifeq ($(TARGET),SGITFP)
#
# SGI power challenge
#
# CORE_SUBDIRS_EXTRA are those machine specific libraries required 
#
# TPS 95/11/22:
# Optimization options const_copy_limit=18000, global_limit=18000 and 
# fprop_limit=1200 added to FOPTIMIZE to allow full optimization of the 
# MD module nwArgos on SGI Power Indigo^2
#
# RJH ... note that fprop_limit is not supported by 7.0 compilers
#
# TPS 95/12/12:
# Increased fprop_limit to 1750
# Removed -j 12 from MAKEFLAGS
# Added -lutil to core libraries
#
# TPS 96/01/14:
# Increased const_copy_limit and global_limit to 18500
#
# RJH ... from Roberto ... on the R10k TENV=3 may cause very expensive
#     interrupts (he recommends 1 when we go to 10K, but 3 is good for 8k)
#     ... also going to 10K use -SWP:if_conversion=OFF
#     ... in going to 6.1/2 then should also set -SWP:*ivdep*=ON/OFF
#         (default changed from agressive to conservative and we want
#         the agressive)
#     ... sometimes the default KAP parameters are best (only for critical
#         routines)
#     ... -dr=AKC forces it to recognize all compiler directives (C=CRAY
#         not on by default) ... can put everywhere.
#     ... on -WK also add -r=3 (level of reduction) even with -o=1
#     ... could benefit from -Wk on FOPTIMIZE ... actually have it on now.
#     ... roundoff/ieee only modify pipelining which happens only at O3
#
# TPS 96/06/27:
# Added -lutil to core libraries (again!)
#
# TPS 96/07/26:
# Fortran optimization limits: const_copy_limit=20000 
#                              global_limit=20000
#                              fprop_limit=2000
#
# JN 96/10/02:
# Replaced -DLongInteger with -DEXT_INT for consistency with GA, DRA, PEIGS ...

	CPP = /usr/lib/cpp
  CORE_SUBDIRS_EXTRA = blas lapack
         FC = f77
     RANLIB = echo


    INSTALL = @echo nwchem is built
  MAKEFLAGS = --no-print-directory

  FOPTIONS = -d8 -i8 -mips4 -64 -r8 -G 0 -OPT:roundoff=3:IEEE_arithmetic=3
  COPTIONS = -fullwarn -mips4 

#optimization flags for R8000 (IP21)
 FOPTIMIZE_8K = -O3 -OPT:fold_arith_limit=4000:const_copy_limit=20000:global_limit=20000:fprop_limit=2000 -TENV:X=3 -WK,-so=1,-o=1,-r=3,-dr=AKC
FVECTORIZE_8K = -O3 -OPT:fold_arith_limit=4000 -TENV:X=3 -WK,-dr=AKC

#optimization flags for R10000 (IP28)
 FOPTIMIZE_10K = -O3 -OPT:fold_arith_limit=4000:const_copy_limit=20000:global_limit=20000:fprop_limit=2000 -TENV:X=1 -WK,-so=1,-o=1,-r=3,-dr=AKC -SWP:if_conversion=OFF
FVECTORIZE_10K = -O3 -OPT:fold_arith_limit=4000 -TENV:X=1 -WK,-dr=AKC -SWP:if_conversion=OFF

 COPTIMIZE = -O
 FOPTIMIZE = -O3

ifeq ($(NWCHEM_TARGET_CPU),R10000)
 FOPTIMIZE = $(FOPTIMIZE_10K)
 FVECTORIZE = $(FVECTORIZE_10K)
endif
ifeq ($(NWCHEM_TARGET_CPU),R8000)
 FOPTIMIZE = $(FOPTIMIZE_8K)
 FVECTORIZE = $(FVECTORIZE_8K)
endif

    DEFINES = -DSGI -DSGITFP -DEXT_INT
  CORE_LIBS = -lutil -lpeigs -lchemio -lglobal -llapack -lblas
endif


ifeq ($(TARGET),SGI)
#
# SGI normal (32-bit platform)
#
# CORE_SUBDIRS_EXTRA are those machine specific libraries required 
#
# JN 12/4/96: 
# removed -lblas from CORE_SUBDIRS_EXTRA and -lmalloc from the EXTRA_LIBS
# replaced -mips2 with -mips3
# On IRIX >= 6.1, SGI recomends using -n32 to utilize internal 64-bit
# registers (up to 50% better floating point performance over -32 flag) 

    CORE_SUBDIRS_EXTRA = lapack
         FC = f77
         AR = ar
     RANLIB = echo

    INSTALL = @echo nwchem is built
  MAKEFLAGS = -j 4 --no-print-directory
    DEFINES = -DSGI

  FOPTIONS = # -mips3
  COPTIONS =  -fullwarn #-mips3
 FOPTIMIZE = -O2
 COPTIMIZE = -O2

       CORE_LIBS = -lutil -lchemio -lglobal -llapack -lblas
#     EXTRA_LIBS = -lmalloc 
endif


ifeq ($(TARGET),SGI_N32)
#
# SGI 64-bit MIPS-4 processors (R5k, R8k, R10k) under IRIX > 6.0  (ABI)
#
# JN, 12.06.96:
# -n32 allows to use 64-bit processor features and 32-bit address space
# 32-bit address space - use SGITFP if 64-bit addresses needed
#
# SGI BLAS can be used directly

    CORE_SUBDIRS_EXTRA = lapack
         FC = f77
         AR = ar
     RANLIB = echo

    INSTALL = @echo nwchem is built
  MAKEFLAGS = -j 4 --no-print-directory
    DEFINES = -DSGI

  FOPTIONS = -n32 -mips4 -G 0 -OPT:roundoff=3:IEEE_arithmetic=3
  COPTIONS = -n32 -mips4 -fullwarn

#optimization flags for R8000 (IP21)
 FOPTIMIZE_8K = -O3 -OPT:fold_arith_limit=4000:const_copy_limit=20000:global_limit=20000:fprop_limit=2000 -TENV:X=3 -WK,-so=1,-o=1,-r=3,-dr=AKC
FVECTORIZE_8K = -O3 -OPT:fold_arith_limit=4000 -TENV:X=3 -WK,-dr=AKC

#optimization flags for R10000 (IP28)
 FOPTIMIZE_10K = -O3 -OPT:fold_arith_limit=4000:const_copy_limit=20000:global_limit=20000:fprop_limit=2000 -TENV:X=1 -WK,-so=1,-o=1,-r=3,-dr=AKC -SWP:if_conversion=OFF
FVECTORIZE_10K = -O3 -OPT:fold_arith_limit=4000 -TENV:X=1 -WK,-dr=AKC -SWP:if_conversion=OFF

 FOPTIMIZE = -O3
 COPTIMIZE = -O2

ifeq ($(NWCHEM_TARGET_CPU),R10000)
 FOPTIMIZE = $(FOPTIMIZE_10K)
 FVECTORIZE = $(FVECTORIZE_10K)
endif
ifeq ($(NWCHEM_TARGET_CPU),R8000)
 FOPTIMIZE = $(FOPTIMIZE_8K)
 FVECTORIZE = $(FVECTORIZE_8K)
endif

       CORE_LIBS = -lutil -lchemio -lglobal -llapack -lblas
endif



ifeq ($(TARGET),CONVEX-SPP)
#
# Convex SPP-1200 running SPP-UX 3.2
#

        CPP = /lib/cpp -P
         FC = fc

# -g is not recognized; 
# Convex debug flag -cxdb does not disable optimization 
     CDEBUG = -no
     FDEBUG = -no
   FOPTIONS = -ppu -or none
   COPTIONS = -or none
  FOPTIMIZE = -O1
  COPTIMIZE = -O


    DEFINES = -DCONVEX -DHPUX -DEXTNAME

# &%@~* Convex compiler will preprocess only *.f and *.FORT files !
  EXPLICITF = TRUE
   FCONVERT = $(CPP) $(CPPFLAGS) $< > $*.f
endif



ifeq ($(TARGET),IBM)
#
# IBM AIX
#

    CORE_SUBDIRS_EXTRA = lapack
#blas
         FC = xlf
    ARFLAGS = urs
     RANLIB = echo
  MAKEFLAGS = -j 1 --no-print-directory
    INSTALL = @echo $@ is built
        CPP = /usr/lib/cpp -P

   FOPTIONS = -qEXTNAME -qnosave -qalign=4k 
# -qinitauto=FF
   COPTIONS = 
# -qstrict required with -O3 (according to Edo)
# -qfloat=rsqrt gives faster square roots (off by -qstrict)
# -qfloat=fltint gives faster real-integer conversion (off by -qstrict)
# -qhot seems to break a lot of things so don't ever use it
# -qarch=pwr (for peril) com (for any) , pwr2  or ppc
  FOPTIMIZE = -O3 -qstrict -qfloat=rsqrt:fltint -NQ40000 -NT80000
  COPTIMIZE = -O

    DEFINES = -DIBM -DAIX -DEXTNAME
ifdef USE_ESSL
   DEFINES += -DESSL
endif

       LIBPATH += -L/usr/lib -L/msrc/apps/lib

       CORE_LIBS = -lglobal -lchemio -lutil -llapack -lblas \
	      -brename:.daxpy_,.daxpy \
	      -brename:.dcopy_,.dcopy \
	      -brename:.ddot_,.ddot \
	      -brename:.dgemm_,.dgemm \
	      -brename:.dgemv_,.dgemv \
	      -brename:.dgesv_,.dgesv \
	      -brename:.dgetrf_,.dgetrf \
	      -brename:.dgetrs_,.dgetrs \
	      -brename:.dlaset_,.dlaset \
	      -brename:.dpotrf_,.dpotrf \
	      -brename:.dpotri_,.dpotri \
	      -brename:.dscal_,.dscal \
	      -brename:.dspsvx_,.dspsvx \
	      -brename:.idamax_,.idamax \
	      -brename:.dswap_,.dswap \
	      -brename:.dger_,.dger \
	      -brename:.dtrsm_,.dtrsm \
              -brename:.dnrm2_,.dnrm2 \
              -brename:.dtrmm_,.dtrmm \
              -brename:.drot_,.drot \
              -brename:.dasum_,.dasum \
              -brename:.dtrmv_,.dtrmv \
              -brename:.dspmv_,.dspmv \
              -brename:.dspr_,.dspr \
              -brename:.dsyrk_,.dsyrk \
              -brename:.dsymm_,.dsymm \
              -brename:.dsyr2k_,.dsyr2k \
              -brename:.dsyr2_,.dsyr2 \
              -brename:.dtrsv_,.dtrsv \
              -brename:.dsymv_,.dsymv \
              -brename:.dznrm2_,.dznrm2 \
              -brename:.zaxpy_,.zaxpy \
              -brename:.zcopy_,.zcopy \
              -brename:.zdotc_,.zdotc \
              -brename:.zdscal_,.zdscal \
              -brename:.zgemm_,.zgemm \
              -brename:.zgemv_,.zgemv \
              -brename:.zgerc_,.zgerc \
              -brename:.zhemm_,.zhemm \
              -brename:.zhemv_,.zhemv \
              -brename:.zher2_,.zher2 \
              -brename:.zher2k_,.zher2k \
              -brename:.zherk_,.zherk \
              -brename:.zscal_,.zscal \
              -brename:.zswap_,.zswap \
              -brename:.ztrmm_,.ztrmm \
              -brename:.ztrmv_,.ztrmv \
              -brename:.ztrsm_,.ztrsm \
              -brename:.xerbla_,.xerbla \
              -brename:.ztrsv_,.ztrsv 
##comment out from dtrmm_ inclusive
#ifdef USE_ESSL
#       CORE_LIBS += -lessl
#endif

  EXPLICITF = TRUE
  FCONVERT = $(CPP) $(CPPFLAGS) $< > $*.f
#
endif


ifeq ($(TARGET),SP1)
#
    CORE_SUBDIRS_EXTRA = peigs lapack
         FC = mpxlf
# -F/u/d3g681/xlhpf.cfg:rjhxlf
         CC = mpcc
    ARFLAGS = urs
     RANLIB = echo
  MAKEFLAGS = -j 25 --no-print-directory
    INSTALL = @echo $@ is built
        CPP = /usr/lib/cpp -P

  LDOPTIONS = 
   FOPTIONS = -qEXTNAME -qnosave
   COPTIONS = 
  FOPTIMIZE = -O3 -qstrict -qfloat=rsqrt:fltint -NQ40000 -NT80000
  COPTIMIZE = -O
#ifdef P2SC
# These from George from Frank Johnson 
  FOPTIMIZE += -qcache=type=d:level=1:size=128:line=256:assoc=4:cost=14 \
        -qcache=type=i:level=1:size=32:line=128
  COPTIMIZE += -qcache=type=d:level=1:size=128:line=256:assoc=4:cost=14 \
        -qcache=type=i:level=1:size=32:line=128
#endif
    DEFINES = -DSP1 -DAIX -DEXTNAME -DPARALLEL_DIAG
#
# Prefix LIBPATH with -L/usr/lib for AIX 3.2.x
#
#  LIBPATH += -L/sphome/harrison/peigs2.0

  CORE_LIBS = -lglobal -lutil -lchemio -lpeigs -llapack

ifndef NOPIOFS
# see inside chemio/elio
  CORE_LIBS += -bI:/usr/lpp/piofs/include/piofs.exp
endif

   USE_ESSL = YES
ifdef USE_ESSL
   DEFINES += -DESSL
# renames not needed for 4.1.  Still are for 3.2.
 CORE_LIBS += -lessl -lpesslp2 -lblacsp2 -lesslp2
#	      -brename:.daxpy_,.daxpy \
#	      -brename:.dgesv_,.dgesv \
#	      -brename:.dcopy_,.dcopy \
#	      -brename:.ddot_,.ddot \
#	      -brename:.dgemm_,.dgemm \
#	      -brename:.dgemv_,.dgemv \
#	      -brename:.dgetrf_,.dgetrf \
#	      -brename:.dgetrs_,.dgetrs \
#	      -brename:.dscal_,.dscal \
#	      -brename:.dspsvx_,.dspsvx \
#	      -brename:.dpotrf_,.dpotrf \
#	      -brename:.dpotri_,.dpotri \
#	      -brename:.idamax_,.idamax 

else
    CORE_SUBDIRS_EXTRA += blas
             CORE_LIBS += -lblas
endif


# IMPORTANT:  These renames are necessary if you try to link against
# a copy of PeIGS built for MPI instead of TCGMSG. (Not recommended, 
# see INSTALL)
# mpipriv is a common block used in MPICH's implementation of MPI.  It
# is critical that this common block is renamed correctly because
# the linker will not detect any problems (there will be separate
# common blocks labeled mpipriv_ and mpipriv) but the program will not
# operate correctly.
#ifdef USE_MPI
#   CORE_LIBS += -brename:.mpi_recv_,.mpi_recv \
#		-brename:.mpi_initialized_,.mpi_initialized \
#		-brename:.mpi_init_,.mpi_init \
#		-brename:.mpi_comm_rank_,.mpi_comm_rank \
#		-brename:.mpi_comm_size_,.mpi_comm_size \
#		-brename:.mpi_finalize_,.mpi_finalize \
#		-brename:.mpi_send_,.mpi_send \
#		-brename:mpipriv_,mpipriv
#endif

 EXPLICITF = TRUE
  FCONVERT = $(CPP) $(CPPFLAGS) $< > $*.f
#
endif


ifeq ($(TARGET),DECOSF)
#
# DEC AXP OSF1
#
# JN 96/10/02:
# Replaced -DLongInteger with -DEXT_INT for consistency with GA, DRA, PEIGS ...

    CORE_SUBDIRS_EXTRA = blas lapack
                  NICE = nice
                SHELL := $(NICE) /bin/sh
                    FC = f77
                    AR = ar
                RANLIB = echo

               INSTALL = @echo nwchem is built
             MAKEFLAGS = -j 1 --no-print-directory

# -fpe2 and call to util/dec_fpe.f from nwchem.F necessary to avoid
# braindead alpha undflows inside texas (c6h6 6-31g)

              FOPTIONS = -i8 -assume noaccuracy_sensitive -align dcommons -math_library fast -fpe2 -check nounderflow
              COPTIONS = 
             FOPTIMIZE = -O 
             COPTIMIZE = -O

               DEFINES = -DDECOSF -DEXT_INT
             CORE_LIBS = -lutil -lchemio -lglobal -llapack -lblas
            EXTRA_LIBS = -laio -lpthreads 
endif

ifeq ($(TARGET),LINUX)
#
# Linux running on an x86 using f77 on f2c
# to use g77 instead f77/f2c, define USE_G77 environment variable
#
       NICE = nice
      SHELL := $(NICE) /bin/sh
    CORE_SUBDIRS_EXTRA = blas lapack
         CC = gcc
     RANLIB = ranlib
  MAKEFLAGS = -j 1 --no-print-directory
    INSTALL = @echo $@ is built

# JN: with g77 we do not need explicit preprocessing
ifdef USE_G77
  FOPTIONS  = -fno-second-underscore
         FC = g77
else
   FOPTIONS = -Nc40 -Nn2500
  EXPLICITF = TRUE
endif

   COPTIONS = -Wall -m486
  FOPTIMIZE = -g -O2
  COPTIMIZE = -g -O2

    DEFINES = -DLINUX

  LDOPTIONS = -g
     LINK.f = gcc $(LDFLAGS)
  CORE_LIBS = -lutil -lchemio -lglobal -llapack -lblas
 EXTRA_LIBS = -lf2c -lm

        CPP = gcc -E -nostdinc -undef -P
   FCONVERT = (/bin/cp $< /tmp/$$$$.c; \
			$(CPP) $(CPPFLAGS) /tmp/$$$$.c | sed '/^$$/d' > $*.f; \
			/bin/rm -f /tmp/$$$$.c) || exit 1
endif

###################################################################
#  All machine dependent sections should be above here, otherwise #
#  some of the definitions below will be 'lost'                   #
###################################################################


# MPI version requires tcgmsg-mpi library
ifdef USE_MPI
   ifdef MPI_LIB
       LIBPATH += -L$(MPI_LIB)
   endif
   CORE_LIBS += -ltcgmsg-mpi -lmpi 
else
   CORE_LIBS += -ltcgmsg
endif
CORE_LIBS += $(EXTRA_LIBS)


ifdef OPTIMIZE
    FFLAGS = $(FOPTIONS) $(FOPTIMIZE)
    CFLAGS =  $(COPTIONS) $(COPTIMIZE)
else
# Need FDEBUG after FOPTIONS on SOLARIS to correctly override optimization
    FFLAGS = $(FOPTIONS) $(FDEBUG) 
    CFLAGS = $(COPTIONS) $(CDEBUG) 
endif
  INCLUDES = -I. $(LIB_INCLUDES) -I$(INCDIR) $(INCPATH)
  CPPFLAGS = $(INCLUDES) $(DEFINES) $(LIB_DEFINES)
   LDFLAGS = $(LDOPTIONS) -L$(LIBDIR) $(LIBPATH)
      LIBS = $(NW_MODULE_LIBS) $(CORE_LIBS) 

# I think this will work everywhere, but it might have to become
# machine-dependent 

MKDIR = mkdir

#
# Define known suffixes mostly so that .p files don't cause pc to be invoked
#

.SUFFIXES:	
.SUFFIXES:	.o .s .F .f .c

ifndef FLINT

ifdef EXPLICITF
#
# Needed on machines where FCC does not preprocess .F files
# with CPP to get .f files
#
# These rules apply to make-ing of files in specfic directories
.SUFFIXES:	
.SUFFIXES:	.o .s .F .f .c

.F.o:	
	@echo Converting $*.F '->' $*.f
	@$(FCONVERT)
	$(FC) -c $(FFLAGS) $*.f
	@$(RM) $*.f

.F.f:
	@echo Converting $*.F '->' $*.f
	@$(FCONVERT)
.f.o:
	$(FC) -c $(FFLAGS) $<
endif
# 
# More explicit rules to avoid infinite recursion, to get dependencies, and
# for efficiency.  CRAY does not like -o with -c.
#
# These rules apply to make-ing of files in with respect to library files
# both these rules and the rules above are needed.
(%.o):	%.F
ifdef EXPLICITF
	@echo Converting $< '->' $*.f
	@$(FCONVERT)
	$(FC) -c $(FFLAGS) $*.f
ifndef NWCHEM_KEEPF
	@/bin/rm -f $*.f
endif
else
	$(FC) -c $(FFLAGS) $(CPPFLAGS) $<
endif

(%.o):	%.f
	$(FC) -c $(FFLAGS) $<

(%.o):	%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $% $<

(%.o):  %.o

# Preceding line has a tab to make an empty rule

# else for ifndef Flint
else
#        -------------

.F.o:; flint $(CPPFLAGS) -m -P SGI,SUN,CRAY -u $<

.f.o:; flint $(CPPFLAGS) -m -P SGI,SUN,CRAY -u $<

endif



