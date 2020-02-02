#ifndef HASHER_H
#define HASHER_H
#include <mhash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hasher_init(void);
void hasher_calculate(unsigned char byte);
void hasher_term(void);
unsigned char *hasher_hashget(unsigned char *s);
#endif


