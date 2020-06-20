///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file Serial Device Parameters
///-----------------------------------------------------------------------------

#pragma once

#include <utility>

namespace stm32g0xx
{
    ///
    /// Serial Device Data Width
    ///
    enum class DataWidth
    {
        EIGHT,  ///< eight bits data width
        NINE    ///< nine bits data width
    };

    ///
    /// Serial Device Stop Bits
    ///
    enum class StopBits
    {
        ONE,  ///< one stop bit
        TWO   ///< two stop bits
    };

    ///
    /// Serial Device Parity
    ///
    enum class Parity
    {
        NONE,  ///< No Parity
        ODD,   ///< Odd Parity
        EVEN   ///< Even Parity
    };

    ///
    /// Serial Device Parameter Definition
    ///
    struct SerialParams
    {
        std::size_t baud_rate;  ///< Baud Rate - from 9200 to 3Mb
        DataWidth data_width;   ///< Data Width, @see stm32f0xx::DataWidth
        StopBits stop_bits;     ///< Stop Bits, @see stm32f0xx::StopBits
        Parity parity;          ///< Parity, @see stm32f0xx::Parity
    };
}  // namespace stm32g0xx