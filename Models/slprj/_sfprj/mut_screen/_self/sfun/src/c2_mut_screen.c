/* Include files */

#include <stddef.h>
#include "blas.h"
#include "mut_screen_sfun.h"
#include "c2_mut_screen.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "mut_screen_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[124] = { "here", "A_1CM", "A_2CM",
  "A_0CF", "A_1CF", "A_2CF", "A_0RM", "A_1RM", "A_2RM", "A_0RF", "A_1RF",
  "A_2RF", "A_0SM", "A_1SM", "A_2SM", "A_0SF", "A_1SF", "A_2SF", "new_0CM",
  "new_1CM", "new_2CM", "new_0CF", "new_1CF", "new_2CF", "expiring_0CM",
  "expiring_1CM", "expiring_2CM", "expiring_0CF", "expiring_1CF", "expiring_2CF",
  "expiring_0RM", "expiring_1RM", "expiring_2RM", "expiring_0RF", "expiring_1RF",
  "expiring_2RF", "expiring_0SM", "expiring_1SM", "expiring_2SM", "expiring_0SF",
  "expiring_1SF", "expiring_2SF", "leaving_1CM", "leaving_2CM", "leaving_0CF",
  "leaving_1CF", "leaving_2CF", "leaving_0RM", "leaving_1RM", "leaving_2RM",
  "leaving_0RF", "leaving_1RF", "leaving_2RF", "incoming_0RM", "incoming_1RM",
  "incoming_2RM", "incoming_0RF", "incoming_1RF", "incoming_2RF", "incoming_0SM",
  "incoming_1SM", "incoming_2SM", "incoming_0SF", "incoming_1SF", "incoming_2SF",
  "LX", "L_CMT", "L_CFT", "L_RMT", "L_RFT", "L_SMT", "L_SFT", "L_T0", "L_T1",
  "L_T2", "L_TC", "L_TR", "L_TS", "nargin", "nargout", "clock", "L_0CM", "L_1CM",
  "L_2CM", "L_0RM", "L_1RM", "L_2RM", "L_0SM", "L_1SM", "L_2SM", "L_0CF",
  "L_1CF", "L_2CF", "L_0RF", "L_1RF", "L_2RF", "L_0SF", "L_1SF", "L_2SF", "mut",
  "nL_0CM", "nL_1CM", "nL_2CM", "nL_0RM", "nL_1RM", "nL_2RM", "nL_0SM", "nL_1SM",
  "nL_2SM", "nL_0CF", "nL_1CF", "nL_2CF", "nL_0RF", "nL_1RF", "nL_2RF", "nL_0SF",
  "nL_1SF", "nL_2SF", "A_0CM", "leaving_0CM", "L_T", "f_0T", "f_1T", "f_2T" };

static const char * c2_b_debug_family_names[4] = { "nargin", "nargout", "mut",
  "behaveMod" };

static const char * c2_c_debug_family_names[5] = { "nargin", "nargout", "p0",
  "p1", "p2" };

static const char * c2_d_debug_family_names[25] = { "L_TRM", "L_TRF", "new_TC",
  "new_TCM", "new_TCF", "probParents", "behaveMod", "p0", "p1", "p2", "nargin",
  "nargout", "L_0RM", "L_1RM", "L_2RM", "L_0RF", "L_1RF", "L_2RF", "mut",
  "new_0CM", "new_1CM", "new_2CM", "new_0CF", "new_1CF", "new_2CF" };

static const char * c2_e_debug_family_names[10] = { "A", "Y", "dist", "nargin",
  "nargout", "L", "mut", "expiring", "childAgeBracket", "leaving" };

/* Function Declarations */
static void initialize_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance);
static void initialize_params_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance);
static void enable_c2_mut_screen(SFc2_mut_screenInstanceStruct *chartInstance);
static void disable_c2_mut_screen(SFc2_mut_screenInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_mut_screen(SFc2_mut_screenInstanceStruct *
  chartInstance);
static void set_sim_state_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_mut_screen(SFc2_mut_screenInstanceStruct *chartInstance);
static void sf_gateway_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance);
static void mdl_start_c2_mut_screen(SFc2_mut_screenInstanceStruct *chartInstance);
static void c2_chartstep_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance);
static void initSimStructsc2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static real_T c2_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_b_f_2T, const char_T *c2_identifier);
static real_T c2_b_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_b_leaving_0CM, const char_T *c2_identifier, real_T c2_y[2]);
static void c2_d_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[2]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_e_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  c2_struct_zKkRWFtALBg7fNtPuY4M6D *c2_y);
static void c2_f_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[6]);
static void c2_g_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[18]);
static c2_struct_qHpeHlL7YRQjHTvGIxkLGB c2_h_emlrt_marshallIn
  (SFc2_mut_screenInstanceStruct *chartInstance, const mxArray *c2_u, const
   emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_i_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[9]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_j_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[2]);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static boolean_T c2_k_emlrt_marshallIn(SFc2_mut_screenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_getNewChildrenMutations(SFc2_mut_screenInstanceStruct
  *chartInstance, real_T c2_b_L_0RM[2], real_T c2_b_L_1RM[2], real_T c2_b_L_2RM
  [2], real_T c2_b_L_0RF[2], real_T c2_b_L_1RF[2], real_T c2_b_L_2RF[2],
  c2_struct_zKkRWFtALBg7fNtPuY4M6D *c2_b_mut, real_T *c2_new_0CM, real_T
  *c2_new_1CM, real_T *c2_new_2CM, real_T *c2_new_0CF, real_T *c2_new_1CF,
  real_T *c2_new_2CF);
static void c2_sum(SFc2_mut_screenInstanceStruct *chartInstance, real_T c2_x[9],
                   real_T c2_y[3]);
static real_T c2_b_sum(SFc2_mut_screenInstanceStruct *chartInstance, real_T
  c2_x[3]);
static void c2_calcLeaving(SFc2_mut_screenInstanceStruct *chartInstance, real_T
  c2_L[2], c2_struct_zKkRWFtALBg7fNtPuY4M6D *c2_b_mut, real_T c2_expiring,
  boolean_T c2_childAgeBracket, real_T c2_leaving[2]);
static real_T c2_c_sum(SFc2_mut_screenInstanceStruct *chartInstance, real_T
  c2_x[3]);
static real_T c2_d_sum(SFc2_mut_screenInstanceStruct *chartInstance, real_T
  c2_x[6]);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_l_emlrt_marshallIn(SFc2_mut_screenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_m_emlrt_marshallIn(SFc2_mut_screenInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_mut_screen, const char_T
  *c2_identifier);
static uint8_T c2_n_emlrt_marshallIn(SFc2_mut_screenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_mut_screenInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_mut_screenInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc2_mut_screen(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_mut_screen = 0U;
}

static void initialize_params_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance)
{
  const mxArray *c2_m0 = NULL;
  const mxArray *c2_mxField;
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_r0;
  const mxArray *c2_m1 = NULL;
  const mxArray *c2_b_mxField;
  c2_m0 = sf_mex_get_sfun_param(chartInstance->S, 0, 1);
  c2_mxField = sf_mex_getfield(c2_m0, "fertility", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_mxField), &c2_r0.fertility, 1, 0, 0U,
                      0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "M2Fprobability", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_mxField), &c2_r0.M2Fprobability, 1, 0,
                      0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "Y_C", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_mxField), &c2_r0.Y_C, 1, 0, 0U, 0, 0U,
                      0);
  c2_mxField = sf_mex_getfield(c2_m0, "Y_R", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_mxField), &c2_r0.Y_R, 1, 0, 0U, 0, 0U,
                      0);
  c2_mxField = sf_mex_getfield(c2_m0, "distribution", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_mxField), c2_r0.distribution, 1, 0,
                      0U, 1, 0U, 2, 1, 2);
  c2_mxField = sf_mex_getfield(c2_m0, "distributionPercent", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_mxField), &c2_r0.distributionPercent,
                      1, 0, 0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "MSM", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_mxField), &c2_r0.MSM, 1, 0, 0U, 0, 0U,
                      0);
  c2_mxField = sf_mex_getfield(c2_m0, "MSF", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_mxField), &c2_r0.MSF, 1, 0, 0U, 0, 0U,
                      0);
  c2_mxField = sf_mex_getfield(c2_m0, "mort", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_mxField), c2_r0.mort, 1, 0, 0U, 1, 0U,
                      2, 1, 6);
  c2_mxField = sf_mex_getfield(c2_m0, "muMort", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_mxField), c2_r0.muMort, 1, 0, 0U, 1,
                      0U, 2, 3, 6);
  c2_mxField = sf_mex_getfield(c2_m0, "screen", "mut", 0);
  c2_m1 = sf_mex_dup(c2_mxField);
  c2_b_mxField = sf_mex_getfield(c2_m1, "NR", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_b_mxField), &c2_r0.screen.NR, 1, 0,
                      0U, 0, 0U, 0);
  c2_b_mxField = sf_mex_getfield(c2_m1, "LR", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_b_mxField), &c2_r0.screen.LR, 1, 0,
                      0U, 0, 0U, 0);
  c2_b_mxField = sf_mex_getfield(c2_m1, "MR", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_b_mxField), &c2_r0.screen.MR, 1, 0,
                      0U, 0, 0U, 0);
  c2_b_mxField = sf_mex_getfield(c2_m1, "HR", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_b_mxField), &c2_r0.screen.HR, 1, 0,
                      0U, 0, 0U, 0);
  c2_b_mxField = sf_mex_getfield(c2_m1, "efficiency", "mut", 0);
  sf_mex_import_named("mut", sf_mex_dup(c2_b_mxField), &c2_r0.screen.efficiency,
                      1, 0, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_m1);
  sf_mex_destroy(&c2_m0);
  chartInstance->c2_mut = c2_r0;
}

