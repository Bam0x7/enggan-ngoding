#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "header/car.h"

int main()
{
   car_t *car = construct_car("supra GTX 800",400);
   accelerate_car(car);
   printf("\n");
   print_car(car);
   destruct_car(car);

   return 0;
}