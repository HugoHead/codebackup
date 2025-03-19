#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double percise_sum(double* arr, int start, int stop) {
	double sum = 0.0;
	double c = 0.0;
	for (int i = start; i <= stop; i++) {
		double y = arr[i] - c;
		double t = sum + y;
		c = (t-sum) - y;
		sum = t;
	}
	return sum;
}

int main (int argc, char** argv) {
	if (argc != 3) {
		printf("Usage: DailyStats <mode> <unit>\n");
		return 0;
	}

	int mode = atoi(argv[1]);
	char* unit = argv[2];

	if (mode != 0 && mode != 1) {
		printf("ERROR: invalid mode!\n");
		return 0;
	}


	//allocate just enough memory, starting with just one unit
	int n = 0;
	double* data = (double*)malloc(sizeof(double));

	if (data == NULL) {
		printf("Memory allocation failure!\n");
		return 0;
	}

	//a temp value to hold inputs as we process them into the array one by one
	double value = 0.0;

	//loop through the inputs one by one and process them, allocating new memory as needed
	while(scanf("%lf", &value) == 1) {
		double* temp = (double*)realloc(data, (n+1) *sizeof(double));		

		if (temp == NULL) {
			printf("Memory allocation failure!\n");
			free(data);
			return 0;
		}

		data = temp;
		data[n] = value;
		n++;
	}

	if (n < 24 ) {
		printf("ERROR: insufficient data!\n");
		free(data);
		return 0;
	}

	//find out how many full days there are using integer division
	int days = n/24;

	//allocate memory to store the dates of the min/max
	int minDayNo = 0, maxDayNo = 0;

	//allocate memory to store the values of the min/max
	double min=100000.0, max=0.0;

	//to store the running total
	double total = 0.0;

	//for each day
	for (int i = 0; i < days; i++) {

		//find total of the hour data for the day
		total = percise_sum(data, i*24, (i+1)*24-1);

		//take the average if average mode is set
		if (mode == 1) {total /= 24.0;}

		total = round(total * 100.0) / 100.0; // Fix: Apply rounding immediately

		//update min/max data
		if (total < min) { min = total; minDayNo = i+1; }
		if (total > max) { max = total; maxDayNo = i+1; }

		//print the line for the day
		printf("Day %d: %.2f %s\n", i+1, total, unit);

	}

	//print min/max
	printf("Min day %d: %.2f %s\n", minDayNo, min, unit);
	printf("Max day %d: %.2f %s\n", maxDayNo, max, unit);

	free(data);
	return 0;
}
