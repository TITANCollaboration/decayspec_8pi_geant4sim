name := ebit
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../../..
endif

.PHONY: all
all: lib bin

## pull in root
RCONF=$(ROOTSYS)/bin/root-config

CPPFLAGS += -I$(shell $(RCONF) --incdir) 
EXTRALIBS = $(shell $(RCONF) --glibs)


include $(G4INSTALL)/config/architecture.gmk
include $(G4INSTALL)/config/binmake.gmk
