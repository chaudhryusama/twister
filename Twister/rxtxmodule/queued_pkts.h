#ifndef _QUEUED_PKTS_H_
#define _QUEUED_PKTS_H_

#include <rte_mbuf.h>
#include <rte_memory.h>
#include <timerfuncs.h>
#include <arplogic.h>

uint64_t queue_time_limit = 15;		//--!TODO get the value from user

struct queued_pkt {
	struct rte_mbuf * pkt;
	uint64_t timercycle;
	uint32_t dest_ip;
	struct queued_pkt * next;
} __attribute__((__packed__));

struct queued_pkt * root_queued_pkt = NULL;

int add_pkt_to_queue(struct rte_mbuf *, uint32_t);
int update_queued_pkts(void);
int delete_queued_pkt(struct queued_pkt **, struct queued_pkt **);
int send_queued_pkt(struct queued_pkt *, struct ether_addr);

#endif
