#ifndef POINT_H
#define POINT_H

typedef struct Point {
        mpz_t x;
        mpz_t y;
} point_t;

void point_init(point_t point);
point_t set_point(char* x_char, char* y_char);

#endif
