/*
 * memory.c
 *
 * Handles all of the memory operations for the project.
 *
 *  Created on: Aug 29, 2017
 *      Author: msit ksr
 */

#include "memory.h"

/**
 * Allocates the requested amount of memory.
 *
 * Inputs: size - Number of bytes required.
 * Returns: Resulting pointer.
 */
void* allocate(size_t size) {
	void* ptr = NULL;
	ptr = calloc(1, size * sizeof(ptr));
	return ptr;
}

/**
 * Resizes the given pointer. Actually allocates a brand new pointer and copies.
 *
 * Inputs: ptr - The pointer.
 *		   old_size - The current size of the pointer in bytes.
 *		   new_size - The required size in bytes.
 * Outputs: New pointer.
 */
void* resize(void* ptr, size_t old_size, size_t new_size) {
	void *new_ptr = calloc(1, new_size * sizeof(ptr));
	memcpy(new_ptr, ptr, old_size * sizeof(ptr));
	free(ptr);
	return new_ptr;
}

void deallocate(void *ptr) {
	if(ptr != NULL) {
		free(ptr);
		ptr = NULL;
	}
}
