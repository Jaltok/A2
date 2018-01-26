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
    short unsigned int n =0; //isolated frac
    short unsigned int k = 0; //isolated exp
    assert(argv[1] && argv[2] && argv[3]);
    sscanf(argv[1], "%hu", &frac_bits);
    sscanf(argv[2], "%hu", &exp_bits);
    sscanf(argv[3], "%x", &hex_to_convert);
    
    n = hex_to_convert&((1<<frac_bits)-1);
    k = (hex_to_convert>>frac_bits)&((1<<exp_bits)-1);
    printf("n: %x | k: %x\n", n, k);
    /*switch() {
        case  
    }*/

    return 0;
}
