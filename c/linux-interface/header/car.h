#ifndef CAR_H
#define CAR_H

typedef struct{
    char name[512];
    int speed;
}car_t;

car_t *construct_car(const char *name, int speed);
void accelerate_car(car_t *car);
void destruct_car(car_t *car);
void print_car(car_t *car);
#endif