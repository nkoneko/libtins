#ifndef TINS_PPP_H
#define TINS_PPP_H

#include <stdint.h>
#include <tins/macros.h>
#include <tins/pdu.h>
#include <tins/config.h>
#include <tins/endianness.h>

namespace Tins {

class TINS_API PPP : public PDU {
public:
    static const PDU::PDUType pdu_flag = PDU::PPP;

    PPP(const uint8_t* buffer, uint32_t total_sz);

    /* Virtual Methods */
    uint32_t header_size() const { return sizeof(header_); }
    uint16_t payload_type() const { return Endian::be_to_host(header_.protocol); }
    //uint32_t trailer_size() const;
    bool matches_response(const uint8_t* ptr, uint32_t total_sz) const;
    PDUType pdu_type() const { return pdu_flag; }
    PPP* clone() const {
        return new PPP(*this);
    }
    void write_serialization(uint8_t* buffer, uint32_t total_sz);
private:
    TINS_BEGIN_PACK
    struct ppp_header {
        uint8_t addr;
        uint8_t constrol;
        uint16_t protocol;
    } TINS_END_PACK;
    ppp_header header_;
};

} // Tins

#endif // TINS_PPP_H
