#include <tins/dns_transaction.h>
#include <tins/udp.h>
#include <tins/pdu.h>
#include <tins/udp.h>

namespace Tins {

DNSTransaction::DNSTransaction() {}

void DNSTransaction::process_packet(PDU& pdu) {
}

DNSTransaction::TransactionIdentifier::TransactionIdentifier(const DNSTransaction::TransactionIdentifier::address_type& client_addr, uint16_t client_port,
                                                             const DNSTransaction::TransactionIdentifier::address_type& client_addr, uint16_t client_port) {
}

} // Tins
