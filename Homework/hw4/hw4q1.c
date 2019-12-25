#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXIMAL_AIRLINES 10
#define DEST 6
#define DIM 2


char* destinations[]={"Miami", "Rio", "Moscow", "Shanghai", "Barcelona", "Melbourne"};

int fillPricesTable(double flightsPrices[][DEST],int n,double* dollarRate);

void compute(double flightsPrices[][DEST],int length,
				double* max,double* min,int* bestAirLine);

void bestPrice(double flightsPrices[][DEST],int length,
		double bestPrices[DEST][DIM],double dollarRate);

void printBestPrices(double bestPrices[DEST][DIM]);

void printMinMaxAvg(double max, double min, int bestAirLine);

void errorPrice(int row);

void errorDollar();


int main()
{
	int num_of_airlines=0, bestAirLine=0;
	double prices[MAXIMAL_AIRLINES][DEST];
    double max=0, min=0, dollarRate=0;
	double bestPrices[DEST][DIM];

    num_of_airlines = fillPricesTable(prices, MAXIMAL_AIRLINES, &dollarRate);
	compute(prices, num_of_airlines, &max, &min, &bestAirLine);
    printMinMaxAvg(max, min, bestAirLine);
	bestPrice(prices, num_of_airlines, bestPrices, dollarRate);
	printBestPrices(bestPrices);


    return 0;
}




void printBestPrices(double bestPrices[DEST][DIM]){
		for(int i=0; i<DEST; i++){
		printf("Best offer for %s is ", destinations[i]);
		printf("Airline # %d price: %.2f shekels\n", (int)(bestPrices[i][0]), bestPrices[i][1]);
	}
}

void printMinMaxAvg(double max, double min, int bestAirLine){
    printf("Maximal price: %.2f\nMinimal price: %.2f\nBest Airline: %d\n", max, min, bestAirLine);

}

void errorPrice(int row){
	printf("ERROR: invalid price in airline # %d\n", row);
}

void errorDollar(){
	printf("ERROR: invalid dollar rate, try again!\n");
}
