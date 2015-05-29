/*
 * isoverlapping_terminate.c
 *
 * Code generation for function 'isoverlapping_terminate'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "isoverlapping.h"
#include "isoverlapping_terminate.h"

/* Function Definitions */
void isoverlapping_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void isoverlapping_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (isoverlapping_terminate.c) */
