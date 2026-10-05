#ifndef _VARIABLETRANSITION_H
#define _VARIABLETRANSITION_H

// 変数の2次関数遷移

// 増加:ratioが0.0でmin、1.0でmaxになる
float VariableTransition_QuadraticIncrease(float ratio, float min, float max);

// 減少:ratioが0.0でmax、1.0でminになる
float VariableTransition_QuadraticDecrease(float ratio, float min, float max);

// 増減:ratioが0.0でmin、0.5でmax、1.0で再びminになる
float VariableTransition_QuadraticFluctuation(float ratio, float min, float max);

#endif