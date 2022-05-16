/*
 * Fuzzy0_types.h
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

#ifndef RTW_HEADER_Fuzzy0_types_h_
#define RTW_HEADER_Fuzzy0_types_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"

/* Model Code Variants */
#ifndef DEFINED_TYPEDEF_FOR_struct_nYqCuDQJxjUMnUawUUBRcD_
#define DEFINED_TYPEDEF_FOR_struct_nYqCuDQJxjUMnUawUUBRcD_

typedef struct {
  uint8_T SimulinkDiagnostic;
  uint8_T Model[6];
  uint8_T Block[30];
  uint8_T OutOfRangeInputValue;
  uint8_T NoRuleFired;
  uint8_T EmptyOutputFuzzySet;
} struct_nYqCuDQJxjUMnUawUUBRcD;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_nDiNttezQ8pHMZv76leKsH_
#define DEFINED_TYPEDEF_FOR_struct_nDiNttezQ8pHMZv76leKsH_

typedef struct {
  uint8_T type[6];
  int32_T origTypeLength;
  real_T params[4];
  int32_T origParamLength;
} struct_nDiNttezQ8pHMZv76leKsH;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_2A5rYhAH4xpaPuilbm7KP_
#define DEFINED_TYPEDEF_FOR_struct_2A5rYhAH4xpaPuilbm7KP_

typedef struct {
  struct_nDiNttezQ8pHMZv76leKsH mf[2];
  int32_T origNumMF;
} struct_2A5rYhAH4xpaPuilbm7KP;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_6VzYiVW2hAWQCI9jAYOVeF_
#define DEFINED_TYPEDEF_FOR_struct_6VzYiVW2hAWQCI9jAYOVeF_

typedef struct {
  struct_nDiNttezQ8pHMZv76leKsH mf[3];
  int32_T origNumMF;
} struct_6VzYiVW2hAWQCI9jAYOVeF;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_6rXIaIwHhT1VfIjAmuQRmD_
#define DEFINED_TYPEDEF_FOR_struct_6rXIaIwHhT1VfIjAmuQRmD_

typedef struct {
  uint8_T type[7];
  uint8_T andMethod[3];
  uint8_T orMethod[3];
  uint8_T defuzzMethod[8];
  uint8_T impMethod[3];
  uint8_T aggMethod[3];
  real_T inputRange[6];
  real_T outputRange[2];
  struct_2A5rYhAH4xpaPuilbm7KP inputMF[3];
  struct_6VzYiVW2hAWQCI9jAYOVeF outputMF;
  real_T antecedent[24];
  real_T consequent[8];
  real_T connection[8];
  real_T weight[8];
  int32_T numSamples;
  int32_T numInputs;
  int32_T numOutputs;
  int32_T numRules;
  int32_T numInputMFs[3];
  int32_T numCumInputMFs[3];
  int32_T numOutputMFs;
  int32_T numCumOutputMFs;
  real_T outputSamplePoints[101];
  int32_T orrSize[2];
  int32_T aggSize[2];
  int32_T irrSize[2];
  int32_T rfsSize[2];
  int32_T sumSize[2];
  int32_T inputFuzzySetType;
} struct_6rXIaIwHhT1VfIjAmuQRmD;

#endif

/* Parameters (default storage) */
typedef struct P_Fuzzy0_T_ P_Fuzzy0_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Fuzzy0_T RT_MODEL_Fuzzy0_T;

#endif                                 /* RTW_HEADER_Fuzzy0_types_h_ */
