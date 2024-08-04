c-----------------------------------------------------------------------
!> \ingroup noft
!> @{
!>
!> \file noft_module.F
!> The file that gathers all code into a module
!>
!> @}
!>
!> \ingroup noft_priv
!> @{
!>
!> \brief The Natural Orbital Functional Theory Module
!>
      module noft
      implicit none
#include "noft_parameters.fh"
#include "noft_files_tp.fh"
#include "noft_parameter_tp.fh"
      contains
#include "noft_load_params.fi"
#include "noft_load_vectors.fi"
#include "noft_task_energy_doit.fi"
      end module noft
!>
!> @}
c-----------------------------------------------------------------------
