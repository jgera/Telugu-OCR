/*
 * isoverlapping.h
 *
 * Code generation for function 'isoverlapping'
 *
 */

#ifndef __ISOVERLAPPING_H__
#define __ISOVERLAPPING_H__

/* Include files */
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blas.h"
#include "rtwtypes.h"
#include "isoverlapping_types.h"

/* Function Declarations */
extern real_T isoverlapping(real_T stroke1, real_T stroke2);

#ifdef __WATCOMC__

#pragma aux isoverlapping value [8087];

#endif
#endif

/* End of code generation (isoverlapping.h) */
