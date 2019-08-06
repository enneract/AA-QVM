#
# Tremulous Makefile
#
# GNU Make required
#

COMPILE_PLATFORM=$(shell uname | sed -e 's/_.*//' | tr '[:upper:]' '[:lower:]' | sed -e 's/\//_/g')
COMPILE_ARCH=$(shell uname -m | sed -e 's/i.86/x86/' | sed -e 's/^arm.*/arm/')

ifeq ($(COMPILE_PLATFORM),sunos)
  # Solaris uname and GNU uname differ
  COMPILE_ARCH=$(shell uname -p | sed -e 's/i.86/x86/')
endif

ifndef BUILD_GAME_SO
  BUILD_GAME_SO    = 0
endif
ifndef BUILD_GAME_QVM
  BUILD_GAME_QVM   = 1
endif
ifndef BUILD_GAME_QVM_11
  BUILD_GAME_QVM_11= 1
endif
ifndef BUILD_ONLY_GAME
  BUILD_ONLY_GAME  = 0
endif
ifndef BUILD_ONLY_CGUI
  BUILD_ONLY_CGUI  = 0
endif

#############################################################################
#
# If you require a different configuration from the defaults below, create a
# new file named "Makefile.local" in the same directory as this file and define
# your parameters there. This allows you to change configuration without
# causing problems with keeping up to date with the repository.
#
#############################################################################
-include GNUmakefile.local

include $(SETTINGS_MAKEFILES)

ifeq ($(COMPILE_PLATFORM),cygwin)
  PLATFORM=mingw32
endif

ifndef PLATFORM
PLATFORM=$(COMPILE_PLATFORM)
endif
export PLATFORM

ifeq ($(COMPILE_ARCH),i86pc)
  COMPILE_ARCH=x86
endif

ifeq ($(COMPILE_ARCH),amd64)
  COMPILE_ARCH=x86_64
endif
ifeq ($(COMPILE_ARCH),x64)
  COMPILE_ARCH=x86_64
endif

ifeq ($(COMPILE_ARCH),powerpc)
  COMPILE_ARCH=ppc
endif
ifeq ($(COMPILE_ARCH),powerpc64)
  COMPILE_ARCH=ppc64
endif

ifeq ($(COMPILE_ARCH),axp)
  COMPILE_ARCH=alpha
endif

ifndef ARCH
ARCH=$(COMPILE_ARCH)
endif
export ARCH

ifneq ($(PLATFORM),$(COMPILE_PLATFORM))
  CROSS_COMPILING=1
else
  CROSS_COMPILING=0

  ifneq ($(ARCH),$(COMPILE_ARCH))
    CROSS_COMPILING=1
  endif
endif
export CROSS_COMPILING

ifndef VERSION
VERSION=slackers
endif

ifndef CLIENTBIN
CLIENTBIN=tremulous
endif

ifndef BASEGAME
BASEGAME=slacker
endif

ifndef BASEGAME_CFLAGS
BASEGAME_CFLAGS=
endif

ifndef COPYDIR
COPYDIR="/usr/local/games/tremulous"
endif

ifndef COPYBINDIR
COPYBINDIR=$(COPYDIR)
endif

ifndef MOUNT_DIR
MOUNT_DIR=src
endif

ifndef ASSETS_DIR
ASSETS_DIR=assets
endif

ifndef BUILD_DIR
BUILD_DIR=bld
endif

ifndef TEMPDIR
TEMPDIR=/tmp
endif

ifndef DEBUG_CFLAGS
DEBUG_CFLAGS=-g -O0
endif

#############################################################################

BD=$(BUILD_DIR) # /debug-$(PLATFORM)-$(ARCH)
BR=$(BUILD_DIR) # /release-$(PLATFORM)-$(ARCH)
CDIR=$(MOUNT_DIR)/client
SDIR=$(MOUNT_DIR)/server
CMDIR=$(MOUNT_DIR)/qcommon
GDIR=$(MOUNT_DIR)/game
CGDIR=$(MOUNT_DIR)/cgame
NDIR=$(MOUNT_DIR)/null
UIDIR=$(MOUNT_DIR)/ui
Q3ASMDIR=$(MOUNT_DIR)/tools/asm
LBURGDIR=$(MOUNT_DIR)/tools/lcc/lburg
Q3CPPDIR=$(MOUNT_DIR)/tools/lcc/cpp
Q3LCCETCDIR=$(MOUNT_DIR)/tools/lcc/etc
Q3LCCSRCDIR=$(MOUNT_DIR)/tools/lcc/src
TEMPDIR=/tmp

# Add git version info
USE_GIT=
ifeq ($(wildcard .git),.git)
  GIT_REV=$(shell git describe --tag)
  ifneq ($(GIT_REV),)
    VERSION:=$(GIT_REV)
    USE_GIT=1
  endif
endif

#############################################################################
# SETUP AND BUILD -- LINUX
#############################################################################

## Defaults
LIB=lib

INSTALL=install
MKDIR=mkdir

