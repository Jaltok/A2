/*********************************************
 *  Jeff Lund
 *  Systems A2: Floating point parser
 *  *****************************************/
// notes: bias = 2^(k-1)-1 k is exp bits


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

double isNegative(short unsigned int frac_bits, short unsigned int exp_bits, unsigned int hex_to_convert) {
    if((hex_to_convert>>(frac_bits+exp_bits))&1)
        return -1.0;
    else
        return 1.0;
}

int main(int argc, char* argv[]) {
    short unsigned int frac_bits, exp_bits;// , isolated_exp, isolated_frac, isolated_sign;
    unsigned int hex_to_convert;
    short unsigned int frac = 0; //isolated frac, n
    short unsigned int exp = 0; //isolated exp, k
    int bias;
    double sign, M, V, E;
	assert(argv[1] && argv[2] && argv[3]);
    sscanf(argv[1], "%hu", &frac_bits);
    sscanf(argv[2], "%hu", &exp_bits);
    sscanf(argv[3], "%x", &hex_to_convert);
    if(frac_bits > 10 || frac_bits < 2) {
        printf("Illegal number of fraction bits(%hu). Should be between 2 and 10.\n", frac_bits);
        return 0;
    }
    if(exp_bits > 5 || exp_bits < 3) {
        printf("Illegal number of exponent bits(%hu). Should be between 3 and 5.\n", exp_bits);
        return 0;
    }
    
    bias = pow(2, (exp_bits-1))-1; 
    sign = isNegative(frac_bits, exp_bits, hex_to_convert);
    frac = hex_to_convert&((1<<frac_bits)-1);
    exp = (hex_to_convert>>frac_bits)&((1<<exp_bits)-1);
    
    if(exp == 0) { //denormalized
        E = 1.0 - bias;
        M = 0.0;
        for(int i = 0; i < frac_bits; i++)
            if((frac>>i)&1)
                M += 1.0/pow(2.0,frac_bits-i);
        V = sign*M*pow(2, E);
        printf("%f\n", V);
    }	
	else if(exp == pow(2,exp_bits)-1) { //inf or NaN
		if(frac == 0) { //infinite
			if((hex_to_convert>>(frac_bits+exp_bits))&1) //neg inf
				printf("-inf\n");
			else //pos inf
				printf("+inf\n");
		}
		else //NaN
			printf("NaN\n");
	}
	else { //Normalized
        M = 1;
        for(int i = 0; i < frac_bits; i++)
            if((frac>>i)&1)
                M += 1.0/pow(2.0,frac_bits-i);
        E = exp - bias;
        V = sign*M*pow(2, E);
        printf("%f\n", V);
    }

    return 0;
}
