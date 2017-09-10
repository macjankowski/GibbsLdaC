//
//  main.c
//  GibbsLdaC
//
//  Created by Maciej Jankowski on 10.09.2017.
//  Copyright © 2017 Maciej Jankowski. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>



int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(r,1000);
    
    int arr[] = {
        1,2,9,
        3,58,21,
        4, 6, 123};
    
    (*(arr+1*3+1))--;
    
    
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%d\t",*((arr+i*3) + j));
        }
        printf("\n");
    }
    
    double p[] = {0.3, 0.2, 0.1, 0.4};
    
    gsl_ran_discrete_t * prob = gsl_ran_discrete_preproc(4, p);
    
    for(int i=0; i<10; i++){
        printf("Hello, World %lu\n", gsl_ran_discrete(r, prob));
    }
    return 0;
}
