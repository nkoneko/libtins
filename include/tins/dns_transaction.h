#ifndef TINS_DNS_TRANSACTION_H
#define TINS_DNS_TRANSACTION_H

#include <tins/config.h>
#include <cstdint>
#include <map>
#include <vector>
#include <array>
#include <functional>
#include <tins/pdu.h>

namespace Tins {

class DNSTransaction {
public:
    enum TerminationReason {
        TIMEOUT
    };
    class TransactionIdentifier;

    DNSTransaction();
    using transaction_callback_type = std::function<void(PDU&)>;
    using transaction_termination_callback_type = std::function<void(PDU&, TerminationReason)>;
    using transaction_id = TransactionIdentifier;
    using payload_type = std::vector<uint8_t>;

    void process_packet(PDU& pdu);

    class TransactionIdentifier {
    public:
        using address_type = std::array<uint8_t, 16>;
        TransactionIdentifier() = delete;
        TransactionIdentifier(const address_type& client_addr, uint16_t client_port,
                              const address_type& server_addr, uint16_t server_port);
        bool operator<(const TransactionIdentifier& rhs) const;
        bool operator==(const TransactionIdentifier& rhs) const;

        static TransactionIdentifier make_identifier(const PDU& packet);
    };
private:
    std::map<transaction_id, payload_type> transactions;
};

} // Tins

#endif // TINS_DNS_TRANSACTION_H