ifneq (,$(findstring "$(PLATFORM)", "linux" "gnu_kfreebsd" "kfreebsd-gnu"))

  ifeq ($(ARCH),x86_64)
    LIB=lib64
  else
  ifeq ($(ARCH),ppc64)
    LIB=lib64
  else
  ifeq ($(ARCH),s390x)
    LIB=lib64
  endif
  endif
  endif

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes \
    -pipe -DUSE_ICON

  OPTIMIZEVM = -O3 -funroll-loops -fomit-frame-pointer
  OPTIMIZE = $(OPTIMIZEVM) -ffast-math

  ifeq ($(ARCH),x86_64)
    OPTIMIZEVM = -O3 -fomit-frame-pointer -funroll-loops \
      -falign-functions=2 -fstrength-reduce
    OPTIMIZE = $(OPTIMIZEVM) -ffast-math
    HAVE_VM_COMPILED = true
  else
  ifeq ($(ARCH),x86)
    OPTIMIZEVM = -O3 -march=i586 -fomit-frame-pointer \
      -funroll-loops -falign-functions=2 -fstrength-reduce
    OPTIMIZE = $(OPTIMIZEVM) -ffast-math
    HAVE_VM_COMPILED=true
  else
  ifeq ($(ARCH),ppc)
    BASE_CFLAGS += -maltivec
    HAVE_VM_COMPILED=true
  endif
  ifeq ($(ARCH),ppc64)
    BASE_CFLAGS += -maltivec
    HAVE_VM_COMPILED=true
  endif
  ifeq ($(ARCH),sparc)
    OPTIMIZE += -mtune=ultrasparc3 -mv8plus
    OPTIMIZEVM += -mtune=ultrasparc3 -mv8plus
    HAVE_VM_COMPILED=true
  endif
  ifeq ($(ARCH),alpha)
    # According to http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=410555
    # -ffast-math will cause the client to die with SIGFPE on Alpha
    OPTIMIZE = $(OPTIMIZEVM)
  endif
  endif
  endif

  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC -fvisibility=hidden
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  THREAD_LIBS=-lpthread
  LIBS=-ldl -lm

  ifeq ($(ARCH),x86)
    # linux32 make ...
    BASE_CFLAGS += -m32
  else
  ifeq ($(ARCH),ppc64)
    BASE_CFLAGS += -m64
  endif
  endif
else # ifeq Linux

#############################################################################
# SETUP AND BUILD -- MAC OS X
#############################################################################

ifeq ($(PLATFORM),darwin)
  HAVE_VM_COMPILED=true
  LIBS = -framework Cocoa
  OPTIMIZEVM=

  BASE_CFLAGS = -Wall -Wimplicit -Wstrict-prototypes -mmacosx-version-min=10.5 \
    -DMAC_OS_X_VERSION_MIN_REQUIRED=1050

  ifeq ($(ARCH),ppc)
    BASE_CFLAGS += -arch ppc -faltivec
    OPTIMIZEVM += -O3
  endif
  ifeq ($(ARCH),ppc64)
    BASE_CFLAGS += -arch ppc64 -faltivec
  endif
  ifeq ($(ARCH),x86)
    OPTIMIZEVM += -mfpmath=387+sse
    # x86 vm will crash without -mstackrealign since MMX instructions will be
    # used no matter what and they corrupt the frame pointer in VM calls
    BASE_CFLAGS += -arch i386 -m32 -mstackrealign
  endif
  ifeq ($(ARCH),x86_64)
    OPTIMIZEVM += -arch x86_64 -mfpmath=sse -msse2
  endif

  # When compiling on OSX for OSX, we're not cross compiling as far as the
  # Makefile is concerned, as target architecture is specified as a compiler
  # argument
  ifeq ($(COMPILE_PLATFORM),darwin)
    CROSS_COMPILING=0
  endif


  ifeq ($(CROSS_COMPILING),1)
    ifeq ($(ARCH),x86_64)
      CC=x86_64-apple-darwin13-cc
      RANLIB=x86_64-apple-darwin13-ranlib
    else
      ifeq ($(ARCH),x86)
        CC=i386-apple-darwin13-cc
        RANLIB=i386-apple-darwin13-ranlib
      else
        $(error Architecture $(ARCH) is not supported when cross compiling)
      endif
    endif
  else
    TOOLS_CFLAGS += -DMACOS_X
  endif

  BASE_CFLAGS += -fno-strict-aliasing -DMACOS_X -fno-common -pipe

  BASE_CFLAGS += -D_THREAD_SAFE=1

  OPTIMIZE = $(OPTIMIZEVM) -ffast-math

  SHLIBEXT=dylib
  SHLIBCFLAGS=-fPIC -fno-common
  SHLIBLDFLAGS=-dynamiclib $(LDFLAGS) -Wl,-U,_com_altivec

  NOTSHLIBCFLAGS=-mdynamic-no-pic

else # ifeq darwin


#############################################################################
# SETUP AND BUILD -- MINGW32
#############################################################################

ifeq ($(PLATFORM),mingw32)

  ifeq ($(CROSS_COMPILING),1)
    # If CC is already set to something generic, we probably want to use
    # something more specific
    ifneq ($(findstring $(strip $(CC)),cc gcc),)
      CC=
    endif

    # We need to figure out the correct gcc and windres
    ifeq ($(ARCH),x86_64)
      MINGW_PREFIXES=amd64-mingw32msvc x86_64-w64-mingw32
    endif
    ifeq ($(ARCH),x86)
      MINGW_PREFIXES=i586-mingw32msvc i686-w64-mingw32
    endif

    ifndef CC
      CC=$(strip $(foreach MINGW_PREFIX, $(MINGW_PREFIXES), \
         $(call bin_path, $(MINGW_PREFIX)-gcc)))
    endif
  else
    # Some MinGW installations define CC to cc, but don't actually provide cc,
    # so check that CC points to a real binary and use gcc if it doesn't
    ifeq ($(call bin_path, $(CC)),)
      CC=gcc
    endif
  endif

  ifeq ($(CC),)
    $(error Cannot find a suitable cross compiler for $(PLATFORM))
  endif

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes \
    -DUSE_ICON

  # In the absence of wspiapi.h, require Windows XP or later
  ifeq ($(shell test -e $(CMDIR)/wspiapi.h; echo $$?),1)
    BASE_CFLAGS += -DWINVER=0x501
  endif

  ifeq ($(ARCH),x86_64)
    OPTIMIZEVM = -O3 -fno-omit-frame-pointer \
      -funroll-loops -falign-functions=2 -fstrength-reduce
    OPTIMIZE = $(OPTIMIZEVM) -ffast-math
    HAVE_VM_COMPILED = true
  endif
  ifeq ($(ARCH),x86)
    OPTIMIZEVM = -O3 -march=i586 -fno-omit-frame-pointer \
      -funroll-loops -falign-functions=2 -fstrength-reduce
    OPTIMIZE = $(OPTIMIZEVM) -ffast-math
    HAVE_VM_COMPILED = true
  endif

  SHLIBEXT=dll
  SHLIBCFLAGS=
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  ifeq ($(CROSS_COMPILING),0)
    TOOLS_BINEXT=.exe
  endif

  ifeq ($(COMPILE_PLATFORM),cygwin)
    TOOLS_BINEXT=.exe
    TOOLS_CC=$(CC)
  endif

  LIBS= -lws2_32 -lwinmm -lpsapi

  ifeq ($(ARCH),x86)
    # build 32bit
    BASE_CFLAGS += -m32
  else
    BASE_CFLAGS += -m64
  endif