static void enable_c2_mut_screen(SFc2_mut_screenInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_mut_screen(SFc2_mut_screenInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_mut_screen(SFc2_mut_screenInstanceStruct *
  chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_u;
  const mxArray *c2_b_y = NULL;
  real_T c2_b_hoistedGlobal;
  real_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real_T c2_c_hoistedGlobal;
  real_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  real_T c2_d_hoistedGlobal;
  real_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_hoistedGlobal;
  real_T c2_e_u;
  const mxArray *c2_f_y = NULL;
  const mxArray *c2_g_y = NULL;
  const mxArray *c2_h_y = NULL;
  const mxArray *c2_i_y = NULL;
  const mxArray *c2_j_y = NULL;
  const mxArray *c2_k_y = NULL;
  const mxArray *c2_l_y = NULL;
  const mxArray *c2_m_y = NULL;
  const mxArray *c2_n_y = NULL;
  const mxArray *c2_o_y = NULL;
  const mxArray *c2_p_y = NULL;
  const mxArray *c2_q_y = NULL;
  const mxArray *c2_r_y = NULL;
  const mxArray *c2_s_y = NULL;
  const mxArray *c2_t_y = NULL;
  const mxArray *c2_u_y = NULL;
  const mxArray *c2_v_y = NULL;
  const mxArray *c2_w_y = NULL;
  const mxArray *c2_x_y = NULL;
  const mxArray *c2_y_y = NULL;
  uint8_T c2_f_hoistedGlobal;
  uint8_T c2_f_u;
  const mxArray *c2_ab_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(25, 1), false);
  c2_hoistedGlobal = *chartInstance->c2_A_0CM;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = *chartInstance->c2_L_T;
  c2_b_u = c2_b_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_c_hoistedGlobal = *chartInstance->c2_f_0T;
  c2_c_u = c2_c_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_d_hoistedGlobal = *chartInstance->c2_f_1T;
  c2_d_u = c2_d_hoistedGlobal;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 3, c2_e_y);
  c2_e_hoistedGlobal = *chartInstance->c2_f_2T;
  c2_e_u = c2_e_hoistedGlobal;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 4, c2_f_y);
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", *chartInstance->c2_leaving_0CM, 0,
    0U, 1U, 0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 5, c2_g_y);
  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", *chartInstance->c2_nL_0CF, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 6, c2_h_y);
  c2_i_y = NULL;
  sf_mex_assign(&c2_i_y, sf_mex_create("y", *chartInstance->c2_nL_0CM, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 7, c2_i_y);
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", *chartInstance->c2_nL_0RF, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 8, c2_j_y);
  c2_k_y = NULL;
  sf_mex_assign(&c2_k_y, sf_mex_create("y", *chartInstance->c2_nL_0RM, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 9, c2_k_y);
  c2_l_y = NULL;
  sf_mex_assign(&c2_l_y, sf_mex_create("y", *chartInstance->c2_nL_0SF, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 10, c2_l_y);
  c2_m_y = NULL;
  sf_mex_assign(&c2_m_y, sf_mex_create("y", *chartInstance->c2_nL_0SM, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 11, c2_m_y);
  c2_n_y = NULL;
  sf_mex_assign(&c2_n_y, sf_mex_create("y", *chartInstance->c2_nL_1CF, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 12, c2_n_y);
  c2_o_y = NULL;
  sf_mex_assign(&c2_o_y, sf_mex_create("y", *chartInstance->c2_nL_1CM, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 13, c2_o_y);
  c2_p_y = NULL;
  sf_mex_assign(&c2_p_y, sf_mex_create("y", *chartInstance->c2_nL_1RF, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 14, c2_p_y);
  c2_q_y = NULL;
  sf_mex_assign(&c2_q_y, sf_mex_create("y", *chartInstance->c2_nL_1RM, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 15, c2_q_y);
  c2_r_y = NULL;
  sf_mex_assign(&c2_r_y, sf_mex_create("y", *chartInstance->c2_nL_1SF, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 16, c2_r_y);
  c2_s_y = NULL;
  sf_mex_assign(&c2_s_y, sf_mex_create("y", *chartInstance->c2_nL_1SM, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 17, c2_s_y);
  c2_t_y = NULL;
  sf_mex_assign(&c2_t_y, sf_mex_create("y", *chartInstance->c2_nL_2CF, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 18, c2_t_y);
  c2_u_y = NULL;
  sf_mex_assign(&c2_u_y, sf_mex_create("y", *chartInstance->c2_nL_2CM, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 19, c2_u_y);
  c2_v_y = NULL;
  sf_mex_assign(&c2_v_y, sf_mex_create("y", *chartInstance->c2_nL_2RF, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 20, c2_v_y);
  c2_w_y = NULL;
  sf_mex_assign(&c2_w_y, sf_mex_create("y", *chartInstance->c2_nL_2RM, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 21, c2_w_y);
  c2_x_y = NULL;
  sf_mex_assign(&c2_x_y, sf_mex_create("y", *chartInstance->c2_nL_2SF, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 22, c2_x_y);
  c2_y_y = NULL;
  sf_mex_assign(&c2_y_y, sf_mex_create("y", *chartInstance->c2_nL_2SM, 0, 0U, 1U,
    0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 23, c2_y_y);
  c2_f_hoistedGlobal = chartInstance->c2_is_active_c2_mut_screen;
  c2_f_u = c2_f_hoistedGlobal;
  c2_ab_y = NULL;
  sf_mex_assign(&c2_ab_y, sf_mex_create("y", &c2_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 24, c2_ab_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[2];
  int32_T c2_i0;
  real_T c2_dv1[2];
  int32_T c2_i1;
  real_T c2_dv2[2];
  int32_T c2_i2;
  real_T c2_dv3[2];
  int32_T c2_i3;
  real_T c2_dv4[2];
  int32_T c2_i4;
  real_T c2_dv5[2];
  int32_T c2_i5;
  real_T c2_dv6[2];
  int32_T c2_i6;
  real_T c2_dv7[2];
  int32_T c2_i7;
  real_T c2_dv8[2];
  int32_T c2_i8;
  real_T c2_dv9[2];
  int32_T c2_i9;
  real_T c2_dv10[2];
  int32_T c2_i10;
  real_T c2_dv11[2];
  int32_T c2_i11;
  real_T c2_dv12[2];
  int32_T c2_i12;
  real_T c2_dv13[2];
  int32_T c2_i13;
  real_T c2_dv14[2];
  int32_T c2_i14;
  real_T c2_dv15[2];
  int32_T c2_i15;
  real_T c2_dv16[2];
  int32_T c2_i16;
  real_T c2_dv17[2];
  int32_T c2_i17;
  real_T c2_dv18[2];
  int32_T c2_i18;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  *chartInstance->c2_A_0CM = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("A_0CM", c2_u, 0)), "A_0CM");
  *chartInstance->c2_L_T = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("L_T", c2_u, 1)), "L_T");
  *chartInstance->c2_f_0T = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("f_0T", c2_u, 2)), "f_0T");
  *chartInstance->c2_f_1T = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("f_1T", c2_u, 3)), "f_1T");
  *chartInstance->c2_f_2T = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("f_2T", c2_u, 4)), "f_2T");
  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("leaving_0CM",
    c2_u, 5)), "leaving_0CM", c2_dv0);
  for (c2_i0 = 0; c2_i0 < 2; c2_i0++) {
    (*chartInstance->c2_leaving_0CM)[c2_i0] = c2_dv0[c2_i0];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_0CF", c2_u,
    6)), "nL_0CF", c2_dv1);
  for (c2_i1 = 0; c2_i1 < 2; c2_i1++) {
    (*chartInstance->c2_nL_0CF)[c2_i1] = c2_dv1[c2_i1];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_0CM", c2_u,
    7)), "nL_0CM", c2_dv2);
  for (c2_i2 = 0; c2_i2 < 2; c2_i2++) {
    (*chartInstance->c2_nL_0CM)[c2_i2] = c2_dv2[c2_i2];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_0RF", c2_u,
    8)), "nL_0RF", c2_dv3);
  for (c2_i3 = 0; c2_i3 < 2; c2_i3++) {
    (*chartInstance->c2_nL_0RF)[c2_i3] = c2_dv3[c2_i3];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_0RM", c2_u,
    9)), "nL_0RM", c2_dv4);
  for (c2_i4 = 0; c2_i4 < 2; c2_i4++) {
    (*chartInstance->c2_nL_0RM)[c2_i4] = c2_dv4[c2_i4];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_0SF", c2_u,
    10)), "nL_0SF", c2_dv5);
  for (c2_i5 = 0; c2_i5 < 2; c2_i5++) {
    (*chartInstance->c2_nL_0SF)[c2_i5] = c2_dv5[c2_i5];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_0SM", c2_u,
    11)), "nL_0SM", c2_dv6);
  for (c2_i6 = 0; c2_i6 < 2; c2_i6++) {
    (*chartInstance->c2_nL_0SM)[c2_i6] = c2_dv6[c2_i6];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_1CF", c2_u,
    12)), "nL_1CF", c2_dv7);
  for (c2_i7 = 0; c2_i7 < 2; c2_i7++) {
    (*chartInstance->c2_nL_1CF)[c2_i7] = c2_dv7[c2_i7];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_1CM", c2_u,
    13)), "nL_1CM", c2_dv8);
  for (c2_i8 = 0; c2_i8 < 2; c2_i8++) {
    (*chartInstance->c2_nL_1CM)[c2_i8] = c2_dv8[c2_i8];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_1RF", c2_u,
    14)), "nL_1RF", c2_dv9);
  for (c2_i9 = 0; c2_i9 < 2; c2_i9++) {
    (*chartInstance->c2_nL_1RF)[c2_i9] = c2_dv9[c2_i9];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_1RM", c2_u,
    15)), "nL_1RM", c2_dv10);
  for (c2_i10 = 0; c2_i10 < 2; c2_i10++) {
    (*chartInstance->c2_nL_1RM)[c2_i10] = c2_dv10[c2_i10];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_1SF", c2_u,
    16)), "nL_1SF", c2_dv11);
  for (c2_i11 = 0; c2_i11 < 2; c2_i11++) {
    (*chartInstance->c2_nL_1SF)[c2_i11] = c2_dv11[c2_i11];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_1SM", c2_u,
    17)), "nL_1SM", c2_dv12);
  for (c2_i12 = 0; c2_i12 < 2; c2_i12++) {
    (*chartInstance->c2_nL_1SM)[c2_i12] = c2_dv12[c2_i12];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_2CF", c2_u,
    18)), "nL_2CF", c2_dv13);
  for (c2_i13 = 0; c2_i13 < 2; c2_i13++) {
    (*chartInstance->c2_nL_2CF)[c2_i13] = c2_dv13[c2_i13];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_2CM", c2_u,
    19)), "nL_2CM", c2_dv14);
  for (c2_i14 = 0; c2_i14 < 2; c2_i14++) {
    (*chartInstance->c2_nL_2CM)[c2_i14] = c2_dv14[c2_i14];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_2RF", c2_u,
    20)), "nL_2RF", c2_dv15);
  for (c2_i15 = 0; c2_i15 < 2; c2_i15++) {
    (*chartInstance->c2_nL_2RF)[c2_i15] = c2_dv15[c2_i15];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_2RM", c2_u,
    21)), "nL_2RM", c2_dv16);
  for (c2_i16 = 0; c2_i16 < 2; c2_i16++) {
    (*chartInstance->c2_nL_2RM)[c2_i16] = c2_dv16[c2_i16];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_2SF", c2_u,
    22)), "nL_2SF", c2_dv17);
  for (c2_i17 = 0; c2_i17 < 2; c2_i17++) {
    (*chartInstance->c2_nL_2SF)[c2_i17] = c2_dv17[c2_i17];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("nL_2SM", c2_u,
    23)), "nL_2SM", c2_dv18);
  for (c2_i18 = 0; c2_i18 < 2; c2_i18++) {
    (*chartInstance->c2_nL_2SM)[c2_i18] = c2_dv18[c2_i18];
  }

  chartInstance->c2_is_active_c2_mut_screen = c2_m_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c2_mut_screen", c2_u,
       24)), "is_active_c2_mut_screen");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_mut_screen(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_mut_screen(SFc2_mut_screenInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance)
{
  int32_T c2_i19;
  int32_T c2_i20;
  int32_T c2_i21;
  int32_T c2_i22;
  int32_T c2_i23;
  int32_T c2_i24;
  int32_T c2_i25;
  int32_T c2_i26;
  int32_T c2_i27;
  int32_T c2_i28;
  int32_T c2_i29;
  int32_T c2_i30;
  int32_T c2_i31;
  int32_T c2_i32;
  int32_T c2_i33;
  int32_T c2_i34;
  int32_T c2_i35;
  int32_T c2_i36;
  int32_T c2_i37;
  int32_T c2_i38;
  int32_T c2_i39;
  int32_T c2_i40;
  int32_T c2_i41;
  int32_T c2_i42;
  int32_T c2_i43;
  int32_T c2_i44;
  int32_T c2_i45;
  int32_T c2_i46;
  int32_T c2_i47;
  int32_T c2_i48;
  int32_T c2_i49;
  int32_T c2_i50;
  int32_T c2_i51;
  int32_T c2_i52;
  int32_T c2_i53;
  int32_T c2_i54;
  int32_T c2_i55;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i19 = 0; c2_i19 < 2; c2_i19++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_2SF)[c2_i19], 18U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i20 = 0; c2_i20 < 2; c2_i20++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_1SF)[c2_i20], 17U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i21 = 0; c2_i21 < 2; c2_i21++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_0SF)[c2_i21], 16U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i22 = 0; c2_i22 < 2; c2_i22++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_2RF)[c2_i22], 15U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i23 = 0; c2_i23 < 2; c2_i23++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_1RF)[c2_i23], 14U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i24 = 0; c2_i24 < 2; c2_i24++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_0RF)[c2_i24], 13U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i25 = 0; c2_i25 < 2; c2_i25++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_2CF)[c2_i25], 12U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i26 = 0; c2_i26 < 2; c2_i26++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_1CF)[c2_i26], 11U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i27 = 0; c2_i27 < 2; c2_i27++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_0CF)[c2_i27], 10U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i28 = 0; c2_i28 < 2; c2_i28++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_2SM)[c2_i28], 9U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i29 = 0; c2_i29 < 2; c2_i29++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_1SM)[c2_i29], 8U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i30 = 0; c2_i30 < 2; c2_i30++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_0SM)[c2_i30], 7U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i31 = 0; c2_i31 < 2; c2_i31++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_2RM)[c2_i31], 6U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i32 = 0; c2_i32 < 2; c2_i32++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_1RM)[c2_i32], 5U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i33 = 0; c2_i33 < 2; c2_i33++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_0RM)[c2_i33], 4U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i34 = 0; c2_i34 < 2; c2_i34++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_2CM)[c2_i34], 3U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i35 = 0; c2_i35 < 2; c2_i35++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_1CM)[c2_i35], 2U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i36 = 0; c2_i36 < 2; c2_i36++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_L_0CM)[c2_i36], 1U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_clock, 0U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_mut_screen(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_mut_screenMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c2_i37 = 0; c2_i37 < 2; c2_i37++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_0CM)[c2_i37], 19U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i38 = 0; c2_i38 < 2; c2_i38++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_1CM)[c2_i38], 20U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i39 = 0; c2_i39 < 2; c2_i39++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_2CM)[c2_i39], 21U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i40 = 0; c2_i40 < 2; c2_i40++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_0RM)[c2_i40], 22U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i41 = 0; c2_i41 < 2; c2_i41++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_1RM)[c2_i41], 23U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i42 = 0; c2_i42 < 2; c2_i42++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_2RM)[c2_i42], 24U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i43 = 0; c2_i43 < 2; c2_i43++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_0SM)[c2_i43], 25U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i44 = 0; c2_i44 < 2; c2_i44++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_1SM)[c2_i44], 26U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i45 = 0; c2_i45 < 2; c2_i45++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_2SM)[c2_i45], 27U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i46 = 0; c2_i46 < 2; c2_i46++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_0CF)[c2_i46], 28U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i47 = 0; c2_i47 < 2; c2_i47++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_1CF)[c2_i47], 29U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i48 = 0; c2_i48 < 2; c2_i48++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_2CF)[c2_i48], 30U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i49 = 0; c2_i49 < 2; c2_i49++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_0RF)[c2_i49], 31U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i50 = 0; c2_i50 < 2; c2_i50++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_1RF)[c2_i50], 32U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i51 = 0; c2_i51 < 2; c2_i51++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_2RF)[c2_i51], 33U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i52 = 0; c2_i52 < 2; c2_i52++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_0SF)[c2_i52], 34U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i53 = 0; c2_i53 < 2; c2_i53++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_1SF)[c2_i53], 35U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i54 = 0; c2_i54 < 2; c2_i54++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_nL_2SF)[c2_i54], 36U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_A_0CM, 37U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  for (c2_i55 = 0; c2_i55 < 2; c2_i55++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_leaving_0CM)[c2_i55], 38U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_L_T, 39U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_f_0T, 40U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_f_1T, 41U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_f_2T, 42U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
}

