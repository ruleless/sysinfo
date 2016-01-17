TOPDIR:=..

TARGET:=sysinfo.out
dirs:=

CXXFLAGS:=-I $(TOPDIR)/snail/include -I $(TOPDIR)/sigar/include
LDFLAGS:=-L $(TOPDIR)/snail/lib -lsnail	-L $(TOPDIR)/sigar/lib -lsigar -lpthread

# SPECOBJS:=$(patsubst %.cpp,%.o,$(notdir $(wildcard ../sysinfo/*.cpp)))
SPECOBJS:=$(patsubst %.cpp,%.o,$(wildcard ../sysinfo/*.cpp))

include $(TOPDIR)/common.mak
