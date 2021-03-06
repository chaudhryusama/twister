#include <rte_ether.h>
#include <portconf.h>
#include <eth.h>
#include <rte_ether.h>
#include <arplogic.h>
#include <queued_pkts.h>
#include <event_loop.h>
#include <tw_common.h>

inline uint16_t tw_ipv4_cksum(struct ipv4_hdr *ipv4_hdr)
{
    ipv4_hdr->hdr_checksum = 0;
    return rte_ipv4_cksum(ipv4_hdr);
}

inline void tw_vlan_strip(tw_buf_t *buffer)
{
    rte_vlan_strip(buffer->pkt);
}

inline int tw_match_port_ether_addr(struct ether_addr *ea, char * port_name)
{
    int port_id = tw_eth_name_to_id(port_name);
    return is_same_ether_addr(ea, port_info[port_id].eth_mac);
}
inline int tw_is_broadcast_ether_addr(const struct ether_addr *ea)
{
    return is_broadcast_ether_addr(ea);

}
inline void tw_copy_ether_addr(struct ether_addr * s_addr, struct ether_addr * d_addr)
{
    ether_addr_copy(s_addr, d_addr);
    return;
}

inline int tw_send_pkt(tw_buf_t * buffer, char * port_name)
{
    int ret = tw_add_pkt_to_tx_queue(buffer->pkt, tw_eth_name_to_id(port_name));
    //rte_free(buffer);
    return ret;
}

inline struct ether_addr * tw_get_ether_addr(char * port_name)
{
    return (port_info[tw_eth_name_to_id(port_name)].eth_mac);
}

//static struct ether_addr eth_port_mac[MAX_ETH_PORTS];
int tw_eth_pkt_ctor(struct rte_mbuf* m, uint8_t port_id, uint16_t eth_type, uint32_t dst_ip)
{
    //uint8_t socket_id = rte_eth_dev_socket_id(port_id);
    //struct rte_mbuf * m = rte_pktmbuf_alloc ( tx_mempool[socket_id] );
    rte_pktmbuf_prepend(m, sizeof(struct ether_hdr));
    struct ether_hdr* eth = rte_pktmbuf_mtod(m, struct ether_hdr *);
    eth->ether_type = rte_cpu_to_be_16(eth_type);
    ether_addr_copy(port_info[port_id].eth_mac, &(eth->s_addr));
    uint32_t arp_ip = 0;
    uint32_t source_and = port_info[port_id].start_ip_addr & port_info[port_id].subnet_mask;
    uint32_t dest_and = dst_ip & port_info[port_id].subnet_mask;

    if(source_and == dest_and)
        arp_ip = dst_ip;
    else
        arp_ip = port_info[port_id].gateway_ip;
    struct arp_table * arp_table_ptr = tw_search_arp_table(rte_cpu_to_be_32(arp_ip));
    if(arp_table_ptr == NULL)
    {
        if(tw_add_pkt_to_queue(m, arp_ip, port_id) == 0)
            tw_construct_arp_packet(arp_ip, port_id);
    }
    else
    {
        ether_addr_copy(&(arp_table_ptr->eth_mac), &(eth->d_addr));
        tw_add_pkt_to_tx_queue(m, port_id);
    }
    return 0;
}

int tw_eth_pkt_parser(struct rte_mbuf * pkt, uint8_t port_id)
{
    //rte_pktmbuf_dump(stdout, pkt, 100);
    struct ether_hdr * eth = rte_pktmbuf_mtod(pkt, struct ether_hdr *);
    uint8_t accept_brdcast = is_broadcast_ether_addr(&(eth->d_addr)) & ACCEPT_BRDCAST;
    if(is_same_ether_addr(&(eth->d_addr), port_info[port_id].eth_mac) || accept_brdcast)
    {
        switch (rte_be_to_cpu_16(eth->ether_type))
        {
            case ETHER_TYPE_ARP:
                tw_parse_arp(pkt, port_id);
                break;
            case ETHER_TYPE_VLAN:
                rte_vlan_strip(pkt);
                tw_parse_arp(pkt, port_id);
                break;
            default:
                rte_pktmbuf_free(pkt);
                break;
        }
    }
    else
        rte_pktmbuf_free(pkt);
    return 0;
}
