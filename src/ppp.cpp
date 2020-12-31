#include <cstring>
#include <tins/macros.h>
#include <tins/ppp.h>
#include <tins/config.h>
#include <tins/constants.h>
#include <tins/memory_helpers.h>
#include <tins/detail/pdu_helpers.h>

using Tins::Memory::InputMemoryStream;
using Tins::Memory::OutputMemoryStream;

namespace Tins {

PPP::PPP(const uint8_t* buffer, uint32_t total_sz) {
    InputMemoryStream stream(buffer, total_sz);
    stream.read(header_);
    if (stream) {
        inner_pdu(
            Internals::pdu_from_flag(
                (Constants::PPP::e) payload_type(),
                stream.pointer(),
                stream.size()
            )
        );
    }
}

bool PPP::matches_response(const uint8_t* ptr, uint32_t total_sz) const {
    if (inner_pdu()) {
        return inner_pdu()->matches_response(ptr + header_size(), total_sz - header_size());
    }
    return true;
}
void PPP::write_serialization(uint8_t* buffer, uint32_t total_sz) {
    OutputMemoryStream stream(buffer, total_sz);
    stream.write(header_);
}

} // Tins
