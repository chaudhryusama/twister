#ifndef _MEMMGMT_C_
#define _MEMMGMT_C_

#include <mempoolconf.h>

uint8_t num_numa_sockets = 1;

int create_rx_tx_mempools(void) {		//--!TODO Have to call "lcore_init" before using this function
	uint8_t numa_socket = 0;
	for(numa_socket=0;numa_socket<num_numa_sockets;numa_socket++) {
		printf("%d socket id %d NB_MBUF, %lu MBUF_SIZE, %d numa_socket\n", rte_socket_id(), NB_MBUF, MBUF_SIZE, numa_socket);
		rx_mempool[numa_socket] = rte_mempool_create("rx_mempool_" + numa_socket, NB_MBUF, MBUF_SIZE, 32, sizeof(struct rte_pktmbuf_pool_private), rte_pktmbuf_pool_init, NULL, rte_pktmbuf_init, NULL, rte_socket_id(), 0);	//--!TODO Is 32 the best cache align val???
		if (rx_mempool[numa_socket] == NULL)
			rte_exit(EXIT_FAILURE, "Cannot init rx mempool on NUMA node %d\n", numa_socket);
		tx_mempool[numa_socket] = rte_mempool_create("tx_mempool_" + numa_socket, NB_MBUF, MBUF_SIZE, 32, sizeof(struct rte_pktmbuf_pool_private), rte_pktmbuf_pool_init, NULL, rte_pktmbuf_init, NULL, rte_socket_id(), 0);
		if (tx_mempool[numa_socket] == NULL)
			rte_exit(EXIT_FAILURE, "Cannot init tx mempool on NUMA node %d\n", numa_socket);
	}
	return 0;
}

tw_buf_t * tw_new_buffer(uint16_t buffer_size) {
	struct rte_mbuf * pkt = app_get_buffer();
	if(buffer_size)
		rte_pktmbuf_append(pkt, buffer_size);
	tw_buf_t * tw_buff = rte_malloc("tw_buf_t *", sizeof(tw_buf_t), RTE_CACHE_LINE_SIZE);
	tw_buff->pkt = pkt;
	tw_buff->data = rte_pktmbuf_mtod(pkt, void *);
	return tw_buff;
}

void tw_memcpy (void * dst, const void * src, size_t n) {
	rte_memcpy(dst, src, n);
	return;
}

struct rte_mbuf * app_get_buffer(void)
{
	return rte_pktmbuf_alloc(tx_mempool[0]);
}

inline void tw_free(void * ptr) {
	rte_free(ptr);
}

inline void tw_free_buffer(tw_buf_t * ptr) {
	rte_pktmbuf_free(ptr->pkt);
	rte_free((void *) ptr);
	return;
}

int create_queued_pkts_mempools(void) {		//--! To be used by queued packets including pakets waiting for an ARP reply
	uint8_t numa_socket = 0;
        for(numa_socket=0;numa_socket<num_numa_sockets;numa_socket++) {
                queued_pkts_mempool[numa_socket] = rte_mempool_create("queued_pkts_mempool" + numa_socket, NB_MBUF, MBUF_SIZE, 32, sizeof(struct rte_pktmbuf_pool_private), rte_pktmbuf_pool_init, NULL, rte_pktmbuf_init, NULL, numa_socket, 0);
                if (queued_pkts_mempool[numa_socket] == NULL)
                        rte_exit(EXIT_FAILURE, "Cannot init queued packets mempool on NUMA node %d\n", numa_socket);
	}
	return 0;
}

#endif
