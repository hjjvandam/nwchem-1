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
#include "noft_instances_tp.fh"
#include "noft_lindep_tp.fh"
#include "noft_operators_tp.fh"
#include "noft_parameter_tp.fh"
#include "noft_wavefunction_tp.fh"
      contains
#include "noft_compute_1electron.fi"
#include "noft_compute_operators.fi"
#include "noft_compute_overlap.fi"
#include "noft_create_operators.fi"
#include "noft_create_wavefunction.fi"
#include "noft_destroy_operators.fi"
#include "noft_destroy_wavefunction.fi"
#include "noft_lindep.fi"
#include "noft_load_basis.fi"
#include "noft_load_geometry.fi"
#include "noft_load_geometry_basis.fi"
#include "noft_load_lindep.fi"
#include "noft_load_params.fi"
#include "noft_load_vectors.fi"
#include "noft_print_header.fi"
#include "noft_set_nao.fi"
#include "noft_task_energy_doit.fi"
      end module noft
!>
!> @}
c-----------------------------------------------------------------------
