cmd_eal_common_devargs.o = gcc -Wp,-MD,./.eal_common_devargs.o.d.tmp -m64 -pthread  -march=native -DRTE_MACHINE_CPUFLAG_SSE -DRTE_MACHINE_CPUFLAG_SSE2 -DRTE_MACHINE_CPUFLAG_SSE3 -DRTE_MACHINE_CPUFLAG_SSSE3 -DRTE_MACHINE_CPUFLAG_SSE4_1 -DRTE_MACHINE_CPUFLAG_SSE4_2 -DRTE_MACHINE_CPUFLAG_AES -DRTE_MACHINE_CPUFLAG_PCLMULQDQ -DRTE_MACHINE_CPUFLAG_AVX -DRTE_MACHINE_CPUFLAG_RDRAND -DRTE_MACHINE_CPUFLAG_FSGSBASE -DRTE_MACHINE_CPUFLAG_F16C -DRTE_COMPILE_TIME_CPUFLAGS=RTE_CPUFLAG_SSE,RTE_CPUFLAG_SSE2,RTE_CPUFLAG_SSE3,RTE_CPUFLAG_SSSE3,RTE_CPUFLAG_SSE4_1,RTE_CPUFLAG_SSE4_2,RTE_CPUFLAG_AES,RTE_CPUFLAG_PCLMULQDQ,RTE_CPUFLAG_AVX,RTE_CPUFLAG_RDRAND,RTE_CPUFLAG_FSGSBASE,RTE_CPUFLAG_F16C  -I/home/dell/hvc2_local/dpdk/x86_64-native-linuxapp-gcc/include -include /home/dell/hvc2_local/dpdk/x86_64-native-linuxapp-gcc/include/rte_config.h -I/home/dell/hvc2_local/dpdk/lib/librte_eal/linuxapp/eal/include -I/home/dell/hvc2_local/dpdk/lib/librte_eal/common -I/home/dell/hvc2_local/dpdk/lib/librte_eal/common/include -I/home/dell/hvc2_local/dpdk/lib/librte_ring -I/home/dell/hvc2_local/dpdk/lib/librte_mempool -I/home/dell/hvc2_local/dpdk/lib/librte_malloc -I/home/dell/hvc2_local/dpdk/lib/librte_ether -I/home/dell/hvc2_local/dpdk/lib/librte_ivshmem -I/home/dell/hvc2_local/dpdk/lib/librte_pmd_ring -I/home/dell/hvc2_local/dpdk/lib/librte_pmd_pcap -I/home/dell/hvc2_local/dpdk/lib/librte_pmd_af_packet -I/home/dell/hvc2_local/dpdk/lib/librte_pmd_xenvirt -W -Wall -Werror -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wpointer-arith -Wcast-align -Wnested-externs -Wcast-qual -Wformat-nonliteral -Wformat-security -Wundef -Wwrite-strings -O3   -o eal_common_devargs.o -c /home/dell/hvc2_local/dpdk/lib/librte_eal/common/eal_common_devargs.c 