static void mdl_start_c2_mut_screen(SFc2_mut_screenInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_chartstep_c2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_clock;
  int32_T c2_i56;
  real_T c2_b_L_0CM[2];
  int32_T c2_i57;
  real_T c2_b_L_1CM[2];
  int32_T c2_i58;
  real_T c2_b_L_2CM[2];
  int32_T c2_i59;
  real_T c2_b_L_0RM[2];
  int32_T c2_i60;
  real_T c2_b_L_1RM[2];
  int32_T c2_i61;
  real_T c2_b_L_2RM[2];
  int32_T c2_i62;
  real_T c2_b_L_0SM[2];
  int32_T c2_i63;
  real_T c2_b_L_1SM[2];
  int32_T c2_i64;
  real_T c2_b_L_2SM[2];
  int32_T c2_i65;
  real_T c2_b_L_0CF[2];
  int32_T c2_i66;
  real_T c2_b_L_1CF[2];
  int32_T c2_i67;
  real_T c2_b_L_2CF[2];
  int32_T c2_i68;
  real_T c2_b_L_0RF[2];
  int32_T c2_i69;
  real_T c2_b_L_1RF[2];
  int32_T c2_i70;
  real_T c2_b_L_2RF[2];
  int32_T c2_i71;
  real_T c2_b_L_0SF[2];
  int32_T c2_i72;
  real_T c2_b_L_1SF[2];
  int32_T c2_i73;
  real_T c2_b_L_2SF[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_b_mut;
  uint32_T c2_debug_family_var_map[124];
  real_T c2_here;
  real_T c2_A_1CM;
  real_T c2_A_2CM;
  real_T c2_A_0CF;
  real_T c2_A_1CF;
  real_T c2_A_2CF;
  real_T c2_A_0RM;
  real_T c2_A_1RM;
  real_T c2_A_2RM;
  real_T c2_A_0RF;
  real_T c2_A_1RF;
  real_T c2_A_2RF;
  real_T c2_A_0SM;
  real_T c2_A_1SM;
  real_T c2_A_2SM;
  real_T c2_A_0SF;
  real_T c2_A_1SF;
  real_T c2_A_2SF;
  real_T c2_new_0CM;
  real_T c2_new_1CM;
  real_T c2_new_2CM;
  real_T c2_new_0CF;
  real_T c2_new_1CF;
  real_T c2_new_2CF;
  real_T c2_expiring_0CM;
  real_T c2_expiring_1CM;
  real_T c2_expiring_2CM;
  real_T c2_expiring_0CF;
  real_T c2_expiring_1CF;
  real_T c2_expiring_2CF;
  real_T c2_expiring_0RM;
  real_T c2_expiring_1RM;
  real_T c2_expiring_2RM;
  real_T c2_expiring_0RF;
  real_T c2_expiring_1RF;
  real_T c2_expiring_2RF;
  real_T c2_expiring_0SM;
  real_T c2_expiring_1SM;
  real_T c2_expiring_2SM;
  real_T c2_expiring_0SF;
  real_T c2_expiring_1SF;
  real_T c2_expiring_2SF;
  real_T c2_leaving_1CM[2];
  real_T c2_leaving_2CM[2];
  real_T c2_leaving_0CF[2];
  real_T c2_leaving_1CF[2];
  real_T c2_leaving_2CF[2];
  real_T c2_leaving_0RM[2];
  real_T c2_leaving_1RM[2];
  real_T c2_leaving_2RM[2];
  real_T c2_leaving_0RF[2];
  real_T c2_leaving_1RF[2];
  real_T c2_leaving_2RF[2];
  real_T c2_incoming_0RM[2];
  real_T c2_incoming_1RM[2];
  real_T c2_incoming_2RM[2];
  real_T c2_incoming_0RF[2];
  real_T c2_incoming_1RF[2];
  real_T c2_incoming_2RF[2];
  real_T c2_incoming_0SM[2];
  real_T c2_incoming_1SM[2];
  real_T c2_incoming_2SM[2];
  real_T c2_incoming_0SF[2];
  real_T c2_incoming_1SF[2];
  real_T c2_incoming_2SF[2];
  real_T c2_LX[18];
  real_T c2_L_CMT;
  real_T c2_L_CFT;
  real_T c2_L_RMT;
  real_T c2_L_RFT;
  real_T c2_L_SMT;
  real_T c2_L_SFT;
  real_T c2_L_T0;
  real_T c2_L_T1;
  real_T c2_L_T2;
  real_T c2_L_TC;
  real_T c2_L_TR;
  real_T c2_L_TS;
  real_T c2_nargin = 20.0;
  real_T c2_nargout = 24.0;
  real_T c2_b_nL_0CM[2];
  real_T c2_b_nL_1CM[2];
  real_T c2_b_nL_2CM[2];
  real_T c2_b_nL_0RM[2];
  real_T c2_b_nL_1RM[2];
  real_T c2_b_nL_2RM[2];
  real_T c2_b_nL_0SM[2];
  real_T c2_b_nL_1SM[2];
  real_T c2_b_nL_2SM[2];
  real_T c2_b_nL_0CF[2];
  real_T c2_b_nL_1CF[2];
  real_T c2_b_nL_2CF[2];
  real_T c2_b_nL_0RF[2];
  real_T c2_b_nL_1RF[2];
  real_T c2_b_nL_2RF[2];
  real_T c2_b_nL_0SF[2];
  real_T c2_b_nL_1SF[2];
  real_T c2_b_nL_2SF[2];
  real_T c2_b_A_0CM;
  real_T c2_b_leaving_0CM[2];
  real_T c2_b_L_T;
  real_T c2_b_f_0T;
  real_T c2_b_f_1T;
  real_T c2_b_f_2T;
  int32_T c2_i74;
  int32_T c2_i75;
  int32_T c2_i76;
  int32_T c2_i77;
  int32_T c2_i78;
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  int32_T c2_i82;
  int32_T c2_i83;
  int32_T c2_i84;
  int32_T c2_i85;
  int32_T c2_i86;
  int32_T c2_i87;
  int32_T c2_i88;
  int32_T c2_i89;
  int32_T c2_i90;
  int32_T c2_i91;
  real_T c2_A;
  real_T c2_B;
  real_T c2_x;
  real_T c2_y;
  real_T c2_b_x;
  real_T c2_b_y;
  real_T c2_b_A;
  real_T c2_b_B;
  real_T c2_c_x;
  real_T c2_c_y;
  real_T c2_d_x;
  real_T c2_d_y;
  real_T c2_c_A;
  real_T c2_c_B;
  real_T c2_e_x;
  real_T c2_e_y;
  real_T c2_f_x;
  real_T c2_f_y;
  real_T c2_d_A;
  real_T c2_d_B;
  real_T c2_g_x;
  real_T c2_g_y;
  real_T c2_h_x;
  real_T c2_h_y;
  real_T c2_e_A;
  real_T c2_e_B;
  real_T c2_i_x;
  real_T c2_i_y;
  real_T c2_j_x;
  real_T c2_j_y;
  real_T c2_f_A;
  real_T c2_f_B;
  real_T c2_k_x;
  real_T c2_k_y;
  real_T c2_l_x;
  real_T c2_l_y;
  real_T c2_g_A;
  real_T c2_g_B;
  real_T c2_m_x;
  real_T c2_m_y;
  real_T c2_n_x;
  real_T c2_n_y;
  real_T c2_h_A;
  real_T c2_h_B;
  real_T c2_o_x;
  real_T c2_o_y;
  real_T c2_p_x;
  real_T c2_p_y;
  real_T c2_i_A;
  real_T c2_i_B;
  real_T c2_q_x;
  real_T c2_q_y;
  real_T c2_r_x;
  real_T c2_r_y;
  real_T c2_j_A;
  real_T c2_j_B;
  real_T c2_s_x;
  real_T c2_s_y;
  real_T c2_t_x;
  real_T c2_t_y;
  real_T c2_k_A;
  real_T c2_k_B;
  real_T c2_u_x;
  real_T c2_u_y;
  real_T c2_v_x;
  real_T c2_v_y;
  real_T c2_l_A;
  real_T c2_l_B;
  real_T c2_w_x;
  real_T c2_w_y;
  real_T c2_x_x;
  real_T c2_x_y;
  real_T c2_m_A;
  real_T c2_m_B;
  real_T c2_y_x;
  real_T c2_y_y;
  real_T c2_ab_x;
  real_T c2_ab_y;
  real_T c2_n_A;
  real_T c2_n_B;
  real_T c2_bb_x;
  real_T c2_bb_y;
  real_T c2_cb_x;
  real_T c2_cb_y;
  real_T c2_o_A;
  real_T c2_o_B;
  real_T c2_db_x;
  real_T c2_db_y;
  real_T c2_eb_x;
  real_T c2_eb_y;
  real_T c2_p_A;
  real_T c2_p_B;
  real_T c2_fb_x;
  real_T c2_fb_y;
  real_T c2_gb_x;
  real_T c2_gb_y;
  real_T c2_q_A;
  real_T c2_q_B;
  real_T c2_hb_x;
  real_T c2_hb_y;
  real_T c2_ib_x;
  real_T c2_ib_y;
  real_T c2_r_A;
  real_T c2_r_B;
  real_T c2_jb_x;
  real_T c2_jb_y;
  real_T c2_kb_x;
  real_T c2_kb_y;
  int32_T c2_i92;
  real_T c2_c_L_0RM[2];
  int32_T c2_i93;
  real_T c2_c_L_1RM[2];
  int32_T c2_i94;
  real_T c2_c_L_2RM[2];
  int32_T c2_i95;
  real_T c2_c_L_0RF[2];
  int32_T c2_i96;
  real_T c2_c_L_1RF[2];
  int32_T c2_i97;
  real_T c2_c_L_2RF[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_c_mut;
  real_T c2_b_new_2CF;
  real_T c2_b_new_1CF;
  real_T c2_b_new_0CF;
  real_T c2_b_new_2CM;
  real_T c2_b_new_1CM;
  real_T c2_b_new_0CM;
  int32_T c2_i98;
  real_T c2_c_L_0CM[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_d_mut;
  real_T c2_dv19[2];
  int32_T c2_i99;
  int32_T c2_i100;
  real_T c2_c_L_1CM[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_e_mut;
  real_T c2_dv20[2];
  int32_T c2_i101;
  int32_T c2_i102;
  real_T c2_c_L_2CM[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_f_mut;
  real_T c2_dv21[2];
  int32_T c2_i103;
  int32_T c2_i104;
  real_T c2_c_L_0CF[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_g_mut;
  real_T c2_dv22[2];
  int32_T c2_i105;
  int32_T c2_i106;
  real_T c2_c_L_1CF[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_h_mut;
  real_T c2_dv23[2];
  int32_T c2_i107;
  int32_T c2_i108;
  real_T c2_c_L_2CF[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_i_mut;
  real_T c2_dv24[2];
  int32_T c2_i109;
  int32_T c2_i110;
  real_T c2_d_L_0RM[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_j_mut;
  real_T c2_dv25[2];
  int32_T c2_i111;
  int32_T c2_i112;
  real_T c2_d_L_1RM[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_k_mut;
  real_T c2_dv26[2];
  int32_T c2_i113;
  int32_T c2_i114;
  real_T c2_d_L_2RM[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_l_mut;
  real_T c2_dv27[2];
  int32_T c2_i115;
  int32_T c2_i116;
  real_T c2_d_L_0RF[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_m_mut;
  real_T c2_dv28[2];
  int32_T c2_i117;
  int32_T c2_i118;
  real_T c2_d_L_1RF[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_n_mut;
  real_T c2_dv29[2];
  int32_T c2_i119;
  int32_T c2_i120;
  real_T c2_d_L_2RF[2];
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_o_mut;
  real_T c2_dv30[2];
  int32_T c2_i121;
  int32_T c2_i122;
  int32_T c2_i123;
  int32_T c2_i124;
  int32_T c2_i125;
  int32_T c2_i126;
  int32_T c2_i127;
  int32_T c2_i128;
  int32_T c2_i129;
  int32_T c2_i130;
  int32_T c2_i131;
  int32_T c2_i132;
  int32_T c2_i133;
  int32_T c2_i134;
  real_T c2_b_LX[3];
  int32_T c2_i135;
  real_T c2_c_LX[3];
  int32_T c2_i136;
  real_T c2_d_LX[3];
  int32_T c2_i137;
  real_T c2_e_LX[3];
  int32_T c2_i138;
  real_T c2_f_LX[3];
  int32_T c2_i139;
  real_T c2_g_LX[3];
  int32_T c2_i140;
  int32_T c2_i141;
  real_T c2_h_LX[6];
  int32_T c2_i142;
  int32_T c2_i143;
  real_T c2_i_LX[6];
  int32_T c2_i144;
  int32_T c2_i145;
  real_T c2_j_LX[6];
  real_T c2_s_A;
  real_T c2_s_B;
  real_T c2_lb_x;
  real_T c2_lb_y;
  real_T c2_mb_x;
  real_T c2_mb_y;
  real_T c2_nb_y;
  real_T c2_t_A;
  real_T c2_t_B;
  real_T c2_nb_x;
  real_T c2_ob_y;
  real_T c2_ob_x;
  real_T c2_pb_y;
  real_T c2_qb_y;
  real_T c2_u_A;
  real_T c2_u_B;
  real_T c2_pb_x;
  real_T c2_rb_y;
  real_T c2_qb_x;
  real_T c2_sb_y;
  real_T c2_tb_y;
  int32_T c2_i146;
  int32_T c2_i147;
  int32_T c2_i148;
  int32_T c2_i149;
  int32_T c2_i150;
  int32_T c2_i151;
  int32_T c2_i152;
  int32_T c2_i153;
  int32_T c2_i154;
  int32_T c2_i155;
  int32_T c2_i156;
  int32_T c2_i157;
  int32_T c2_i158;
  int32_T c2_i159;
  int32_T c2_i160;
  int32_T c2_i161;
  int32_T c2_i162;
  int32_T c2_i163;
  int32_T c2_i164;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *chartInstance->c2_clock;
  c2_b_clock = c2_hoistedGlobal;
  for (c2_i56 = 0; c2_i56 < 2; c2_i56++) {
    c2_b_L_0CM[c2_i56] = (*chartInstance->c2_L_0CM)[c2_i56];
  }

  for (c2_i57 = 0; c2_i57 < 2; c2_i57++) {
    c2_b_L_1CM[c2_i57] = (*chartInstance->c2_L_1CM)[c2_i57];
  }

  for (c2_i58 = 0; c2_i58 < 2; c2_i58++) {
    c2_b_L_2CM[c2_i58] = (*chartInstance->c2_L_2CM)[c2_i58];
  }

  for (c2_i59 = 0; c2_i59 < 2; c2_i59++) {
    c2_b_L_0RM[c2_i59] = (*chartInstance->c2_L_0RM)[c2_i59];
  }

  for (c2_i60 = 0; c2_i60 < 2; c2_i60++) {
    c2_b_L_1RM[c2_i60] = (*chartInstance->c2_L_1RM)[c2_i60];
  }

  for (c2_i61 = 0; c2_i61 < 2; c2_i61++) {
    c2_b_L_2RM[c2_i61] = (*chartInstance->c2_L_2RM)[c2_i61];
  }

  for (c2_i62 = 0; c2_i62 < 2; c2_i62++) {
    c2_b_L_0SM[c2_i62] = (*chartInstance->c2_L_0SM)[c2_i62];
  }

  for (c2_i63 = 0; c2_i63 < 2; c2_i63++) {
    c2_b_L_1SM[c2_i63] = (*chartInstance->c2_L_1SM)[c2_i63];
  }

  for (c2_i64 = 0; c2_i64 < 2; c2_i64++) {
    c2_b_L_2SM[c2_i64] = (*chartInstance->c2_L_2SM)[c2_i64];
  }

  for (c2_i65 = 0; c2_i65 < 2; c2_i65++) {
    c2_b_L_0CF[c2_i65] = (*chartInstance->c2_L_0CF)[c2_i65];
  }

  for (c2_i66 = 0; c2_i66 < 2; c2_i66++) {
    c2_b_L_1CF[c2_i66] = (*chartInstance->c2_L_1CF)[c2_i66];
  }

  for (c2_i67 = 0; c2_i67 < 2; c2_i67++) {
    c2_b_L_2CF[c2_i67] = (*chartInstance->c2_L_2CF)[c2_i67];
  }

  for (c2_i68 = 0; c2_i68 < 2; c2_i68++) {
    c2_b_L_0RF[c2_i68] = (*chartInstance->c2_L_0RF)[c2_i68];
  }

  for (c2_i69 = 0; c2_i69 < 2; c2_i69++) {
    c2_b_L_1RF[c2_i69] = (*chartInstance->c2_L_1RF)[c2_i69];
  }

  for (c2_i70 = 0; c2_i70 < 2; c2_i70++) {
    c2_b_L_2RF[c2_i70] = (*chartInstance->c2_L_2RF)[c2_i70];
  }

  for (c2_i71 = 0; c2_i71 < 2; c2_i71++) {
    c2_b_L_0SF[c2_i71] = (*chartInstance->c2_L_0SF)[c2_i71];
  }

  for (c2_i72 = 0; c2_i72 < 2; c2_i72++) {
    c2_b_L_1SF[c2_i72] = (*chartInstance->c2_L_1SF)[c2_i72];
  }

  for (c2_i73 = 0; c2_i73 < 2; c2_i73++) {
    c2_b_L_2SF[c2_i73] = (*chartInstance->c2_L_2SF)[c2_i73];
  }

  c2_b_mut = chartInstance->c2_mut;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 124U, 124U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_here, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_1CM, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_2CM, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_0CF, 3U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_1CF, 4U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_2CF, 5U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_0RM, 6U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_1RM, 7U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_2RM, 8U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_0RF, 9U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_1RF, 10U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_2RF, 11U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_0SM, 12U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_1SM, 13U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_2SM, 14U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_0SF, 15U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_1SF, 16U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A_2SF, 17U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_new_0CM, 18U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_new_1CM, 19U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_new_2CM, 20U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_new_0CF, 21U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_new_1CF, 22U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_new_2CF, 23U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_0CM, 24U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_1CM, 25U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_2CM, 26U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_0CF, 27U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_1CF, 28U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_2CF, 29U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_0RM, 30U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_1RM, 31U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_2RM, 32U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_0RF, 33U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_1RF, 34U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_2RF, 35U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_0SM, 36U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_1SM, 37U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_2SM, 38U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_0SF, 39U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_1SF, 40U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring_2SF, 41U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving_1CM, 42U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving_2CM, 43U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving_0CF, 44U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving_1CF, 45U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving_2CF, 46U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving_0RM, 47U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving_1RM, 48U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving_2RM, 49U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving_0RF, 50U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving_1RF, 51U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving_2RF, 52U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_0RM, 53U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_1RM, 54U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_2RM, 55U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_0RF, 56U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_1RF, 57U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_2RF, 58U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_0SM, 59U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_1SM, 60U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_2SM, 61U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_0SF, 62U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_1SF, 63U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_incoming_2SF, 64U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_LX, 65U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_CMT, 66U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_CFT, 67U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_RMT, 68U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_RFT, 69U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_SMT, 70U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_SFT, 71U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_T0, 72U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_T1, 73U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_T2, 74U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_TC, 75U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_TR, 76U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_TS, 77U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 78U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 79U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_clock, 80U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_0CM, 81U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_1CM, 82U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_2CM, 83U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_0RM, 84U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_1RM, 85U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_2RM, 86U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_0SM, 87U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_1SM, 88U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_2SM, 89U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_0CF, 90U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_1CF, 91U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_2CF, 92U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_0RF, 93U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_1RF, 94U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_2RF, 95U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_0SF, 96U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_1SF, 97U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_L_2SF, 98U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_mut, 99U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_0CM, 100U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_1CM, 101U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_2CM, 102U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_0RM, 103U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_1RM, 104U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_2RM, 105U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_0SM, 106U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_1SM, 107U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_2SM, 108U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_0CF, 109U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_1CF, 110U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_2CF, 111U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_0RF, 112U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_1RF, 113U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_2RF, 114U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_0SF, 115U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_1SF, 116U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_nL_2SF, 117U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_A_0CM, 118U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_leaving_0CM, 119U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_L_T, 120U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_f_0T, 121U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_f_1T, 122U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_f_2T, 123U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 16);
  if (CV_EML_IF(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 0, c2_b_clock, 35.0, -1, 5U,
        c2_b_clock >= 35.0))) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 17);
    c2_here = 1.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
  for (c2_i74 = 0; c2_i74 < 2; c2_i74++) {
    c2_b_nL_0CM[c2_i74] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 21);
  for (c2_i75 = 0; c2_i75 < 2; c2_i75++) {
    c2_b_nL_1CM[c2_i75] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
  for (c2_i76 = 0; c2_i76 < 2; c2_i76++) {
    c2_b_nL_2CM[c2_i76] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
  for (c2_i77 = 0; c2_i77 < 2; c2_i77++) {
    c2_b_nL_0CF[c2_i77] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 24);
  for (c2_i78 = 0; c2_i78 < 2; c2_i78++) {
    c2_b_nL_1CF[c2_i78] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
  for (c2_i79 = 0; c2_i79 < 2; c2_i79++) {
    c2_b_nL_2CF[c2_i79] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 26);
  for (c2_i80 = 0; c2_i80 < 2; c2_i80++) {
    c2_b_nL_0RM[c2_i80] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
  for (c2_i81 = 0; c2_i81 < 2; c2_i81++) {
    c2_b_nL_1RM[c2_i81] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  for (c2_i82 = 0; c2_i82 < 2; c2_i82++) {
    c2_b_nL_2RM[c2_i82] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
  for (c2_i83 = 0; c2_i83 < 2; c2_i83++) {
    c2_b_nL_0RF[c2_i83] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
  for (c2_i84 = 0; c2_i84 < 2; c2_i84++) {
    c2_b_nL_1RF[c2_i84] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  for (c2_i85 = 0; c2_i85 < 2; c2_i85++) {
    c2_b_nL_2RF[c2_i85] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
  for (c2_i86 = 0; c2_i86 < 2; c2_i86++) {
    c2_b_nL_0SM[c2_i86] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 33);
  for (c2_i87 = 0; c2_i87 < 2; c2_i87++) {
    c2_b_nL_1SM[c2_i87] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
  for (c2_i88 = 0; c2_i88 < 2; c2_i88++) {
    c2_b_nL_2SM[c2_i88] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
  for (c2_i89 = 0; c2_i89 < 2; c2_i89++) {
    c2_b_nL_0SF[c2_i89] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 36);
  for (c2_i90 = 0; c2_i90 < 2; c2_i90++) {
    c2_b_nL_1SF[c2_i90] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 37);
  for (c2_i91 = 0; c2_i91 < 2; c2_i91++) {
    c2_b_nL_2SF[c2_i91] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 40);
  c2_A = c2_b_L_0CM[1];
  c2_B = c2_b_L_0CM[0];
  c2_x = c2_A;
  c2_y = c2_B;
  c2_b_x = c2_x;
  c2_b_y = c2_y;
  c2_b_A_0CM = c2_b_x / c2_b_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 41);
  c2_b_A = c2_b_L_1CM[1];
  c2_b_B = c2_b_L_1CM[0];
  c2_c_x = c2_b_A;
  c2_c_y = c2_b_B;
  c2_d_x = c2_c_x;
  c2_d_y = c2_c_y;
  c2_A_1CM = c2_d_x / c2_d_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 42);
  c2_c_A = c2_b_L_2CM[1];
  c2_c_B = c2_b_L_2CM[0];
  c2_e_x = c2_c_A;
  c2_e_y = c2_c_B;
  c2_f_x = c2_e_x;
  c2_f_y = c2_e_y;
  c2_A_2CM = c2_f_x / c2_f_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  c2_d_A = c2_b_L_0CF[1];
  c2_d_B = c2_b_L_0CF[0];
  c2_g_x = c2_d_A;
  c2_g_y = c2_d_B;
  c2_h_x = c2_g_x;
  c2_h_y = c2_g_y;
  c2_A_0CF = c2_h_x / c2_h_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
  c2_e_A = c2_b_L_1CF[1];
  c2_e_B = c2_b_L_1CF[0];
  c2_i_x = c2_e_A;
  c2_i_y = c2_e_B;
  c2_j_x = c2_i_x;
  c2_j_y = c2_i_y;
  c2_A_1CF = c2_j_x / c2_j_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 45);
  c2_f_A = c2_b_L_2CF[1];
  c2_f_B = c2_b_L_2CF[0];
  c2_k_x = c2_f_A;
  c2_k_y = c2_f_B;
  c2_l_x = c2_k_x;
  c2_l_y = c2_k_y;
  c2_A_2CF = c2_l_x / c2_l_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 46);
  c2_g_A = c2_b_L_0RM[1];
  c2_g_B = c2_b_L_0RM[0];
  c2_m_x = c2_g_A;
  c2_m_y = c2_g_B;
  c2_n_x = c2_m_x;
  c2_n_y = c2_m_y;
  c2_A_0RM = c2_n_x / c2_n_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
  c2_h_A = c2_b_L_1RM[1];
  c2_h_B = c2_b_L_1RM[0];
  c2_o_x = c2_h_A;
  c2_o_y = c2_h_B;
  c2_p_x = c2_o_x;
  c2_p_y = c2_o_y;
  c2_A_1RM = c2_p_x / c2_p_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 48);
  c2_i_A = c2_b_L_2RM[1];
  c2_i_B = c2_b_L_2RM[0];
  c2_q_x = c2_i_A;
  c2_q_y = c2_i_B;
  c2_r_x = c2_q_x;
  c2_r_y = c2_q_y;
  c2_A_2RM = c2_r_x / c2_r_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 49);
  c2_j_A = c2_b_L_0RF[1];
  c2_j_B = c2_b_L_0RF[0];
  c2_s_x = c2_j_A;
  c2_s_y = c2_j_B;
  c2_t_x = c2_s_x;
  c2_t_y = c2_s_y;
  c2_A_0RF = c2_t_x / c2_t_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 50);
  c2_k_A = c2_b_L_1RF[1];
  c2_k_B = c2_b_L_1RF[0];
  c2_u_x = c2_k_A;
  c2_u_y = c2_k_B;
  c2_v_x = c2_u_x;
  c2_v_y = c2_u_y;
  c2_A_1RF = c2_v_x / c2_v_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 51);
  c2_l_A = c2_b_L_2RF[1];
  c2_l_B = c2_b_L_2RF[0];
  c2_w_x = c2_l_A;
  c2_w_y = c2_l_B;
  c2_x_x = c2_w_x;
  c2_x_y = c2_w_y;
  c2_A_2RF = c2_x_x / c2_x_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 52);
  c2_m_A = c2_b_L_0SM[1];
  c2_m_B = c2_b_L_0SM[0];
  c2_y_x = c2_m_A;
  c2_y_y = c2_m_B;
  c2_ab_x = c2_y_x;
  c2_ab_y = c2_y_y;
  c2_A_0SM = c2_ab_x / c2_ab_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 53);
  c2_n_A = c2_b_L_1SM[1];
  c2_n_B = c2_b_L_1SM[0];
  c2_bb_x = c2_n_A;
  c2_bb_y = c2_n_B;
  c2_cb_x = c2_bb_x;
  c2_cb_y = c2_bb_y;
  c2_A_1SM = c2_cb_x / c2_cb_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 54);
  c2_o_A = c2_b_L_2SM[1];
  c2_o_B = c2_b_L_2SM[0];
  c2_db_x = c2_o_A;
  c2_db_y = c2_o_B;
  c2_eb_x = c2_db_x;
  c2_eb_y = c2_db_y;
  c2_A_2SM = c2_eb_x / c2_eb_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 55);
  c2_p_A = c2_b_L_0SF[1];
  c2_p_B = c2_b_L_0SF[0];
  c2_fb_x = c2_p_A;
  c2_fb_y = c2_p_B;
  c2_gb_x = c2_fb_x;
  c2_gb_y = c2_fb_y;
  c2_A_0SF = c2_gb_x / c2_gb_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 56);
  c2_q_A = c2_b_L_1SF[1];
  c2_q_B = c2_b_L_1SF[0];
  c2_hb_x = c2_q_A;
  c2_hb_y = c2_q_B;
  c2_ib_x = c2_hb_x;
  c2_ib_y = c2_hb_y;
  c2_A_1SF = c2_ib_x / c2_ib_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 57);
  c2_r_A = c2_b_L_2SF[1];
  c2_r_B = c2_b_L_2SF[0];
  c2_jb_x = c2_r_A;
  c2_jb_y = c2_r_B;
  c2_kb_x = c2_jb_x;
  c2_kb_y = c2_jb_y;
  c2_A_2SF = c2_kb_x / c2_kb_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 60);
  for (c2_i92 = 0; c2_i92 < 2; c2_i92++) {
    c2_c_L_0RM[c2_i92] = c2_b_L_0RM[c2_i92];
  }

  for (c2_i93 = 0; c2_i93 < 2; c2_i93++) {
    c2_c_L_1RM[c2_i93] = c2_b_L_1RM[c2_i93];
  }

  for (c2_i94 = 0; c2_i94 < 2; c2_i94++) {
    c2_c_L_2RM[c2_i94] = c2_b_L_2RM[c2_i94];
  }

  for (c2_i95 = 0; c2_i95 < 2; c2_i95++) {
    c2_c_L_0RF[c2_i95] = c2_b_L_0RF[c2_i95];
  }

  for (c2_i96 = 0; c2_i96 < 2; c2_i96++) {
    c2_c_L_1RF[c2_i96] = c2_b_L_1RF[c2_i96];
  }

  for (c2_i97 = 0; c2_i97 < 2; c2_i97++) {
    c2_c_L_2RF[c2_i97] = c2_b_L_2RF[c2_i97];
  }

  c2_c_mut = c2_b_mut;
  c2_getNewChildrenMutations(chartInstance, c2_c_L_0RM, c2_c_L_1RM, c2_c_L_2RM,
    c2_c_L_0RF, c2_c_L_1RF, c2_c_L_2RF, &c2_c_mut, &c2_b_new_0CM, &c2_b_new_1CM,
    &c2_b_new_2CM, &c2_b_new_0CF, &c2_b_new_1CF, &c2_b_new_2CF);
  c2_new_0CM = c2_b_new_0CM;
  c2_new_1CM = c2_b_new_1CM;
  c2_new_2CM = c2_b_new_2CM;
  c2_new_0CF = c2_b_new_0CF;
  c2_new_1CF = c2_b_new_1CF;
  c2_new_2CF = c2_b_new_2CF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 68);
  c2_expiring_0CM = (c2_b_mut.muMort[0] + c2_b_mut.mort[0]) * c2_b_L_0CM[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 69);
  c2_expiring_1CM = (c2_b_mut.muMort[1] + c2_b_mut.mort[0]) * c2_b_L_1CM[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 70);
  c2_expiring_2CM = (c2_b_mut.muMort[2] + c2_b_mut.mort[0]) * c2_b_L_2CM[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 71);
  c2_expiring_0CF = (c2_b_mut.muMort[3] + c2_b_mut.mort[1]) * c2_b_L_0CF[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 72);
  c2_expiring_1CF = (c2_b_mut.muMort[4] + c2_b_mut.mort[1]) * c2_b_L_1CF[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 73);
  c2_expiring_2CF = (c2_b_mut.muMort[5] + c2_b_mut.mort[1]) * c2_b_L_2CF[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 75);
  c2_expiring_0RM = (c2_b_mut.muMort[6] + c2_b_mut.mort[2]) * c2_b_L_0RM[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 76);
  c2_expiring_1RM = (c2_b_mut.muMort[7] + c2_b_mut.mort[2]) * c2_b_L_1RM[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 77);
  c2_expiring_2RM = (c2_b_mut.muMort[8] + c2_b_mut.mort[2]) * c2_b_L_2RM[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 78);
  c2_expiring_0RF = (c2_b_mut.muMort[9] + c2_b_mut.mort[3]) * c2_b_L_0RF[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 79);
  c2_expiring_1RF = (c2_b_mut.muMort[10] + c2_b_mut.mort[3]) * c2_b_L_1RF[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 80);
  c2_expiring_2RF = (c2_b_mut.muMort[11] + c2_b_mut.mort[3]) * c2_b_L_2RF[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 82);
  c2_expiring_0SM = (c2_b_mut.muMort[12] + c2_b_mut.mort[4]) * c2_b_L_0SM[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 83);
  c2_expiring_1SM = (c2_b_mut.muMort[13] + c2_b_mut.mort[4]) * c2_b_L_1SM[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 84);
  c2_expiring_2SM = (c2_b_mut.muMort[14] + c2_b_mut.mort[4]) * c2_b_L_2SM[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 85);
  c2_expiring_0SF = (c2_b_mut.muMort[15] + c2_b_mut.mort[5]) * c2_b_L_0SF[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 86);
  c2_expiring_1SF = (c2_b_mut.muMort[16] + c2_b_mut.mort[5]) * c2_b_L_1SF[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 87);
  c2_expiring_2SF = (c2_b_mut.muMort[17] + c2_b_mut.mort[5]) * c2_b_L_2SF[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 91);
  for (c2_i98 = 0; c2_i98 < 2; c2_i98++) {
    c2_c_L_0CM[c2_i98] = c2_b_L_0CM[c2_i98];
  }

  c2_d_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_c_L_0CM, &c2_d_mut, c2_expiring_0CM, true,
                 c2_dv19);
  for (c2_i99 = 0; c2_i99 < 2; c2_i99++) {
    c2_b_leaving_0CM[c2_i99] = c2_dv19[c2_i99];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 92);
  for (c2_i100 = 0; c2_i100 < 2; c2_i100++) {
    c2_c_L_1CM[c2_i100] = c2_b_L_1CM[c2_i100];
  }

  c2_e_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_c_L_1CM, &c2_e_mut, c2_expiring_1CM, true,
                 c2_dv20);
  for (c2_i101 = 0; c2_i101 < 2; c2_i101++) {
    c2_leaving_1CM[c2_i101] = c2_dv20[c2_i101];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 93);
  for (c2_i102 = 0; c2_i102 < 2; c2_i102++) {
    c2_c_L_2CM[c2_i102] = c2_b_L_2CM[c2_i102];
  }

  c2_f_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_c_L_2CM, &c2_f_mut, c2_expiring_2CM, true,
                 c2_dv21);
  for (c2_i103 = 0; c2_i103 < 2; c2_i103++) {
    c2_leaving_2CM[c2_i103] = c2_dv21[c2_i103];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 94);
  for (c2_i104 = 0; c2_i104 < 2; c2_i104++) {
    c2_c_L_0CF[c2_i104] = c2_b_L_0CF[c2_i104];
  }

  c2_g_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_c_L_0CF, &c2_g_mut, c2_expiring_0CF, true,
                 c2_dv22);
  for (c2_i105 = 0; c2_i105 < 2; c2_i105++) {
    c2_leaving_0CF[c2_i105] = c2_dv22[c2_i105];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 95);
  for (c2_i106 = 0; c2_i106 < 2; c2_i106++) {
    c2_c_L_1CF[c2_i106] = c2_b_L_1CF[c2_i106];
  }

  c2_h_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_c_L_1CF, &c2_h_mut, c2_expiring_1CF, true,
                 c2_dv23);
  for (c2_i107 = 0; c2_i107 < 2; c2_i107++) {
    c2_leaving_1CF[c2_i107] = c2_dv23[c2_i107];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 96);
  for (c2_i108 = 0; c2_i108 < 2; c2_i108++) {
    c2_c_L_2CF[c2_i108] = c2_b_L_2CF[c2_i108];
  }

  c2_i_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_c_L_2CF, &c2_i_mut, c2_expiring_2CF, true,
                 c2_dv24);
  for (c2_i109 = 0; c2_i109 < 2; c2_i109++) {
    c2_leaving_2CF[c2_i109] = c2_dv24[c2_i109];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 98);
  for (c2_i110 = 0; c2_i110 < 2; c2_i110++) {
    c2_d_L_0RM[c2_i110] = c2_b_L_0RM[c2_i110];
  }

  c2_j_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_d_L_0RM, &c2_j_mut, c2_expiring_0RM, false,
                 c2_dv25);
  for (c2_i111 = 0; c2_i111 < 2; c2_i111++) {
    c2_leaving_0RM[c2_i111] = c2_dv25[c2_i111];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 99);
  for (c2_i112 = 0; c2_i112 < 2; c2_i112++) {
    c2_d_L_1RM[c2_i112] = c2_b_L_1RM[c2_i112];
  }

  c2_k_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_d_L_1RM, &c2_k_mut, c2_expiring_1RM, false,
                 c2_dv26);
  for (c2_i113 = 0; c2_i113 < 2; c2_i113++) {
    c2_leaving_1RM[c2_i113] = c2_dv26[c2_i113];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 100);
  for (c2_i114 = 0; c2_i114 < 2; c2_i114++) {
    c2_d_L_2RM[c2_i114] = c2_b_L_2RM[c2_i114];
  }

  c2_l_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_d_L_2RM, &c2_l_mut, c2_expiring_2RM, false,
                 c2_dv27);
  for (c2_i115 = 0; c2_i115 < 2; c2_i115++) {
    c2_leaving_2RM[c2_i115] = c2_dv27[c2_i115];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 101);
  for (c2_i116 = 0; c2_i116 < 2; c2_i116++) {
    c2_d_L_0RF[c2_i116] = c2_b_L_0RF[c2_i116];
  }

  c2_m_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_d_L_0RF, &c2_m_mut, c2_expiring_0RF, false,
                 c2_dv28);
  for (c2_i117 = 0; c2_i117 < 2; c2_i117++) {
    c2_leaving_0RF[c2_i117] = c2_dv28[c2_i117];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 102);
  for (c2_i118 = 0; c2_i118 < 2; c2_i118++) {
    c2_d_L_1RF[c2_i118] = c2_b_L_1RF[c2_i118];
  }

  c2_n_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_d_L_1RF, &c2_n_mut, c2_expiring_1RF, false,
                 c2_dv29);
  for (c2_i119 = 0; c2_i119 < 2; c2_i119++) {
    c2_leaving_1RF[c2_i119] = c2_dv29[c2_i119];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 103);
  for (c2_i120 = 0; c2_i120 < 2; c2_i120++) {
    c2_d_L_2RF[c2_i120] = c2_b_L_2RF[c2_i120];
  }

  c2_o_mut = c2_b_mut;
  c2_calcLeaving(chartInstance, c2_d_L_2RF, &c2_o_mut, c2_expiring_2RF, false,
                 c2_dv30);
  for (c2_i121 = 0; c2_i121 < 2; c2_i121++) {
    c2_leaving_2RF[c2_i121] = c2_dv30[c2_i121];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 107);
  for (c2_i122 = 0; c2_i122 < 2; c2_i122++) {
    c2_incoming_0RM[c2_i122] = c2_b_leaving_0CM[c2_i122];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 110);
  for (c2_i123 = 0; c2_i123 < 2; c2_i123++) {
    c2_incoming_1RM[c2_i123] = c2_leaving_1CM[c2_i123];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 113);
  for (c2_i124 = 0; c2_i124 < 2; c2_i124++) {
    c2_incoming_2RM[c2_i124] = c2_leaving_2CM[c2_i124];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 116);
  for (c2_i125 = 0; c2_i125 < 2; c2_i125++) {
    c2_incoming_0RF[c2_i125] = c2_leaving_0CF[c2_i125];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 119);
  for (c2_i126 = 0; c2_i126 < 2; c2_i126++) {
    c2_incoming_1RF[c2_i126] = c2_leaving_1CF[c2_i126];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 122);
  for (c2_i127 = 0; c2_i127 < 2; c2_i127++) {
    c2_incoming_2RF[c2_i127] = c2_leaving_2CF[c2_i127];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 126);
  for (c2_i128 = 0; c2_i128 < 2; c2_i128++) {
    c2_incoming_0SM[c2_i128] = c2_leaving_0RM[c2_i128];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 129U);
  for (c2_i129 = 0; c2_i129 < 2; c2_i129++) {
    c2_incoming_1SM[c2_i129] = c2_leaving_1RM[c2_i129];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 132U);
  for (c2_i130 = 0; c2_i130 < 2; c2_i130++) {
    c2_incoming_2SM[c2_i130] = c2_leaving_2RM[c2_i130];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 135U);
  for (c2_i131 = 0; c2_i131 < 2; c2_i131++) {
    c2_incoming_0SF[c2_i131] = c2_leaving_0RF[c2_i131];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 138U);
  for (c2_i132 = 0; c2_i132 < 2; c2_i132++) {
    c2_incoming_1SF[c2_i132] = c2_leaving_1RF[c2_i132];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 141U);
  for (c2_i133 = 0; c2_i133 < 2; c2_i133++) {
    c2_incoming_2SF[c2_i133] = c2_leaving_2RF[c2_i133];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 145U);
  c2_b_nL_0CM[0] = ((c2_b_L_0CM[0] + c2_new_0CM) - c2_b_leaving_0CM[0]) -
    c2_expiring_0CM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 146U);
  c2_b_nL_1CM[0] = ((c2_b_L_1CM[0] + c2_new_1CM) - c2_leaving_1CM[0]) -
    c2_expiring_1CM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 147U);
  c2_b_nL_2CM[0] = ((c2_b_L_2CM[0] + c2_new_2CM) - c2_leaving_2CM[0]) -
    c2_expiring_2CM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 148U);
  c2_b_nL_0CF[0] = ((c2_b_L_0CF[0] + c2_new_0CF) - c2_leaving_0CF[0]) -
    c2_expiring_0CF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 149U);
  c2_b_nL_1CF[0] = ((c2_b_L_1CF[0] + c2_new_1CF) - c2_leaving_1CF[0]) -
    c2_expiring_1CF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 150U);
  c2_b_nL_2CF[0] = ((c2_b_L_2CF[0] + c2_new_2CF) - c2_leaving_2CF[0]) -
    c2_expiring_2CF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 153U);
  c2_b_nL_0RM[0] = ((c2_b_L_0RM[0] + c2_incoming_0RM[0]) - c2_leaving_0RM[0]) -
    c2_expiring_0RM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 154U);
  c2_b_nL_1RM[0] = ((c2_b_L_1RM[0] + c2_incoming_1RM[0]) - c2_leaving_1RM[0]) -
    c2_expiring_1RM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 155U);
  c2_b_nL_2RM[0] = ((c2_b_L_2RM[0] + c2_incoming_2RM[0]) - c2_leaving_2RM[0]) -
    c2_expiring_2RM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 156U);
  c2_b_nL_0RF[0] = ((c2_b_L_0RF[0] + c2_incoming_0RF[0]) - c2_leaving_0RF[0]) -
    c2_expiring_0RF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 157U);
  c2_b_nL_1RF[0] = ((c2_b_L_1RF[0] + c2_incoming_1RF[0]) - c2_leaving_1RF[0]) -
    c2_expiring_1RF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 158U);
  c2_b_nL_2RF[0] = ((c2_b_L_2RF[0] + c2_incoming_2RF[0]) - c2_leaving_2RF[0]) -
    c2_expiring_2RF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 161U);
  c2_b_nL_0SM[0] = (c2_b_L_0SM[0] + c2_incoming_0SM[0]) - c2_expiring_0SM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 162U);
  c2_b_nL_1SM[0] = (c2_b_L_1SM[0] + c2_incoming_1SM[0]) - c2_expiring_1SM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 163U);
  c2_b_nL_2SM[0] = (c2_b_L_2SM[0] + c2_incoming_2SM[0]) - c2_expiring_2SM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 164U);
  c2_b_nL_0SF[0] = (c2_b_L_0SF[0] + c2_incoming_0SF[0]) - c2_expiring_0SF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 165U);
  c2_b_nL_1SF[0] = (c2_b_L_1SF[0] + c2_incoming_1SF[0]) - c2_expiring_1SF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 166U);
  c2_b_nL_2SF[0] = (c2_b_L_2SF[0] + c2_incoming_2SF[0]) - c2_expiring_2SF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 169U);
  c2_b_nL_0CM[1] = ((c2_b_L_0CM[1] + c2_b_L_0CM[0]) - c2_b_leaving_0CM[1]) -
    c2_expiring_0CM * c2_b_A_0CM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 170U);
  c2_b_nL_1CM[1] = ((c2_b_L_1CM[1] + c2_b_L_1CM[0]) - c2_leaving_1CM[1]) -
    c2_expiring_1CM * c2_A_1CM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 171U);
  c2_b_nL_2CM[1] = ((c2_b_L_2CM[1] + c2_b_L_2CM[0]) - c2_leaving_2CM[1]) -
    c2_expiring_2CM * c2_A_2CM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 172U);
  c2_b_nL_0CF[1] = ((c2_b_L_0CF[1] + c2_b_L_0CF[0]) - c2_leaving_0CF[1]) -
    c2_expiring_0CF * c2_A_0CF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 173U);
  c2_b_nL_1CF[1] = ((c2_b_L_1CF[1] + c2_b_L_1CF[0]) - c2_leaving_1CF[1]) -
    c2_expiring_1CF * c2_A_1CF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 174U);
  c2_b_nL_2CF[1] = ((c2_b_L_2CF[1] + c2_b_L_2CF[0]) - c2_leaving_2CF[1]) -
    c2_expiring_2CF * c2_A_2CF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 178U);
  c2_b_nL_0RM[1] = (((c2_b_L_0RM[1] + c2_b_L_0RM[0]) + c2_incoming_0RM[1]) -
                    c2_leaving_0RM[1]) - c2_expiring_0RM * c2_A_0RM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 179U);
  c2_b_nL_1RM[1] = (((c2_b_L_1RM[1] + c2_b_L_1RM[0]) + c2_incoming_1RM[1]) -
                    c2_leaving_1RM[1]) - c2_expiring_1RM * c2_A_1RM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 180U);
  c2_b_nL_2RM[1] = (((c2_b_L_2RM[1] + c2_b_L_2RM[0]) + c2_incoming_2RM[1]) -
                    c2_leaving_2RM[1]) - c2_expiring_2RM * c2_A_2RM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 181U);
  c2_b_nL_0RF[1] = (((c2_b_L_0RF[1] + c2_b_L_0RF[0]) + c2_incoming_0RF[1]) -
                    c2_leaving_0RF[1]) - c2_expiring_0RF * c2_A_0RF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 182U);
  c2_b_nL_1RF[1] = (((c2_b_L_1RF[1] + c2_b_L_1RF[0]) + c2_incoming_1RF[1]) -
                    c2_leaving_1RF[1]) - c2_expiring_1RF * c2_A_1RF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 183U);
  c2_b_nL_2RF[1] = (((c2_b_L_2RF[1] + c2_b_L_2RF[0]) + c2_incoming_2RF[1]) -
                    c2_leaving_2RF[1]) - c2_expiring_2RF * c2_A_2RF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 186U);
  c2_b_nL_0SM[1] = ((c2_b_L_0SM[1] + c2_b_L_0SM[0]) + c2_incoming_0SM[1]) -
    c2_expiring_0SM * c2_A_0SM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 187U);
  c2_b_nL_1SM[1] = ((c2_b_L_1SM[1] + c2_b_L_1SM[0]) + c2_incoming_1SM[1]) -
    c2_expiring_1SM * c2_A_1SM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 188U);
  c2_b_nL_2SM[1] = ((c2_b_L_2SM[1] + c2_b_L_2SM[0]) + c2_incoming_2SM[1]) -
    c2_expiring_2SM * c2_A_2SM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 189U);
  c2_b_nL_0SF[1] = ((c2_b_L_0SF[1] + c2_b_L_0SF[0]) + c2_incoming_0SF[1]) -
    c2_expiring_0SF * c2_A_0SF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 190U);
  c2_b_nL_1SF[1] = ((c2_b_L_1SF[1] + c2_b_L_1SF[0]) + c2_incoming_1SF[1]) -
    c2_expiring_1SF * c2_A_1SF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 191U);
  c2_b_nL_2SF[1] = ((c2_b_L_2SF[1] + c2_b_L_2SF[0]) + c2_incoming_2SF[1]) -
    c2_expiring_2SF * c2_A_2SF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 193U);
  c2_LX[0] = c2_b_L_0CM[0];
  c2_LX[3] = c2_b_L_0CF[0];
  c2_LX[6] = c2_b_L_0RM[0];
  c2_LX[9] = c2_b_L_0RF[0];
  c2_LX[12] = c2_b_L_0SM[0];
  c2_LX[15] = c2_b_L_0SF[0];
  c2_LX[1] = c2_b_L_1CM[0];
  c2_LX[4] = c2_b_L_1CF[0];
  c2_LX[7] = c2_b_L_1RM[0];
  c2_LX[10] = c2_b_L_1RF[0];
  c2_LX[13] = c2_b_L_1SM[0];
  c2_LX[16] = c2_b_L_1SF[0];
  c2_LX[2] = c2_b_L_2CM[0];
  c2_LX[5] = c2_b_L_2CF[0];
  c2_LX[8] = c2_b_L_2RM[0];
  c2_LX[11] = c2_b_L_2RF[0];
  c2_LX[14] = c2_b_L_2SM[0];
  c2_LX[17] = c2_b_L_2SF[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 198U);
  for (c2_i134 = 0; c2_i134 < 3; c2_i134++) {
    c2_b_LX[c2_i134] = c2_LX[c2_i134];
  }

  c2_L_CMT = c2_c_sum(chartInstance, c2_b_LX);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 199U);
  for (c2_i135 = 0; c2_i135 < 3; c2_i135++) {
    c2_c_LX[c2_i135] = c2_LX[c2_i135 + 3];
  }

  c2_L_CFT = c2_c_sum(chartInstance, c2_c_LX);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 200U);
  for (c2_i136 = 0; c2_i136 < 3; c2_i136++) {
    c2_d_LX[c2_i136] = c2_LX[c2_i136 + 6];
  }

  c2_L_RMT = c2_c_sum(chartInstance, c2_d_LX);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 201U);
  for (c2_i137 = 0; c2_i137 < 3; c2_i137++) {
    c2_e_LX[c2_i137] = c2_LX[c2_i137 + 9];
  }

  c2_L_RFT = c2_c_sum(chartInstance, c2_e_LX);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 202U);
  for (c2_i138 = 0; c2_i138 < 3; c2_i138++) {
    c2_f_LX[c2_i138] = c2_LX[c2_i138 + 12];
  }

  c2_L_SMT = c2_c_sum(chartInstance, c2_f_LX);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 203U);
  for (c2_i139 = 0; c2_i139 < 3; c2_i139++) {
    c2_g_LX[c2_i139] = c2_LX[c2_i139 + 15];
  }

  c2_L_SFT = c2_c_sum(chartInstance, c2_g_LX);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 205U);
  c2_i140 = 0;
  for (c2_i141 = 0; c2_i141 < 6; c2_i141++) {
    c2_h_LX[c2_i141] = c2_LX[c2_i140];
    c2_i140 += 3;
  }

  c2_L_T0 = c2_d_sum(chartInstance, c2_h_LX);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 206U);
  c2_i142 = 0;
  for (c2_i143 = 0; c2_i143 < 6; c2_i143++) {
    c2_i_LX[c2_i143] = c2_LX[c2_i142 + 1];
    c2_i142 += 3;
  }

  c2_L_T1 = c2_d_sum(chartInstance, c2_i_LX);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 207U);
  c2_i144 = 0;
  for (c2_i145 = 0; c2_i145 < 6; c2_i145++) {
    c2_j_LX[c2_i145] = c2_LX[c2_i144 + 2];
    c2_i144 += 3;
  }

  c2_L_T2 = c2_d_sum(chartInstance, c2_j_LX);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 209U);
  c2_L_TC = c2_L_CMT + c2_L_CFT;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 210U);
  c2_L_TR = c2_L_RMT + c2_L_RFT;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 211U);
  c2_L_TS = c2_L_SMT + c2_L_SFT;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 213U);
  c2_b_L_T = (c2_L_TC + c2_L_TR) + c2_L_TS;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 215U);
  c2_s_A = c2_L_T0;
  c2_s_B = c2_b_L_T;
  c2_lb_x = c2_s_A;
  c2_lb_y = c2_s_B;
  c2_mb_x = c2_lb_x;
  c2_mb_y = c2_lb_y;
  c2_nb_y = c2_mb_x / c2_mb_y;
  c2_b_f_0T = c2_nb_y * 100.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 216U);
  c2_t_A = c2_L_T1;
  c2_t_B = c2_b_L_T;
  c2_nb_x = c2_t_A;
  c2_ob_y = c2_t_B;
  c2_ob_x = c2_nb_x;
  c2_pb_y = c2_ob_y;
  c2_qb_y = c2_ob_x / c2_pb_y;
  c2_b_f_1T = c2_qb_y * 100.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 217U);
  c2_u_A = c2_L_T2;
  c2_u_B = c2_b_L_T;
  c2_pb_x = c2_u_A;
  c2_rb_y = c2_u_B;
  c2_qb_x = c2_pb_x;
  c2_sb_y = c2_rb_y;
  c2_tb_y = c2_qb_x / c2_sb_y;
  c2_b_f_2T = c2_tb_y * 100.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 219U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -219);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i146 = 0; c2_i146 < 2; c2_i146++) {
    (*chartInstance->c2_nL_0CM)[c2_i146] = c2_b_nL_0CM[c2_i146];
  }

  for (c2_i147 = 0; c2_i147 < 2; c2_i147++) {
    (*chartInstance->c2_nL_1CM)[c2_i147] = c2_b_nL_1CM[c2_i147];
  }

  for (c2_i148 = 0; c2_i148 < 2; c2_i148++) {
    (*chartInstance->c2_nL_2CM)[c2_i148] = c2_b_nL_2CM[c2_i148];
  }

  for (c2_i149 = 0; c2_i149 < 2; c2_i149++) {
    (*chartInstance->c2_nL_0RM)[c2_i149] = c2_b_nL_0RM[c2_i149];
  }

  for (c2_i150 = 0; c2_i150 < 2; c2_i150++) {
    (*chartInstance->c2_nL_1RM)[c2_i150] = c2_b_nL_1RM[c2_i150];
  }

  for (c2_i151 = 0; c2_i151 < 2; c2_i151++) {
    (*chartInstance->c2_nL_2RM)[c2_i151] = c2_b_nL_2RM[c2_i151];
  }

  for (c2_i152 = 0; c2_i152 < 2; c2_i152++) {
    (*chartInstance->c2_nL_0SM)[c2_i152] = c2_b_nL_0SM[c2_i152];
  }

  for (c2_i153 = 0; c2_i153 < 2; c2_i153++) {
    (*chartInstance->c2_nL_1SM)[c2_i153] = c2_b_nL_1SM[c2_i153];
  }

  for (c2_i154 = 0; c2_i154 < 2; c2_i154++) {
    (*chartInstance->c2_nL_2SM)[c2_i154] = c2_b_nL_2SM[c2_i154];
  }

  for (c2_i155 = 0; c2_i155 < 2; c2_i155++) {
    (*chartInstance->c2_nL_0CF)[c2_i155] = c2_b_nL_0CF[c2_i155];
  }

  for (c2_i156 = 0; c2_i156 < 2; c2_i156++) {
    (*chartInstance->c2_nL_1CF)[c2_i156] = c2_b_nL_1CF[c2_i156];
  }

  for (c2_i157 = 0; c2_i157 < 2; c2_i157++) {
    (*chartInstance->c2_nL_2CF)[c2_i157] = c2_b_nL_2CF[c2_i157];
  }

  for (c2_i158 = 0; c2_i158 < 2; c2_i158++) {
    (*chartInstance->c2_nL_0RF)[c2_i158] = c2_b_nL_0RF[c2_i158];
  }

  for (c2_i159 = 0; c2_i159 < 2; c2_i159++) {
    (*chartInstance->c2_nL_1RF)[c2_i159] = c2_b_nL_1RF[c2_i159];
  }

  for (c2_i160 = 0; c2_i160 < 2; c2_i160++) {
    (*chartInstance->c2_nL_2RF)[c2_i160] = c2_b_nL_2RF[c2_i160];
  }

  for (c2_i161 = 0; c2_i161 < 2; c2_i161++) {
    (*chartInstance->c2_nL_0SF)[c2_i161] = c2_b_nL_0SF[c2_i161];
  }

  for (c2_i162 = 0; c2_i162 < 2; c2_i162++) {
    (*chartInstance->c2_nL_1SF)[c2_i162] = c2_b_nL_1SF[c2_i162];
  }

  for (c2_i163 = 0; c2_i163 < 2; c2_i163++) {
    (*chartInstance->c2_nL_2SF)[c2_i163] = c2_b_nL_2SF[c2_i163];
  }

  *chartInstance->c2_A_0CM = c2_b_A_0CM;
  for (c2_i164 = 0; c2_i164 < 2; c2_i164++) {
    (*chartInstance->c2_leaving_0CM)[c2_i164] = c2_b_leaving_0CM[c2_i164];
  }

  *chartInstance->c2_L_T = c2_b_L_T;
  *chartInstance->c2_f_0T = c2_b_f_0T;
  *chartInstance->c2_f_1T = c2_b_f_1T;
  *chartInstance->c2_f_2T = c2_b_f_2T;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_mut_screen(SFc2_mut_screenInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_b_f_2T, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_f_2T), &c2_thisId);
  sf_mex_destroy(&c2_b_f_2T);
  return c2_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_f_2T;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_b_f_2T = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_f_2T), &c2_thisId);
  sf_mex_destroy(&c2_b_f_2T);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i165;
  real_T c2_u[2];
  const mxArray *c2_y = NULL;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i165 = 0; c2_i165 < 2; c2_i165++) {
    c2_u[c2_i165] = (*(real_T (*)[2])c2_inData)[c2_i165];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 2), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_b_leaving_0CM, const char_T *c2_identifier, real_T c2_y[2])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_leaving_0CM), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_b_leaving_0CM);
}

