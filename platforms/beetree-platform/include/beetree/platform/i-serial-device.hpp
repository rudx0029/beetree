///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file UART Virtual Com Port interface for beetree platform
///-----------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <utility>
#include "beetree/platform/i-system-clock.hpp"

namespace bte {
///
/// Serial Device Interface
///
/// Provides a common serial interface for the application decoupling it from
/// the hardware interfaces, e.g. USART, UART, I2C, SPI, etc.
///
class ISerialDevice
{
public:
    ISerialDevice()          = default;
    virtual ~ISerialDevice() = default;
    ///
    /// Writes the data buffer to the serial device.
    ///
    /// @param address      address of the recepient or 0 if not supported
    /// @param data         the buffer containing the data to transmit
    /// @param len          the length of data in buffer
    /// @param timeout      max amount of time to wait for the write operation
    /// to complete
    /// @return int32_t     the number of bytes transmitted which may be less
    /// than `len`
    /// @return int32_t     -1 on error
    ///
    virtual int32_t write(std::size_t         address,
                          const uint8_t*      data,
                          std::size_t         len,
                          chrono::duration_ms timeout) = 0;
    ///
    /// Reads the requested number of bytes from the serial device into the data
    /// buffer.
    ///
    /// @param address      address of the transmitter or 0 if not supported
    /// @param data         a buffer that can recieve the data from the device
    /// @param len          the requested number of bytes to recieve
    /// @param timeout      max amount of time to wait for the read operation to
    /// complete
    /// @return int32_t     the number of bytes received which may be less than
    /// `len`
    /// @return int32_t     -1 on error
    ///
    virtual int32_t read(std::size_t         address,
                         uint8_t*            data,
                         std::size_t         len,
                         chrono::duration_ms timeout) = 0;
};
}  // namespace bte