else # ifeq mingw32

#############################################################################
# SETUP AND BUILD -- FREEBSD
#############################################################################

ifeq ($(PLATFORM),freebsd)

  # flags
  BASE_CFLAGS = -Wall -fno-strict-aliasing -DUSE_ICON
  HAVE_VM_COMPILED = true

  OPTIMIZEVM = -O3 -funroll-loops -fomit-frame-pointer
  OPTIMIZE = $(OPTIMIZEVM) -ffast-math

  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  # don't need -ldl (FreeBSD)
  LIBS=-lm

  # cross-compiling tweaks
  ifeq ($(ARCH),x86)
    ifeq ($(CROSS_COMPILING),1)
      BASE_CFLAGS += -m32
    endif
  endif
  ifeq ($(ARCH),x86_64)
    ifeq ($(CROSS_COMPILING),1)
      BASE_CFLAGS += -m64
    endif
  endif
else # ifeq freebsd

#############################################################################
# SETUP AND BUILD -- OPENBSD
#############################################################################

ifeq ($(PLATFORM),openbsd)

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes \
    -pipe -DUSE_ICON -DMAP_ANONYMOUS=MAP_ANON

  OPTIMIZEVM = -O3 -funroll-loops -fomit-frame-pointer
  OPTIMIZE = $(OPTIMIZEVM) -ffast-math

  ifeq ($(ARCH),x86_64)
    OPTIMIZEVM = -O3 -fomit-frame-pointer -funroll-loops \
      -falign-functions=2 -fstrength-reduce
    OPTIMIZE = $(OPTIMIZEVM) -ffast-math
    HAVE_VM_COMPILED = true
  else
  ifeq ($(ARCH),x86)
    OPTIMIZEVM = -O3 -march=i586 -fomit-frame-pointer \
      -funroll-loops -falign-functions=2 -fstrength-reduce
    OPTIMIZE = $(OPTIMIZEVM) -ffast-math
    HAVE_VM_COMPILED=true
  else
  ifeq ($(ARCH),ppc)
    BASE_CFLAGS += -maltivec
    HAVE_VM_COMPILED=true
  endif
  ifeq ($(ARCH),ppc64)
    BASE_CFLAGS += -maltivec
    HAVE_VM_COMPILED=true
  endif
  ifeq ($(ARCH),sparc64)
    OPTIMIZE += -mtune=ultrasparc3 -mv8plus
    OPTIMIZEVM += -mtune=ultrasparc3 -mv8plus
    HAVE_VM_COMPILED=true
  endif
  ifeq ($(ARCH),alpha)
    # According to http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=410555
    # -ffast-math will cause the client to die with SIGFPE on Alpha
    OPTIMIZE = $(OPTIMIZEVM)
  endif
  endif
  endif

  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  THREAD_LIBS=-lpthread
  LIBS=-lm
else # ifeq openbsd

#############################################################################
# SETUP AND BUILD -- NETBSD
#############################################################################

ifeq ($(PLATFORM),netbsd)

  LIBS=-lm
  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)
  THREAD_LIBS=-lpthread

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes

  ifeq ($(ARCH),x86)
    HAVE_VM_COMPILED=true
  endif
else # ifeq netbsd

#############################################################################
# SETUP AND BUILD -- IRIX
#############################################################################

ifeq ($(PLATFORM),irix64)

  ARCH=mips

  CC = c99
  MKDIR = mkdir -p

  BASE_CFLAGS=-Dstricmp=strcasecmp -Xcpluscomm -woff 1185 \
    -I. -I$(ROOT)/usr/include
  OPTIMIZE = -O3

  SHLIBEXT=so
  SHLIBCFLAGS=
  SHLIBLDFLAGS=-shared

  LIBS=-ldl -lm -lgen
else # ifeq IRIX

#############################################################################
# SETUP AND BUILD -- SunOS
#############################################################################

ifeq ($(PLATFORM),sunos)

  CC=gcc
  INSTALL=ginstall
  MKDIR=gmkdir
  COPYDIR="/usr/local/share/games/tremulous"

  ifneq ($(ARCH),x86)
    ifneq ($(ARCH),sparc)
      $(error arch $(ARCH) is currently not supported)
    endif
  endif

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes \
    -pipe -DUSE_ICON

  OPTIMIZEVM = -O3 -funroll-loops

  ifeq ($(ARCH),sparc)
    OPTIMIZEVM += -O3 \
      -fstrength-reduce -falign-functions=2 \
      -mtune=ultrasparc3 -mv8plus -mno-faster-structs
    HAVE_VM_COMPILED=true
  else
  ifeq ($(ARCH),x86)
    OPTIMIZEVM += -march=i586 -fomit-frame-pointer \
      -falign-functions=2 -fstrength-reduce
    HAVE_VM_COMPILED=true
    BASE_CFLAGS += -m32
  endif
  endif

  OPTIMIZE = $(OPTIMIZEVM) -ffast-math

  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  THREAD_LIBS=-lpthread
  LIBS=-lsocket -lnsl -ldl -lm
else # ifeq sunos

#############################################################################
# SETUP AND BUILD -- GENERIC
#############################################################################
  BASE_CFLAGS=
  OPTIMIZE = -O3

  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared

endif #Linux
endif #darwin
endif #mingw32
endif #FreeBSD
endif #OpenBSD
endif #NetBSD
endif #IRIX
endif #SunOS

ifndef CC
  CC=gcc
endif

ifndef RANLIB
  RANLIB=ranlib
endif

