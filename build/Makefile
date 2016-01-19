TOPDIR:=..

DIRS:=$(TOPDIR)/sysinfo $(TOPDIR)/main
OBJS:=$(foreach v,$(DIRS),$(wildcard $(v)/*.o))

TARGET:=sysinfo.out

LDFLAGS:=-L $(TOPDIR)/snail/lib -lsnail	-L $(TOPDIR)/sigar/lib -lsigar -lpthread

include ./build.mak