static void c2_d_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[2])
{
  real_T c2_dv31[2];
  int32_T c2_i166;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv31, 1, 0, 0U, 1, 0U, 2, 1, 2);
  for (c2_i166 = 0; c2_i166 < 2; c2_i166++) {
    c2_y[c2_i166] = c2_dv31[c2_i166];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_leaving_0CM;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[2];
  int32_T c2_i167;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_b_leaving_0CM = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_leaving_0CM), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_b_leaving_0CM);
  for (c2_i167 = 0; c2_i167 < 2; c2_i167++) {
    (*(real_T (*)[2])c2_outData)[c2_i167] = c2_y[c2_i167];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_u;
  const mxArray *c2_y = NULL;
  real_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  real_T c2_c_u;
  const mxArray *c2_c_y = NULL;
  real_T c2_d_u;
  const mxArray *c2_d_y = NULL;
  real_T c2_e_u;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i168;
  real_T c2_f_u[2];
  const mxArray *c2_f_y = NULL;
  real_T c2_g_u;
  const mxArray *c2_g_y = NULL;
  real_T c2_h_u;
  const mxArray *c2_h_y = NULL;
  real_T c2_i_u;
  const mxArray *c2_i_y = NULL;
  int32_T c2_i169;
  real_T c2_j_u[6];
  const mxArray *c2_j_y = NULL;
  int32_T c2_i170;
  real_T c2_k_u[18];
  const mxArray *c2_k_y = NULL;
  c2_struct_qHpeHlL7YRQjHTvGIxkLGB c2_l_u;
  const mxArray *c2_l_y = NULL;
  real_T c2_m_u;
  const mxArray *c2_m_y = NULL;
  real_T c2_n_u;
  const mxArray *c2_n_y = NULL;
  real_T c2_o_u;
  const mxArray *c2_o_y = NULL;
  real_T c2_p_u;
  const mxArray *c2_p_y = NULL;
  real_T c2_q_u;
  const mxArray *c2_q_y = NULL;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(c2_struct_zKkRWFtALBg7fNtPuY4M6D *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c2_b_u = c2_u.fertility;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_b_y, "fertility", "fertility", 0);
  c2_c_u = c2_u.M2Fprobability;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_c_y, "M2Fprobability", "M2Fprobability", 0);
  c2_d_u = c2_u.Y_C;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_d_y, "Y_C", "Y_C", 0);
  c2_e_u = c2_u.Y_R;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_e_y, "Y_R", "Y_R", 0);
  for (c2_i168 = 0; c2_i168 < 2; c2_i168++) {
    c2_f_u[c2_i168] = c2_u.distribution[c2_i168];
  }

  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_f_u, 0, 0U, 1U, 0U, 2, 1, 2),
                false);
  sf_mex_addfield(c2_y, c2_f_y, "distribution", "distribution", 0);
  c2_g_u = c2_u.distributionPercent;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_g_y, "distributionPercent", "distributionPercent", 0);
  c2_h_u = c2_u.MSM;
  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_h_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_h_y, "MSM", "MSM", 0);
  c2_i_u = c2_u.MSF;
  c2_i_y = NULL;
  sf_mex_assign(&c2_i_y, sf_mex_create("y", &c2_i_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_i_y, "MSF", "MSF", 0);
  for (c2_i169 = 0; c2_i169 < 6; c2_i169++) {
    c2_j_u[c2_i169] = c2_u.mort[c2_i169];
  }

  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", c2_j_u, 0, 0U, 1U, 0U, 2, 1, 6),
                false);
  sf_mex_addfield(c2_y, c2_j_y, "mort", "mort", 0);
  for (c2_i170 = 0; c2_i170 < 18; c2_i170++) {
    c2_k_u[c2_i170] = c2_u.muMort[c2_i170];
  }

  c2_k_y = NULL;
  sf_mex_assign(&c2_k_y, sf_mex_create("y", c2_k_u, 0, 0U, 1U, 0U, 2, 3, 6),
                false);
  sf_mex_addfield(c2_y, c2_k_y, "muMort", "muMort", 0);
  c2_l_u = c2_u.screen;
  c2_l_y = NULL;
  sf_mex_assign(&c2_l_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c2_m_u = c2_l_u.NR;
  c2_m_y = NULL;
  sf_mex_assign(&c2_m_y, sf_mex_create("y", &c2_m_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_l_y, c2_m_y, "NR", "NR", 0);
  c2_n_u = c2_l_u.LR;
  c2_n_y = NULL;
  sf_mex_assign(&c2_n_y, sf_mex_create("y", &c2_n_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_l_y, c2_n_y, "LR", "LR", 0);
  c2_o_u = c2_l_u.MR;
  c2_o_y = NULL;
  sf_mex_assign(&c2_o_y, sf_mex_create("y", &c2_o_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_l_y, c2_o_y, "MR", "MR", 0);
  c2_p_u = c2_l_u.HR;
  c2_p_y = NULL;
  sf_mex_assign(&c2_p_y, sf_mex_create("y", &c2_p_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_l_y, c2_p_y, "HR", "HR", 0);
  c2_q_u = c2_l_u.efficiency;
  c2_q_y = NULL;
  sf_mex_assign(&c2_q_y, sf_mex_create("y", &c2_q_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_l_y, c2_q_y, "efficiency", "efficiency", 0);
  sf_mex_addfield(c2_y, c2_l_y, "screen", "screen", 0);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  c2_struct_zKkRWFtALBg7fNtPuY4M6D *c2_y)
{
  emlrtMsgIdentifier c2_thisId;
  static const char * c2_fieldNames[11] = { "fertility", "M2Fprobability", "Y_C",
    "Y_R", "distribution", "distributionPercent", "MSM", "MSF", "mort", "muMort",
    "screen" };

  c2_thisId.fParent = c2_parentId;
  c2_thisId.bParentIsCell = false;
  sf_mex_check_struct(c2_parentId, c2_u, 11, c2_fieldNames, 0U, NULL);
  c2_thisId.fIdentifier = "fertility";
  c2_y->fertility = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_u, "fertility", "fertility", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "M2Fprobability";
  c2_y->M2Fprobability = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_u, "M2Fprobability", "M2Fprobability", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Y_C";
  c2_y->Y_C = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "Y_C", "Y_C", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Y_R";
  c2_y->Y_R = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "Y_R", "Y_R", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "distribution";
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u,
    "distribution", "distribution", 0)), &c2_thisId, c2_y->distribution);
  c2_thisId.fIdentifier = "distributionPercent";
  c2_y->distributionPercent = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_u, "distributionPercent", "distributionPercent", 0)),
    &c2_thisId);
  c2_thisId.fIdentifier = "MSM";
  c2_y->MSM = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "MSM", "MSM", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "MSF";
  c2_y->MSF = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "MSF", "MSF", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "mort";
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u, "mort",
    "mort", 0)), &c2_thisId, c2_y->mort);
  c2_thisId.fIdentifier = "muMort";
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u, "muMort",
    "muMort", 0)), &c2_thisId, c2_y->muMort);
  c2_thisId.fIdentifier = "screen";
  c2_y->screen = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "screen", "screen", 0)), &c2_thisId);
  sf_mex_destroy(&c2_u);
}

