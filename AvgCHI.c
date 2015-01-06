/*Implemented by Junyeon Julian Weon*/
/*Feature Selection with Avg.CHI 	*/
/*From 2015/01/02					*/
/* Til 2015/01/06					*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#pragma warning (disable:4996)

#define NUM_OF_FEATURE 68
#define NUM_OF_LABEL 174
#define SAMPLE_DATA_SIZE 500
#define NUM_OF_BIN 25
#define DEFAULT_DATA "dat.arff"

double** dataSet;
double chisqAvg[2][NUM_OF_FEATURE];
int intervalLabelFreq[NUM_OF_BIN][NUM_OF_LABEL];
int numOfData;

void initData(FILE* inputData);
void QuickSort(int front,int rear);
int partition(int front, int rear);
void RandomDataGen();
void CalcAvgChi();
void EqualWidthInterval(int arr[][2],int fIndex,int iIndex);
void ShowResult(int no);
void CalcChisq(int index, double chiTable[]);
double Mean(double Table[]);

int main(int argc, char* argv[]) {
	FILE* inputData;
	unsigned int howManyFeature;

	if(argc==1) {
		RandomDataGen();
		howManyFeature = 10;
		numOfData = SAMPLE_DATA_SIZE;
		//inputData = fopen(DEFAULT_DATA,"r");
	} else {
		initData(inputData);
		inputData = fopen(argv[1],"r");
		howManyFeature=atoi(argv[2]);
		//To be implemented...
	}
	CalcAvgChi();
	QuickSort(0,NUM_OF_FEATURE-1);
	ShowResult(howManyFeature);
	return 0;
}

void initData(FILE* inputData) {
	
}

int partition(int front, int rear) {
	int i,j;
	double pivot,temp,tempIndexVal;

	pivot = chisqAvg[0][front];
	i=front;
	j=rear+1;
	while(1) {
		do ++i;while(chisqAvg[0][i]>=pivot && i>=rear);
		do --j;while(chisqAvg[0][j]<pivot);
		if(i>=j)break;
		temp = chisqAvg[0][i];tempIndexVal = chisqAvg[1][i];
		chisqAvg[0][i]=chisqAvg[0][j];chisqAvg[1][i]=chisqAvg[1][j];
		chisqAvg[0][j]=temp;chisqAvg[1][j]=tempIndexVal;
	}
	temp = chisqAvg[0][front];tempIndexVal = chisqAvg[1][front];
	chisqAvg[0][front]=chisqAvg[0][j];chisqAvg[1][front]=chisqAvg[1][j];
	chisqAvg[0][j]=temp;chisqAvg[1][j]=tempIndexVal;
	return j;
}

void QuickSort(int front,int rear){
	int i;
	if(front<rear) {
		i=partition(front,rear);
		QuickSort(front,i-1);
		QuickSort(i+1,rear);
	}
}

void ShowResult(int no) {
	int i;
	for(i=0;i<no;i++) {
		printf("%.0f\n",chisqAvg[1][i]);
	}
}

void RandomDataGen() {
	int i,j;
	srand((unsigned)time(NULL));

	dataSet = (double**)malloc(sizeof(double*)*SAMPLE_DATA_SIZE);
	for(i=0;i<SAMPLE_DATA_SIZE;i++) {
		dataSet[i] = (double*)malloc(sizeof(double)*(NUM_OF_FEATURE+NUM_OF_LABEL));
		for(j=0;j<NUM_OF_FEATURE;j++) {
			dataSet[i][j] = (rand()%10000)/100;
		}
		for(j=NUM_OF_FEATURE;j<(NUM_OF_FEATURE+NUM_OF_LABEL);j++) {
			dataSet[i][j] = rand()%2;
		}
	}
}

void EqualWidthInterval(int arr[][2],int fIndex,int iIndex) {
	int i,j,quotient;
	double max,min,interval;

	max = min = dataSet[0][fIndex];
	for(i=1;i<numOfData;i++) {
		if(dataSet[i][fIndex]>max) max = dataSet[i][fIndex];
		if(dataSet[i][fIndex]<min) min = dataSet[i][fIndex];
	}
	interval = (max-min)/NUM_OF_BIN;

	for(i=0;i<NUM_OF_BIN;i++) {
		for(j=0;j<2;j++) {
			arr[i][j]=0;
		}
	}

	for(i=0;i<numOfData;i++) {
		quotient = (dataSet[i][fIndex]-min)/interval;
		if(!quotient) {
			if(dataSet[i][NUM_OF_FEATURE+iIndex])
				arr[0][0]++;
			else
				arr[0][1]++;
		} else if(quotient>24) {
			if(dataSet[i][NUM_OF_FEATURE+iIndex])
				arr[24][0]++;
			else
				arr[24][1]++;
		} else {
			if(dataSet[i][NUM_OF_FEATURE+iIndex])
				arr[quotient][0]++;
			else
				arr[quotient][1]++;
		}
	}
}


void CalcChisq(int index, double chiTable[]) {
	int i,j,k,p;
	int binList[NUM_OF_BIN][2];
	int sum,total,noC,noI;
	double chisq;
	double expectRate;

	for(i=0;i<NUM_OF_LABEL;i++) {
		chisq=0;
		EqualWidthInterval(binList,index,i);
		for(j=0;j<NUM_OF_BIN;j++) {
			for(k=0;k<2;k++) {
				noI=0;noC=0;total=0;
				for(p=0;p<2;p++) {
					noI+=binList[j][p];
				}
				for(p=0;p<NUM_OF_BIN;p++) {
					noC+=binList[p][k];
				}
				for(p=0;p<NUM_OF_BIN*2;p++) {
					total+=*(*(binList)+p);
					expectRate=noI*noC/total;
				}
				chisq += pow((binList[j][k]-expectRate),2.0)/expectRate;
			}
		}
		chiTable[i]=chisq;
	}
}

double Mean(double Table[]) {
	int i;
	double sum=0;

	for(i=0;i<NUM_OF_LABEL;i++)
		sum+=Table[i];
	return sum/NUM_OF_LABEL;
}

void CalcAvgChi() {
	int i;
	for(i=0;i<NUM_OF_FEATURE;i++) {
		double chiTable[NUM_OF_LABEL];
		CalcChisq(i,chiTable);
		chisqAvg[0][i] = Mean(chiTable);
		chisqAvg[1][i] = i;
	}
}