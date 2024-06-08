#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES 
#include "foo.c"

void gen_arrays(double **time,double **Uvx, double **Uvix, double tn, double tk,double Un,double U, double a,double b,double dt, int n);

int precision(double **time,double **Uvx, double **Uvix, double tn, double tk,double Un,double U, double a,double b, double prec, double parametr );

double return_extremum(double * arr, int size, int flag);
double impulse_duration(double dt, double *U, int size);
double duration_of_back_front_impulse(double dt, double *U, int size);
double voltage_point(double *time, double *U,int size, double voltage);
double maximum_point(double *time, double *U,int size);
void show_arrays(double *time,double *Uvx, double *Uvix, int n); 

int show_zast();
int write_to_file(double *time,double *Uvx, double *Uvix, int size);

int get_valid_int();
