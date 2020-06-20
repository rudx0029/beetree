#include "beetree/trace/serial-listener.hpp"
#include "beetree/trace/trace-protocol.hpp"
#include "beetree/trace/trace.hpp"
#include "beetree/units/units.hpp"

namespace bte {
using trace_prot::BUF_LEN;
using trace_prot::package;

void SerialListener::configure(ISerialDevice& out, TraceVerbosity verb)
{
    m_out = &out;
    m_manager.set_listener(this);
    m_manager.set_verbosity(verb);
    set_trace_manager(&m_manager);
}

void SerialListener::on_log_received(TraceProcessor processor, const TracePackage& p)
{
    constexpr auto timeout = 100_ms;
    uint8_t        buffer[BUF_LEN];

    if (m_out)
    {
        std::size_t address = 0;  // ignored
        std::size_t nbytes  = package(processor, p, buffer);
        m_out->write(address, buffer, nbytes, timeout.count());
    }
}
}  // namespace bte