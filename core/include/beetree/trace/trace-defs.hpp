//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <cstdint>
#include <limits>
#include <utility>

namespace bte {

/// Protocol - UInt32 Header
/// MSb   --- LSb
/// | - 0xA - | Len    |Processor  | Verbosity | Channel | Token   |
/// | 4 bits  | 4 bits | 2 bits    | 3 bits    | 3 bits  | 16 bits |
namespace trace_prot {
/// protocol allows for 3 bits to represent length, only allow 4 args
constexpr std::size_t MAX_TOKEN_ARGS = 0x4;
/// 11-bits allocated
constexpr std::size_t MAX_TOKEN_ID = 0xFFFF;
/// 3-bits allowed for processor id
constexpr std::size_t MAX_PROCESSOR_ID = 0x3;
/// 5-bits designated for channel, 32 channels
constexpr std::size_t MAX_CHANNEL_ID = 0x7;
/// Protocol packet size in DWords (uint32_t)
/// Header (1 dword) + Args (4 dword) + CRC (1 dword)
constexpr std::size_t BUF_DWORD_LEN = 1 + MAX_TOKEN_ARGS + 1;
/// Protocol packet size in Bytes
constexpr std::size_t BUF_LEN = BUF_DWORD_LEN * sizeof(uint32_t);
}  // namespace trace_prot

enum class TraceProcessor
{
    ID_0,
    ID_1,
    ID_2,
    ID_3,
};

enum class TraceVerbosity
{
    Debug,
    Info,
    Warn,
    Error,
    Fatal
};

enum class TraceChannel
{
    Log,            /// Channel to send log messages on.
    Nodes,          /// Channel to send node changes on
    Registry,       /// Dedicated channel for continuous streaming registry banks
    Diagnostics,    /// Channel dedicated to continuous streaming of key-value pairs.
    CH_4_Reserved,  /// Reserved for future use
    CH_5_Reserved,  /// Reserved for future use
    User_1,         /// Dedicated channel for user
    User_2          /// Dedicated channel for user
};

struct TraceToken
{
    uint32_t id{0};
    constexpr TraceToken() = default;
    constexpr TraceToken(uint32_t _id) : id(_id) {}
};

struct TracePackage
{
    TraceToken     token{0};
    TraceChannel   channel{TraceChannel::Log};
    TraceVerbosity verbosity{TraceVerbosity::Info};
    uint32_t       num_args{0};
    uint32_t       args[trace_prot::MAX_TOKEN_ARGS] = {0};
};

class TraceListener
{
public:
    TraceListener()          = default;
    virtual ~TraceListener() = default;

    virtual void on_log_received(TraceProcessor processor, const TracePackage& package) = 0;
};
}  // namespace bte