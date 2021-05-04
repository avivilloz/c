#ifndef __FSQ_H__
#define __FSQ_H__

#include <stddef.h>

typedef struct fsq fsq_t;

fsq_t *FSQCreate(size_t capacity);

void FSQDestroy(fsq_t *fsq);

int FSQIsEmpty(fsq_t *fsq);

int FSQIsFull(fsq_t *fsq);

size_t FSQDequeue(fsq_t *fsq);

void FSQEnqueue(fsq_t *fsq, size_t data);

#endif /* __FSQ_H__ */
