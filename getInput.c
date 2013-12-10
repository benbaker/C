#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x,y;
	int product;
	float quotient;
	
	printf("\nEnter a number: ");
	scanf("%d", &x);

	printf("Enter another number: ");
	scanf("%d", &y);

	product = x * y;
	printf("\nThe product of %d & %d is %d", x,y,product);
	
	quotient = (float) x / (float) y;
	printf("\nThe quotient of %d / %d is %lf\n\n",x,y,quotient);

}
