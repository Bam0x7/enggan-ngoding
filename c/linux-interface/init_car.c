#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include "header/car.h"

car_t *construct_car(const char *name, int speed)
{
    car_t *car_init = (car_t *)malloc(sizeof(car_t));
    if(car_init == NULL){
        perror("construct_car()");
        exit(EXIT_FAILURE);
    }
    strncpy(car_init->name,name,strlen(name));
    car_init->speed = speed; 

    return car_init;
}

void accelerate_car(car_t *car)
{
    if(car->speed > 300){
        printf("mobil %s melaju sangat cepat\n" ,car->name);
        printf("kecepatan: %d\n" ,car->speed);
    }else if(car->speed <=200){
        printf("mobil %s melaju cukup cepat\n" ,car->name);
        printf("kecepatan: %d\n" ,car->speed);
    }else{
        printf("mobil %s melaju dengan lambat\n" ,car->name);
        printf("kecepatan: %d\n" ,car->speed);
    }
}

void print_car(car_t *car)
{
    if(car==NULL){
        puts("mobil belum di inisialisasi");
        exit(EXIT_FAILURE);
    }

    printf("nama mobil: %s\n" ,car->name);
    printf("kecepatan: %d\n" ,car->speed);
}

void destruct_car(car_t *car)
{
    if(car==NULL){
        puts("mobil belum di inisialisasi");
        exit(EXIT_FAILURE);
    }
    free(car);
}

