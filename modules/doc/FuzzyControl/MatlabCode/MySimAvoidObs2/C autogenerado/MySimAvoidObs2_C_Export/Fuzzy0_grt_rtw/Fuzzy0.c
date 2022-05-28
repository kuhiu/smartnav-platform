/*
 * Fuzzy0.c
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

#include "Fuzzy0.h"
#include "Fuzzy0_private.h"

/* External inputs (root inport signals with default storage) */
ExtU_Fuzzy0_T Fuzzy0_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Fuzzy0_T Fuzzy0_Y;

/* Real-time model */
static RT_MODEL_Fuzzy0_T Fuzzy0_M_;
RT_MODEL_Fuzzy0_T *const Fuzzy0_M = &Fuzzy0_M_;

/* Forward declaration for local functions */
static real_T Fuzzy0_trapmf(real_T x, const real_T params[4]);
static void Fuzzy0_trapmf_e(const real_T x[101], const real_T params[4], real_T
  y[101]);

/* Function for MATLAB Function: '<S1>/Evaluate Rule Antecedents' */
static real_T Fuzzy0_trapmf(real_T x, const real_T params[4])
{
  real_T b_x;
  real_T b_y;
  b_x = 0.0;
  b_y = 0.0;
  if (x >= params[1]) {
    b_x = 1.0;
  }

  if (x < params[0]) {
    b_x = 0.0;
  }

  if ((params[0] <= x) && (x < params[1])) {
    b_x = 1.0 / (params[1] - params[0]) * (x - params[0]);
  }

  if (x <= params[2]) {
    b_y = 1.0;
  }

  if (x > params[3]) {
    b_y = 0.0;
  }

  if ((params[2] < x) && (x <= params[3])) {
    b_y = (0.2378 - x) * 9.2764378478664185;
  }

  return fmin(b_x, b_y);
}

/* Function for MATLAB Function: '<S1>/Evaluate Rule Consequents' */
static void Fuzzy0_trapmf_e(const real_T x[101], const real_T params[4], real_T
  y[101])
{
  real_T a;
  real_T b;
  real_T c;
  real_T d;
  int32_T i;
  a = params[0];
  b = params[1];
  c = params[2];
  d = params[3];
  for (i = 0; i < 101; i++) {
    real_T b_y1;
    real_T x_0;
    real_T y2;
    x_0 = x[i];
    b_y1 = 0.0;
    y2 = 0.0;
    if (x_0 >= b) {
      b_y1 = 1.0;
    }

    if (x_0 < a) {
      b_y1 = 0.0;
    }

    if ((a <= x_0) && (x_0 < b) && (a != b)) {
      b_y1 = 1.0 / (b - a) * (x_0 - a);
    }

    if (x_0 <= c) {
      y2 = 1.0;
    }

    if (x_0 > d) {
      y2 = 0.0;
    }

    if ((c < x_0) && (x_0 <= d) && (c != d)) {
      y2 = 1.0 / (d - c) * (d - x_0);
    }

    y[i] = fmin(b_y1, y2);
  }
}