static void c2_f_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[6])
{
  real_T c2_dv32[6];
  int32_T c2_i171;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv32, 1, 0, 0U, 1, 0U, 2, 1, 6);
  for (c2_i171 = 0; c2_i171 < 6; c2_i171++) {
    c2_y[c2_i171] = c2_dv32[c2_i171];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_g_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[18])
{
  real_T c2_dv33[18];
  int32_T c2_i172;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv33, 1, 0, 0U, 1, 0U, 2, 3, 6);
  for (c2_i172 = 0; c2_i172 < 18; c2_i172++) {
    c2_y[c2_i172] = c2_dv33[c2_i172];
  }

  sf_mex_destroy(&c2_u);
}

static c2_struct_qHpeHlL7YRQjHTvGIxkLGB c2_h_emlrt_marshallIn
  (SFc2_mut_screenInstanceStruct *chartInstance, const mxArray *c2_u, const
   emlrtMsgIdentifier *c2_parentId)
{
  c2_struct_qHpeHlL7YRQjHTvGIxkLGB c2_y;
  emlrtMsgIdentifier c2_thisId;
  static const char * c2_fieldNames[5] = { "NR", "LR", "MR", "HR", "efficiency"
  };

  c2_thisId.fParent = c2_parentId;
  c2_thisId.bParentIsCell = false;
  sf_mex_check_struct(c2_parentId, c2_u, 5, c2_fieldNames, 0U, NULL);
  c2_thisId.fIdentifier = "NR";
  c2_y.NR = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u,
    "NR", "NR", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "LR";
  c2_y.LR = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u,
    "LR", "LR", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "MR";
  c2_y.MR = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u,
    "MR", "MR", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "HR";
  c2_y.HR = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u,
    "HR", "HR", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "efficiency";
  c2_y.efficiency = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_u, "efficiency", "efficiency", 0)), &c2_thisId);
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_mut;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_y;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_b_mut = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_mut), &c2_thisId, &c2_y);
  sf_mex_destroy(&c2_b_mut);
  *(c2_struct_zKkRWFtALBg7fNtPuY4M6D *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i173;
  real_T c2_u[2];
  const mxArray *c2_y = NULL;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i173 = 0; c2_i173 < 2; c2_i173++) {
    c2_u[c2_i173] = (*(real_T (*)[2])c2_inData)[c2_i173];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i174;
  int32_T c2_i175;
  int32_T c2_i176;
  real_T c2_u[18];
  const mxArray *c2_y = NULL;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i174 = 0;
  for (c2_i175 = 0; c2_i175 < 6; c2_i175++) {
    for (c2_i176 = 0; c2_i176 < 3; c2_i176++) {
      c2_u[c2_i176 + c2_i174] = (*(real_T (*)[18])c2_inData)[c2_i176 + c2_i174];
    }

    c2_i174 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 6), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_LX;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[18];
  int32_T c2_i177;
  int32_T c2_i178;
  int32_T c2_i179;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_LX = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_LX), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_LX);
  c2_i177 = 0;
  for (c2_i178 = 0; c2_i178 < 6; c2_i178++) {
    for (c2_i179 = 0; c2_i179 < 3; c2_i179++) {
      (*(real_T (*)[18])c2_outData)[c2_i179 + c2_i177] = c2_y[c2_i179 + c2_i177];
    }

    c2_i177 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i180;
  int32_T c2_i181;
  int32_T c2_i182;
  real_T c2_u[9];
  const mxArray *c2_y = NULL;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i180 = 0;
  for (c2_i181 = 0; c2_i181 < 3; c2_i181++) {
    for (c2_i182 = 0; c2_i182 < 3; c2_i182++) {
      c2_u[c2_i182 + c2_i180] = (*(real_T (*)[9])c2_inData)[c2_i182 + c2_i180];
    }

    c2_i180 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_i_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[9])
{
  real_T c2_dv34[9];
  int32_T c2_i183;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv34, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c2_i183 = 0; c2_i183 < 9; c2_i183++) {
    c2_y[c2_i183] = c2_dv34[c2_i183];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_behaveMod;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[9];
  int32_T c2_i184;
  int32_T c2_i185;
  int32_T c2_i186;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_behaveMod = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_behaveMod), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_behaveMod);
  c2_i184 = 0;
  for (c2_i185 = 0; c2_i185 < 3; c2_i185++) {
    for (c2_i186 = 0; c2_i186 < 3; c2_i186++) {
      (*(real_T (*)[9])c2_outData)[c2_i186 + c2_i184] = c2_y[c2_i186 + c2_i184];
    }

    c2_i184 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_j_emlrt_marshallIn(SFc2_mut_screenInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[2])
{
  real_T c2_dv35[2];
  int32_T c2_i187;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv35, 1, 0, 0U, 1, 0U, 1, 2);
  for (c2_i187 = 0; c2_i187 < 2; c2_i187++) {
    c2_y[c2_i187] = c2_dv35[c2_i187];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_L_2RF;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[2];
  int32_T c2_i188;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_b_L_2RF = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_L_2RF), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_L_2RF);
  for (c2_i188 = 0; c2_i188 < 2; c2_i188++) {
    (*(real_T (*)[2])c2_outData)[c2_i188] = c2_y[c2_i188];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  boolean_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(boolean_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static boolean_T c2_k_emlrt_marshallIn(SFc2_mut_screenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  boolean_T c2_y;
  boolean_T c2_b0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_b0, 1, 11, 0U, 0, 0U, 0);
  c2_y = c2_b0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_childAgeBracket;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  boolean_T c2_y;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_childAgeBracket = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_childAgeBracket),
    &c2_thisId);
  sf_mex_destroy(&c2_childAgeBracket);
  *(boolean_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_mut_screen_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c2_nameCaptureInfo;
}

