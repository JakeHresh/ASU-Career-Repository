/**
* Calculates the total volume of a collection of cylinders.
* The number of cylinders is specified by the user.
* The dimensions of each cylinder are specified by the user.
* Completion time: 3 hours across all 3 programs
*
* @author Jacob Hreshchyshyn, Professor Acuna
* @version 8/31/2020 at 8:30 AM
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>

int main(void)
{
    int numCylinders;
    float volumeSum = 0;
	//Add a prompt for the number of cylinders to sum. Make sure to use the control
	//symbol for integers. [2 points]
    printf("How many cylinders would you like to sum?\n");
    scanf("%d", &numCylinders);
	//Create a loop based on the number of cylinders the user enters. [2 points]
    for(numCylinders; numCylinders > 0; numCylinders--)
    {
        //    Within the loop, prompt for height and radius parameters (allow floating
        //    point numbers), and calculate the volume for that particular cylinder.
        //    [4 points]
        float height;
        float radius;
        float volumePart;
        printf("What is the height of the cylinder?\n");
        scanf("%f", &height);
        printf("What is the radius of the cylinder?\n");
        scanf("%f", &radius);
        volumePart = 3.14159265359 * (radius * radius) * height;
        volumeSum += volumePart;
    }
	//Display the total volume sum back to the user. Make sure to use the right control
	//symbol. [2 points]
    printf("The total volume of the cylinders is %f.", volumeSum);
	return 0;
}
