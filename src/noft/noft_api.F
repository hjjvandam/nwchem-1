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
#include "inp.fh"
#include "mafdecls.fh"
#include "noft_functional_options.fh"
#include "noft_solver_options.fh"
#include "rtdb.fh"
      integer, intent(inout) :: rtdb !> [Input] The runtime database
!
      integer, parameter :: dp = selected_real_kind(15)
      character(len=255) :: test
      character(len=16)  :: xc
      integer :: maxiter
      integer :: nfield, ifield
      real(kind=dp) :: threshold
      real(kind=dp) :: levelshift_orbitals
      real(kind=dp) :: levelshift_tildefuncs
      real(kind=dp) :: c_aa
      real(kind=dp) :: c_ab
      real(kind=dp) :: p_aa
      real(kind=dp) :: p_ab
      real(kind=dp) :: temperature
      integer       :: nindep ! Number of linearly independ vectors
      real(kind=dp) :: cindep ! Cutoff to determine independ vectors
      integer       :: itype
      integer       :: nopen
      integer       :: functional
      logical       :: symmetrize
!
!     Fix the SCF type for the atomic guess
!
      if (.not. rtdb_get(rtdb, "bgj:scf_type", mt_int, 1, itype)) then
!       bgj:scf_type is not set, so set it to something, i.e. hf
        if (.not. rtdb_put(rtdb, "bgj:scf_type", mt_int, 1, 1))
     &    call errquit("bgj:scf_type: error writing rtdb", 5, RTDB_ERR)
      endif
!
!     Set the integrals to "direct" for the atomic guess
!
      if (.not. rtdb_put(rtdb,'int2e:filesize', mt_int, 1, -1))
     &  call errquit('noft_input: failed to store filesize',0, RTDB_ERR)
      if (.not. rtdb_put(rtdb,'int2e:memsize', mt_int, 1, -1))
     &  call errquit('noft_input: failed to store memsize',0, RTDB_ERR)
!
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
!       Nopen
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),"nopen"))
     &  then
          if (.not. inp_i(nopen))
     &      call errquit("noft_input: read nopen failed", 0,
     &                   INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:nopen", mt_int, 1, nopen))
     &      call errquit("noft_input: rtdb_put failed", 15, RTDB_ERR)
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
!       Vectors
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "vectors")) then
          call vectors_input(rtdb,'noft')
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
!       "Temperature"
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "temperature"))
     &  then
          if (.not. inp_f(temperature))
     &      call errquit("noft_input: read temperature failed",
     &                   0, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:temperature", mt_dbl, 1,
     &                       temperature))
     &      call errquit("noft_input: rtdb_put failed", 80, RTDB_ERR)
!
!       Lindep [ off | nvec <integer num> | cutoff <real val> ]
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),"lindep"))
     &  then
          nindep = -2
          cindep = -2.0d0
          nfield = inp_n_field()
          ifield = inp_cur_field()
          do while (ifield.lt.nfield)
            if (.not. inp_a(test))
     &        call errquit("noft_input: invalid lindep directive",
     &                     0, INPUT_ERR)
              if (inp_compare(.false.,test(1:inp_strlen(test)),"nvec"))
     &        then
                if (.not. inp_i(nindep))
     &            call errquit("noft_input: read nindep failed",
     &                         0, INPUT_ERR)
                if (nindep.lt.1) then
                  call errquit("noft_input: invalid nindep value",
     &                         0, INPUT_ERR)
                endif
              else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                             "cutoff"))
     &        then
                if (.not. inp_f(cindep))
     &            call errquit("noft_input: read cindep failed",
     &                         0, INPUT_ERR)
                if (cindep.lt.0.0d0) then
                  call errquit("noft_input: invalid cindep value",
     &                         0, INPUT_ERR)
                endif
              if (inp_compare(.false.,test(1:inp_strlen(test)),"off"))
     &        then
                nindep = -1
                cindep = -1.0d0
              endif
            endif
          enddo
          if (nindep.gt.-2) then
            if (.not. rtdb_put(rtdb, "noft:nindep", mt_int, 1, nindep))
     &        call errquit("noft_input: rtdb_put failed", 90, RTDB_ERR)
          endif
          if (cindep.gt.-2.0d0) then
            if (.not. rtdb_put(rtdb, "noft:cindep", mt_dbl, 1, cindep))
     &        call errquit("noft_input: rtdb_put failed", 92, RTDB_ERR)
          endif
!
!       Restricted
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "restricted"))
     &  then
          if (.not. rtdb_put(rtdb, "noft:restricted", mt_log, 1,
     &                       .true.))
     &      call errquit("noft_input: rtdb_put failed", 100, RTDB_ERR)
!
!       Unrestricted
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "unrestricted"))
     &  then
          if (.not. rtdb_put(rtdb, "noft:unrestricted", mt_log, 1,
     &                       .false.))
     &      call errquit("noft_input: rtdb_put failed", 110, RTDB_ERR)
!
!       Symmetrize
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "symmetrize"))
     &  then
          if (.not.inp_l(symmetrize))
     &      call errquit("noft_input: invalid symmetrize option",
     &                   120, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:symmetrize", mt_log, 1,
     &                       symmetrize))
     &      call errquit("noft_input: rtdb_put failed", 130, RTDB_ERR)
