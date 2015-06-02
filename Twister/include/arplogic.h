#ifndef _ARPLOGIC_H_
#define _ARPLOGIC_H_

#include <rte_arp.h>
#include <rte_malloc.h>
#include <rte_ether.h>
#include <tx.h>
#include <portconf.h>

#define ARP_ENTRY_TIMEOUT 15000

struct arp_table {
	uint32_t ip_addr;
	struct ether_addr eth_mac;
	uint8_t port_id;
	struct arp_table * next;
} __attribute__((__packed__));

static  struct ether_addr broadcastMac = {
   .addr_bytes[1] = 0xff,
   .addr_bytes[2] = 0xff,
   .addr_bytes[3] = 0xff,
   .addr_bytes[4] = 0xff,
   .addr_bytes[5] = 0xff,
   .addr_bytes[0] = 0xff,
};

struct arp_table * arp_table_root = NULL;
uint32_t arp_table_size = 0;

int arp_parser(struct ether_hdr *, uint8_t);
int send_arp_reply(struct ether_hdr *, uint8_t);
int process_arp_reply(struct ether_hdr *, uint8_t);
struct arp_table * search_arp_table(uint32_t);
int add_arp_entry(uint32_t ip_to_add, struct ether_addr, uint8_t);
int construct_arp_packet(uint8_t, uint8_t, uint8_t);
#endif
