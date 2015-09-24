#include <stdio.h>

int main(){
	double weight;
	printf("Please enter the weight you'd like to convert:");
	scanf("%lf", &weight);
	printf("Here is your weight on other planets:\n");
	printf("Mercury 	%lf lbs\n", weight*0.38);
	printf("Venus           %lf lbs\n", weight*0.91);
	printf("Mars            %lf lbs\n", weight*0.38);
	printf("Jupiter         %lf lbs\n", weight*2.54);
	printf("Saturn          %lf lbs\n", weight*1.08);
	printf("Uranus          %lf lbs\n", weight*0.91);
	printf("Neptune         %lf lbs\n", weight*1.19);
	return 0;
}