ifneq ($(HAVE_VM_COMPILED),true)
  BASE_CFLAGS += -DNO_VM_COMPILED
  BUILD_GAME_QVM=0
endif

TARGETS =

ifndef FULLBINEXT
  FULLBINEXT=$(BINEXT)
endif

ifndef SHLIBNAME
  SHLIBNAME=.$(SHLIBEXT)
endif

ifneq ($(BUILD_GAME_SO),0)
  ifeq ($(BUILD_ONLY_GAME),1)
    TARGETS += \
      $(B)/out/$(BASEGAME)/game$(SHLIBNAME)
  else
    ifeq ($(BUILD_ONLY_CGUI),1)
      TARGETS += \
        $(B)/out/$(BASEGAME)/cgame$(SHLIBNAME) \
        $(B)/out/$(BASEGAME)/ui$(SHLIBNAME)
    else
      TARGETS += \
        $(B)/out/$(BASEGAME)/cgame$(SHLIBNAME) \
        $(B)/out/$(BASEGAME)/game$(SHLIBNAME) \
        $(B)/out/$(BASEGAME)/ui$(SHLIBNAME)
    endif
  endif
endif

ifneq ($(BUILD_GAME_QVM),0)
  ifeq ($(BUILD_ONLY_GAME),1)
    TARGETS += \
      $(B)/out/$(BASEGAME)/vm/game.qvm
  else
    ifeq ($(BUILD_ONLY_CGUI),1)
      TARGETS += \
        $(B)/out/$(BASEGAME)/vm/cgame.qvm \
        $(B)/out/$(BASEGAME)/vm/ui.qvm \
        $(B)/out/$(BASEGAME)/vms-gpp1-$(VERSION).pk3
    else
      TARGETS += \
        $(B)/out/$(BASEGAME)/vm/cgame.qvm \
        $(B)/out/$(BASEGAME)/vm/game.qvm \
        $(B)/out/$(BASEGAME)/vm/ui.qvm \
        $(B)/out/$(BASEGAME)/vms-gpp1-$(VERSION).pk3
    endif
  endif
endif

ifneq ($(BUILD_GAME_QVM_11),0)
  ifneq ($(BUILD_ONLY_GAME),1)
    TARGETS += \
      $(B)/out/$(BASEGAME)_11/vm/cgame.qvm \
      $(B)/out/$(BASEGAME)_11/vm/ui.qvm \
      $(B)/out/$(BASEGAME)_11/vms-1.1.0-$(VERSION).pk3
  endif
endif

ifeq ("$(CC)", $(findstring "$(CC)", "clang" "clang++"))
  BASE_CFLAGS += -Qunused-arguments
endif

ifdef DEFAULT_BASEDIR
  BASE_CFLAGS += -DDEFAULT_BASEDIR=\\\"$(DEFAULT_BASEDIR)\\\"
endif

ifeq ($(GENERATE_DEPENDENCIES),1)
  DEPEND_CFLAGS = -MMD
else
  DEPEND_CFLAGS =
endif

ifeq ($(NO_STRIP),1)
  STRIP_FLAG =
else
  STRIP_FLAG = -s
endif

BASE_CFLAGS += -DPRODUCT_VERSION=\\\"$(VERSION)\\\"

ifeq ($(V),1)
echo_cmd=@:
Q=
else
echo_cmd=@echo
Q=@
endif

ifeq ($(GENERATE_DEPENDENCIES),1)
  DO_QVM_DEP=cat $(@:%.o=%.d) | sed -e 's/\.o/\.asm/g' >> $(@:%.o=%.d)
endif

define DO_SHLIB_CC
$(echo_cmd) "SHLIB_CC $<"
$(Q)$(CC) $(BASEGAME_CFLAGS) $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZEVM) -o $@ -c $<
$(Q)$(DO_QVM_DEP)
endef

define DO_GAME_CC
$(echo_cmd) "GAME_CC $<"
$(Q)$(CC) $(BASEGAME_CFLAGS) -DGAME $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZEVM) -o $@ -c $<
$(Q)$(DO_QVM_DEP)
endef

define DO_CGAME_CC
$(echo_cmd) "CGAME_CC $<"
$(Q)$(CC) $(BASEGAME_CFLAGS) -DCGAME $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZEVM) -o $@ -c $<
$(Q)$(DO_QVM_DEP)
endef

define DO_UI_CC
$(echo_cmd) "UI_CC $<"
$(Q)$(CC) $(BASEGAME_CFLAGS) -DUI $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZEVM) -o $@ -c $<
$(Q)$(DO_QVM_DEP)
endef

define DO_AS
$(echo_cmd) "AS $<"
$(Q)$(CC) $(CFLAGS) $(OPTIMIZE) -x assembler-with-cpp -o $@ -c $<
endef


#############################################################################
# MAIN TARGETS
#############################################################################

default: release
all: debug release

debug:
	@$(MAKE) targets B=$(BD) CFLAGS="$(CFLAGS) $(BASE_CFLAGS) $(DEPEND_CFLAGS)" \
	  OPTIMIZE="$(DEBUG_CFLAGS)" OPTIMIZEVM="$(DEBUG_CFLAGS)" V=$(V)

release:
	@$(MAKE) targets B=$(BR) CFLAGS="$(CFLAGS) $(BASE_CFLAGS) $(DEPEND_CFLAGS)" \
	  OPTIMIZE="-DNDEBUG $(OPTIMIZE)" OPTIMIZEVM="-DNDEBUG $(OPTIMIZEVM)" V=$(V)

ifneq ($(call bin_path, tput),)
  TERM_COLUMNS=$(shell echo $$((`tput cols`-4)))
else
  TERM_COLUMNS=76
endif

NAKED_TARGETS=$(shell echo $(TARGETS) | sed -e "s!$(B)/!!g")

print_list=@for i in $(1); \
     do \
             echo "    $$i"; \
     done

ifneq ($(call bin_path, fmt),)
  print_wrapped=@echo $(1) | fmt -w $(TERM_COLUMNS) | sed -e "s/^\(.*\)$$/    \1/"
