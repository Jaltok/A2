/*********************************************
 *  Jeff Lund
 *  Systems A2: Floating point parser
 *  *****************************************/
// notes: bias = 2^(k-1)-1 k is exp bits


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


int main(int argc, char* argv[]) {
    short unsigned int frac_bits, exp_bits;// , isolated_exp, isolated_frac, isolated_sign;
    unsigned int hex_to_convert;
    short unsigned int frac = 0; //isolated frac, n
    short unsigned int exp = 0; //isolated exp, k
//    double M, V;
	assert(argv[1] && argv[2] && argv[3]);
    sscanf(argv[1], "%hu", &frac_bits);
    sscanf(argv[2], "%hu", &exp_bits);
    sscanf(argv[3], "%x", &hex_to_convert);
    
    frac = hex_to_convert&((1<<frac_bits)-1);
    exp = (hex_to_convert>>frac_bits)&((1<<exp_bits)-1);
    printf("frac: %x | exp: %x\n", frac, exp);
    //denormalized
	if(exp == 0) {
		printf("denormalized\n");
	}	
	//Inf or Nan
	else if(!exp == 0) { //this is not right, always NaN
		if(frac == 0) { //infinite
			if((hex_to_convert>>(frac_bits+exp_bits))&1) //neg inf
				printf("-inf\n");
			else //pos inf
				printf("+inf\n");
		}
		else //NaN
			printf("NaN\n");
	}
	//Normalized
	else {
		printf("normalized\n");
	}

    return 0;
}
