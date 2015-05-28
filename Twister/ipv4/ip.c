#include <rte_ip.h>
#include <rte_memcpy.h>
#include <rte_byteorder.h>
#include <rte_mbuf.h>
#include <rte_udp.h>
#include <portconf.h>
#include <ip.h>
#include <udp.h>
#define UDP_PROTO_ID	17
#define TCP_PROTO_ID	6


void ip4_packet_parser(struct rte_mbuf *pkt,uint8_t port_id)
{
    struct ipv4_hdr *ipHdr = rte_pktmbuf_mtod(pkt, struct ipv4_hdr *);
    //uint16_t ipchecksum = rte_ipv4_cksum(ipHdr);	
 /*   if (ipchecksum == ipHdr->hdr_checksum && ipHdr->version_ihl > 20 && ipHdr->time_to_live >= 0)
	{*/
	uint32_t dst_ip  = rte_be_to_cpu_32(ipHdr->dst_addr);
	uint32_t src_ip = rte_be_to_cpu_32(ipHdr->src_addr);
	if (dst_ip == port_info[port_id].ip_addr || dst_ip == 2130706433) 
	{	
		rte_pktmbuf_adj(pkt, ipHdr->version_ihl);
		switch(ipHdr->next_proto_id)
			{
				case (UDP_PROTO_ID):
					udp_packet_parser(pkt,src_ip,dst_ip);
					break;
				case (TCP_PROTO_ID):
					//tcp_packet_parser(pkt);
					break;
				default:
					rte_pktmbuf_free(pkt);
				break;
			}
	}
	else
	{
		rte_pktmbuf_free(pkt);	
	}
		
/*	}
    else
    {
		rte_pktmbuf_free(pkt);
	}		
	*/
}

void ip4_packet_create(struct rte_mbuf *pkt,uint8_t next_port_id,uint32_t src_ip,uint32_t dst_ip,uint16_t length)
{
	rte_pktmbuf_prepend(pkt, sizeof(struct ipv4_hdr *));
	struct ipv4_hdr *ip_hdr  = rte_pktmbuf_mtod(pkt, struct ipv4_hdr *);
	ip_hdr->total_length = length + sizeof(struct ipv4_hdr *);
	ip_hdr->next_proto_id = next_port_id;
	ip_hdr->src_addr = rte_cpu_to_be_32(src_ip);
	ip_hdr->dst_addr = rte_cpu_to_be_32(dst_ip);
	ip_hdr->version_ihl = sizeof(struct udp_hdr);
	ip_hdr->time_to_live = 20;
	ip_hdr->hdr_checksum =rte_ipv4_cksum(ip_hdr);
	// will call L2 creater
	
}

