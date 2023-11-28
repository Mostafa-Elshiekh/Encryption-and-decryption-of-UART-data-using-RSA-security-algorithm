/*
 * RSA_Algorithm.c
 *
 *  Created on: Nov 28, 2023
 *      Author: musta
 */



double RSA_Encryption(double  original_mess , double n , double e)
{
	double Encreipted_Mess =0;
	Encreipted_Mess =pow(original_mess,e);
	Encreipted_Mess= fmod(Encreipted_Mess,n);
	return Encreipted_Mess;
}


double RSA_Calc_Euler(double p, double q)
{
	double euler1 = (p-1)*(q-1);
	return euler1;
}

int RSA_Calc_N(double p, double q)
{
	double n1 = p * q;
	return n1;
}

int gcd(int a, int b)
{
	int t;
	while(1) {
		t= a%b;
		if(t==0)
			return b;
		a = b;
		b= t;
	}
}

double RSA_Generate_e(double euler)
{
	double e =2;
	//public key
	//e stands for encrypt
	double temp;
	e=2;
	//for checking that 1 < e < phi(n) and gcd(e, phi(n)) = 1; i.e., e and phi(n) are coprime.
	while(e<euler) {
		temp = gcd(e,euler);
		if(temp==1)
			break;
		else
			e++;
	}
	return e;
}

double RSA_Decryption(double Encrypted_Mes , double n,double d)
{
	double Original_Mess = 0;
	double m = pow(Encrypted_Mes,d);
	Original_Mess=fmod(m,n);
	return Original_Mess;
}

double RSA_Decryption_Calc_d(double Euler, double e)
{
	double d = 0;

	//private key
	//d stands for decrypt
	//choosing d such that it satisfies d*e = 1 mod phi
	double d1 = 1 / e;
	d = fmod(d1, Euler);

	return d;
}
