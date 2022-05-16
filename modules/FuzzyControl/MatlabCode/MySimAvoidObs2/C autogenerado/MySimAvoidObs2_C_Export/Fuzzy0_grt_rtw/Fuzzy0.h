/*
 * Fuzzy0.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Fuzzy0".
 *
 * Model version              : 1.0
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Mon Oct 18 16:40:03 2021
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Fuzzy0_h_
#define RTW_HEADER_Fuzzy0_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef Fuzzy0_COMMON_INCLUDES_
#define Fuzzy0_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* Fuzzy0_COMMON_INCLUDES_ */

#include "Fuzzy0_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T in[3];                        /* '<Root>/in' */
} ExtU_Fuzzy0_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T out;                          /* '<Root>/out' */
} ExtY_Fuzzy0_T;

/* Parameters (default storage) */
struct P_Fuzzy0_T_ {
  real_T OutputSamplePoints_Value[101];/* Expression: fis.outputSamplePoints
                                        * Referenced by: '<S1>/Output Sample Points'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Fuzzy0_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_Fuzzy0_T Fuzzy0_P;

/* External inputs (root inport signals with default storage) */
extern ExtU_Fuzzy0_T Fuzzy0_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Fuzzy0_T Fuzzy0_Y;

/* Model entry point functions */
extern void Fuzzy0_initialize(void);
extern void Fuzzy0_step(void);
extern void Fuzzy0_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Fuzzy0_T *const Fuzzy0_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('untitled/Fuzzy Logic  Controller')    - opens subsystem untitled/Fuzzy Logic  Controller
 * hilite_system('untitled/Fuzzy Logic  Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'untitled'
 * '<S1>'   : 'untitled/Fuzzy Logic  Controller'
 * '<S2>'   : 'untitled/Fuzzy Logic  Controller/Defuzzify Outputs'
 * '<S3>'   : 'untitled/Fuzzy Logic  Controller/Evaluate Rule Antecedents'
 * '<S4>'   : 'untitled/Fuzzy Logic  Controller/Evaluate Rule Consequents'
 */
#endif                                 /* RTW_HEADER_Fuzzy0_h_ */
