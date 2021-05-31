///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file 'C' implementation of a Ring 'Q'
///-----------------------------------------------------------------------------

#include "beetree/platform/ring-q.h"

EXTERN_C_BEG

void ringq_init(uint8_t* buff, size_t len, RingQ_t* q)
{
    q->buff = buff;
    q->len = len;
    q->head = 0;
    q->count = 0;
};

uint8_t ringq_pop(RingQ_t* q)
{
    // get the value
    uint8_t value = q->buff[q->head];
    // pop it
    q->head = (q->head + 1) % q->len;
    q->count--;
    return value;
}
void ringq_push(RingQ_t* q, uint8_t byte)
{
    // store the value
    size_t idx = (q->head + q->count) % q->len;
    q->buff[idx] = byte;
    q->count++;
}

EXTERN_C_END