#include <stdio.h>


int count_onebits(unsigned int n);


int main(int argc, char **argv) {
    int i, res;
    unsigned int n;

    printf("TESTING COUNT ONE BITS\n");
    int c1 = count_onebits(16);
    printf("16 = %d", c1);
    int c2 = count_onebits(100);
    int c3 = count_onebits(2);
    int c4 = count_onebits(45);
    int c5 = count_onebits(0);
    printf("\n15= %d, 100 = %d, 2 = %d, 45 =  %d, 0 = %d \n" , c1, c2, c3, c4, c5);

    if (argc == 1) {
        printf("usage:  %s N1 [N2 ...]\n\n", argv[0]);
        printf("\tN1, N2, ... are positive integers\n\n");
        printf("\tFor each argument, the program prints out the number of\n"
               "\tbits that are 1 in the number.\n\n");
        return 1;
    }
    


    for (i = 1; i < argc; i++) {
        res = sscanf(argv[i], "%u", &n);
        if (res == 1)
            printf("Input:  %u\tOne-bits:  %u\n\n", n, count_onebits(n));
        else
            printf("Unparseable input \"%s\".  Skipping.\n\n", argv[i]);
    }
   
    return 0;
}

/*
*ONE BITS
 * Given an unsigned integer n, this function returns the number of bits in n
 * that are 1.
 */
int count_onebits(unsigned int n) {

    int count = 0;
    /*
    *If the rightmost bit is a 1, increment counter. Rightshift by one bit.
    *return counter value.
    */
    while (n != 0){
        if (n & 1){
            count++;
        }
        n = n >> 1;
    }

    return count;
}

