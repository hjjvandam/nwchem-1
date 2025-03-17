!-----------------------------------------------------------------------
!
!> \brief a utility function to set a GA to a unit matrix
!>
!> This is essentially the unit matrix equivalent of ga_zero
!>
      subroutine ga_unit(g_m)
      implicit none
#include "global.fh"
      !> The matrix to be initialized
      integer, intent(inout) :: g_m
!
      integer :: iproc
      integer :: ilo, ihi, jlo, jhi
      integer :: ii
      integer, parameter :: dp = selected_real_kind(15)
      real(kind=dp), parameter :: r_one = 1.0_dp
      integer, parameter :: i_one = 1
!
      call ga_zero(g_m)
!
      iproc = ga_nodeid()
      call ga_inquire(g_m,iproc,ilo,ihi,jlo,jhi)
      do ii = max(ilo,jlo), min(ihi,jhi)
        call ga_acc(g_m,ii,ii,ii,ii,r_one,i_one,r_one)
      enddo
!
      call ga_sync()
!
      end subroutine ga_unit
!
!-----------------------------------------------------------------------
