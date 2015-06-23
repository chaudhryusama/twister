cmd_test = gcc -m64 -pthread  -march=native -DRTE_MACHINE_CPUFLAG_SSE -DRTE_MACHINE_CPUFLAG_SSE2 -DRTE_MACHINE_CPUFLAG_SSE3 -DRTE_MACHINE_CPUFLAG_SSSE3 -DRTE_MACHINE_CPUFLAG_SSE4_1 -DRTE_MACHINE_CPUFLAG_SSE4_2 -DRTE_MACHINE_CPUFLAG_AES -DRTE_MACHINE_CPUFLAG_PCLMULQDQ -DRTE_MACHINE_CPUFLAG_AVX -DRTE_MACHINE_CPUFLAG_RDRAND -DRTE_MACHINE_CPUFLAG_FSGSBASE -DRTE_MACHINE_CPUFLAG_F16C -DRTE_COMPILE_TIME_CPUFLAGS=RTE_CPUFLAG_SSE,RTE_CPUFLAG_SSE2,RTE_CPUFLAG_SSE3,RTE_CPUFLAG_SSSE3,RTE_CPUFLAG_SSE4_1,RTE_CPUFLAG_SSE4_2,RTE_CPUFLAG_AES,RTE_CPUFLAG_PCLMULQDQ,RTE_CPUFLAG_AVX,RTE_CPUFLAG_RDRAND,RTE_CPUFLAG_FSGSBASE,RTE_CPUFLAG_F16C  -I/home/dell/hvc2_local/dpdk/x86_64-native-linuxapp-gcc/include -include /home/dell/hvc2_local/dpdk/x86_64-native-linuxapp-gcc/include/rte_config.h -O3 -W -Wall -Werror -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wpointer-arith -Wcast-align -Wnested-externs -Wcast-qual -Wformat-nonliteral -Wformat-security -Wundef -Wwrite-strings -D_GNU_SOURCE  -Wl,-Map=test.map,--cref -o test commands.o test.o test_pci.o test_prefetch.o test_byteorder.o test_per_lcore.o test_atomic.o test_malloc.o test_cycles.o test_spinlock.o test_memory.o test_memzone.o test_ring.o test_ring_perf.o test_pmd_perf.o test_table.o test_table_pipeline.o test_table_tables.o test_table_ports.o test_table_combined.o test_table_acl.o test_rwlock.o test_timer.o test_timer_perf.o test_mempool.o test_mempool_perf.o test_mbuf.o test_logs.o test_memcpy.o test_memcpy_perf.o test_hash.o test_hash_perf.o test_lpm.o test_lpm6.o test_debug.o test_errno.o test_tailq.o test_string_fns.o test_cpuflags.o test_mp_secondary.o test_eal_flags.o test_eal_fs.o test_alarm.o test_interrupts.o test_version.o test_func_reentrancy.o test_cmdline.o test_cmdline_num.o test_cmdline_etheraddr.o test_cmdline_portlist.o test_cmdline_ipaddr.o test_cmdline_cirbuf.o test_cmdline_string.o test_cmdline_lib.o test_red.o test_sched.o test_meter.o test_kni.o test_power.o test_power_acpi_cpufreq.o test_power_kvm_vm.o test_common.o test_distributor.o test_distributor_perf.o test_reorder.o test_devargs.o virtual_pmd.o packet_burst_generator.o test_acl.o test_link_bonding.o test_link_bonding_mode4.o test_pmd_ring.o test_kvargs.o -Wl,--no-as-needed -Wl,-export-dynamic -L/home/dell/hvc2_local/dpdk/x86_64-native-linuxapp-gcc/lib  -L/home/dell/hvc2_local/dpdk/x86_64-native-linuxapp-gcc/lib -Wl,--whole-archive -Wl,-lrte_distributor -Wl,-lrte_reorder -Wl,-lrte_kni -Wl,-lrte_pipeline -Wl,-lrte_table -Wl,-lrte_port -Wl,-lrte_timer -Wl,-lrte_hash -Wl,-lrte_jobstats -Wl,-lrte_lpm -Wl,-lrte_power -Wl,-lrte_acl -Wl,-lrte_meter -Wl,-lrte_sched -Wl,-lm -Wl,-lrt -Wl,--start-group -Wl,-lrte_kvargs -Wl,-lrte_mbuf -Wl,-lrte_ip_frag -Wl,-lethdev -Wl,-lrte_malloc -Wl,-lrte_mempool -Wl,-lrte_ring -Wl,-lrte_eal -Wl,-lrte_cmdline -Wl,-lrte_cfgfile -Wl,-lrte_pmd_bond -Wl,-lrte_pmd_vmxnet3_uio -Wl,-lrte_pmd_virtio_uio -Wl,-lrte_pmd_enic -Wl,-lrte_pmd_i40e -Wl,-lrte_pmd_fm10k -Wl,-lrte_pmd_ixgbe -Wl,-lrte_pmd_e1000 -Wl,-lrte_pmd_ring -Wl,-lrte_pmd_af_packet -Wl,-lrt -Wl,-lm -Wl,-ldl -Wl,--end-group -Wl,--no-whole-archive 
