#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "ffunc.h"


/* This function takes an array of single-precision floating point values,
 * and computes a sum in the order of the inputs.  Very simple.
 */
float fsum(FloatArray *floats) {
    float sum = 0;
    int i;

    for (i = 0; i < floats->count; i++)
        sum += floats->values[i];

    return sum;
}


/* FUNCTION: my_fsum (PARTIAL SUMMATION)

*WARNING: TAKES ~1 MINUTE TO RUN.
*WORKS, MUST WAIT.

* my_fsum takes a float array and sums the values using partial 
*summation.
*input: float array
*does not change global variables
*works by storing overflow and underflow errors in an array partials.
*returns a float sum value of the exact sum of the input list.
 */
float my_fsum(FloatArray *floats) {

    /*make list called partials and set all of my values in 
    *partials to 0
    */
    int size = floats->count + 1;
    FloatArray partials[size];
    partials->count = size;
    partials->values = malloc(sizeof(float)*partials->count);
    if (partials->values == NULL){
        fprintf(stderr, "Error: failed to allocate memory");
        exit(1);
    }

    for (int i =0; i  < partials->count; i++){
        partials->values[i] = 0;
    }

    /*
    *Creating local variables needed for the function
    *high, low, sum, x, y
    */
    float sum = 0.0;
    float x;
    float y;
    float high;
    float low;
    
    /*
    *Loop through all values in the input list of floats
    *For each float value in the input list, loop thorugh all 
    *of the values in partials (starts off with all 0s).
    *When there is nonzero overflow/underflow, we update the 
    *list of overflow/underflow values with the new overflow/underflow,
    *while saving the current sum of the value x of the input list float
    *in the list of partial remainders. 
    */
    for (int i = 0; i < floats->count; i++){
        int index = 0;
        x = floats->values[i];
        for (int j = 0; j < partials->count; j++){
            y = partials->values[j];

            if (abs(x) < abs(y)){
                float temp = x;
                x = y;
                y = temp;
            }

            high = x + y;
            low = y - (high - x);

            if (low != 0){
                partials->values[index] = low;
                index += 1;
            }
        
            x = high;
        }
        partials->values[index] = x;
        memset(partials->values+index + 1, 0, (partials->count-index-1) 
            * sizeof(float));
    }

    /*
    *Sum through all of the partials list, which will include the computed sum 
    *in addition to all of the overflow/underflow error values.
    */

    for (int i =0; i < partials->count; i++){
        sum += partials->values[i];
    }
   
    return sum;
}




/* FUNCTION: my_fsum2 (PAIRWISE SUMMATION)
* my_fsum2 takes a float array and sums the values using pairwise 
*summation.
*input: float array
*does not change global variables
*works by recursively splitting list of floats up into smaller chunks 
*of size 5 in order to reduce overflow/rounding errors. 
*returns a float sum value of the exact sum of the input list.
 */

float my_fsum2(FloatArray *floats) {
    float sum = 0;

    /*
    *The threshold value for the recursion is 5. When the size of the 
    *list gets broken down to 5, we simply add them in order because
    *recursion becomes less efficient at the small size.
    */
    if (floats->count <= 5){
        for (unsigned int i = 0; i < 5; i++){
            sum += floats->values[i];
        }
    }
    /*
    *If not yet the threshold, recursively split the list of floats
    *in half to 2 lists. 
    */
    else{
        int mid = (int)floor(floats->count / 2);
        FloatArray floatsLower[mid];
        floatsLower->count = mid;
        floatsLower->values = malloc(sizeof(float)*floatsLower->count);
        if (floatsLower->values == NULL){
            fprintf(stderr, "Error: failed to allocate memory");
            exit(1);
        }
        for (unsigned int i = 0; i < floatsLower->count; i++){
            floatsLower->values[i] = floats->values[i];
        }

        int upperSize = floats->count - mid;
        FloatArray floatsUpper [upperSize];
        floatsUpper->count = upperSize;
        floatsUpper->values = malloc(sizeof(float)*floatsUpper->count);
        if (floatsUpper->values == NULL){
            fprintf(stderr, "Error: failed to allocate memory");
            exit(1);
        }
        for (unsigned int i = 0; i < floatsUpper->count; i++){
            floatsUpper->values[i] = floats->values[mid + i];
        }
    /*
    *Call my_fsum2 on both lists, summing recursively
    *until the threshold is reaches and returns the sums of 5 elements.
    */
        sum = my_fsum2(floatsLower) + my_fsum2(floatsUpper);
    }
    return sum;

}



int main() {
    FloatArray floats;
    float sum1, sum2, sum3, my_sum1, my_sum2;

    load_floats(stdin, &floats);
    printf("Loaded %d floats from stdin.\n", floats.count);

    /* Compute a sum, in the order of input. */
    sum1 = fsum(&floats);

    /* Use my_fsum() to compute a sum of the values.  Ideally, your
     * summation function won't be affected by the order of the input floats.
     */

    /*
    *my_sum1 computes the sum using partial summation. my_sum2 computes the 
    *sum using pairwise summation.
    */

    my_sum1 = my_fsum(&floats);
    my_sum2 = my_fsum2(&floats);

    /* Compute a sum, in order of increasing magnitude. */
    sort_incmag(&floats);
    sum2 = fsum(&floats);

    /* Compute a sum, in order of decreasing magnitude. */
    sort_decmag(&floats);
    sum3 = fsum(&floats);

    /* %e prints the floating-point value in full precision,
     * using scientific notation.
     */
    printf("Sum computed in order of input:  %e\n", sum1);
    printf("Sum computed in order of increasing magnitude:  %e\n", sum2);
    printf("Sum computed in order of decreasing magnitude:  %e\n", sum3);


    printf("My sum with Partials:  %e\n", my_sum1);
    printf("My sum with Pairwise:  %e\n", my_sum2);
    

    return 0;
}

