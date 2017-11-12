#ifndef _Stdlib
#include <stdlib.h>
#define _Stdlib
#endif

#define uchar unsigned char

#define null NULL

unsigned int getStringLength(const char *c){
	unsigned int i = 0;

	while(c[i] != '\0'){
		i++;
	}

	return i;
}

unsigned int rand_between(unsigned int min, unsigned int max){
	return (rand() % (max+1 - min)+min );
}
