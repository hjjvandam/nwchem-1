c
c     Modified to handle second and third derivatives while reusing code
c
c     DWS - 6/12
c     BGJ - 8/98
c
#if !defined SECOND_DERIV && !defined THIRD_DERIV
      Subroutine xc_dirac_pow2(tol_rho1, fac, lfac, nlfac, rho, Amat,
     &                    nq, jpol, Ex, qwght, ldew, func)
#elif defined(SECOND_DERIV) && !defined THIRD_DERIV
c     For locations of 2nd derivatives of functionals in array
#include "dft2drv.fh"
      Subroutine xc_dirac_pow2_d2(tol_rho1, fac, lfac, nlfac, rho, Amat,
     &                       Amat2, nq, jpol, Ex, qwght, ldew,
     &                       func)
#else
#include "dft2drv.fh"
#include "dft3drv.fh"
      Subroutine xc_dirac_pow2_d3(tol_rho1, fac, lfac, nlfac, rho, Amat,
     &                       Amat2, Amat3, nq, jpol, Ex, qwght, ldew,
     &                       func)
#endif
c
C$Id$
c
      Implicit none
#include "errquit.fh"
c
#include "stdio.fh"
#include "cdft.fh"
c
c This functional is defined as
c
c    (rhoa*rhob)**(pow/2)
c
c where `pow` is a variable. The thought is that maybe a good DDFT functional
c is the DDFT density to some power. This idea is based on the fact that the
c exchange functional as well as the kinetic energy functional are simple powers
c of rho. In addition the DDFT density is a measure of how far you are from
c single determinant state. A functional maximizing this quantity seems relevant
c even from the a perturbation theory point of view.
c
c This form also accounts for the fact that alpha-beta correlation is the main
c contribution to the correlation energy. Allowing for spin symmetry breaking
c in, e.g. H2, rhoa-->0 where rhob > 0 and vice versa, so the correlation
c energy will automatically vanish in those regions of conformation space.
c
c ipol also comes in through cdft.fh
      integer nq, jpol
      double precision fac, Ex
      logical ldew, lfac, nlfac
      double precision func(*)  ! value of the functional [output]
c
c     Charge Density
c
      double precision rho(nq,(ipol*(ipol+1))/2)
c
c     Quadrature Weights
c
      double precision qwght(nq)
c
c     Partial First Derivatives of the Exchange Energy Functional
c
      double precision Amat(nq,ipol)
#if defined(SECOND_DERIV)
      double precision Amat2
#endif
#if defined(THIRD_DERIV)
      double precision Amat3
#endif
c
c
c     Compute the partial derivatives of the exchange functional of Dirac.
c
      double precision P1, P2, P3, P4, PI
      double precision tol_rho1
c
c Daniel (5-23-12): P1 and P2 are for restricted calculations, P3 
c and P4 are for unrestricted calculations.
c
c     P1 =       -(3/PI)**(1/3)
c     P2 = -(3/4)*(3/PI)**(1/3)
c     P3 =       -(6/PI)**(1/3)
c     P4 = -(3/4)*(6/PI)**(1/3)
c
      double precision rho13, rho32, rho33, one_third, term
      double precision rhot1, rhot2, rhot3
      double precision two_ninth, rhom23
      Parameter (one_third = 1.d0/3.d0)
      Parameter (two_ninth = 2.d0/9.d0)
      integer n
c
      term = 0.d0
      PI = dacos(-1.0d0)
c
      if (ipol.eq.1)then
c
c        ======> SPIN-RESTRICTED <======
c
         call errquit("we don't do closed shell",UERR)
         P1 = -(3.0d0/PI)**(p_ddft_d-1.0d0)
         do 10 n = 1, nq
            if (rho(n,1).gt.tol_rho)then
               rho13=rho(n,1)**(p_ddft_d-1.0d0)
               Amat(n,1) = Amat(n,1) + rho13
               term = term + rho(n,1)*rho13*qwght(n)
               if(ldew)
     &           func(n) = func(n) + rho(n,1)*rho13*fac*P1/p_ddft_d
            endif
   10    continue
         call dscal(nq, P1*fac, Amat(1,1), 1)
c
         Ex = Ex + P1*term*fac/p_ddft_d
c
      else
c
c        ======> SPIN-UNRESTRICTED <======
c
         P3 = -(6.0d0/PI)**(p_ddft_d-1.0d0)
         do 20 n = 1,nq
            if (rho(n,1).gt.tol_rho)then
               rho32=0.0d0
               rho33=0.0d0
               if (rho(n,2).gt.tol_rho)
     &             rho32=(2.0d0*rho(n,2))
               if (rho(n,3).gt.tol_rho)
     &             rho33=(2.0d0*rho(n,3))
               rhot1 = 1.0d0*(rho32*rho33)**(p_ddft_d/2.0d0)
               if (rho(n,2).gt.tol_rho)
     &             Amat(n,1) = Amat(n,1) + p_ddft_d*P3*rhot1*fac/rho32
               if (rho(n,3).gt.tol_rho)
     &             Amat(n,2) = Amat(n,2) + p_ddft_d*P3*rhot1*fac/rho33
               if (ldew)
     &           func(n) = func(n) + rhot1*P3*fac
               term = term + rhot1*qwght(n)
c      write(LuOut,*)'from xc_dirac ; rho32, rho33, qwght(n): ',
c     &                           rho32, rho33, qwght(n)
            endif
   20    continue
c
         Ex = Ex + P3*term*fac
c
      endif
c      write(LuOut,*)'from xc_dirac ; p4, exp, fac, Ex: ',
c     &                           p4, exp, fac, Ex
      return
      end
#ifndef SECOND_DERIV
#define SECOND_DERIV
c
c     Compile source again for the 2nd derivative case
c
#include "xc_dirac_pow2.F"
#endif
#ifndef THIRD_DERIV
#define THIRD_DERIV
c
c     Compile source again for the 3rd derivative case
c
#include "xc_dirac_pow2.F"
#endif
