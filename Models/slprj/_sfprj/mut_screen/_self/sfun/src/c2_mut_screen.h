#ifndef __c2_mut_screen_h__
#define __c2_mut_screen_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef struct_struct_qHpeHlL7YRQjHTvGIxkLGB_tag
#define struct_struct_qHpeHlL7YRQjHTvGIxkLGB_tag

struct struct_qHpeHlL7YRQjHTvGIxkLGB_tag
{
  real_T NR;
  real_T LR;
  real_T MR;
  real_T HR;
  real_T efficiency;
};

#endif                                 /*struct_struct_qHpeHlL7YRQjHTvGIxkLGB_tag*/

#ifndef typedef_c2_struct_qHpeHlL7YRQjHTvGIxkLGB
#define typedef_c2_struct_qHpeHlL7YRQjHTvGIxkLGB

typedef struct struct_qHpeHlL7YRQjHTvGIxkLGB_tag
  c2_struct_qHpeHlL7YRQjHTvGIxkLGB;

#endif                                 /*typedef_c2_struct_qHpeHlL7YRQjHTvGIxkLGB*/

#ifndef struct_struct_zKkRWFtALBg7fNtPuY4M6D_tag
#define struct_struct_zKkRWFtALBg7fNtPuY4M6D_tag

struct struct_zKkRWFtALBg7fNtPuY4M6D_tag
{
  real_T fertility;
  real_T M2Fprobability;
  real_T Y_C;
  real_T Y_R;
  real_T distribution[2];
  real_T distributionPercent;
  real_T MSM;
  real_T MSF;
  real_T mort[6];
  real_T muMort[18];
  c2_struct_qHpeHlL7YRQjHTvGIxkLGB screen;
};

#endif                                 /*struct_struct_zKkRWFtALBg7fNtPuY4M6D_tag*/

#ifndef typedef_c2_struct_zKkRWFtALBg7fNtPuY4M6D
#define typedef_c2_struct_zKkRWFtALBg7fNtPuY4M6D

typedef struct struct_zKkRWFtALBg7fNtPuY4M6D_tag
  c2_struct_zKkRWFtALBg7fNtPuY4M6D;

#endif                                 /*typedef_c2_struct_zKkRWFtALBg7fNtPuY4M6D*/

#ifndef typedef_SFc2_mut_screenInstanceStruct
#define typedef_SFc2_mut_screenInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_mut_screen;
  c2_struct_zKkRWFtALBg7fNtPuY4M6D c2_mut;
  real_T *c2_clock;
  real_T (*c2_L_0CM)[2];
  real_T (*c2_L_1CM)[2];
  real_T (*c2_L_2CM)[2];
  real_T (*c2_L_0RM)[2];
  real_T (*c2_L_1RM)[2];
  real_T (*c2_L_2RM)[2];
  real_T (*c2_L_0SM)[2];
  real_T (*c2_L_1SM)[2];
  real_T (*c2_L_2SM)[2];
  real_T (*c2_L_0CF)[2];
  real_T (*c2_L_1CF)[2];
  real_T (*c2_L_2CF)[2];
  real_T (*c2_L_0RF)[2];
  real_T (*c2_L_1RF)[2];
  real_T (*c2_L_2RF)[2];
  real_T (*c2_L_0SF)[2];
  real_T (*c2_L_1SF)[2];
  real_T (*c2_L_2SF)[2];
  real_T (*c2_nL_0CM)[2];
  real_T (*c2_nL_1CM)[2];
  real_T (*c2_nL_2CM)[2];
  real_T (*c2_nL_0RM)[2];
  real_T (*c2_nL_1RM)[2];
  real_T (*c2_nL_2RM)[2];
  real_T (*c2_nL_0SM)[2];
  real_T (*c2_nL_1SM)[2];
  real_T (*c2_nL_2SM)[2];
  real_T (*c2_nL_0CF)[2];
  real_T (*c2_nL_1CF)[2];
  real_T (*c2_nL_2CF)[2];
  real_T (*c2_nL_0RF)[2];
  real_T (*c2_nL_1RF)[2];
  real_T (*c2_nL_2RF)[2];
  real_T (*c2_nL_0SF)[2];
  real_T (*c2_nL_1SF)[2];
  real_T (*c2_nL_2SF)[2];
  real_T *c2_A_0CM;
  real_T (*c2_leaving_0CM)[2];
  real_T *c2_L_T;
  real_T *c2_f_0T;
  real_T *c2_f_1T;
  real_T *c2_f_2T;
} SFc2_mut_screenInstanceStruct;

#endif                                 /*typedef_SFc2_mut_screenInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_mut_screen_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_mut_screen_get_check_sum(mxArray *plhs[]);
extern void c2_mut_screen_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
