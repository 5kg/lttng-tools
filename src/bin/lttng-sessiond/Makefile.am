AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src \
			  -DINSTALL_BIN_PATH=\""$(lttnglibexecdir)"\" \
			  -DINSTALL_LIB_PATH=\""$(libdir)"\"

AM_CFLAGS = -fno-strict-aliasing

bin_PROGRAMS = lttng-sessiond

lttng_sessiond_SOURCES = utils.c utils.h \
                       trace-kernel.c trace-kernel.h \
                       kernel.c kernel.h \
                       ust-ctl.h ust-app.h trace-ust.h ust-thread.h \
                       ust-registry.h \
                       context.c context.h \
                       channel.c channel.h \
                       event.c event.h \
                       shm.c shm.h \
                       consumer.c consumer.h \
                       session.c session.h \
                       modprobe.c modprobe.h kern-modules.h \
                       lttng-ust-ctl.h lttng-ust-abi.h lttng-ust-error.h \
                       fd-limit.c fd-limit.h \
                       kernel-consumer.c kernel-consumer.h \
                       consumer.h \
                       health-sessiond.h \
                       cmd.c cmd.h \
                       buffer-registry.c buffer-registry.h \
                       testpoint.h ht-cleanup.c \
                       snapshot.c snapshot.h \
                       jul.c jul.h \
                       save.h save.c

if HAVE_LIBLTTNG_UST_CTL
lttng_sessiond_SOURCES += trace-ust.c ust-registry.c ust-app.c \
			ust-consumer.c ust-consumer.h ust-thread.c \
			ust-metadata.c ust-clock.h jul-thread.c jul-thread.h
endif

# Add main.c at the end for compile order
lttng_sessiond_SOURCES += lttng-sessiond.h main.c

# link on liblttngctl for check if sessiond is already alive.
lttng_sessiond_LDADD = -lrt -lurcu-common -lurcu \
		$(top_builddir)/src/lib/lttng-ctl/liblttng-ctl.la \
		$(top_builddir)/src/common/sessiond-comm/libsessiond-comm.la \
		$(top_builddir)/src/common/kernel-ctl/libkernel-ctl.la \
		$(top_builddir)/src/common/hashtable/libhashtable.la \
		$(top_builddir)/src/common/libcommon.la \
		$(top_builddir)/src/common/compat/libcompat.la \
		$(top_builddir)/src/common/relayd/librelayd.la \
		$(top_builddir)/src/common/testpoint/libtestpoint.la \
		$(top_builddir)/src/common/health/libhealth.la \
		$(top_builddir)/src/common/config/libconfig.la


if HAVE_LIBLTTNG_UST_CTL
lttng_sessiond_LDADD += -llttng-ust-ctl
endif
