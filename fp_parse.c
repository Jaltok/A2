/*********************************************
 *  Jeff Lund
 *  Systems A2: Floating point parser
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>


double isNegative(unsigned int frac_bits, unsigned int exp_bits, unsigned int hex_to_convert) {
    if((hex_to_convert>>(frac_bits+exp_bits))&1)
        return -1.0;
    else
        return 1.0;
}
double normalized(int frac_bits, int exp_bits, unsigned int hex_to_convert) {
    
}

double denormalized(int frac_bits, int exp_bits, unsigned int hex_to_convert) {

}

int main(int argc, char* argv[]) {
    int frac_bits, exp_bits, frac, exp;
    unsigned int hex_to_convert;
    int bias;
    double sign, M, V, E;
    int len;

    assert(argv[1] && argv[2] && argv[3]);
    len = strlen(argv[3]);
    for(int i = 0; i < len; i++)
        assert(isxdigit(argv[3][i]));

    sscanf(argv[1], "%8d", &frac_bits);
    sscanf(argv[2], "%8d", &exp_bits);
    sscanf(argv[3], "%8x", &hex_to_convert);

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