static void c2_getNewChildrenMutations(SFc2_mut_screenInstanceStruct
  *chartInstance, real_T c2_b_L_0RM[2], real_T c2_b_L_1RM[2], real_T c2_b_L_2RM
  [2], real_T c2_b_L_0RF[2], real_T c2_b_L_1RF[2], real_T c2_b_L_2RF[2],
  c2_struct_zKkRWFtALBg7fNtPuY4M6D *c2_b_mut, real_T *c2_new_0CM, real_T
  *c2_new_1CM, real_T *c2_new_2CM, real_T *c2_new_0CF, real_T *c2_new_1CF,
  real_T *c2_new_2CF)
{
  uint32_T c2_debug_family_var_map[25];
  real_T c2_L_TRM;
  real_T c2_L_TRF;
  real_T c2_new_TC;
  real_T c2_new_TCM;
  real_T c2_new_TCF;
  real_T c2_probParents[9];
  real_T c2_behaveMod[9];
  real_T c2_p0[9];
  real_T c2_p1[9];
  real_T c2_p2[9];
  real_T c2_nargin = 7.0;
  real_T c2_nargout = 6.0;
  int32_T c2_i189;
  static real_T c2_a[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  real_T c2_A;
  real_T c2_B;
  real_T c2_x;
  real_T c2_y;
  real_T c2_b_x;
  real_T c2_b_y;
  real_T c2_c_y;
  real_T c2_b_A;
  real_T c2_b_B;
  real_T c2_c_x;
  real_T c2_d_y;
  real_T c2_d_x;
  real_T c2_e_y;
  real_T c2_f_y;
  real_T c2_c_A;
  real_T c2_c_B;
  real_T c2_e_x;
  real_T c2_g_y;
  real_T c2_f_x;
  real_T c2_h_y;
  real_T c2_i_y;
  real_T c2_d_A;
  real_T c2_d_B;
  real_T c2_g_x;
  real_T c2_j_y;
  real_T c2_h_x;
  real_T c2_k_y;
  real_T c2_l_y;
  real_T c2_e_A;
  real_T c2_e_B;
  real_T c2_i_x;
  real_T c2_m_y;
  real_T c2_j_x;
  real_T c2_n_y;
  real_T c2_o_y;
  real_T c2_f_A;
  real_T c2_f_B;
  real_T c2_k_x;
  real_T c2_p_y;
  real_T c2_l_x;
  real_T c2_q_y;
  real_T c2_r_y;
  real_T c2_g_A;
  real_T c2_g_B;
  real_T c2_m_x;
  real_T c2_s_y;
  real_T c2_n_x;
  real_T c2_t_y;
  real_T c2_u_y;
  real_T c2_h_A;
  real_T c2_h_B;
  real_T c2_o_x;
  real_T c2_v_y;
  real_T c2_p_x;
  real_T c2_w_y;
  real_T c2_x_y;
  real_T c2_i_A;
  real_T c2_i_B;
  real_T c2_q_x;
  real_T c2_y_y;
  real_T c2_r_x;
  real_T c2_ab_y;
  real_T c2_bb_y;
  real_T c2_j_A;
  real_T c2_j_B;
  real_T c2_s_x;
  real_T c2_cb_y;
  real_T c2_t_x;
  real_T c2_db_y;
  real_T c2_eb_y;
  real_T c2_k_A;
  real_T c2_k_B;
  real_T c2_u_x;
  real_T c2_fb_y;
  real_T c2_v_x;
  real_T c2_gb_y;
  real_T c2_hb_y;
  real_T c2_l_A;
  real_T c2_l_B;
  real_T c2_w_x;
  real_T c2_ib_y;
  real_T c2_x_x;
  real_T c2_jb_y;
  real_T c2_kb_y;
  real_T c2_m_A;
  real_T c2_m_B;
  real_T c2_y_x;
  real_T c2_lb_y;
  real_T c2_ab_x;
  real_T c2_mb_y;
  real_T c2_nb_y;
  real_T c2_n_A;
  real_T c2_n_B;
  real_T c2_bb_x;
  real_T c2_ob_y;
  real_T c2_cb_x;
  real_T c2_pb_y;
  real_T c2_qb_y;
  real_T c2_o_A;
  real_T c2_o_B;
  real_T c2_db_x;
  real_T c2_rb_y;
  real_T c2_eb_x;
  real_T c2_sb_y;
  real_T c2_tb_y;
  real_T c2_p_A;
  real_T c2_p_B;
  real_T c2_fb_x;
  real_T c2_ub_y;
  real_T c2_gb_x;
  real_T c2_vb_y;
  real_T c2_wb_y;
  real_T c2_q_A;
  real_T c2_q_B;
  real_T c2_hb_x;
  real_T c2_xb_y;
  real_T c2_ib_x;
  real_T c2_yb_y;
  real_T c2_ac_y;
  real_T c2_r_A;
  real_T c2_r_B;
  real_T c2_jb_x;
  real_T c2_bc_y;
  real_T c2_kb_x;
  real_T c2_cc_y;
  real_T c2_dc_y;
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_c_mut;
  uint32_T c2_b_debug_family_var_map[4];
  real_T c2_b_nargin = 1.0;
  real_T c2_b_nargout = 1.0;
  int32_T c2_i190;
  real_T c2_b_a[9];
  real_T c2_b;
  int32_T c2_i191;
  int32_T c2_i192;
  int32_T c2_i193;
  uint32_T c2_c_debug_family_var_map[5];
  real_T c2_c_nargin = 0.0;
  real_T c2_c_nargout = 3.0;
  real_T c2_b_p0[9];
  real_T c2_b_p1[9];
  real_T c2_b_p2[9];
  int32_T c2_i194;
  int32_T c2_i195;
  int32_T c2_i196;
  int32_T c2_i197;
  int32_T c2_i198;
  int32_T c2_i199;
  int32_T c2_i200;
  real_T c2_b_probParents[9];
  real_T c2_dv36[3];
  int32_T c2_i201;
  real_T c2_dv37[3];
  int32_T c2_i202;
  real_T c2_c_probParents[9];
  int32_T c2_i203;
  real_T c2_dv38[3];
  int32_T c2_i204;
  real_T c2_d_probParents[9];
  int32_T c2_i205;
  real_T c2_dv39[3];
  int32_T c2_i206;
  real_T c2_e_probParents[9];
  int32_T c2_i207;
  real_T c2_dv40[3];
  int32_T c2_i208;
  real_T c2_f_probParents[9];
  int32_T c2_i209;
  real_T c2_dv41[3];
  int32_T c2_i210;
  real_T c2_g_probParents[9];
  int32_T c2_i211;
  real_T c2_dv42[3];
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 25U, 25U, c2_d_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_TRM, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_L_TRF, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_new_TC, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_new_TCM, 3U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_new_TCF, 4U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_probParents, 5U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_behaveMod, 6U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_p0, 7U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_p1, 8U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_p2, 9U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 10U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 11U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_L_0RM, 12U, c2_d_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_L_1RM, 13U, c2_d_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_L_2RM, 14U, c2_d_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_L_0RF, 15U, c2_d_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_L_1RF, 16U, c2_d_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_L_2RF, 17U, c2_d_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_mut, 18U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_new_0CM, 19U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_new_1CM, 20U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_new_2CM, 21U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_new_0CF, 22U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_new_1CF, 23U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_new_2CF, 24U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 228U);
  c2_L_TRM = (c2_b_L_0RM[0] + c2_b_L_1RM[0]) + c2_b_L_2RM[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 229U);
  c2_L_TRF = (c2_b_L_0RF[0] + c2_b_L_1RF[0]) + c2_b_L_2RF[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 232U);
  c2_new_TC = c2_b_mut->fertility * c2_L_TRM * c2_b_mut->fertility * c2_L_TRF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 234U);
  c2_new_TCM = c2_new_TC * c2_b_mut->M2Fprobability;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 235U);
  c2_new_TCF = c2_new_TC * (1.0 - c2_b_mut->M2Fprobability);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 238U);
  for (c2_i189 = 0; c2_i189 < 9; c2_i189++) {
    c2_probParents[c2_i189] = c2_a[c2_i189];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 239U);
  c2_A = c2_b_L_0RM[0];
  c2_B = c2_L_TRM;
  c2_x = c2_A;
  c2_y = c2_B;
  c2_b_x = c2_x;
  c2_b_y = c2_y;
  c2_c_y = c2_b_x / c2_b_y;
  c2_b_A = c2_b_L_0RF[0];
  c2_b_B = c2_L_TRF;
  c2_c_x = c2_b_A;
  c2_d_y = c2_b_B;
  c2_d_x = c2_c_x;
  c2_e_y = c2_d_y;
  c2_f_y = c2_d_x / c2_e_y;
  c2_probParents[0] = c2_c_y * c2_f_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 240U);
  c2_c_A = c2_b_L_0RM[0];
  c2_c_B = c2_L_TRM;
  c2_e_x = c2_c_A;
  c2_g_y = c2_c_B;
  c2_f_x = c2_e_x;
  c2_h_y = c2_g_y;
  c2_i_y = c2_f_x / c2_h_y;
  c2_d_A = c2_b_L_1RF[0];
  c2_d_B = c2_L_TRF;
  c2_g_x = c2_d_A;
  c2_j_y = c2_d_B;
  c2_h_x = c2_g_x;
  c2_k_y = c2_j_y;
  c2_l_y = c2_h_x / c2_k_y;
  c2_probParents[3] = c2_i_y * c2_l_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 241U);
  c2_e_A = c2_b_L_0RM[0];
  c2_e_B = c2_L_TRM;
  c2_i_x = c2_e_A;
  c2_m_y = c2_e_B;
  c2_j_x = c2_i_x;
  c2_n_y = c2_m_y;
  c2_o_y = c2_j_x / c2_n_y;
  c2_f_A = c2_b_L_2RF[0];
  c2_f_B = c2_L_TRF;
  c2_k_x = c2_f_A;
  c2_p_y = c2_f_B;
  c2_l_x = c2_k_x;
  c2_q_y = c2_p_y;
  c2_r_y = c2_l_x / c2_q_y;
  c2_probParents[6] = c2_o_y * c2_r_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 243U);
  c2_g_A = c2_b_L_1RM[0];
  c2_g_B = c2_L_TRM;
  c2_m_x = c2_g_A;
  c2_s_y = c2_g_B;
  c2_n_x = c2_m_x;
  c2_t_y = c2_s_y;
  c2_u_y = c2_n_x / c2_t_y;
  c2_h_A = c2_b_L_0RF[0];
  c2_h_B = c2_L_TRF;
  c2_o_x = c2_h_A;
  c2_v_y = c2_h_B;
  c2_p_x = c2_o_x;
  c2_w_y = c2_v_y;
  c2_x_y = c2_p_x / c2_w_y;
  c2_probParents[1] = c2_u_y * c2_x_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 244U);
  c2_i_A = c2_b_L_1RM[0];
  c2_i_B = c2_L_TRM;
  c2_q_x = c2_i_A;
  c2_y_y = c2_i_B;
  c2_r_x = c2_q_x;
  c2_ab_y = c2_y_y;
  c2_bb_y = c2_r_x / c2_ab_y;
  c2_j_A = c2_b_L_1RF[0];
  c2_j_B = c2_L_TRF;
  c2_s_x = c2_j_A;
  c2_cb_y = c2_j_B;
  c2_t_x = c2_s_x;
  c2_db_y = c2_cb_y;
  c2_eb_y = c2_t_x / c2_db_y;
  c2_probParents[4] = c2_bb_y * c2_eb_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 245U);
  c2_k_A = c2_b_L_1RM[0];
  c2_k_B = c2_L_TRM;
  c2_u_x = c2_k_A;
  c2_fb_y = c2_k_B;
  c2_v_x = c2_u_x;
  c2_gb_y = c2_fb_y;
  c2_hb_y = c2_v_x / c2_gb_y;
  c2_l_A = c2_b_L_2RF[0];
  c2_l_B = c2_L_TRF;
  c2_w_x = c2_l_A;
  c2_ib_y = c2_l_B;
  c2_x_x = c2_w_x;
  c2_jb_y = c2_ib_y;
  c2_kb_y = c2_x_x / c2_jb_y;
  c2_probParents[7] = c2_hb_y * c2_kb_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 247U);
  c2_m_A = c2_b_L_2RM[0];
  c2_m_B = c2_L_TRM;
  c2_y_x = c2_m_A;
  c2_lb_y = c2_m_B;
  c2_ab_x = c2_y_x;
  c2_mb_y = c2_lb_y;
  c2_nb_y = c2_ab_x / c2_mb_y;
  c2_n_A = c2_b_L_0RF[0];
  c2_n_B = c2_L_TRF;
  c2_bb_x = c2_n_A;
  c2_ob_y = c2_n_B;
  c2_cb_x = c2_bb_x;
  c2_pb_y = c2_ob_y;
  c2_qb_y = c2_cb_x / c2_pb_y;
  c2_probParents[2] = c2_nb_y * c2_qb_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 248U);
  c2_o_A = c2_b_L_2RM[0];
  c2_o_B = c2_L_TRM;
  c2_db_x = c2_o_A;
  c2_rb_y = c2_o_B;
  c2_eb_x = c2_db_x;
  c2_sb_y = c2_rb_y;
  c2_tb_y = c2_eb_x / c2_sb_y;
  c2_p_A = c2_b_L_1RF[0];
  c2_p_B = c2_L_TRF;
  c2_fb_x = c2_p_A;
  c2_ub_y = c2_p_B;
  c2_gb_x = c2_fb_x;
  c2_vb_y = c2_ub_y;
  c2_wb_y = c2_gb_x / c2_vb_y;
  c2_probParents[5] = c2_tb_y * c2_wb_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 249U);
  c2_q_A = c2_b_L_2RM[0];
  c2_q_B = c2_L_TRM;
  c2_hb_x = c2_q_A;
  c2_xb_y = c2_q_B;
  c2_ib_x = c2_hb_x;
  c2_yb_y = c2_xb_y;
  c2_ac_y = c2_ib_x / c2_yb_y;
  c2_r_A = c2_b_L_2RF[0];
  c2_r_B = c2_L_TRF;
  c2_jb_x = c2_r_A;
  c2_bc_y = c2_r_B;
  c2_kb_x = c2_jb_x;
  c2_cc_y = c2_bc_y;
  c2_dc_y = c2_kb_x / c2_cc_y;
  c2_probParents[8] = c2_ac_y * c2_dc_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 251U);
  c2_c_mut = *c2_b_mut;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargin, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargout, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_mut, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_behaveMod, 3U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 267);
  c2_behaveMod[0] = c2_c_mut.screen.NR;
  c2_behaveMod[3] = c2_c_mut.screen.LR;
  c2_behaveMod[6] = c2_c_mut.screen.LR;
  c2_behaveMod[1] = c2_c_mut.screen.LR;
  c2_behaveMod[4] = c2_c_mut.screen.MR;
  c2_behaveMod[7] = c2_c_mut.screen.MR;
  c2_behaveMod[2] = c2_c_mut.screen.LR;
  c2_behaveMod[5] = c2_c_mut.screen.MR;
  c2_behaveMod[8] = c2_c_mut.screen.HR;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 271);
  for (c2_i190 = 0; c2_i190 < 9; c2_i190++) {
    c2_b_a[c2_i190] = c2_behaveMod[c2_i190];
  }

  c2_b = c2_c_mut.screen.efficiency;
  for (c2_i191 = 0; c2_i191 < 9; c2_i191++) {
    c2_behaveMod[c2_i191] = c2_b_a[c2_i191] * c2_b;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 272);
  for (c2_i192 = 0; c2_i192 < 9; c2_i192++) {
    c2_behaveMod[c2_i192] = 1.0 - c2_behaveMod[c2_i192];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 274);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -274);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 252U);
  for (c2_i193 = 0; c2_i193 < 9; c2_i193++) {
    c2_probParents[c2_i193] *= c2_behaveMod[c2_i193];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 254U);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 5U, 5U, c2_c_debug_family_names,
    c2_c_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargin, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargout, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_p0, 2U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_p1, 3U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_p2, 4U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  CV_EML_FCN(0, 3);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 278);
  for (c2_i194 = 0; c2_i194 < 9; c2_i194++) {
    c2_b_p0[c2_i194] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 279);
  for (c2_i195 = 0; c2_i195 < 9; c2_i195++) {
    c2_b_p1[c2_i195] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 280);
  for (c2_i196 = 0; c2_i196 < 9; c2_i196++) {
    c2_b_p2[c2_i196] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 282);
  c2_b_p0[0] = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 283);
  c2_b_p0[3] = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 284);
  c2_b_p0[6] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 285);
  c2_b_p0[1] = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 286);
  c2_b_p0[4] = 0.25;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 287);
  c2_b_p0[7] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 288);
  c2_b_p0[2] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 289);
  c2_b_p0[5] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 290);
  c2_b_p0[8] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 292);
  c2_b_p1[0] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 293);
  c2_b_p1[3] = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 294);
  c2_b_p1[6] = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 295);
  c2_b_p1[1] = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 296);
  c2_b_p1[4] = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 297);
  c2_b_p1[7] = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 298);
  c2_b_p1[2] = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 299);
  c2_b_p1[5] = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 300);
  c2_b_p1[8] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 302);
  c2_b_p2[0] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 303);
  c2_b_p2[3] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 304);
  c2_b_p2[6] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 305);
  c2_b_p2[1] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 306);
  c2_b_p2[4] = 0.25;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 307);
  c2_b_p2[7] = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 308);
  c2_b_p2[2] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 309);
  c2_b_p2[5] = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 310);
  c2_b_p2[8] = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 312);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -312);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i197 = 0; c2_i197 < 9; c2_i197++) {
    c2_p0[c2_i197] = c2_b_p0[c2_i197];
  }

  for (c2_i198 = 0; c2_i198 < 9; c2_i198++) {
    c2_p1[c2_i198] = c2_b_p1[c2_i198];
  }

  for (c2_i199 = 0; c2_i199 < 9; c2_i199++) {
    c2_p2[c2_i199] = c2_b_p2[c2_i199];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 256);
  for (c2_i200 = 0; c2_i200 < 9; c2_i200++) {
    c2_b_probParents[c2_i200] = c2_probParents[c2_i200] * c2_p0[c2_i200];
  }

  c2_sum(chartInstance, c2_b_probParents, c2_dv36);
  for (c2_i201 = 0; c2_i201 < 3; c2_i201++) {
    c2_dv37[c2_i201] = c2_dv36[c2_i201];
  }

  *c2_new_0CM = c2_b_sum(chartInstance, c2_dv37) * c2_new_TCM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 257);
  for (c2_i202 = 0; c2_i202 < 9; c2_i202++) {
    c2_c_probParents[c2_i202] = c2_probParents[c2_i202] * c2_p1[c2_i202];
  }

  c2_sum(chartInstance, c2_c_probParents, c2_dv36);
  for (c2_i203 = 0; c2_i203 < 3; c2_i203++) {
    c2_dv38[c2_i203] = c2_dv36[c2_i203];
  }

  *c2_new_1CM = c2_b_sum(chartInstance, c2_dv38) * c2_new_TCM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 258);
  for (c2_i204 = 0; c2_i204 < 9; c2_i204++) {
    c2_d_probParents[c2_i204] = c2_probParents[c2_i204] * c2_p2[c2_i204];
  }

  c2_sum(chartInstance, c2_d_probParents, c2_dv36);
  for (c2_i205 = 0; c2_i205 < 3; c2_i205++) {
    c2_dv39[c2_i205] = c2_dv36[c2_i205];
  }

  *c2_new_2CM = c2_b_sum(chartInstance, c2_dv39) * c2_new_TCM;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 259);
  for (c2_i206 = 0; c2_i206 < 9; c2_i206++) {
    c2_e_probParents[c2_i206] = c2_probParents[c2_i206] * c2_p0[c2_i206];
  }

  c2_sum(chartInstance, c2_e_probParents, c2_dv36);
  for (c2_i207 = 0; c2_i207 < 3; c2_i207++) {
    c2_dv40[c2_i207] = c2_dv36[c2_i207];
  }

  *c2_new_0CF = c2_b_sum(chartInstance, c2_dv40) * c2_new_TCF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 260);
  for (c2_i208 = 0; c2_i208 < 9; c2_i208++) {
    c2_f_probParents[c2_i208] = c2_probParents[c2_i208] * c2_p1[c2_i208];
  }

  c2_sum(chartInstance, c2_f_probParents, c2_dv36);
  for (c2_i209 = 0; c2_i209 < 3; c2_i209++) {
    c2_dv41[c2_i209] = c2_dv36[c2_i209];
  }

  *c2_new_1CF = c2_b_sum(chartInstance, c2_dv41) * c2_new_TCF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 261);
  for (c2_i210 = 0; c2_i210 < 9; c2_i210++) {
    c2_g_probParents[c2_i210] = c2_probParents[c2_i210] * c2_p2[c2_i210];
  }

  c2_sum(chartInstance, c2_g_probParents, c2_dv36);
  for (c2_i211 = 0; c2_i211 < 3; c2_i211++) {
    c2_dv42[c2_i211] = c2_dv36[c2_i211];
  }

  *c2_new_2CF = c2_b_sum(chartInstance, c2_dv42) * c2_new_TCF;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 263);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -263);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c2_sum(SFc2_mut_screenInstanceStruct *chartInstance, real_T c2_x[9],
                   real_T c2_y[3])
{
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_i;
  int32_T c2_ixstart;
  real_T c2_s;
  int32_T c2_k;
  (void)chartInstance;
  c2_ix = -1;
  c2_iy = -1;
  for (c2_i = 1; c2_i < 4; c2_i++) {
    c2_ixstart = c2_ix + 2;
    c2_ixstart;
    c2_ix = c2_ixstart - 1;
    c2_s = c2_x[c2_ix];
    for (c2_k = 2; c2_k < 4; c2_k++) {
      c2_ix++;
      c2_s += c2_x[c2_ix];
    }

    c2_iy++;
    c2_y[c2_iy] = c2_s;
  }
}

