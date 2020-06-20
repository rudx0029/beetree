///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file Extern 'C' macros for use with cpp compilers
///-----------------------------------------------------------------------------

#pragma once

#if defined(__cplusplus)
#define EXTERN_C extern "C"
#define EXTERN_C_BEG \
    extern "C"       \
    {
#define EXTERN_C_END }
#else
#define EXTERN_C
#define EXTERN_C_BEG
#define EXTERN_C_END
#endif