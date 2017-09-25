/*
 * memory.h
 *
 *  Created on: Aug 29, 2017
 *      Author: msit ksr
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdlib.h>
#include <string.h>

void* allocate(size_t size);
void* resize(void* ptr, size_t old_size, size_t new_size);
void deallocate(void *ptr);

#endif /* MEMORY_H_ */
