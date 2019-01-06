/*
Dustin Meckley
ciss420
a09.c
4/28/2016
/////////////////////////////////////////////////////////
CPU Type: Intel i7-3610QM
CPU Speed: 2.30GHz
CPU Cores: 4 
Output: Image File named a09_image attached of the 
program's execution.
/////////////////////////////////////////////////////////
*/

// Preprocessor Directives:
#include <stdio.h>
#include <omp.h>
#define MAX_THREADS 4

// Global Variable Declarations:
static long num_steps = 100000000;
double step;

// Function Prototypes:
int spacing(int);
void title_bar();
void title_heading();
void serial_pi();
void my_parallel_pi();
void final_parallel_pi();

// Main Program Function Block:
int main ()
{
	title_heading();
	serial_pi();
	my_parallel_pi();
	final_parallel_pi();
	return 0;
}

// Title Heading Program Function Block:
void title_heading()
{
	// Prints the 1st line of the title header:
	int i, counter;
	counter = 20;
	spacing(counter);
	printf("execution time (sec.) for threads:\n");

	// Prints the 2nd line of the title header:
	printf("code");
    counter -= 4;
    spacing(counter);
    i = 1; 
    while (i <= 4)
    {
    	int j = 0;
    	counter = 7;
      	printf("%d", i);
      	spacing(counter);
      	i++;
    }
    printf("\n");

    // Prints the 3rd line of the title header:
    title_bar();
    printf("\n");
}

// Spacing Program Function Block:
int spacing(int counter)
{
	// Prints the characters of spacing when needed:
	int i;
	for(i = 0; i < counter; i++)
	{
		printf(" ");
	}
	return counter;
}

// Title Bar Program Function Block:
void title_bar()
{
	// Prints the title bar underlining:
	int i;
	int counter = 54;
	for(i = 0; i < counter; i++)
	{
		printf("-");
	}
}

// Serial PI Program Function Block:
void serial_pi()
{
	// Local Variable Declaration:
	int i, j, counter;
	double x, pi, sum;
	double start_time, run_time;

	// Local Variable Initialization:
	sum = 0.0;
	step = 1.0 / (double) num_steps;
	start_time = omp_get_wtime();

	// Caluculating PI & Execution Time:
	for (i = 1;i <= num_steps; i++)
	{
		x = (i - 0.5) * step;
		sum = sum + 4.0 / (1.0 + x * x);
	}
	pi = step * sum;
	run_time = omp_get_wtime() - start_time;

	// Output Display:
	printf("serial");
	counter = 13;
	counter = spacing(counter);
	
    // Display the Official Execution Time:
	printf("%0.1f",run_time);

	// Display the Voided Threads:
	counter -= 7;
	counter = spacing(counter);
	printf("-");
    counter += 1;
    counter = spacing(counter);
    printf("-");
    counter = spacing(counter);
    printf("-");
    printf("\n");
}

// Parallel PI Program Function Block:
void my_parallel_pi()
{
	// Local Variable Declaration:
	int i, counter;
	double x, pi, sum;
	double start_time, run_time;

	// Local Variable Initialization:
	sum = 0.0;
	step = 1.0/(double) num_steps;

	// Output Display:
	printf("my_parallel");
	counter = 8;
	spacing(counter);
	
	// Caluculating PI & Execution Time:
	for (i = 1;i <= 4; i++)
	{
		sum = 0.0;
		omp_set_num_threads(i);
		start_time = omp_get_wtime();
		#pragma omp parallel  
		{
			#pragma omp for reduction(+:sum)
			for (i = 1; i <= num_steps; i++)
			{
				x = (i - 0.5) * step;
				sum = sum + 4.0 / (1.0 + x * x);
			}
		}
		pi = step * sum;
		run_time = omp_get_wtime() - start_time;

		// Display the Official Execution Times:
		printf("%0.1f", run_time);
		counter = 5;
		spacing(counter);
	}
	printf("\n");	  
}

// Parallel PI w/pragma omg critical
// Program Function Block:
void final_parallel_pi()
{
	// Local Variable Declaration:
	int i, j, counter;
	double pi, full_sum;
	double start_time, run_time;
	double sum[MAX_THREADS];

	// Local Variable Initialization:
	full_sum = 0.0;
	step = 1.0 / (double) num_steps;

	// Output Display:
	printf("final_parallel");
	counter = 5;
	spacing(counter);

	// Caluculating PI & Execution Time:
	for(j = 1; j <= MAX_THREADS; j++)
	{
		omp_set_num_threads(j);
		full_sum = 0.0;
		start_time = omp_get_wtime();
		#pragma omp parallel private(i)
		{
			int id = omp_get_thread_num();
			int numthreads = omp_get_num_threads();
			double x;

			double partial_sum = 0;

			for (i = id; i < num_steps; i += numthreads)
			{
				x = (i + 0.5) * step;
				partial_sum += + 4.0 / (1.0 + x * x);
			}
			#pragma omp critical
			full_sum += partial_sum;
		}
		pi = step * full_sum;
		run_time = omp_get_wtime() - start_time;

		// Display the Official Execution Times:
		printf("%0.1f", run_time);
		counter = 5;
		spacing(counter);
	}	
	printf("\n");  
}