/* Model step function */
void Fuzzy0_step(void)
{
  real_T outputMFCache[303];
  real_T rtb_aggregatedOutputs[101];
  real_T tmp[101];
  real_T tmp_0[101];
  real_T tmp_1[101];
  real_T rtb_antecedentOutputs[8];
  real_T inputMFCache[6];
  real_T mfVal;
  real_T rtb_antecedentOutputs_j;
  real_T sumAntecedentOutputs;
  real_T x_idx_1;
  int32_T i;
  int32_T inputID;
  static const real_T b[4] = { -0.09, -0.0435, 0.13, 0.2378 };

  static const real_T c[4] = { 0.1504, 0.2253, 1.076, 1.076 };

  static const real_T d[4] = { 0.1504, 0.2254, 1.076, 1.076 };

  static const int8_T e[24] = { 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2,
    1, 2, 1, 2, 1, 2, 1, 2 };

  static const real_T b_0[4] = { -1.62, -0.8441, -0.14, -0.078 };

  static const real_T c_0[4] = { 0.078, 0.14, 0.8421, 1.342 };

  static const real_T d_0[4] = { -0.1, -0.04998, 0.04998, 0.1 };

  static const int8_T e_0[8] = { 3, 2, 3, 3, 1, 1, 1, 3 };

  /* Outputs for Atomic SubSystem: '<Root>/Fuzzy Logic  Controller' */
  /* MATLAB Function: '<S1>/Evaluate Rule Antecedents' incorporates:
   *  Inport: '<Root>/in'
   */
  sumAntecedentOutputs = 0.0;
  inputMFCache[0] = Fuzzy0_trapmf(Fuzzy0_U.in[0], b);
  inputMFCache[1] = Fuzzy0_trapmf(Fuzzy0_U.in[0], c);
  inputMFCache[2] = Fuzzy0_trapmf(Fuzzy0_U.in[1], b);
  inputMFCache[3] = Fuzzy0_trapmf(Fuzzy0_U.in[1], d);
  inputMFCache[4] = Fuzzy0_trapmf(Fuzzy0_U.in[2], b);
  inputMFCache[5] = Fuzzy0_trapmf(Fuzzy0_U.in[2], c);
  for (i = 0; i < 8; i++) {
    x_idx_1 = inputMFCache[e[i] - 1];
    if (1.0 > x_idx_1) {
      rtb_antecedentOutputs_j = x_idx_1;
    } else {
      rtb_antecedentOutputs_j = 1.0;
    }

    x_idx_1 = inputMFCache[e[i + 8] + 1];
    if (rtb_antecedentOutputs_j > x_idx_1) {
      rtb_antecedentOutputs_j = x_idx_1;
    }

    x_idx_1 = inputMFCache[e[i + 16] + 3];
    if (rtb_antecedentOutputs_j > x_idx_1) {
      rtb_antecedentOutputs_j = x_idx_1;
    }

    sumAntecedentOutputs += rtb_antecedentOutputs_j;
    rtb_antecedentOutputs[i] = rtb_antecedentOutputs_j;
  }

  /* MATLAB Function: '<S1>/Evaluate Rule Consequents' incorporates:
   *  Constant: '<S1>/Output Sample Points'
   */
  Fuzzy0_trapmf_e(Fuzzy0_P.OutputSamplePoints_Value, b_0, tmp);
  Fuzzy0_trapmf_e(Fuzzy0_P.OutputSamplePoints_Value, c_0, tmp_0);
  Fuzzy0_trapmf_e(Fuzzy0_P.OutputSamplePoints_Value, d_0, tmp_1);
  for (i = 0; i < 101; i++) {
    rtb_aggregatedOutputs[i] = 0.0;
    outputMFCache[3 * i] = tmp[i];
    outputMFCache[3 * i + 1] = tmp_0[i];
    outputMFCache[3 * i + 2] = tmp_1[i];
  }

  for (i = 0; i < 8; i++) {
    x_idx_1 = rtb_antecedentOutputs[i];
    for (inputID = 0; inputID < 101; inputID++) {
      rtb_antecedentOutputs_j = rtb_aggregatedOutputs[inputID];
      mfVal = outputMFCache[(3 * inputID + e_0[i]) - 1];
      if ((mfVal > x_idx_1) || rtIsNaN(mfVal)) {
        mfVal = x_idx_1;
      }

      if ((rtb_antecedentOutputs_j < mfVal) || (rtIsNaN(rtb_antecedentOutputs_j)
           && (!rtIsNaN(mfVal)))) {
        rtb_antecedentOutputs_j = mfVal;
      }

      rtb_aggregatedOutputs[inputID] = rtb_antecedentOutputs_j;
    }
  }

  /* End of MATLAB Function: '<S1>/Evaluate Rule Consequents' */

  /* MATLAB Function: '<S1>/Defuzzify Outputs' incorporates:
   *  Constant: '<S1>/Output Sample Points'
   *  MATLAB Function: '<S1>/Evaluate Rule Antecedents'
   */
  if (sumAntecedentOutputs == 0.0) {
    /* Outport: '<Root>/out' */
    Fuzzy0_Y.out = 0.0;
  } else {
    sumAntecedentOutputs = 0.0;
    mfVal = 0.0;
    for (i = 0; i < 101; i++) {
      mfVal += rtb_aggregatedOutputs[i];
    }

    if (mfVal == 0.0) {
      /* Outport: '<Root>/out' incorporates:
       *  Constant: '<S1>/Output Sample Points'
       */
      Fuzzy0_Y.out = (Fuzzy0_P.OutputSamplePoints_Value[0] +
                      Fuzzy0_P.OutputSamplePoints_Value[100]) / 2.0;
    } else {
      for (i = 0; i < 101; i++) {
        sumAntecedentOutputs += Fuzzy0_P.OutputSamplePoints_Value[i] *
          rtb_aggregatedOutputs[i];
      }

      /* Outport: '<Root>/out' incorporates:
       *  Constant: '<S1>/Output Sample Points'
       */
      Fuzzy0_Y.out = 1.0 / mfVal * sumAntecedentOutputs;
    }
  }

  /* End of MATLAB Function: '<S1>/Defuzzify Outputs' */
  /* End of Outputs for SubSystem: '<Root>/Fuzzy Logic  Controller' */

  /* Matfile logging */
  rt_UpdateTXYLogVars(Fuzzy0_M->rtwLogInfo, (&Fuzzy0_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.2s, 0.0s] */
    if ((rtmGetTFinal(Fuzzy0_M)!=-1) &&
        !((rtmGetTFinal(Fuzzy0_M)-Fuzzy0_M->Timing.taskTime0) >
          Fuzzy0_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(Fuzzy0_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Fuzzy0_M->Timing.clockTick0)) {
    ++Fuzzy0_M->Timing.clockTickH0;
  }

  Fuzzy0_M->Timing.taskTime0 = Fuzzy0_M->Timing.clockTick0 *
    Fuzzy0_M->Timing.stepSize0 + Fuzzy0_M->Timing.clockTickH0 *
    Fuzzy0_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Fuzzy0_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Fuzzy0_M, 0,
                sizeof(RT_MODEL_Fuzzy0_T));
  rtmSetTFinal(Fuzzy0_M, 10.0);
  Fuzzy0_M->Timing.stepSize0 = 0.2;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    Fuzzy0_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Fuzzy0_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Fuzzy0_M->rtwLogInfo, (NULL));
    rtliSetLogT(Fuzzy0_M->rtwLogInfo, "tout");
    rtliSetLogX(Fuzzy0_M->rtwLogInfo, "");
    rtliSetLogXFinal(Fuzzy0_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Fuzzy0_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Fuzzy0_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Fuzzy0_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Fuzzy0_M->rtwLogInfo, 1);
    rtliSetLogY(Fuzzy0_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Fuzzy0_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Fuzzy0_M->rtwLogInfo, (NULL));
  }

  /* external inputs */
  (void)memset(&Fuzzy0_U, 0, sizeof(ExtU_Fuzzy0_T));

  /* external outputs */
  Fuzzy0_Y.out = 0.0;

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Fuzzy0_M->rtwLogInfo, 0.0, rtmGetTFinal
    (Fuzzy0_M), Fuzzy0_M->Timing.stepSize0, (&rtmGetErrorStatus(Fuzzy0_M)));
}

/* Model terminate function */
void Fuzzy0_terminate(void)
{
  /* (no terminate code required) */
}
