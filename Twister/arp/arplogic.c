#ifndef _ARPLOGIC_C_
#define _ARPLOGIC_C_

#include <arplogic.h>

int arp_parser(struct ether_hdr * eth, uint8_t port_id) {
	struct arp_hdr * arp_pkt = (struct arp_hdr *) (eth+1);	//remove the eth header, and see if its a request or reply and act accordingly
	if(arp_pkt->arp_op == ARP_OP_REQUEST) {
		if((arp_pkt->arp_data.arp_tip == port_info->ip_addr) && (port_info[port_id].flags & REPLY_ARP)) {
				send_arp_reply(eth, port_id);
		}
	}
	else if(arp_pkt->arp_op == ARP_OP_REPLY) {
		process_arp_reply(eth, port_id);
	}
	else
		rte_pktmbuf_free((struct rte_mbuf *) eth);
	return 0;
}
	
int send_arp_reply(struct ether_hdr * eth, uint8_t port_id) {
	struct arp_hdr * arp_pkt = (struct arp_hdr *) (eth+1);		//ether_hdr pointer type was passed because we want to reuse the pktmbuf for transmission also
	arp_pkt->arp_op = ARP_OP_REPLY;
	ether_addr_copy(&(arp_pkt->arp_data.arp_sha), &(arp_pkt->arp_data.arp_tha));
	ether_addr_copy(port_info[port_id].eth_mac, &(arp_pkt->arp_data.arp_sha));
	arp_pkt->arp_data.arp_sip = arp_pkt->arp_data.arp_tip;
	arp_pkt->arp_data.arp_tip = port_info[port_id].ip_addr;
	add_pkt_to_tx_queue((struct rte_mbuf *) eth, port_id);				//--!TODO implement add_pkt_to_tx_queue
	return 0;
}	

int process_arp_reply(struct ether_hdr * eth, uint8_t port_id) {
	struct arp_hdr * arp_pkt = (struct arp_hdr *) (eth+1);
	if(search_arp_table(arp_pkt->arp_data.arp_sip) == NULL)	{	//if ARP entry doesn't exist. One MAC can have multiple IPs associated
		if(add_arp_entry(arp_pkt->arp_data.arp_sip, arp_pkt->arp_data.arp_sha, port_id))
			return -1;
	}
	rte_pktmbuf_free((struct rte_mbuf *) eth);
	return 0;
}

struct arp_table * search_arp_table(uint32_t ip_to_search) {
	struct arp_table * arp_table_ptr = arp_table_root;
	while(arp_table_ptr != NULL) {
		if(arp_table_ptr->ip_addr == ip_to_search)
			return arp_table_ptr;
		else	
			arp_table_ptr = arp_table_ptr->next;
	}
	return NULL;
}

int add_arp_entry(uint32_t ip_to_add, struct ether_addr mac_to_add, uint8_t port_id) {
	struct arp_table * arp_table_ptr = arp_table_root;
	while(arp_table_ptr != NULL)
			arp_table_ptr = arp_table_ptr->next;
	arp_table_ptr = rte_malloc("struct arp_table", sizeof(struct arp_table), RTE_CACHE_LINE_SIZE);
	if(arp_table_ptr == NULL)
		return -1;
	arp_table_ptr->ip_addr = ip_to_add;
	ether_addr_copy(&(mac_to_add), &(arp_table_ptr->eth_mac));
	arp_table_ptr->port_id = port_id;
	arp_table_size++;
	return 0;
}
int construct_arp_packet(uint8_t ip, uint8_t port_id, uint8_t vlan) {

    socket_id = rte_eth_dev_socket_id(port_id);
    struct rte_mbuf * m = rte_pktmbuf_alloc ( tx_mempool[socket_id] );
    
    rte_pktmbuf_append(m, sizeof ( struct arp_hdr* ));
    struct arp_hdr * arp_pkt = rte_pktmbuf_mtod (m, sizeof ( struct arp_hdr *) );
    arp_pkt->arp_op = ARP_OP_REQUEST;
    
    ether_addr_copy(port_info[port_id].eth_mac, &(arp_pkt->arp_data.arp_sha));
	ether_addr_copy(&(broadcastmac), &(arp_pkt->arp_data.arp_tha));
	arp_pkt->arp_data.arp_sip = port_info[port_id].ip_addr;
	arp_pkt->arp_data.arp_tip = ip;
    
    rte_pktmbuf_prepend( m, sizeof ( struct ether_hdr* )  );
    struct ether_hdr* eth = rte_pktmbuf_mtod(m, struct ether_hdr *);
    
    if (vlan)
    {
        eth->ether_type = ETHER_TYPE_VLAN;
    }
    
    else 
    {
        eth->ether_type = ETHER_TYPE_IPv4;
    }
        ether_addr_copy(port_info[port_id].eth_mac, &(eth->s_addr));
	ether_addr_copy(&(broadcastmac), &(eth->d_addr));
	add_pkt_to_tx_queue(m, port_id);				
	return 0;
}
#endif