else
  print_wrapped=$(print_list)
endif

# Create the build directories, check libraries and print out
# an informational message, then start building
targets: makedirs
	@echo ""
	@echo "Building in $(B):"
	@echo "  PLATFORM: $(PLATFORM)"
	@echo "  ARCH: $(ARCH)"
	@echo "  VERSION: $(VERSION)"
	@echo "  COMPILE_PLATFORM: $(COMPILE_PLATFORM)"
	@echo "  COMPILE_ARCH: $(COMPILE_ARCH)"
	@echo "  CC: $(CC)"
	@echo ""
	@echo "  CFLAGS:"
	$(call print_wrapped, $(CFLAGS) $(OPTIMIZE))
	@echo ""
	@echo "  LDFLAGS:"
	$(call print_wrapped, $(LDFLAGS))
	@echo ""
	@echo "  LIBS:"
	$(call print_wrapped, $(LIBS))
	@echo ""
	@echo "  Output:"
	$(call print_list, $(NAKED_TARGETS))
	@echo ""
ifneq ($(TARGETS),)
  ifndef DEBUG_MAKEFILE
	@$(MAKE) $(TARGETS) V=$(V)
  endif
endif

makedirs:
	@if [ ! -d $(BUILD_DIR) ];then $(MKDIR) $(BUILD_DIR);fi
	@if [ ! -d $(B) ];then $(MKDIR) $(B);fi
	@if [ ! -d $(B)/cgame ];then $(MKDIR) $(B)/cgame;fi
	@if [ ! -d $(B)/game ];then $(MKDIR) $(B)/game;fi
	@if [ ! -d $(B)/ui ];then $(MKDIR) $(B)/ui;fi
	@if [ ! -d $(B)/qcommon ];then $(MKDIR) $(B)/qcommon;fi
	@if [ ! -d $(B)/11 ];then $(MKDIR) $(B)/11;fi
	@if [ ! -d $(B)/11/cgame ];then $(MKDIR) $(B)/11/cgame;fi
	@if [ ! -d $(B)/11/ui ];then $(MKDIR) $(B)/11/ui;fi
	@if [ ! -d $(B)/out ];then $(MKDIR) $(B)/out;fi
	@if [ ! -d $(B)/out/$(BASEGAME) ];then $(MKDIR) $(B)/out/$(BASEGAME);fi
	@if [ ! -d $(B)/out/$(BASEGAME)/vm ];then $(MKDIR) $(B)/out/$(BASEGAME)/vm;fi
	@if [ ! -d $(B)/out/$(BASEGAME)_11 ];then $(MKDIR) $(B)/out/$(BASEGAME)_11;fi
	@if [ ! -d $(B)/out/$(BASEGAME)_11/vm ];then $(MKDIR) $(B)/out/$(BASEGAME)_11/vm;fi
	@if [ ! -d $(B)/tools ];then $(MKDIR) $(B)/tools;fi
	@if [ ! -d $(B)/tools/asm ];then $(MKDIR) $(B)/tools/asm;fi
	@if [ ! -d $(B)/tools/etc ];then $(MKDIR) $(B)/tools/etc;fi
	@if [ ! -d $(B)/tools/rcc ];then $(MKDIR) $(B)/tools/rcc;fi
	@if [ ! -d $(B)/tools/cpp ];then $(MKDIR) $(B)/tools/cpp;fi
	@if [ ! -d $(B)/tools/lburg ];then $(MKDIR) $(B)/tools/lburg;fi

#############################################################################
# QVM BUILD TOOLS
#############################################################################

ifndef TOOLS_CC
  # A compiler which probably produces native binaries
  TOOLS_CC=$(CC)
endif

TOOLS_OPTIMIZE = -g -Wall -fno-strict-aliasing
TOOLS_CFLAGS += $(TOOLS_OPTIMIZE) \
                -DTEMPDIR=\"$(TEMPDIR)\" -DSYSTEM=\"\" \
                -I$(Q3LCCSRCDIR) \
                -I$(LBURGDIR)
TOOLS_LIBS =
TOOLS_LDFLAGS =

ifeq ($(GENERATE_DEPENDENCIES),1)
  TOOLS_CFLAGS += -MMD
endif

define DO_TOOLS_CC
$(echo_cmd) "TOOLS_CC $<"
$(Q)$(TOOLS_CC) $(TOOLS_CFLAGS) -o $@ -c $<
endef

define DO_TOOLS_CC_DAGCHECK
$(echo_cmd) "TOOLS_CC_DAGCHECK $<"
$(Q)$(TOOLS_CC) $(TOOLS_CFLAGS) -Wno-unused -o $@ -c $<
endef

LBURG       = $(B)/tools/lburg/lburg$(TOOLS_BINEXT)
DAGCHECK_C  = $(B)/tools/rcc/dagcheck.c
Q3RCC       = $(B)/tools/q3rcc$(TOOLS_BINEXT)
Q3CPP       = $(B)/tools/q3cpp$(TOOLS_BINEXT)
Q3LCC       = $(B)/tools/q3lcc$(TOOLS_BINEXT)
Q3ASM       = $(B)/tools/q3asm$(TOOLS_BINEXT)

LBURGOBJ= \
  $(B)/tools/lburg/lburg.o \
  $(B)/tools/lburg/gram.o

$(B)/tools/lburg/%.o: $(LBURGDIR)/%.c
	$(DO_TOOLS_CC)

