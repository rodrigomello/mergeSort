/*
* Compile:  gcc -g -Wall -fopenmp -o mergesort.e mergesort.c
* Run:      ./mergesort.e 2 < test8.txt > output.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 

/* Serial Mergesort */
void sort(int *vector, int begin, int end){
    int m;
    int *B;
    int i;
    int j;
    int k;
    int inverso;
    B = (int*) malloc((end+1)* sizeof(int));
    if(end > begin ){
        m = (begin + end)/2;
        sort(vector,begin,m);
        sort(vector,m+1,end);
        for(i = begin; i <= m; i++){
            B[i] = vector[i];
        }
        for(j = m+1;j <= end;j++){
            inverso = end + m + 1 - j ;
            B[inverso] = vector[j];
        }    
        i = begin;
        j = end;
        for(k = begin; k <= end;k++){
            if(B[i] < B[j]){
                vector[k] = B[i];
                i++;                
            }else{
                vector[k] = B[j];
                j--;                       
            }                 
        }
    }       
    free(B);
}

/*Merge de dois vetores*/
int * merge(int * vector1, int size1, int * vector2, int size2){
    int * res;
    int i = 0;
    int j = 0;
    int k = 0;
    res = (int *) malloc((size1 + size2) * sizeof(int));
    while((i < size1) && (j < size2)){
        if(vector1[i] < vector2[j]){
            res[k] = vector1[i];
            i++;
            k++;
        }else{
            res[k] = vector2[j];
            j++;
            k++;
        }
    }
    while(i < size1){
        res[k] = vector1[i];
        i++;
        k++;
    }
    while(j < size2){
        res[k] = vector2[j];
        j++;
        k++;
    }
    return res;
}

void Hello(void) {
   	int my_rank = omp_get_thread_num();
   	int thread_count = omp_get_num_threads();
   	printf("Hello from thread %d of %d\n", my_rank, thread_count);
}

/*Main*/
int main(int argc, char* argv[]) {
	int thread_count = strtol(argv[1], NULL, 10);
   	double start, finish;
   	int i, j, k, n;
   	int *dataIn, *dataCopy;
   	scanf("%d", &i);
   	while(i > 0){
   		scanf("%d", &n);
   		dataIn = (int*) malloc( n * sizeof(int));
   		dataCopy = (int*) malloc( n * sizeof(int));
   		for(j = 0; j < n; j++){
      		scanf("%d", &dataIn[j]);
    	}
    	for(k = 0; k < i; k++){
    		for(j = 0; j < n; j++){
    			dataCopy[j] = dataIn[j];
    		}
    		start = omp_get_wtime();
    		//Início do Sort
    		/*
			for (thread = 0; thread < thread_count; thread++){  
        		pthread_create(&thread_handles[thread], NULL, ptsort, (void*) thread);  
      		}
    		*/
    		#pragma omp parallel num_threads(thread_count) 
	   			Hello();
    		//Fim do Sort
    		//Início do Merge
	   		/*
			for(x = thread_count/2; x > 0; x = x/2){
		        thread_count = x;
		        //Cria x threads de merge
		        for (thread = 0; thread < x; thread++){  
		          pthread_create(&thread_handles[thread], NULL, ptmerge, (void*) thread);  
		        } 
		        //Mata as threads
		        for (thread = 0; thread < x; thread++){ 
		          pthread_join(thread_handles[thread], NULL);
		        } 
		        if(x == 1){
		          break;
		        }
		    }
	   		*/
	   		#pragma omp parallel num_threads(thread_count) 
	   			Hello();
    		//Fim do Merge			
	   		finish = omp_get_wtime();
	   		for(j = 0; j < n; j++){
	   			printf("%d ", dataCopy[j]);
	   		}
	    	printf("\nElapsed time = %f seconds\n", finish - start);
    	}
    	free(dataIn);
    	free(dataCopy);
    	scanf("%d",&i);
   }
   return 0; 
}