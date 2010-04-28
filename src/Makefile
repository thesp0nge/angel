EXTRA_CFLAGS += -Wall -I. -I.. 

# Configure AngeL here waiting for better Kconfig...
DENY_ON_THE_FLY_MOUNT_OPERATIONS=y
DENY_EXECUTABLES_FILE_CREATION=y
ALLOW_SYSCTL_ENTRIES=y
DENY_HARD_LINK=y
DENY_SOFT_LINK=y
DENY_UNLINK=y
DENY_SETTIME=y
DENY_STAT=y
DENY_RENAME=y
DENY_PTRACE=y
HOOK_DIRECTORY=y
HOOK_CAPABLE=y
ENABLE_NETFILTER=n

ifeq ($(DENY_ON_THE_FLY_MOUNT_OPERATIONS), y)
   EXTRA_CFLAGS+=-DCONFIG_ANGEL_DENY_MOUNT
endif

ifeq ($(DENY_EXECUTABLES_FILE_CREATION), y)
   EXTRA_CFLAGS+=-DANGEL_DENY_CREATE_EXECUTABLES
endif

ifeq ($(ALLOW_SYSCTL_ENTRIES), y)
	EXTRA_CFLAGS+=-DCONFIG_SECURITY_ANGEL_SYSCTL
endif

ifeq ($(DENY_HARD_LINK), y)
	EXTRA_CFLAGS+=-DANGEL_DENY_HARD_LINK
endif

ifeq ($(DENY_SOFT_LINK), y)
	EXTRA_CFLAGS+=-DANGEL_DENY_SOFT_LINK
endif
ifeq ($(DENY_SETTIME), y)
	EXTRA_CFLAGS+=-DANGEL_DENY_SETTIME
endif
ifeq ($(DENY_STAT), y)
	EXTRA_CFLAGS+=-DCONFIG_ANGEL_DENY_STAT
endif
ifeq ($(HOOK_CAPABLE), y)
	EXTRA_CFLAGS+=-DCONFIG_ANGEL_CAPABLE
endif
ifeq ($(DENY_UNLINK), y) 
	EXTRA_CFLAGS+=-DCONFIG_ANGEL_DENY_UNLINK
endif
ifeq ($(HOOK_DIRECTORY), y)
	EXTRA_CFLAGS+=-DCONFIG_ANGEL_DIR
endif
ifeq ($(DENY_RENAME), y)
	EXTRA_CFLAGS+=-DCONFIG_ANGEL_DENY_RENAME
endif
ifeq ($(DENY_PTRACE), y)
	EXTRA_CFLAGS+=-DCONFIG_ANGEL_DENY_PTRACE
endif

ifeq ($(ENABLE_NETFILTER), y)
	EXTRA_CFLAGS+=-DCONFIG_ANGEL_NETFILTER
endif
EXTRA_CFLAGS+=-DANGEL_DEBUG
#obj-$(CONFIG_SECURITY_ANGEL) += angel.o
#angel-objs := engine.o angel_sysctl.o angel_array.o angel_sniffing.o

obj-m := angel.o
angel-y := engine.o angel_sysctl.o angel_array.o angel_sniffing.o angel_inode.o angel_devices.o angel_settime.o angel_capable.o angel_ptrace.o angel_syslog.o angel_netfilter.o angel_tcp.o angel_ip.o angel_icmp.o angel_socket.o angel_task.o angel_list.o
