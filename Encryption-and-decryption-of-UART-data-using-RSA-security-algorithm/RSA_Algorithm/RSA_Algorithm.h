/*
 * RSA_Algorithm.h
 *
 *  Created on: Nov 28, 2023
 *      Author: Mostafa Mahmoud Elshiekh
 */

#ifndef RSA_ALGORITHM_H_
#define RSA_ALGORITHM_H_

#include <stdio.h>
#include <math.h>


double p = 13 ;
double q = 29 ;



double RSA_Encryption(double  original_mess , double n , double e);
double RSA_Calc_Euler(double p, double q);
int RSA_Calc_N(double p, double q);
int gcd(int a, int b);
double RSA_Generate_e(double euler);
double RSA_Decryption(double Encrypted_Mes , double n,double d);
double RSA_Decryption_Calc_d(double Euler, double e);






#endif /* RSA_ALGORITHM_H_ */
