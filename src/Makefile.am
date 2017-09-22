# Copyright (c) 2013 Dave Freese, W1HKJ (w1hkj AT w1hkj DOT com)

bin_PROGRAMS = comptext

comptext_cxxFLAGS = @comptext_BUILD_cxxFLAGS@
comptext_CXXFLAGS = @comptext_BUILD_CXXFLAGS@
comptext_CFLAGS = $(comptext_CXXFLAGS)
comptext_LDFLAGS = @comptext_BUILD_LDFLAGS@
comptext_LDADD = @comptext_BUILD_LDADD@

MINGW32_SRC = \
	comptext.rc \
	include/comptextrc.h

# We distribute these but do not always compile them
EXTRA_comptext_SOURCES = $(comptext_WIN32_RES_SRC) $(MINGW32_SRC)

comptext_SOURCES =

if MINGW32
if HAVE_WINDRES
  comptext_SOURCES += $(MINGW32_SRC)
endif
endif

########################################################################


comptext_VERSION_MAJOR = @comptext_VERSION_MAJOR@
comptext_VERSION_MINOR = @comptext_VERSION_MINOR@
comptext_VERSION_PATCH = @comptext_VERSION_PATCH@
comptext_VERSION = @comptext_VERSION@

.EXPORT_ALL_VARIABLES: nsisinst appbundle

# Sources that are generated,
BUILT_SOURCES =
# not distributed,
nodist_comptext_SOURCES = $(BUILT_SOURCES)
# and deleted by the clean targets
CLEANFILES = $(BUILT_SOURCES)
CLEAN_LOCAL =

if MINGW32
if HAVE_WINDRES
.rc.o:
	$(WINDRES) -I$(srcdir)/include -I$(srcdir)/../data/win32 $< -O coff $@
endif
endif

install-data-local:
	if test -f $(srcdir)/../data/comptext.xpm; then \
	    $(mkinstalldirs) $(DESTDIR)/$(datadir)/pixmaps; \
	    $(INSTALL_DATA) $(srcdir)/../data/comptext.xpm $(DESTDIR)/$(datadir)/pixmaps; \
	fi
	if test -f $(srcdir)/../data/comptext.desktop; then \
	    $(mkinstalldirs) $(DESTDIR)/$(datadir)/applications; \
	    $(INSTALL_DATA) $(srcdir)/../data/comptext.desktop $(DESTDIR)/$(datadir)/applications; \
	fi

uninstall-local:
	rm -f $(DESTDIR)/$(datadir)/pixmaps/comptext.xpm
	rm -f $(DESTDIR)/$(datadir)/applications/comptext.desktop

FL_SRC = comp_ui.fl

if HAVE_FLUID
flgen: $(FL_SRC)
	(cd $(srcdir)/include; \
	for f in $(FL_SRC); do \
	    c=$${f%.fl}.cxx; \
		h=$${f%.fl}.h; \
		h=$${h##*/}; \
	    $(FLUID) -c -o ../$$c -h $$h ../$$f; \
	done)
endif


INSTALLER_FILE = comptext-$(comptext_VERSION)_setup.exe
APPBUNDLE=comptext-$(comptext_VERSION)
APPBUNDLE_NOLIBS=$(APPBUNDLE)-nolibs

if HAVE_NSIS
nsisinst: $(bin_PROGRAMS)
	sh $(srcdir)/../scripts/mknsisinst.sh "$(srcdir)/../data" .
    CLEANFILES += $(INSTALLER_FILE)
endif

if DARWIN
appbundle: $(bin_PROGRAMS)
	sh $(srcdir)/../scripts/mkappbundle.sh "$(srcdir)/../data" .
    CLEAN_LOCAL += $(APPBUNDLE_NOLIBS) $(APPBUNDLE) $(APPBUNDLE)*.dmg
endif

clean-local:
	-rm -rf $(CLEAN_LOCAL)

# Sources that we build. It is OK to have headers here.
comptext_SOURCES += \
	main.cxx \
	comp_txt.cxx \
	comp_ui.cxx \
	include/comp_txt.h  \
	include/comp_ui.h \
	include/compat.h \
	include/compat-mingw.h

# Additional source files that are distributed
EXTRA_DIST = \
	comptext.rc \
	comp_ui.fl \
	comptext_icon.cxx \
	include/comptextrc.h

# Additional non-source files that are distributed
# Additional source files that support non-Linux cross compilation
EXTRA_DIST += \
	$(srcdir)/../data/comptext.desktop \
	$(srcdir)/../data/comptext.xpm \
	$(srcdir)/../data/win32/fl_app.nsi \
	$(srcdir)/../data/win32/comptext.ico \
	$(srcdir)/../scripts/mknsisinst.sh \
	$(srcdir)/../scripts/build4mingw.sh \
	$(srcdir)/../data/mac/Info.plist.in \
	$(srcdir)/../data/mac/comptext.icns \
	$(srcdir)/../scripts/mkappbundle.sh \
	$(comptext_WIN32_SRC) \
	$(comptext_FL_SRC)