static real_T c2_b_sum(SFc2_mut_screenInstanceStruct *chartInstance, real_T
  c2_x[3])
{
  real_T c2_y;
  int32_T c2_k;
  int32_T c2_b_k;
  (void)chartInstance;
  c2_y = c2_x[0];
  for (c2_k = 2; c2_k < 4; c2_k++) {
    c2_b_k = c2_k - 1;
    c2_y += c2_x[c2_b_k];
  }

  return c2_y;
}

static void c2_calcLeaving(SFc2_mut_screenInstanceStruct *chartInstance, real_T
  c2_L[2], c2_struct_zKkRWFtALBg7fNtPuY4M6D *c2_b_mut, real_T c2_expiring,
  boolean_T c2_childAgeBracket, real_T c2_leaving[2])
{
  uint32_T c2_debug_family_var_map[10];
  real_T c2_A;
  real_T c2_Y;
  real_T c2_dist;
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i212;
  real_T c2_b_A;
  real_T c2_B;
  real_T c2_x;
  real_T c2_y;
  real_T c2_b_x;
  real_T c2_b_y;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c2_e_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Y, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dist, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 3U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 4U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_L, 5U, c2_d_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_mut, 6U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_expiring, 7U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_childAgeBracket, 8U,
    c2_g_sf_marshallOut, c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_leaving, 9U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  CV_EML_FCN(0, 4);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 315);
  for (c2_i212 = 0; c2_i212 < 2; c2_i212++) {
    c2_leaving[c2_i212] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 316);
  if (CV_EML_IF(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 1, c2_L[0], 0.0, -1, 1U,
        c2_L[0] != 0.0))) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 317);
    c2_b_A = c2_L[1];
    c2_B = c2_L[0];
    c2_x = c2_b_A;
    c2_y = c2_B;
    c2_b_x = c2_x;
    c2_b_y = c2_y;
    c2_A = c2_b_x / c2_b_y;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 319);
    c2_A = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 321);
  if (CV_EML_IF(0, 1, 2, c2_childAgeBracket)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 322);
    c2_Y = c2_b_mut->Y_C;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 323);
    c2_dist = c2_b_mut->distribution[0];
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 325);
    c2_Y = c2_b_mut->Y_R;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 326);
    c2_dist = c2_b_mut->distribution[1];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 328);
  if (CV_EML_IF(0, 1, 3, CV_RELATIONAL_EVAL(4U, 0U, 2, c2_A, c2_Y - c2_dist, -1,
        5U, c2_A >= c2_Y - c2_dist))) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 329);
    c2_leaving[0] = c2_b_mut->distributionPercent * (c2_L[0] - c2_expiring);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 331);
    c2_leaving[0] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 333);
  c2_leaving[1] = c2_leaving[0] * c2_Y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 335);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -335);
  _SFD_SYMBOL_SCOPE_POP();
}

