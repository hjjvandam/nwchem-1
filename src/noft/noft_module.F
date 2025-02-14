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
#include "noft_energy_tp.fh"
#include "noft_files_tp.fh"
#include "noft_fock_tp.fh"
#include "noft_instances_tp.fh"
#include "noft_lindep_tp.fh"
#include "noft_local.fh"
#include "noft_monte_carlo_range_tp.fh"
#include "noft_monte_carlo_rotation_tp.fh"
#include "noft_monte_carlo_step_tp.fh"
#include "noft_occupations_tp.fh"
#include "noft_operators_tp.fh"
#include "noft_parameter_monte_carlo_tp.fh"
#include "noft_parameter_tp.fh"
#include "noft_wavefunction_tp.fh"
      contains
#include "noft_1e_occupation.fi"
#include "noft_2e_occupation.fi"
#include "noft_2e_anti_symmetry.fi"
#include "noft_2e_sign.fi"
#include "noft_2e_weight.fi"
#include "noft_2index.fi"
#include "noft_4index.fi"
#include "noft_adjust_wavefunction.fi"
#include "noft_compute_1electron.fi"
#include "noft_compute_2electron.fi"
#include "noft_compute_operators.fi"
#include "noft_compute_overlap.fi"
#include "noft_create_operators.fi"
#include "noft_create_wavefunction.fi"
#include "noft_destroy_operators.fi"
#include "noft_destroy_wavefunction.fi"
#include "noft_eval_1e_energy.fi"
#include "noft_eval_2e_energy.fi"
#include "noft_eval_2e_energy_aa.fi"
#include "noft_eval_2e_energy_ab.fi"
#include "noft_eval_energy.fi"
#include "noft_eval_nuc_energy.fi"
#include "noft_eval_tot_energy.fi"
#include "noft_gemm.fi"
#include "noft_guess_mos.fi"
#include "noft_guess_tilde.fi"
#include "noft_guess_wavefunction.fi"
#include "noft_initialize_integrals.fi"
#include "noft_ionode.fi"
#include "noft_lindep.fi"
#include "noft_load_basis.fi"
#include "noft_load_geometry.fi"
#include "noft_load_geometry_basis.fi"
#include "noft_load_lindep.fi"
#include "noft_load_monte_carlo_params.fi"
#include "noft_load_params.fi"
#include "noft_load_vectors.fi"
#include "noft_local.fi"
#include "noft_monte_carlo_range.fi"
#include "noft_monte_carlo_rotate_wavefunction.fi"
#include "noft_monte_carlo_rotation.fi"
#include "noft_monte_carlo_step.fi"
#include "noft_occupations.fi"
#include "noft_ortho_operators.fi"
#include "noft_orthogonalize_vecs.fi"
#include "noft_orthogonalizing_transformation.fi"
#include "noft_print_basis.fi"
#include "noft_print_energy.fi"
#include "noft_print_geometry.fi"
#include "noft_print_header.fi"
#include "noft_replace_data.fi"
#include "noft_save_convergence.fi"
#include "noft_save_energy.fi"
#include "noft_set_nao.fi"
#include "noft_set_nuclear_energy.fi"
#include "noft_set_num_electrons.fi"
#include "noft_solve_monte_carlo.fi"
#include "noft_swap_wavefunctions.fi"
#include "noft_task_energy_doit.fi"
      end module noft
!>
!> @}
c-----------------------------------------------------------------------
