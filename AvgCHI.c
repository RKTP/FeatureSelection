/*Implemented by Junyeon Julian Weon*/
/*Feature Selection with Avg.CHI 	*/
/*From 2015/01/02					*/
/* Til 2015/01/00					*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_statistics.h>
#include <time.h>

#define NUM_OF_FEATURE 68
#define NUM_OF_LABEL 174
#define SAMPLE_DATA_SIZE 500
#define NUM_OF_BIN 25
#define DEFAULT_DATA "dat.arff"

double** dataSet;
double chisq[NUM_OF_FEATURE][NUM_OF_LABEL]={{0.0,},};
double chisqAvg[2][NUM_OF_FEATURE];
int sizeOfData;

void QuickSort();
void RandomDataGen();//DONE
void CalcChisq(int);
void CalcAvgChi();
void EqualWidthInterval();

int main(int argc, char* argv[]) {
	FILE* inputData;
	unsigned int howManyFeature;

	if(argc==1) {
		RandomDataGen();
		howManyFeature = 10;
		sizeOfData = SAMPLE_DATA_SIZE;
		//inputData = fopen(DEFAULT_DATA,"r");
	} else {
		inputData = fopen(argv[1],"r");
		howManyFeature=atoi(argv[2]);
		//To be implemented...
	}

}

void QuickSort(){
	//To be implemented...
}

void RandomDataGen() {
	int i,j;
	srand((unsigned)time(NULL));

	dataSet = (double**)malloc(sizeof(double*)*SAMPLE_DATA_SIZE);
	for(i=0;i<SAMPLE_DATA_SIZE;i++) {
		dataSet[i] = (double*)malloc(sizeof(double)*(NUM_OF_FEATURE+NUM_OF_LABEL));
		for(j=0;i<NUM_OF_FEATURE;i++) {
			dataSet[i][j] = (rand()%10000)/100;
		}
		for(j=NUM_OF_FEATURE;j<(NUM_OF_FEATURE+NUM_OF_LABEL);j++) {
			dataSet[i][j] = rand()%2;
		}
	}
}

void CalcChisq(int index) {
	//To be implemented...
}

void EqualWidthInterval() {

}

void CalcAvgChi() {
	int i;
	for(i=0;i<NUM_OF_FEATURE;i++) {
		CalcChisq(i);
	}
}