static real_T c2_c_sum(SFc2_mut_screenInstanceStruct *chartInstance, real_T
  c2_x[3])
{
  real_T c2_y;
  int32_T c2_k;
  int32_T c2_b_k;
  (void)chartInstance;
  c2_y = c2_x[0];
  for (c2_k = 2; c2_k < 4; c2_k++) {
    c2_b_k = c2_k - 1;
    c2_y += c2_x[c2_b_k];
  }

  return c2_y;
}

static real_T c2_d_sum(SFc2_mut_screenInstanceStruct *chartInstance, real_T
  c2_x[6])
{
  real_T c2_y;
  int32_T c2_k;
  int32_T c2_b_k;
  (void)chartInstance;
  c2_y = c2_x[0];
  for (c2_k = 2; c2_k < 7; c2_k++) {
    c2_b_k = c2_k - 1;
    c2_y += c2_x[c2_b_k];
  }

  return c2_y;
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_l_emlrt_marshallIn(SFc2_mut_screenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i213;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i213, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i213;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_m_emlrt_marshallIn(SFc2_mut_screenInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_mut_screen, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_mut_screen), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_mut_screen);
  return c2_y;
}

static uint8_T c2_n_emlrt_marshallIn(SFc2_mut_screenInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_mut_screenInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_mut_screenInstanceStruct
  *chartInstance)
{
  chartInstance->c2_clock = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_L_0CM = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_L_1CM = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_L_2CM = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_L_0RM = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c2_L_1RM = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c2_L_2RM = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c2_L_0SM = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c2_L_1SM = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c2_L_2SM = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c2_L_0CF = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 10);
  chartInstance->c2_L_1CF = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 11);
  chartInstance->c2_L_2CF = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 12);
  chartInstance->c2_L_0RF = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 13);
  chartInstance->c2_L_1RF = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 14);
  chartInstance->c2_L_2RF = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 15);
  chartInstance->c2_L_0SF = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 16);
  chartInstance->c2_L_1SF = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 17);
  chartInstance->c2_L_2SF = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 18);
  chartInstance->c2_nL_0CM = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_nL_1CM = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_nL_2CM = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_nL_0RM = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c2_nL_1RM = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c2_nL_2RM = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c2_nL_0SM = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c2_nL_1SM = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c2_nL_2SM = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c2_nL_0CF = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 10);
  chartInstance->c2_nL_1CF = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 11);
  chartInstance->c2_nL_2CF = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 12);
  chartInstance->c2_nL_0RF = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 13);
  chartInstance->c2_nL_1RF = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 14);
  chartInstance->c2_nL_2RF = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 15);
  chartInstance->c2_nL_0SF = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 16);
  chartInstance->c2_nL_1SF = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 17);
  chartInstance->c2_nL_2SF = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 18);
  chartInstance->c2_A_0CM = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 19);
  chartInstance->c2_leaving_0CM = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 20);
  chartInstance->c2_L_T = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 21);
  chartInstance->c2_f_0T = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 22);
  chartInstance->c2_f_1T = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 23);
  chartInstance->c2_f_2T = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 24);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_mut_screen_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(498370731U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1131582375U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3870908647U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3423823305U);
}

mxArray* sf_c2_mut_screen_get_post_codegen_info(void);
mxArray *sf_c2_mut_screen_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("dfOfKjIlYwi2DmM5x9AXpG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,19,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,15,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,15,"type",mxType);
    }

    mxSetField(mxData,15,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,16,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,16,"type",mxType);
    }

    mxSetField(mxData,16,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,17,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,17,"type",mxType);
    }

    mxSetField(mxData,17,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,18,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,18,"type",mxType);
    }

    mxSetField(mxData,18,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,24,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,15,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,15,"type",mxType);
    }

    mxSetField(mxData,15,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,16,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,16,"type",mxType);
    }

    mxSetField(mxData,16,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,17,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,17,"type",mxType);
    }

    mxSetField(mxData,17,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,18,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,18,"type",mxType);
    }

    mxSetField(mxData,18,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(2);
      mxSetField(mxData,19,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,19,"type",mxType);
    }

    mxSetField(mxData,19,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,20,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,20,"type",mxType);
    }

    mxSetField(mxData,20,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,21,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,21,"type",mxType);
    }

    mxSetField(mxData,21,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,22,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,22,"type",mxType);
    }

    mxSetField(mxData,22,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,23,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,23,"type",mxType);
    }

    mxSetField(mxData,23,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_mut_screen_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_mut_screen_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_mut_screen_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_mut_screen_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_mut_screen_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_mut_screen(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[70],T\"A_0CM\",},{M[1],M[72],T\"L_T\",},{M[1],M[73],T\"f_0T\",},{M[1],M[74],T\"f_1T\",},{M[1],M[75],T\"f_2T\",},{M[1],M[71],T\"leaving_0CM\",},{M[1],M[55],T\"nL_0CF\",},{M[1],M[46],T\"nL_0CM\",},{M[1],M[58],T\"nL_0RF\",},{M[1],M[49],T\"nL_0RM\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[61],T\"nL_0SF\",},{M[1],M[52],T\"nL_0SM\",},{M[1],M[56],T\"nL_1CF\",},{M[1],M[47],T\"nL_1CM\",},{M[1],M[59],T\"nL_1RF\",},{M[1],M[50],T\"nL_1RM\",},{M[1],M[62],T\"nL_1SF\",},{M[1],M[53],T\"nL_1SM\",},{M[1],M[57],T\"nL_2CF\",},{M[1],M[48],T\"nL_2CM\",}}",
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[60],T\"nL_2RF\",},{M[1],M[51],T\"nL_2RM\",},{M[1],M[63],T\"nL_2SF\",},{M[1],M[54],T\"nL_2SM\",},{M[8],M[0],T\"is_active_c2_mut_screen\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 25, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_mut_screen_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_mut_screenInstanceStruct *chartInstance =
      (SFc2_mut_screenInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _mut_screenMachineNumber_,
           2,
           1,
           1,
           0,
           44,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_mut_screenMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_mut_screenMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _mut_screenMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"clock");
          _SFD_SET_DATA_PROPS(1,1,1,0,"L_0CM");
          _SFD_SET_DATA_PROPS(2,1,1,0,"L_1CM");
          _SFD_SET_DATA_PROPS(3,1,1,0,"L_2CM");
          _SFD_SET_DATA_PROPS(4,1,1,0,"L_0RM");
          _SFD_SET_DATA_PROPS(5,1,1,0,"L_1RM");
          _SFD_SET_DATA_PROPS(6,1,1,0,"L_2RM");
          _SFD_SET_DATA_PROPS(7,1,1,0,"L_0SM");
          _SFD_SET_DATA_PROPS(8,1,1,0,"L_1SM");
          _SFD_SET_DATA_PROPS(9,1,1,0,"L_2SM");
          _SFD_SET_DATA_PROPS(10,1,1,0,"L_0CF");
          _SFD_SET_DATA_PROPS(11,1,1,0,"L_1CF");
          _SFD_SET_DATA_PROPS(12,1,1,0,"L_2CF");
          _SFD_SET_DATA_PROPS(13,1,1,0,"L_0RF");
          _SFD_SET_DATA_PROPS(14,1,1,0,"L_1RF");
          _SFD_SET_DATA_PROPS(15,1,1,0,"L_2RF");
          _SFD_SET_DATA_PROPS(16,1,1,0,"L_0SF");
          _SFD_SET_DATA_PROPS(17,1,1,0,"L_1SF");
          _SFD_SET_DATA_PROPS(18,1,1,0,"L_2SF");
          _SFD_SET_DATA_PROPS(19,2,0,1,"nL_0CM");
          _SFD_SET_DATA_PROPS(20,2,0,1,"nL_1CM");
          _SFD_SET_DATA_PROPS(21,2,0,1,"nL_2CM");
          _SFD_SET_DATA_PROPS(22,2,0,1,"nL_0RM");
          _SFD_SET_DATA_PROPS(23,2,0,1,"nL_1RM");
          _SFD_SET_DATA_PROPS(24,2,0,1,"nL_2RM");
          _SFD_SET_DATA_PROPS(25,2,0,1,"nL_0SM");
          _SFD_SET_DATA_PROPS(26,2,0,1,"nL_1SM");
          _SFD_SET_DATA_PROPS(27,2,0,1,"nL_2SM");
          _SFD_SET_DATA_PROPS(28,2,0,1,"nL_0CF");
          _SFD_SET_DATA_PROPS(29,2,0,1,"nL_1CF");
          _SFD_SET_DATA_PROPS(30,2,0,1,"nL_2CF");
          _SFD_SET_DATA_PROPS(31,2,0,1,"nL_0RF");
          _SFD_SET_DATA_PROPS(32,2,0,1,"nL_1RF");
          _SFD_SET_DATA_PROPS(33,2,0,1,"nL_2RF");
          _SFD_SET_DATA_PROPS(34,2,0,1,"nL_0SF");
          _SFD_SET_DATA_PROPS(35,2,0,1,"nL_1SF");
          _SFD_SET_DATA_PROPS(36,2,0,1,"nL_2SF");
          _SFD_SET_DATA_PROPS(37,2,0,1,"A_0CM");
          _SFD_SET_DATA_PROPS(38,2,0,1,"leaving_0CM");
          _SFD_SET_DATA_PROPS(39,2,0,1,"L_T");
          _SFD_SET_DATA_PROPS(40,2,0,1,"f_0T");
          _SFD_SET_DATA_PROPS(41,2,0,1,"f_1T");
          _SFD_SET_DATA_PROPS(42,2,0,1,"f_2T");
          _SFD_SET_DATA_PROPS(43,10,0,0,"mut");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,5,0,4,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,9062);
        _SFD_CV_INIT_EML_FCN(0,1,"getNewChildrenMutations",9062,-1,10620);
        _SFD_CV_INIT_EML_FCN(0,2,"behavioralModification",10620,-1,10939);
        _SFD_CV_INIT_EML_FCN(0,3,"probMutationInheritance",10939,-1,11452);
        _SFD_CV_INIT_EML_FCN(0,4,"calcLeaving",11452,-1,11828);
        _SFD_CV_INIT_EML_IF(0,1,0,549,563,-1,579);
        _SFD_CV_INIT_EML_IF(0,1,1,11531,11543,11561,11578);
        _SFD_CV_INIT_EML_IF(0,1,2,11579,11597,11643,11696);
        _SFD_CV_INIT_EML_IF(0,1,3,11697,11712,11769,11795);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,552,563,-1,5);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,11534,11543,-1,1);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,2,11700,11712,-1,5);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(19,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(20,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(21,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(22,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(23,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(24,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(25,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(26,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(27,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(28,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(29,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(30,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(31,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(32,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(33,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(34,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(35,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(36,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(37,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(38,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(39,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(40,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(41,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(42,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(43,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)c2_c_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _mut_screenMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_mut_screenInstanceStruct *chartInstance =
      (SFc2_mut_screenInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c2_clock);
        _SFD_SET_DATA_VALUE_PTR(1U, *chartInstance->c2_L_0CM);
        _SFD_SET_DATA_VALUE_PTR(2U, *chartInstance->c2_L_1CM);
        _SFD_SET_DATA_VALUE_PTR(3U, *chartInstance->c2_L_2CM);
        _SFD_SET_DATA_VALUE_PTR(4U, *chartInstance->c2_L_0RM);
        _SFD_SET_DATA_VALUE_PTR(5U, *chartInstance->c2_L_1RM);
        _SFD_SET_DATA_VALUE_PTR(6U, *chartInstance->c2_L_2RM);
        _SFD_SET_DATA_VALUE_PTR(7U, *chartInstance->c2_L_0SM);
        _SFD_SET_DATA_VALUE_PTR(8U, *chartInstance->c2_L_1SM);
        _SFD_SET_DATA_VALUE_PTR(9U, *chartInstance->c2_L_2SM);
        _SFD_SET_DATA_VALUE_PTR(10U, *chartInstance->c2_L_0CF);
        _SFD_SET_DATA_VALUE_PTR(11U, *chartInstance->c2_L_1CF);
        _SFD_SET_DATA_VALUE_PTR(12U, *chartInstance->c2_L_2CF);
        _SFD_SET_DATA_VALUE_PTR(13U, *chartInstance->c2_L_0RF);
        _SFD_SET_DATA_VALUE_PTR(14U, *chartInstance->c2_L_1RF);
        _SFD_SET_DATA_VALUE_PTR(15U, *chartInstance->c2_L_2RF);
        _SFD_SET_DATA_VALUE_PTR(16U, *chartInstance->c2_L_0SF);
        _SFD_SET_DATA_VALUE_PTR(17U, *chartInstance->c2_L_1SF);
        _SFD_SET_DATA_VALUE_PTR(18U, *chartInstance->c2_L_2SF);
        _SFD_SET_DATA_VALUE_PTR(19U, *chartInstance->c2_nL_0CM);
        _SFD_SET_DATA_VALUE_PTR(20U, *chartInstance->c2_nL_1CM);
        _SFD_SET_DATA_VALUE_PTR(21U, *chartInstance->c2_nL_2CM);
        _SFD_SET_DATA_VALUE_PTR(22U, *chartInstance->c2_nL_0RM);
        _SFD_SET_DATA_VALUE_PTR(23U, *chartInstance->c2_nL_1RM);
        _SFD_SET_DATA_VALUE_PTR(24U, *chartInstance->c2_nL_2RM);
        _SFD_SET_DATA_VALUE_PTR(25U, *chartInstance->c2_nL_0SM);
        _SFD_SET_DATA_VALUE_PTR(26U, *chartInstance->c2_nL_1SM);
        _SFD_SET_DATA_VALUE_PTR(27U, *chartInstance->c2_nL_2SM);
        _SFD_SET_DATA_VALUE_PTR(28U, *chartInstance->c2_nL_0CF);
        _SFD_SET_DATA_VALUE_PTR(29U, *chartInstance->c2_nL_1CF);
        _SFD_SET_DATA_VALUE_PTR(30U, *chartInstance->c2_nL_2CF);
        _SFD_SET_DATA_VALUE_PTR(31U, *chartInstance->c2_nL_0RF);
        _SFD_SET_DATA_VALUE_PTR(32U, *chartInstance->c2_nL_1RF);
        _SFD_SET_DATA_VALUE_PTR(33U, *chartInstance->c2_nL_2RF);
        _SFD_SET_DATA_VALUE_PTR(34U, *chartInstance->c2_nL_0SF);
        _SFD_SET_DATA_VALUE_PTR(35U, *chartInstance->c2_nL_1SF);
        _SFD_SET_DATA_VALUE_PTR(36U, *chartInstance->c2_nL_2SF);
        _SFD_SET_DATA_VALUE_PTR(43U, &chartInstance->c2_mut);
        _SFD_SET_DATA_VALUE_PTR(37U, chartInstance->c2_A_0CM);
        _SFD_SET_DATA_VALUE_PTR(38U, *chartInstance->c2_leaving_0CM);
        _SFD_SET_DATA_VALUE_PTR(39U, chartInstance->c2_L_T);
        _SFD_SET_DATA_VALUE_PTR(40U, chartInstance->c2_f_0T);
        _SFD_SET_DATA_VALUE_PTR(41U, chartInstance->c2_f_1T);
        _SFD_SET_DATA_VALUE_PTR(42U, chartInstance->c2_f_2T);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "smZnEXf53NFNhbUjHPwffSB";
}

static void sf_opaque_initialize_c2_mut_screen(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_mut_screenInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c2_mut_screen((SFc2_mut_screenInstanceStruct*)
    chartInstanceVar);
  initialize_c2_mut_screen((SFc2_mut_screenInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_mut_screen(void *chartInstanceVar)
{
  enable_c2_mut_screen((SFc2_mut_screenInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_mut_screen(void *chartInstanceVar)
{
  disable_c2_mut_screen((SFc2_mut_screenInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_mut_screen(void *chartInstanceVar)
{
  sf_gateway_c2_mut_screen((SFc2_mut_screenInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_mut_screen(SimStruct* S)
{
  return get_sim_state_c2_mut_screen((SFc2_mut_screenInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_mut_screen(SimStruct* S, const mxArray
  *st)
{
  set_sim_state_c2_mut_screen((SFc2_mut_screenInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c2_mut_screen(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_mut_screenInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_mut_screen_optimization_info();
    }

    finalize_c2_mut_screen((SFc2_mut_screenInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_mut_screen((SFc2_mut_screenInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_mut_screen(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_mut_screen((SFc2_mut_screenInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c2_mut_screen(SimStruct *S)
{
  /* Actual parameters from chart:
     mut
   */
  const char_T *rtParamNames[] = { "mut" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0],
    sf_get_param_data_type_id(S,0));
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_mut_screen_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 2);
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 11, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 12, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 13, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 14, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 15, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 16, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 17, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 18, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,19);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,24);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=24; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 19; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1002801405U));
  ssSetChecksum1(S,(1337270314U));
  ssSetChecksum2(S,(4281821175U));
  ssSetChecksum3(S,(3073550720U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_mut_screen(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_mut_screen(SimStruct *S)
{
  SFc2_mut_screenInstanceStruct *chartInstance;
  chartInstance = (SFc2_mut_screenInstanceStruct *)utMalloc(sizeof
    (SFc2_mut_screenInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_mut_screenInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_mut_screen;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_mut_screen;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_mut_screen;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_mut_screen;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_mut_screen;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_mut_screen;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_mut_screen;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_mut_screen;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_mut_screen;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_mut_screen;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_mut_screen;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c2_mut_screen(chartInstance);
}

void c2_mut_screen_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_mut_screen(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_mut_screen(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_mut_screen(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_mut_screen_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
