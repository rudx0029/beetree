///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file 'C' implementation of a simple ring 'Q'. User of the ring 'Q' must be
/// knowledgeable with its shortcomings, i.e. it is not inherently robust.
///-----------------------------------------------------------------------------

#pragma once

#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

///
/// Ring 'Q' context
///
typedef struct bte_ringq
{
    uint8_t* buff;  ///< the buffer the context points to.
    size_t head;    ///< current head of the Q, i.e. the oldest element
    size_t len;     ///< the length of the buffer `buff`, i.e. the capacity
    size_t count;   ///< current number of elements in the Q
} bte_ringq_t;

///
/// Initialize the Ring 'Q' with the given buffer
///
/// @param buff the buffer the 'Q' will point to
/// @param len the length of the buffer, i.e. it's capacity
/// @param q the ring 'Q' context.
///
inline void bte_ringq_init(uint8_t* buff, size_t len, bte_ringq_t* q)
{
    q->buff = buff;
    q->len = len;
    q->head = 0;
    q->count = 0;
};

///
/// Pop the oldest element from the ring Q and return its value.
///
/// @note
/// Invoking `bte_ringq_pop()` is undefined when the Q contains 0 elements. It is
/// the responsibility of the caller to check the size of the Q before invoking.
///
/// @param q the ring 'Q' context
/// @return uint8_t the value of the popped element from the ring Q
///
inline uint8_t bte_ringq_pop(bte_ringq_t* q)
{
    // get the value
    uint8_t value = q->buff[q->head];
    // pop it
    q->head = (q->head + 1) % q->len;
    q->count--;
    return value;
}

///
/// Push the given `byte` onto the ring queue.
///
/// @note
/// Invoking `bte_ringq_push()` is undefined when the number of elements in the Q
/// is greater than or equal to it's capacity. It is the responsibility of the
/// caller to check the size of the Q against it's capacity before invoking.
///
/// @param q    the ring 'Q' context
/// @param byte the value to push onto the ring 'Q'
///
inline void bte_ringq_push(bte_ringq_t* q, uint8_t byte)
{
    // store the value
    size_t idx = (q->head + q->count) % q->len;
    q->buff[idx] = byte;
    q->count++;
}

///
/// @param q the ring 'Q' context
/// @return the number of elements currently in the ring 'Q'
///
inline size_t bte_ringq_count(const bte_ringq_t* q) { return q->count; }

///
/// @param q  the ring Q context
/// @return the ring Q's capacity, i.e. the size of the underlying buffer
///
inline size_t bte_ringq_capacity(const bte_ringq_t* q) { return q->len; }

#if defined(__cplusplus)
} // extern "C"
#endif