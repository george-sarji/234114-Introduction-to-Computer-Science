#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXIMAL_AIRLINES 10
#define DEST 6
#define DIM 2

char *destinations[] = {"Miami", "Rio", "Moscow", "Shanghai", "Barcelona", "Melbourne"};

int fillPricesTable(double flightsPrices[][DEST], int n, double *dollarRate);

void compute(double flightsPrices[][DEST], int length,
			 double *max, double *min, int *bestAirLine);

void bestPrice(double flightsPrices[][DEST], int length,
			   double bestPrices[DEST][DIM], double dollarRate);

void printBestPrices(double bestPrices[DEST][DIM]);

void printMinMaxAvg(double max, double min, int bestAirLine);

void errorPrice(int row);

void errorDollar();

int main()
{
	int num_of_airlines = 0, bestAirLine = 0;
	double prices[MAXIMAL_AIRLINES][DEST];
	double max = 0, min = 0, dollarRate = 0;
	double bestPrices[DEST][DIM];

	num_of_airlines = fillPricesTable(prices, MAXIMAL_AIRLINES, &dollarRate);
	compute(prices, num_of_airlines, &max, &min, &bestAirLine);
	printMinMaxAvg(max, min, bestAirLine);
	bestPrice(prices, num_of_airlines, bestPrices, dollarRate);
	printBestPrices(bestPrices);

	return 0;
}

void printBestPrices(double bestPrices[DEST][DIM])
{
	for (int i = 0; i < DEST; i++)
	{
		printf("Best offer for %s is ", destinations[i]);
		printf("Airline # %d price: %.2f shekels\n", (int)(bestPrices[i][0]), bestPrices[i][1]);
	}
}

void printMinMaxAvg(double max, double min, int bestAirLine)
{
	printf("Maximal price: %.2f\nMinimal price: %.2f\nBest Airline: %d\n", max, min, bestAirLine);
}

void errorPrice(int row)
{
	printf("ERROR: invalid price in airline # %d\n", row);
}

void errorDollar()
{
	printf("ERROR: invalid dollar rate, try again!\n");
}

int fillPricesTable(double flightsPrices[][DEST], int n, double *dollarRate)
{
	bool is_EOF = false;
	int price_error_index = -1, current_airline;
	// Scan for the dollar rate and make sure it is a legal input.
	while (scanf("%lf", dollarRate) && *dollarRate <= 0)
	{
		// Illegal dollar rate.
		errorDollar();
	}

	// Begin receiving the airline information for each flight.
	// Each airline will have a specific line for it to input.
	for (current_airline = 0; current_airline <= n && !is_EOF; current_airline++)
	{
		for (int current_dest = 0; current_dest < DEST; current_dest++)
		{
			// Scan.
			if (scanf("%lf", &flightsPrices[current_airline][current_dest]) == EOF)
			{
				is_EOF = true;
				break;
			}
			else if (flightsPrices[current_airline][current_dest] <= 0 && price_error_index == -1)
			{
				// Provide error
				price_error_index = current_airline;
			}
		}
	}

	// Provide the logic to check whether everything is valid.
	if (price_error_index != -1)
	{
		// Price error.
		errorPrice(price_error_index);
		return -1;
	}
	return current_airline - 1;
}

void compute(double flightsPrices[][DEST], int length, double *max, double *min, int *bestAirLine)
{
	if (length <= 0)
		exit(-1);

	// Initiate the pointers
	double best_average = 0, current_average = 0;
	*min = flightsPrices[0][0], *max = flightsPrices[0][0];
	for (int airline = 0; airline < length; airline++)
	{
		current_average = 0;
		for (int current = 0; current < DEST; current++)
		{
			// Check if max
			double *currentPrice = &flightsPrices[airline][current];
			if (*currentPrice > *max)
				*max = *currentPrice;
			if (*currentPrice < *min)
				*min = *currentPrice;

			current_average += *currentPrice;
		}

		current_average /= DEST;
		if (airline == 0 || current_average < best_average)
		{
			*bestAirLine = airline;
			best_average = current_average;
		}
	}
}

void bestPrice(double flightsPrices[][DEST], int length, double bestPrices[DEST][DIM], double dollarRate)
{
	for (int current = 0; current < DEST; current++)
	{
		bestPrices[current][0] = 0;
		bestPrices[current][1] = flightsPrices[0][current] * dollarRate;
		for (int airline = 0; airline < length; airline++)
		{
			double currentValue = flightsPrices[airline][current] * dollarRate;
			// printf("Current value: %lf\n", currentValue);
			// printf("Airline: %d, current col: %d\n", airline, current);
			if (currentValue < bestPrices[current][1])
			{
				bestPrices[current][0] = airline;
				bestPrices[current][1] = currentValue;
			}
		}
	}
}