$(LBURG): $(LBURGOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(TOOLS_CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)

Q3RCCOBJ = \
  $(B)/tools/rcc/alloc.o \
  $(B)/tools/rcc/bind.o \
  $(B)/tools/rcc/bytecode.o \
  $(B)/tools/rcc/dag.o \
  $(B)/tools/rcc/dagcheck.o \
  $(B)/tools/rcc/decl.o \
  $(B)/tools/rcc/enode.o \
  $(B)/tools/rcc/error.o \
  $(B)/tools/rcc/event.o \
  $(B)/tools/rcc/expr.o \
  $(B)/tools/rcc/gen.o \
  $(B)/tools/rcc/init.o \
  $(B)/tools/rcc/inits.o \
  $(B)/tools/rcc/input.o \
  $(B)/tools/rcc/lex.o \
  $(B)/tools/rcc/list.o \
  $(B)/tools/rcc/main.o \
  $(B)/tools/rcc/null.o \
  $(B)/tools/rcc/output.o \
  $(B)/tools/rcc/prof.o \
  $(B)/tools/rcc/profio.o \
  $(B)/tools/rcc/simp.o \
  $(B)/tools/rcc/stmt.o \
  $(B)/tools/rcc/string.o \
  $(B)/tools/rcc/sym.o \
  $(B)/tools/rcc/symbolic.o \
  $(B)/tools/rcc/trace.o \
  $(B)/tools/rcc/tree.o \
  $(B)/tools/rcc/types.o

$(DAGCHECK_C): $(LBURG) $(Q3LCCSRCDIR)/dagcheck.md
	$(echo_cmd) "LBURG $(Q3LCCSRCDIR)/dagcheck.md"
	$(Q)$(LBURG) $(Q3LCCSRCDIR)/dagcheck.md $@

$(B)/tools/rcc/dagcheck.o: $(DAGCHECK_C)
	$(DO_TOOLS_CC_DAGCHECK)

$(B)/tools/rcc/%.o: $(Q3LCCSRCDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3RCC): $(Q3RCCOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(TOOLS_CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)

Q3CPPOBJ = \
  $(B)/tools/cpp/cpp.o \
  $(B)/tools/cpp/lex.o \
  $(B)/tools/cpp/nlist.o \
  $(B)/tools/cpp/tokens.o \
  $(B)/tools/cpp/macro.o \
  $(B)/tools/cpp/eval.o \
  $(B)/tools/cpp/include.o \
  $(B)/tools/cpp/hideset.o \
  $(B)/tools/cpp/getopt.o \
  $(B)/tools/cpp/unix.o

$(B)/tools/cpp/%.o: $(Q3CPPDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3CPP): $(Q3CPPOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(TOOLS_CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)

Q3LCCOBJ = \
	$(B)/tools/etc/lcc.o \
	$(B)/tools/etc/bytecode.o

$(B)/tools/etc/%.o: $(Q3LCCETCDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3LCC): $(Q3LCCOBJ) $(Q3RCC) $(Q3CPP)
	$(echo_cmd) "LD $@"
	$(Q)$(TOOLS_CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $(Q3LCCOBJ) $(TOOLS_LIBS)

define DO_Q3LCC
$(echo_cmd) "Q3LCC $<"
$(Q)$(Q3LCC) $(BASEGAME_CFLAGS) -o $@ $<
endef

define DO_CGAME_Q3LCC
$(echo_cmd) "CGAME_Q3LCC $<"
$(Q)$(Q3LCC) $(BASEGAME_CFLAGS) -DCGAME -o $@ $<
endef

define DO_CGAME_Q3LCC_11
$(echo_cmd) "CGAME_Q3LCC_11 $<"
$(Q)$(Q3LCC) $(BASEGAME_CFLAGS) -DCGAME -DMODULE_INTERFACE_11 -o $@ $<
endef

define DO_GAME_Q3LCC
$(echo_cmd) "GAME_Q3LCC $<"
$(Q)$(Q3LCC) $(BASEGAME_CFLAGS) -DGAME -o $@ $<
endef

define DO_UI_Q3LCC
$(echo_cmd) "UI_Q3LCC $<"
$(Q)$(Q3LCC) $(BASEGAME_CFLAGS) -DUI -o $@ $<
endef

define DO_UI_Q3LCC_11
$(echo_cmd) "UI_Q3LCC_11 $<"
$(Q)$(Q3LCC) $(BASEGAME_CFLAGS) -DUI -DMODULE_INTERFACE_11 -o $@ $<
endef


Q3ASMOBJ = \
  $(B)/tools/asm/q3asm.o \
  $(B)/tools/asm/cmdlib.o

$(B)/tools/asm/%.o: $(Q3ASMDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3ASM): $(Q3ASMOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(TOOLS_CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)


#############################################################################
## TREMULOUS CGAME
#############################################################################

CGOBJ_ = \
  $(B)/cgame/cg_main.o \
  $(B)/cgame/bg_misc.o \
  $(B)/cgame/bg_pmove.o \
  $(B)/cgame/bg_slidemove.o \
  $(B)/cgame/cg_consolecmds.o \
  $(B)/cgame/cg_buildable.o \
  $(B)/cgame/cg_animation.o \
  $(B)/cgame/cg_animmapobj.o \
  $(B)/cgame/cg_draw.o \
  $(B)/cgame/cg_drawtools.o \
  $(B)/cgame/cg_ents.o \
  $(B)/cgame/cg_event.o \
  $(B)/cgame/cg_marks.o \
  $(B)/cgame/cg_players.o \
  $(B)/cgame/cg_playerstate.o \
  $(B)/cgame/cg_predict.o \
  $(B)/cgame/cg_servercmds.o \
  $(B)/cgame/cg_snapshot.o \
  $(B)/cgame/cg_view.o \
  $(B)/cgame/cg_weapons.o \
  $(B)/cgame/cg_mem.o \
  $(B)/cgame/cg_scanner.o \
  $(B)/cgame/cg_attachment.o \
  $(B)/cgame/cg_trails.o \
  $(B)/cgame/cg_particles.o \
  $(B)/cgame/cg_ptr.o \
  $(B)/cgame/cg_tutorial.o \
  $(B)/cgame/ui_shared.o \
  \
  $(B)/qcommon/q_math.o \
  $(B)/qcommon/q_shared.o

CGOBJ11_ = \
  $(B)/11/cgame/cg_main.o \
  $(B)/cgame/bg_misc.o \
  $(B)/cgame/bg_pmove.o \
  $(B)/cgame/bg_slidemove.o \
  $(B)/cgame/cg_consolecmds.o \
  $(B)/cgame/cg_buildable.o \
  $(B)/cgame/cg_animation.o \
  $(B)/cgame/cg_animmapobj.o \
  $(B)/cgame/cg_draw.o \
  $(B)/cgame/cg_drawtools.o \
  $(B)/cgame/cg_ents.o \
  $(B)/cgame/cg_event.o \
  $(B)/cgame/cg_marks.o \
  $(B)/cgame/cg_players.o \
  $(B)/cgame/cg_playerstate.o \
  $(B)/cgame/cg_predict.o \
  $(B)/11/cgame/cg_servercmds.o \
  $(B)/11/cgame/cg_snapshot.o \
  $(B)/cgame/cg_view.o \
  $(B)/cgame/cg_weapons.o \
  $(B)/cgame/cg_mem.o \
  $(B)/cgame/cg_scanner.o \
  $(B)/cgame/cg_attachment.o \
  $(B)/cgame/cg_trails.o \
  $(B)/cgame/cg_particles.o \
  $(B)/cgame/cg_ptr.o \
  $(B)/cgame/cg_tutorial.o \
  $(B)/cgame/ui_shared.o \
  \
  $(B)/qcommon/q_math.o \
  $(B)/qcommon/q_shared.o

CGOBJ = $(CGOBJ_) $(B)/cgame/cg_syscalls.o
CGVMOBJ = $(CGOBJ_:%.o=%.asm) $(B)/cgame/bg_lib.asm
CGVMOBJ11 = $(CGOBJ11_:%.o=%.asm) $(B)/cgame/bg_lib.asm

$(B)/out/$(BASEGAME)/cgame$(SHLIBNAME): $(CGOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(CGOBJ)

$(B)/out/$(BASEGAME)/vm/cgame.qvm: $(CGVMOBJ) $(CGDIR)/cg_syscalls.asm $(Q3ASM)
	$(echo_cmd) "Q3ASM $@"
	$(Q)$(Q3ASM) -o $@ $(CGVMOBJ) $(CGDIR)/cg_syscalls.asm

$(B)/out/$(BASEGAME)_11/vm/cgame.qvm: $(CGVMOBJ11) $(CGDIR)/cg_syscalls_11.asm $(Q3ASM)
	$(echo_cmd) "Q3ASM $@"
	$(Q)$(Q3ASM) -o $@ $(CGVMOBJ11) $(CGDIR)/cg_syscalls_11.asm



#############################################################################
## TREMULOUS GAME
#############################################################################

GOBJ_ = \
  $(B)/game/g_main.o \
  $(B)/game/bg_misc.o \
  $(B)/game/bg_pmove.o \
  $(B)/game/bg_slidemove.o \
  $(B)/game/g_mem.o \
  $(B)/game/g_active.o \
  $(B)/game/g_client.o \
  $(B)/game/g_cmds.o \
  $(B)/game/g_combat.o \
  $(B)/game/g_physics.o \
  $(B)/game/g_buildable.o \
  $(B)/game/g_misc.o \
  $(B)/game/g_missile.o \
  $(B)/game/g_mover.o \
  $(B)/game/g_session.o \
  $(B)/game/g_spawn.o \
  $(B)/game/g_svcmds.o \
  $(B)/game/g_target.o \
  $(B)/game/g_team.o \
  $(B)/game/g_trigger.o \
  $(B)/game/g_utils.o \
  $(B)/game/g_maprotation.o \
  $(B)/game/g_ptr.o \
  $(B)/game/g_weapon.o \
  $(B)/game/g_admin.o \
  \
  $(B)/qcommon/q_math.o \
  $(B)/qcommon/q_shared.o

GOBJ = $(GOBJ_) $(B)/game/g_syscalls.o
GVMOBJ = $(GOBJ_:%.o=%.asm) $(B)/game/bg_lib.asm

$(B)/out/$(BASEGAME)/game$(SHLIBNAME): $(GOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(GOBJ)

$(B)/out/$(BASEGAME)/vm/game.qvm: $(GVMOBJ) $(GDIR)/g_syscalls.asm $(Q3ASM)
	$(echo_cmd) "Q3ASM $@"
	$(Q)$(Q3ASM) -o $@ $(GVMOBJ) $(GDIR)/g_syscalls.asm



#############################################################################
## TREMULOUS UI
#############################################################################

UIOBJ_ = \
  $(B)/ui/ui_main.o \
  $(B)/ui/ui_atoms.o \
  $(B)/ui/ui_players.o \
  $(B)/ui/ui_shared.o \
  $(B)/ui/ui_gameinfo.o \
  \
  $(B)/ui/bg_misc.o \
  $(B)/qcommon/q_math.o \
  $(B)/qcommon/q_shared.o

UIOBJ11_ = \
  $(B)/11/ui/ui_main.o \
  $(B)/ui/ui_atoms.o \
  $(B)/ui/ui_players.o \
  $(B)/ui/ui_shared.o \
  $(B)/ui/ui_gameinfo.o \
  \
  $(B)/ui/bg_misc.o \
  $(B)/qcommon/q_math.o \
  $(B)/qcommon/q_shared.o

UIOBJ = $(UIOBJ_) $(B)/ui/ui_syscalls.o
UIVMOBJ = $(UIOBJ_:%.o=%.asm) $(B)/ui/bg_lib.asm
UIVMOBJ11 = $(UIOBJ11_:%.o=%.asm) $(B)/ui/bg_lib.asm

$(B)/out/$(BASEGAME)/ui$(SHLIBNAME): $(UIOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(UIOBJ)

$(B)/out/$(BASEGAME)/vm/ui.qvm: $(UIVMOBJ) $(UIDIR)/ui_syscalls.asm $(Q3ASM)
	$(echo_cmd) "Q3ASM $@"
	$(Q)$(Q3ASM) -o $@ $(UIVMOBJ) $(UIDIR)/ui_syscalls.asm

$(B)/out/$(BASEGAME)_11/vm/ui.qvm: $(UIVMOBJ11) $(UIDIR)/ui_syscalls_11.asm $(Q3ASM)
	$(echo_cmd) "Q3ASM $@"
	$(Q)$(Q3ASM) -o $@ $(UIVMOBJ11) $(UIDIR)/ui_syscalls_11.asm


#############################################################################
## QVM Package
#############################################################################
  
$(B)/out/$(BASEGAME)/vms-gpp1-$(VERSION).pk3: $(B)/out/$(BASEGAME)/vm/ui.qvm $(B)/out/$(BASEGAME)/vm/cgame.qvm $(B)/out/$(BASEGAME)/vm/game.qvm
	@(cd $(B)/out/$(BASEGAME) && zip -r vms-gpp1-$(VERSION).pk3 vm/)

$(B)/out/$(BASEGAME)_11/vms-1.1.0-$(VERSION).pk3: $(B)/out/$(BASEGAME)_11/vm/ui.qvm $(B)/out/$(BASEGAME)_11/vm/cgame.qvm
	@(cd $(B)/out/$(BASEGAME)_11 && zip -r vms-1.1.0-$(VERSION).pk3 vm/)
 
#############################################################################
## Assets Package
#############################################################################

$(B)/out/$(BASEGAME)/data-$(VERSION).pk3: $(ASSETS_DIR)/ui/main.menu
	@(cd $(ASSETS_DIR) && zip -r data-$(VERSION).pk3 *)
	@mv $(ASSETS_DIR)/data-$(VERSION).pk3 $(B)/out/$(BASEGAME)

#############################################################################
## GAME MODULE RULES
#############################################################################

$(B)/cgame/bg_%.o: $(GDIR)/bg_%.c
	$(DO_CGAME_CC)

$(B)/cgame/ui_%.o: $(UIDIR)/ui_%.c
	$(DO_CGAME_CC)

$(B)/cgame/%.o: $(CGDIR)/%.c
	$(DO_CGAME_CC)

$(B)/cgame/bg_%.asm: $(GDIR)/bg_%.c $(Q3LCC)
	$(DO_CGAME_Q3LCC)

$(B)/cgame/ui_%.asm: $(UIDIR)/ui_%.c $(Q3LCC)
	$(DO_CGAME_Q3LCC)

$(B)/cgame/%.asm: $(CGDIR)/%.c $(Q3LCC)
	$(DO_CGAME_Q3LCC)

$(B)/11/cgame/%.asm: $(CGDIR)/%.c $(Q3LCC)
	$(DO_CGAME_Q3LCC_11)


$(B)/game/%.o: $(GDIR)/%.c
	$(DO_GAME_CC)

$(B)/game/%.asm: $(GDIR)/%.c $(Q3LCC)
	$(DO_GAME_Q3LCC)


$(B)/ui/bg_%.o: $(GDIR)/bg_%.c
	$(DO_UI_CC)

$(B)/ui/%.o: $(UIDIR)/%.c
	$(DO_UI_CC)

$(B)/ui/bg_%.asm: $(GDIR)/bg_%.c $(Q3LCC)
	$(DO_UI_Q3LCC)

$(B)/ui/%.asm: $(UIDIR)/%.c $(Q3LCC)
	$(DO_UI_Q3LCC)

$(B)/11/ui/%.asm: $(UIDIR)/%.c $(Q3LCC)
	$(DO_UI_Q3LCC_11)


$(B)/qcommon/%.o: $(CMDIR)/%.c
	$(DO_SHLIB_CC)

$(B)/qcommon/%.asm: $(CMDIR)/%.c $(Q3LCC)
	$(DO_Q3LCC)


#############################################################################
# MISC
#############################################################################

OBJ = $(GOBJ) $(CGOBJ) $(UIOBJ) $(CGOBJ11) $(UIOBJ11) \
  $(GVMOBJ) $(CGVMOBJ) $(UIVMOBJ) $(CGVMOBJ11) $(UIVMOBJ11)
TOOLSOBJ = $(LBURGOBJ) $(Q3CPPOBJ) $(Q3RCCOBJ) $(Q3LCCOBJ) $(Q3ASMOBJ)
STRINGOBJ = $(Q3R2STRINGOBJ)

clean: clean-debug clean-release
	@$(MAKE) -C $(MASTERDIR) clean

clean-debug:
	@$(MAKE) clean2 B=$(BD)

clean-release:
	@$(MAKE) clean2 B=$(BR)

clean2:
	@echo "CLEAN $(B)"
	@rm -f $(OBJ)
	@rm -f $(OBJ_D_FILES)
	@rm -f $(STRINGOBJ)
	@rm -f $(TARGETS)

toolsclean: toolsclean-debug toolsclean-release

toolsclean-debug:
	@$(MAKE) toolsclean2 B=$(BD)

toolsclean-release:
	@$(MAKE) toolsclean2 B=$(BR)

toolsclean2:
	@echo "TOOLS_CLEAN $(B)"
	@rm -f $(TOOLSOBJ)
	@rm -f $(TOOLSOBJ_D_FILES)
	@rm -f $(LBURG) $(DAGCHECK_C) $(Q3RCC) $(Q3CPP) $(Q3LCC) $(Q3ASM)

distclean: clean toolsclean
	@rm -rf $(BUILD_DIR)

dist:
	git archive --format zip --output $(CLIENTBIN)-$(VERSION).zip HEAD

#############################################################################
# DEPENDENCIES
#############################################################################

ifneq ($(B),)
  OBJ_D_FILES=$(filter %.d,$(OBJ:%.o=%.d))
  TOOLSOBJ_D_FILES=$(filter %.d,$(TOOLSOBJ:%.o=%.d))
  -include $(OBJ_D_FILES) $(TOOLSOBJ_D_FILES)
endif

.PHONY: all clean clean2 clean-debug clean-release copyfiles \
	debug default dist distclean makedirs \
	release targets \
	toolsclean toolsclean2 toolsclean-debug toolsclean-release \
	$(OBJ_D_FILES) $(TOOLSOBJ_D_FILES)

# If the target name contains "clean", don't do a parallel build
ifneq ($(findstring clean, $(MAKECMDGOALS)),)
.NOTPARALLEL:
endif
