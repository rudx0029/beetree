//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/trace/trace-protocol.hpp"

namespace bte {
namespace trace_prot {
std::size_t package(TraceProcessor processor, const TracePackage& package, uint8_t buffer[BUF_LEN])
{
    // byte packing is defined trace/trace-defs.hpp
    uint8_t start_char_len = 0xA0 | (0x0F & package.num_args);
    uint8_t proc_verb      = ((static_cast<uint8_t>(processor) & 0x03) << 6) |
                        ((static_cast<uint8_t>(package.verbosity) & 0x07) << 3) |
                        (static_cast<uint8_t>(package.channel) & 0x07 << 0);
    uint16_t channel_token = static_cast<uint16_t>(package.token.id);

    // add the header as individual bytes, bytes 1 and 2
    buffer[0] = start_char_len;
    buffer[1] = proc_verb;

    // add channel and token as a word, bytes 3 and 4
    uint16_t* chan_tok_word = reinterpret_cast<uint16_t*>(&buffer[2]);
    *chan_tok_word          = channel_token;

    // add the args as dwords, bytes 5+
    uint32_t* dword_buff = reinterpret_cast<uint32_t*>(buffer);

    for (std::size_t i = 0; i < package.num_args && MAX_TOKEN_ARGS; i++)
    {
        dword_buff[i + 1] = package.args[i];
    }

    // finally add the crc as dword
    // todo: add the crc
    dword_buff[package.num_args + /*header*/ 1] = 0;

    std::size_t numbytes = sizeof(uint32_t) * (/*header*/ 1 + package.num_args + /*crc*/ 1);
    return numbytes;
}
}  // namespace trace_prot
}  // namespace bte