!
!       MonteCarlo
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "montecarlo"))
     &  then
          call noft_input_monte_carlo(rtdb)
!
!       PairRotation
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "pairrotation"))
     &  then
          if (.not. rtdb_put(rtdb, "noft:solver", mt_int, 1,
     &                       pair_rotation))
     &      call errquit("noft_input: rtdb_put failed", 140, RTDB_ERR)
!
!       Functional
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "functional"))
     &  then
          if (.not. inp_a(test))
     &      call errquit("noft_input: failed to read functional",150,
     &                   INPUT_ERR)
          if (inp_compare(.false.,test(1:inp_strlen(test)),"same"))
     &    then
            functional = same
          else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                         "conjugate"))
     &    then
            functional = conjugate
          else if (inp_compare(.false.,test(1:inp_strlen(test)),"both"))
     &    then
            functional = both
          else
            call errquit("noft_input: invalid functional: "//test,
     &                   160, INPUT_ERR)
          endif
          if (.not. rtdb_put(rtdb, "noft:functional", mt_int, 1,
     &                       functional))
     &      call errquit("noft_input: rtdb_put failed", 170, RTDB_ERR)
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
!> \brief Input the Monte Carlo parameters
!>
      subroutine noft_input_monte_carlo(rtdb)
      implicit none
#include "errquit.fh"
#include "rtdb.fh"
#include "inp.fh"
#include "mafdecls.fh"
#include "noft_solver_options.fh"
      integer, intent(inout) :: rtdb !> [Input] The runtime database
!
      integer, parameter :: dp = selected_real_kind(15)
      character(len=255) :: test
      character(len=25), parameter :: pname = "noft_input_monte_carlo: "
      integer :: maxiter
      integer :: fails
      real(kind=dp) :: threshold
      real(kind=dp) :: stepmax
      real(kind=dp) :: scale_a
      real(kind=dp) :: scale_b
      real(kind=dp) :: scale_c
      real(kind=dp) :: scale
!
      do while (inp_read())
        if (.not. inp_a(test))
     &    call errquit("noft_input: keyword read failed", 10,
     &                 INPUT_ERR)
!
!       (Step) Threshold
!
        if (inp_compare(.false.,test(1:inp_strlen(test)),"threshold"))
     &  then
          if (.not. inp_f(threshold))
     &      call errquit(pname//"read threshold failed", 20, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:mc:threshold",MT_DBL,1,
     &                       threshold))
     &      call errquit(pname//"rtdb_put failed", 20, RTDB_ERR)
!
!       (Step) Maximum
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "stepmax"))
     &  then
          if (.not. inp_f(stepmax))
     &      call errquit(pname//"read stepmax failed", 30, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:mc:stepmax",MT_DBL,1,stepmax))
     &      call errquit(pname//"rtdb_put failed", 30, RTDB_ERR)
!
!       Scale_a
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "scale_a"))
     &  then
          if (.not. inp_f(scale_a))
     &      call errquit(pname//"read scale_a failed", 40, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:mc:scale_a",MT_DBL,1,scale_a))
     &      call errquit(pname//"rtdb_put failed", 40, RTDB_ERR)
!
!       Scale_b
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "scale_b"))
     &  then
          if (.not. inp_f(scale_b))
     &      call errquit(pname//"read scale_b failed", 50, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:mc:scale_b",MT_DBL,1,scale_b))
     &      call errquit(pname//"rtdb_put failed", 50, RTDB_ERR)
!
!       Scale_c
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "scale_c"))
     &  then
          if (.not. inp_f(scale_c))
     &      call errquit(pname//"read scale_c failed", 60, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:mc:scale_c",MT_DBL,1,scale_c))
     &      call errquit(pname//"rtdb_put failed", 60, RTDB_ERR)
!
!       Scale
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),"scale"))
     &  then
          if (.not. inp_f(scale))
     &      call errquit(pname//"read scale failed", 70, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:mc:scale",MT_DBL,1,scale))
     &      call errquit(pname//"rtdb_put failed", 70, RTDB_ERR)
!
!       Maxiter
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),
     &                       "maxiter"))
     &  then
          if (.not. inp_i(maxiter))
     &      call errquit(pname//"read maxiter failed", 80, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:mc:maxiter",MT_INT,1,maxiter))
     &      call errquit(pname//"rtdb_put failed", 80, RTDB_ERR)
!
!       Fails
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),"fails"))
     &  then
          if (.not. inp_i(fails))
     &      call errquit(pname//"read fails failed", 90, INPUT_ERR)
          if (.not. rtdb_put(rtdb, "noft:mc:fails",MT_DBL,1,fails))
     &      call errquit(pname//"rtdb_put failed", 90, RTDB_ERR)
!
!       End
!
        else if (inp_compare(.false.,test(1:inp_strlen(test)),"end"))
     &  then
          if (.not. rtdb_put(rtdb, "noft:solver", mt_int, 1,
     &                       monte_carlo))
     &      call errquit("noft_input: rtdb_put failed", 100, RTDB_ERR)
          return
        else
          call errquit("noft_input: unknown directive", 110, INPUT_ERR)
        endif
      enddo
!
      end subroutine noft_input_monte_carlo
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
      noft_success = noft_task_energy_doit(rtdb)
      end function noft_task_energy
!>
!>----------------------------------------------------------------------
!> @}
