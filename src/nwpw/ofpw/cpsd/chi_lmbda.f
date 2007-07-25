*     ***************************
*     *				*
*     *		psi_lmbda	*
*     *				*
*     ***************************

*     Routine now uses D3dB_Vector routines to reduce latency
*
*
      subroutine psi_lmbda(ispin,ne,nemax,
     >                     psi1,psi2,
     >                     dte,
     >                     lmbda,tmp,ierr)

      implicit none
      include 'aimd.h'
      integer nfft3d
      parameter (nfft3d=(nfft1/2+1)*nfft2*nslabs) 
      integer ispin,ne(2),nemax
      complex*16 psi1(nfft3d,nemax)
      complex*16 psi2(nfft3d,nemax)
      real*8     dte
      real*8     lmbda(*)
      real*8     tmp(*)
      integer	 ierr


*     ***** timing variables *****
*     1 - fft_time
*     2 - dot_time
*     3 - ABC_time
*     4 - vxc_time
*     5 - vlocal_time
*     6 - vnl_time
*     7 - vh_time
*     8 - strfac_time
*     9 - maskC_time
      real*8 tim1,tim2
      real*8 times(50)
      common / timing / times



*     **** local variables ****
      integer n1(2),n2(2)
      integer i,j,ii,jj,ms,it,k
      integer index,indext,n,nn
      integer s11,s12,s21,s22,st1,st2,sa1,sa0
      integer sl(2)
      real*8  sum,adiff,alpha
*     ::::  iteration limit and tolerence for non-liner equations  ::::
      integer itrlmd,idamax
      real*8  convg
      parameter (itrlmd=20, convg=1.0d-15)



      call current_second(tim1)

      n    = ne(1)
      nn   = n**2
      
      s11  = 0*nn + 1
      s12  = 1*nn + 1
      s21  = 2*nn + 1
      s22  = 3*nn + 1
      sa0  = 4*nn + 1
      sa1  = 5*nn + 1
      st1  = 6*nn + 1
      st2  = 7*nn + 1

      call dcopy(8*nn,0.0d0,0,tmp,1)

      sl(1)  = 0*nn + 1
      sl(2)  = 1*nn + 1
      call dcopy(2*nn,0.0d0,0,lmbda,1)

      n1(1)=1
      n2(1)=ne(1)
      n1(2)=ne(1)+1
      n2(2)=ne(1)+ne(2)
      
*::::::::::::::::::::::  Lagrangian multipliers  ::::::::::::::::::::::
      DO 640 ms=1,ispin
        IF(ne(ms).le.0) GO TO 640

*       ***** compute the overlap matrices ****
        call D3dB_cc_Vector_dot(nfft3d,n,ne(ms),
     >                          psi2(1,n1(ms)),
     >                          psi2(1,n1(ms)),
     >                          tmp(s22))
        call D3dB_cc_Vector_dot(nfft3d,n,ne(ms),
     >                          psi2(1,n1(ms)),
     >                          psi1(1,n1(ms)),
     >                          tmp(s21))
        call D3dB_cc_Vector_dot(nfft3d,n,ne(ms),
     >                          psi1(1,n1(ms)),
     >                          psi2(1,n1(ms)),
     >                          tmp(s12))
        call D3dB_cc_Vector_dot(nfft3d,n,ne(ms),
     >                          psi1(1,n1(ms)),
     >                          psi1(1,n1(ms)),
     >                          tmp(s11))

*       ***** scale the overlap matrices ****
        do i=1,ne(ms)
          index = (i-1) + (i-1)*n
      
          tmp(s22+index)=(1.0d0-tmp(s22+index))*0.5d0/dte
          tmp(s21+index)=(1.0d0-tmp(s21+index))*0.5d0
          tmp(s12+index)=(1.0d0-tmp(s12+index))*0.5d0
          tmp(s11+index)= (-tmp(s11+index))*0.5d0*dte
          
           do j=i+1,ne(ms)
             index  = (i-1) + (j-1)*n
             indext = (j-1) + (i-1)*n
   
             tmp(s22+index)= (-tmp(s22+index))*0.5d0/dte
             tmp(s21+index)= (-tmp(s21+index))*0.5d0
             tmp(s12+index)= (-tmp(s12+index))*0.5d0
             tmp(s11+index)= (-tmp(s11+index))*0.5d0*dte

             tmp(s22+indext)=tmp(s22+index)
             tmp(s21+indext)=tmp(s12+index)
             tmp(s12+indext)=tmp(s21+index)
             tmp(s11+indext)=tmp(s11+index)
          end do
        end do

        call dcopy(nn,tmp(s22),1,tmp(sa0),1)

        do it=1,itrlmd
          CALL dcopy(nn,tmp(s22),1,tmp(sa1),1)
          CALL DMMUL(n,ne(MS), tmp(s21), tmp(sa0), tmp(st1))
          CALL DMMUL(n,ne(MS), tmp(sa0), tmp(s12), tmp(st2))
          CALL DMADD(n,ne(MS), tmp(st1), tmp(st2), tmp(st1))
          CALL DMADD(n,ne(MS), tmp(st1), tmp(sa1), tmp(sa1))
          CALL DMMUL(n,ne(MS), tmp(s11), tmp(sa0), tmp(st1))
          CALL DMMUL(n,ne(MS), tmp(sa0), tmp(st1), tmp(st2))
          CALL DMADD(n,ne(MS), tmp(st2), tmp(sa1), tmp(sa1))
          CALL DMSUB(n,ne(MS), tmp(sa1), tmp(sa0), tmp(st1))
          adiff=tmp(st1 - 1 + (idamax(n*ne(ms),tmp(st1),1)))
          if(adiff.lt.convg) GO TO 630
          call dcopy(n*ne(ms),tmp(sa1),1,tmp(sa0),1)
        end do
        ierr=10
        WRITE(6,*) 'ierr=10',adiff
C       return
  630   continue
        call dcopy(n*ne(ms),tmp(sa1),1,lmbda(sl(ms)),1)
  640 continue

*     **** correction due to the constraint ****
      do ms=1,ispin

        do ii=n1(ms),n2(ms)
           i=ii-n1(ms)+1

           do jj=n1(ms),n2(ms)
              j=jj-n1(ms)+1

              index = (i-1) + (j-1)*n
              alpha = dte*lmbda(sl(ms) + index)

c             do k=1,nfft3d
c                psi2(k,ii) = psi2(k,ii)  + alpha*psi1(k,jj)
c             end do
              call D3dB_cc_daxpy(alpha,psi1(1,jj),psi2(1,ii))
           end do
        end do
      end do

      call current_second(tim2)
      times(3) = times(3) + (tim2-tim1)

      return
      end

