# ============================================================================
#  Name	 : build_help.mk
#  Part of  : NPR
# ============================================================================
#  Name	 : build_help.mk
#  Part of  : NPR
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

# build the help from the MAKMAKE step so the header file generated
# will be found by cpp.exe when calculating the dependency information
# in the mmp makefiles.

MAKMAKE : NPR_0xEEB0E481.hlp
NPR_0xEEB0E481.hlp : NPR.xml NPR.cshlp Custom.xml
	cshlpcmp NPR.cshlp
ifeq (WINSCW,$(findstring WINSCW, $(PLATFORM)))
	md $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy NPR_0xEEB0E481.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del NPR_0xEEB0E481.hlp
	del NPR_0xEEB0E481.hlp.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo NPR_0xEEB0E481.hlp

FINAL : do_nothing
