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
#include "platform-library/extern-c.h"

EXTERN_C_BEG

///
/// Ring 'Q' context
///
typedef struct ___RingQ
{
    uint8_t* buff;  ///< the buffer the context points to.
    size_t head;    ///< current head of the Q, i.e. the oldest element
    size_t len;     ///< the length of the buffer `buff`, i.e. the capacity
    size_t count;   ///< current number of elements in the Q
} RingQ_t;

///
/// Initialize the Ring 'Q' with the given buffer
///
/// @param buff the buffer the 'Q' will point to
/// @param len the length of the buffer, i.e. it's capacity
/// @param q the ring 'Q' context.
///
void ringq_init(uint8_t* buff, size_t len, RingQ_t* q);

///
/// Pop the oldest element from the ring Q and return its value.
///
/// @note
/// Invoking `ringq_pop()` is undefined when the Q contains 0 elements. It is
/// the responsibility of the caller to check the size of the Q before invoking.
///
/// @param q the ring 'Q' context
/// @return uint8_t the value of the popped element from the ring Q
///
uint8_t ringq_pop(RingQ_t* q);

///
/// Push the given `byte` onto the ring queue.
///
/// @note
/// Invoking `ringq_push()` is undefined when the number of elementes in the Q
/// is greater than or equal to it's capacity. It is the responsibility of the
/// caller to check the size of the Q against it's capacity before invoking.
///
/// @param q    the ring 'Q' context
/// @param byte the value to push onto the ring 'Q'
///
void ringq_push(RingQ_t* q, uint8_t byte);

///
/// @param q the ring 'Q' context
/// @return the number of elements currently in the ring 'Q'
///
inline size_t ringq_count(const RingQ_t* q) { return q->count; }

///
/// @param q  the ring Q context
/// @return the ring Q's capacity, i.e. the size of the underlying buffer
///
inline size_t ringq_capacity(const RingQ_t* q) { return q->len; }

EXTERN_C_END