/*
Isaiah Larsen
CS3060-601 Fall 2018
#3
I promise that this source code file has, in its entirety,
been written by myself and by no other person or persons.
If at any time an exact copy of this source code is found
to be used by another person in this term, I understand
that both myself and the student that submitted the
copy will recieve a zero on this assignment.

*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXSIZE (99)

struct data_t{
	int nums[MAXSIZE];
	int count;
};

void * thread_func(void *p){
	struct data_t *pd = (struct data_t *)p;
	int i = 0;
	int sum;
	int* answers = malloc(pd->count * sizeof(int));
	printf("Received data starting process...\n");
	for(int k = 0; k < pd->count; k+=3){
		sum = pd->nums[k] * pd->nums[k+1] * pd->nums[k+2];
		answers[i] = sum;
		i++;
	}
	printf("Calculations complete returning answers...\n");
	return answers;
}

int main(int argc, char *argv[]){
	pthread_t thandle;
	struct data_t d;
	int i = 0;
	d.count = 0;
	FILE *fptr = stdin;
	printf("Isaiah Larsen Assn 3\n");

	//Check num of args
	if(argc > 1){//file was given
		fptr = fopen(argv[1], "r");
		//Check for file open issues
		if(fptr == NULL){
			perror("Problem opening file.");
			return -1;
		}else{
			while(fscanf(fptr, "%d%d%d", &d.nums[i],&d.nums[i+1],&d.nums[i+2]) == 3){
				printf("Main thread read  %d %d %d \n", d.nums[i],d.nums[i+1],d.nums[i+2]);
				i+=3;
				d.count += 3;
			}
			printf("Passing input to another thread...\n");
			pthread_create(&thandle, NULL, thread_func, &d);
		}
	}else{//read from stdin
		while(scanf("%d%d%d", &d.nums[i],&d.nums[i+1],&d.nums[i+2]) == 3){
			printf("Main thread read  %d %d %d\n", d.nums[i],d.nums[i+1],d.nums[i+2]);
			i+=3;
			d.count += 3;
		}
		printf("Passing input to another thread...\n");
		pthread_create(&thandle, NULL, thread_func, &d);
	}
	void *retptr;
	pthread_join(thandle, &retptr);//like wait
	int *st = (int *)retptr;
	int ite = 0;
	printf("Results from thread 2 are in ....\n");
	for(int i = 0; i < (d.count/3); i++){
		printf("The result of %d * %d * %d = %d\n",d.nums[ite], d.nums[ite +1],d.nums[ite+2], st[i]);
		ite += 3;
	}
	//if you allocate, free up
	free(retptr);

	return 0;

}
