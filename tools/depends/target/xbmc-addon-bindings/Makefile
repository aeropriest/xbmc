include ../../Makefile.include
DEPS= ../../Makefile.include Makefile

# sync with <xbmc root>Makefile.in
BINDINGS =xbmc/addons/include/xbmc_addon_cpp_dll.h
BINDINGS+=xbmc/addons/include/xbmc_addon_dll.h
BINDINGS+=xbmc/addons/include/xbmc_addon_types.h
BINDINGS+=xbmc/addons/include/xbmc_epg_types.h
BINDINGS+=xbmc/addons/include/xbmc_pvr_dll.h
BINDINGS+=xbmc/addons/include/xbmc_pvr_types.h
BINDINGS+=xbmc/addons/include/xbmc_scr_dll.h
BINDINGS+=xbmc/addons/include/xbmc_scr_types.h
BINDINGS+=xbmc/addons/include/xbmc_vis_dll.h
BINDINGS+=xbmc/addons/include/xbmc_vis_types.h
BINDINGS+=addons/library.xbmc.addon/libXBMC_addon.h
BINDINGS+=addons/library.xbmc.gui/libXBMC_gui.h
BINDINGS+=addons/library.xbmc.pvr/libXBMC_pvr.h

all: .installed-$(PLATFORM)

.installed-$(PLATFORM): $(DEPS)
	@echo "Copy addon bindings to $(PREFIX)/include/xbmc"
	@mkdir -p $(PREFIX)/include/xbmc
	@for f in $(BINDINGS); do \
	  cp -f $(XBMCROOT)/$$f $(PREFIX)/include/xbmc ; \
	done
	@touch $@

clean:
	@rm -rf .installed-$(PLATFORM) $(PREFIX)/include/xbmc

distclean:: clean
