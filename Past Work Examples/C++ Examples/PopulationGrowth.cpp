/*
Name: Mark Brown
Date: 27/09/2015
Description: The program is designed to estimate the population growth 
for a country over a number of years.
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

//prototypes
double get_population();
double get_birth_rate();
double get_death_rate();
double get_years();
double get_growth_projection(double population,double birth_rate, double 
death_rate);



//main program
int main ()
{
	char repeat;
	do
	{	
		double population, birth_rate, death_rate, years;
		double projected_population;
		double final_projected_population;
		int count = 0;
		
		//below are the call functions
		population = get_population();
		birth_rate = get_birth_rate();
		death_rate = get_death_rate();
		years = get_years();
		
		//calulations for the projected_populations
		while (count < years)
		{
			projected_population = get_growth_projection(population, birth_rate, death_rate);
			population = projected_population;
			final_projected_population = projected_population;
			count++;
		}
		
		//output - rounding double numbers are included
		cout << setprecision(0) << fixed << "After " << years << " years, the population is projected to be " << final_projected_population << endl;
		//prompt to repeat program
		cout << "Another country (y/n)?";
		cin >> repeat;
	}while (repeat == 'y' || repeat == 'Y');
	return EXIT_SUCCESS;
}

//funtions
double get_population()
{
	double population;
	do{
		cout << "Enter the current population: ";
		cin >> population;
		if (population < 2)
			cout << "Population must be 2 or more" << endl;
	}while (population < 2);
	return population;
	
}

double get_birth_rate()
{
	double birth_rate;
	do{
		cout << "Enter the birth rate: ";
		cin >> birth_rate;
		if (birth_rate < 0 && birth_rate > 100) 
			cout << "Birth rate must be between 0 and 100" << endl;
	}while (birth_rate < 0 && birth_rate > 100);
	return birth_rate;
	
}

double get_death_rate()
{
	double death_rate;
	do{
		cout << "Enter the death rate: ";
		cin >> death_rate;
		if (death_rate < 0 && death_rate > 100)
			cout << "Death rate must be between 0 and 100." << endl;
	}while (death_rate < 0 && death_rate > 100);
	return death_rate;
	
}

double get_years()
{
	double years;
	do{
		cout << "How many years: ";
		cin >> years;
		if (years < 1)
			cout << "The number of year(s) must be 1 or greater." << endl;
	}while (years < 1);
	return years;
	
}

//the meat of the calculations
double get_growth_projection(double population, double birth_rate, 
double death_rate)
{
	double projected_population;
	double population_growth;
	
	population_growth = birth_rate - death_rate;
	projected_population = population + ((population_growth / 100) * population);
	return projected_population;
}
