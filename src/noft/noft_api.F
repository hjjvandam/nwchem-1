!> \ingroup noft_api
!> @{
!>
!> \file noft_api.F
!> Implements the NOFT module API
!>
!>----------------------------------------------------------------------
!>
!> \brief Read the input
!>
!> Read the input for the NOFT calculations
!>
      subroutine noft_input(rtdb)
      implicit none
#include "errquit.fh"
#include "rtdb.fh"
#include "inp.fh"
#include "mafdecls.fh"
      integer, intent(inout) :: rtdb !> [Input] The runtime database
!
      integer, parameter :: dp = selected_real_kind(15)
      character(len=255) :: test
      character(len=16)  :: xc
      integer :: maxiter
      real(kind=dp) :: threshold
      real(kind=dp) :: levelshift_orbitals
      real(kind=dp) :: levelshift_tildefuncs
      real(kind=dp) :: c_aa
      real(kind=dp) :: c_ab
      real(kind=dp) :: p_aa
      real(kind=dp) :: p_ab
      do while (inp_read())
        if (.not. inp_a(test))
     &    call errquit("noft_input: keyword read failed", 0,
     &                 INPUT_ERR)
!
!       Maxiter
!
        if (inp_compare(.false.,test(1:inp_strlen(test)),"maxiter"))
     &  then
          if (.not. inp_i(maxiter))
     &      call errquit("noft_input: read maxiter failed", 0,
     &                   INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:maxiter", mt_int, 1, maxiter))
     &      call errquit("noft_input: rtdb_put failed", 10, RTDB_ERR)
!
!       Threshold
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "threshold")) then
          if (.not. inp_f(threshold))
     &      call errquit("noft_input: read threshold failed", 0,
     &                   INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:threshold", mt_dbl, 1,
     &                       threshold))
     &      call errquit("noft_input: rtdb_put failed", 20, RTDB_ERR)
!
!       Levelshift
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "levelshift")) then
          if (.not. inp_f(levelshift_orbitals))
     &      call errquit("noft_input: read levelshift orbitals failed",
     &                   0, INPUT_ERR)
          if (.not. inp_f(levelshift_tildefuncs))
     &      call errquit("noft_input: read levelshift tilde failed", 0,
     &                   INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:levelshift_orbitals", mt_dbl,
     &                       1, levelshift_orbitals))
     &      call errquit("noft_input: rtdb_put failed", 30, RTDB_ERR)
          if (.not. rtdb_put(rtdb, "noft:levelshift_tildefuncs",
     &                       mt_dbl, 1, levelshift_tildefuncs))
     &      call errquit("noft_input: rtdb_put failed", 35, RTDB_ERR)
!
!       C_aa (note C_aa refers to same spin interactions,
!             hence conceptually C_bb = C_aa)
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),"c_aa"))
     &  then
          if (.not. inp_f(c_aa))
     &      call errquit("noft_input: read c_aa failed", 0, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:c_aa", mt_dbl, 1, c_aa))
     &      call errquit("noft_input: rtdb_put failed", 40, RTDB_ERR)
!
!       C_ab
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),"c_ab"))
     &  then
          if (.not. inp_f(c_ab))
     &      call errquit("noft_input: read c_ab failed", 0, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:c_ab", mt_dbl, 1, c_ab))
     &      call errquit("noft_input: rtdb_put failed", 50, RTDB_ERR)
!
!       P_aa
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),"p_aa"))
     &  then
          if (.not. inp_f(p_aa))
     &      call errquit("noft_input: read p_aa failed", 0, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:p_aa", mt_dbl, 1, p_aa))
     &      call errquit("noft_input: rtdb_put failed", 60, RTDB_ERR)
!
!       P_ab
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),"p_ab"))
     &  then
          if (.not. inp_f(p_ab))
     &      call errquit("noft_input: read p_ab failed", 0, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:p_ab", mt_dbl, 1, p_ab))
     &      call errquit("noft_input: rtdb_put failed", 70, RTDB_ERR)
!
!       End
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),"end"))
     &  then
          return
        else
          call errquit("noft_input: unknown directive", 0, INPUT_ERR)
        endif
      enddo
      call errquit("noft_input: inp_read failed", 0, INPUT_ERR)
      end subroutine noft_input
!>
!>----------------------------------------------------------------------
!>
!> \brief Optimize the energy
!>
!> This function provides the interface between the NWChem tasks and
!> the NOFT energy solver. 
!>
!> If the calculation converged the energy will be stored on the RTDB
!> with the key "noft:energy" and the corresponding wavefunction 
!> will be stored in multiple files:
!>   - "*.movecs" the molecular orbitals expressed in terms of AOs.
!>     This can be used by other NWChem modules.
!>   - "*.svecs" the orthogonalizing transformation. A set of
!>     orthonormal vectors expressed in AOs. We call them SOs because
!>     they are eigenfunctions of the overlap matrix S.
!>   - "*.mvecs" the molecular orbitals (MOs) given in terms of SOs.
!>   - "*.tvecs" the tilde functions (TOs) given in terms of the MOs.
!>
!> The SOs, MOs and TOs only make sense in the context of the NOFT 
!> code. Only the molecular orbitals as stored in the "*.movecs"
!> file make sense to the rest of NWChem.
!>
!> \return Returns .TRUE. if the calculation converged successfully and
!>         returns .FALSE. otherwise.
!>         
!>
      function noft_task_energy(rtdb) result(noft_success)
      use noft
      implicit none
      integer, intent(inout) :: rtdb !> [Input] The runtime database
      logical :: noft_success
!      noft_success = noft_task_energy_doit(rtdb)
      end function noft_task_energy
!>
!>----------------------------------------------------------------------
!> @}
