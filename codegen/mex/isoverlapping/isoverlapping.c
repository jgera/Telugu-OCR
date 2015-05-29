/*
 * isoverlapping.c
 *
 * Code generation for function 'isoverlapping'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "isoverlapping.h"

/* Function Definitions */
real_T isoverlapping(real_T stroke1, real_T stroke2)
{
  real_T y;
  real_T c;
  if (stroke1 < stroke2) {
    c = (stroke1 - stroke2) / (stroke1 - stroke1);
  } else {
    c = (stroke2 - stroke1) / (stroke2 - stroke2);
  }

  if (c > 0.0) {
    /* there should be atleast 20%overlap--threshold */
    y = 1.0;
  } else {
    y = 0.0;
  }

  return y;
}

/* End of code generation (isoverlapping.c) */
