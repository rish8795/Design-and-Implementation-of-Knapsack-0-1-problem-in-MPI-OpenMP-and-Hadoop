
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include <time.h>
#include <sys/times.h>
#include <sys/time.h>

#define N 10000
#define CAPACITY_MAX 10000
#define VALUE_MAX 100

int n; // number of items
int knapsack_capacity; // total weight
int weight[N]; // weight of items
int value[N]; // values of items
int knapsack[N+1][CAPACITY_MAX]; 
int seed;

void inputs(int argc, char *argv[]);
void outputs();

int main(int argc,char *argv[]) {
	int i, j;

	/* Timing variables */
  	struct timeval etstart, etstop;  /* Elapsed times using gettimeofday() */
	struct timezone tzdummy;
	unsigned long long usecstart, usecstop;

	inputs(argc, argv);

	printf("\nStarting clock.\n");
	gettimeofday(&etstart, &tzdummy);

	for( i=0; i<=n; i++ ){
		for( j=0; j<knapsack_capacity; j++ ) {

			if( i==0 || j==0 ){
				knapsack[i][j]= 0;

			} else if( weight[i-1] <= j ){

				int one = value[i-1] + knapsack[i-1][j-weight[i-1]];
				int two = knapsack[i-1][j];

				if(one > two) {
					knapsack[i][j] = one;
				} else {
					knapsack[i][j] = two;
				}          
			} else {
				knapsack[i][j] = knapsack[i-1][j];
			}

		}

	}


/* Stop Clock */
	gettimeofday(&etstop, &tzdummy);
	printf("Stopped clock.\n");
	usecstart = (unsigned long long)etstart.tv_sec * 1000000 + etstart.tv_usec;
	usecstop = (unsigned long long)etstop.tv_sec * 1000000 + etstop.tv_usec;


	outputs();

	printf("\nElapsed time = %g ms.\n",
		(float)(usecstop - usecstart)/(float)1000);

	
	
	
	return 0;
}


void inputs(int argc, char *argv[]){
	int i;

	if(argc != 4){
		printf("Error: knapsack <max capacity weight> <number of items> <seed>\n");
		exit(0);
	}

	knapsack_capacity = atoi(argv[1])+1;
	n  = atoi(argv[2]);
	seed = atoi(argv[3]);

	srandom(seed);

	//printf("Items :\n");

	for(int i=0;i<n;i++){
		value[i]=random()%VALUE_MAX;
		weight[i]=random()%(knapsack_capacity-1)+1;
		//printf("\tItem %d: value = %d / Weight = %d\n", i, value[i], weight[i]);
	}
}

void outputs(){
	int i, j;

	printf("\n\nResults:\n");
	printf("\tKnapsack max weight: %d / Number of items: %d\n", knapsack_capacity-1, n);
	printf("\tBest value: %d \n", knapsack[n][knapsack_capacity-1]);
	printf("\tItems taken: ");

	i = n;
	j = knapsack_capacity-1;
	while(i > 0 && j>0){
		if( knapsack[i][j] == knapsack[i-1][j] ) {
			i--;
		} else {
			printf("%d, ", i-1);
			j-=weight[i-1];
			i--;
		}
	}

	printf("\n\n");


}
