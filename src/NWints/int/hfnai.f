      Subroutine hfnai(E,R0,IJK,Vab,Nint,NPP,La,Lb,Li,Lp,Lp3,canAB)
c $Id: hfnai.f,v 1.3 1996-01-17 22:03:51 d3e129 Exp $

      Implicit real*8 (a-h,o-z)
      Implicit integer (i-n)

      Logical canAB

c--> Hermite Linear Expansion Coefficients

      Dimension E(3,NPP,0:((La+Li)+(Lb+Li)),0:(La+Li),0:(Lb+Li))

c--> Auxiliary Function Integrals & Index

      Dimension R0(NPP,Lp3),IJK(0:Lp,0:Lp,0:Lp)

c--> Nuclear Attraction Integrals

      Dimension Vab(Nint)

c--> Scratch Space

      Dimension Nxyz(3)
c
c Compute the nuclear attraction integrals.
c
c     formula:
c           __
c           \    Ia,Ib    Ja,Jb    Ka,Kb
c     Vab = /  Ex     * Ey     * Ez     * R
c           --   Ip       Jp       Kp      Ip,Jp,Kp
c        Ip,Jp,Kp
c
c******************************************************************************

c Initialize the block of NAIs.

      do 10 nn = 1,Nint
       Vab(nn) = 0.D0
   10 continue

c Define the number of shell components on each center.

      La2 = ((La+1)*(La+2))/2
      Lb2 = ((Lb+1)*(Lb+2))/2

c Loop over shell components.

      nn = 0

      do 50 ma = 1,La2

c Define the angular momentum indices for shell "A".

       call getNxyz(La,ma,Nxyz)

       Ia = Nxyz(1)
       Ja = Nxyz(2)
       Ka = Nxyz(3)

       if( canAB )then
        mb_limit = ma
       else
        mb_limit = Lb2
       end if

       do 40 mb = 1,mb_limit

c Define the angular momentum indices for shell "B".

        call getNxyz(Lb,mb,Nxyz)

        Ib = Nxyz(1)
        Jb = Nxyz(2)
        Kb = Nxyz(3)

        nn = nn + 1

        do 30 Ip = 0,Ia+Ib
        do 30 Jp = 0,Ja+Jb
        do 30 Kp = 0,Ka+Kb

         np = IJK(Ip,Jp,Kp)

         do 20 mp = 1,NPP
          Vab(nn) = Vab(nn) + (E(1,mp,Ip,Ia,Ib)*
     &                         E(2,mp,Jp,Ja,Jb)*
     &                         E(3,mp,Kp,Ka,Kb))*R0(mp,np)
   20    continue

   30   continue

   40  continue

   50 continue

      end
      Subroutine hfnai_gc(E,R0,IJK,Vab,VabP,VabH,Nint,
     &    NCA,NCB,NPP,
     &    La,Lb,Li,Lp,Lp3,
     &    gct_a,gct_b,canAB)

      Implicit real*8 (a-h,o-z)
      Implicit integer (i-n)

      Logical canAB

c--> Hermite Linear Expansion Coefficients

      Dimension E(3,NPP,0:((La+Li)+(Lb+Li)),0:(La+Li),0:(Lb+Li))

c--> Auxiliary Function Integrals & Index

      Dimension R0(NPP,Lp3),IJK(0:Lp,0:Lp,0:Lp)

c--> Nuclear Attraction Integrals

      Dimension Vab(Nint*nca*ncb)
      double precision VabP(NPP,Nint)
      double precision VabH(NPP,Nint,NCA)
c--> general contraction matrices
      double precision gct_a(NPP,NCA) ! [output] general contraction coefs for A multiply
      double precision gct_b(NCB,NPP) ! [output] general contraction coefs for B multiply

c--> Scratch Space

      Dimension Nxyz(3)
c
c Compute the nuclear attraction integrals.
c
c     formula:
c           __
c           \    Ia,Ib    Ja,Jb    Ka,Kb
c     Vab = /  Ex     * Ey     * Ez     * R
c           --   Ip       Jp       Kp      Ip,Jp,Kp
c        Ip,Jp,Kp
c
c******************************************************************************

c Initialize the block of NAIs.

      call dfill(Nint*nca*ncb,0.0d00,Vab,1)
      call dfill(NPP*Nint,0.0d00,VabP,1)
      call dfill(NPP*Nint*NCA,0.0d00,VabH,1)

c Define the number of shell components on each center.

      La2 = ((La+1)*(La+2))/2
      Lb2 = ((Lb+1)*(Lb+2))/2

c Loop over shell components.

      nn = 0

      do 50 ma = 1,La2

c Define the angular momentum indices for shell "A".

       call getNxyz(La,ma,Nxyz)

       Ia = Nxyz(1)
       Ja = Nxyz(2)
       Ka = Nxyz(3)

       if( canAB )then
        mb_limit = ma
       else
        mb_limit = Lb2
       end if

       do 40 mb = 1,mb_limit

c Define the angular momentum indices for shell "B".

        call getNxyz(Lb,mb,Nxyz)

        Ib = Nxyz(1)
        Jb = Nxyz(2)
        Kb = Nxyz(3)

        nn = nn + 1

        do 30 Ip = 0,Ia+Ib
        do 30 Jp = 0,Ja+Jb
        do 30 Kp = 0,Ka+Kb

         np = IJK(Ip,Jp,Kp)

         do 20 mp = 1,NPP
          VabP(mp,nn) = VabP(mp,nn) +
     &        (E(1,mp,Ip,Ia,Ib)*
     &         E(2,mp,Jp,Ja,Jb)*
     &         E(3,mp,Kp,Ka,Kb))  *R0(mp,np)
   20    continue

   30   continue

   40  continue

   50 continue

c take primitives and half transformed multiplied by A general contraction matrix

      do 10100 ica = 1,NCA
        do 10200 nn = 1,Nint
          do 10300 mp = 1,NPP
            VabH(mp,nn,ica) = VabP(mp,nn)*gct_a(mp,ica)
10300     continue
10200   continue
10100 continue
c
      nn = 0
      do 10400 ica = 1,NCA
        do 10500 icb = 1,NCB
          do 10600 iii = 1,Nint
*            if (iwiw.eq.0)
*     &            write(6,*)'complex integrals for ica = ',
*     &            ica,'and icb = ',icb
            iwiw = iwiw + 1
            nn = nn + 1
            Vab(nn) = 0.0d00
            do 10700 mp = 1,NPP
              e_tmp = VabH(mp,iii,ica)*gct_b(icb,mp)
              Vab(nn) = Vab(nn) + e_tmp
*              write(6,10000)
*     &              ' int=',nn,' mp =',mp,
*     &              ' val = ',e_tmp,' integral=',Vab(nn)
10700       continue
*            write(80,*)' complex ',ica,icb,iii,Vab(nn),nn
10600     continue
10500   continue
10400 continue
10000 format(a,i4,a,i4,a,1pd20.10,a,1pd20.10)
c
c      copy integrals
c
      call dcopy((nint*nca*ncb),Vab,1,VabH,1)
      call hf1_tran_shift(Vab,VabH,(nca*ncb),la,lb,nca,ncb)
      end
