//
//  gibbs.c
//  GibbsLdaC
//
//  Created by Maciej Jankowski on 10.09.2017.
//  Copyright © 2017 Maciej Jankowski. All rights reserved.
//

#include "gibbs.h"
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

void singleRow(
               int doc,
               int row[],
               int hiddenRow[],
               int rowLength,
               int *wt,
               int wtRows,
               int wtColumns,
               int *dt,
               int dtRows,
               int dtColumns,
               int *wtSum,
               int dtSum,
               double alpha,
               double beta,
               int K,
               int V,
               int M){
    
    gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(r,1000);

    
    for(int i=0; i<dtColumns; i++){
        int word = row[i];
        int currentTopic = hiddenRow[i];
        
        (*((wt+word*wtColumns) + currentTopic))--; // wt[word][currentTopic]--;
        (*(wtSum+currentTopic))--;
        
        (*((dt+doc*dtColumns) + currentTopic))--;  // dt[doc][currentTopic]--;
        dtSum--;
        // dtSum doesn't change. We take from one column and add to the other, so sum for current row is the same.
        
        double prob[K];
        
        for(int k=0; k<K; k++){
            prob[k] = ((*((wt+word*wtColumns) + k) + beta)/(*(wtSum+k)+V*beta)) * ((*((dt+doc*dtColumns) + k) + alpha)/(dtSum + K*alpha));
        }
        
        gsl_ran_discrete_t * normalized = gsl_ran_discrete_preproc(K, prob);
        size_t newTopic = gsl_ran_discrete(r, normalized);
        
        (*((wt+word*wtColumns) + newTopic))++;
        (*(wtSum+newTopic))++;
        
        (*((dt+doc*dtColumns) + newTopic))++;
        dtSum++;
    }
}
