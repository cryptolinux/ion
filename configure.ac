m4_define([libunivalue_major_version], [1])
m4_define([libunivalue_minor_version], [1])
m4_define([libunivalue_micro_version], [2])
m4_define([libunivalue_interface_age], [2])
# If you need a modifier for the version number. 
# Normally empty, but can be used to make "fixup" releases.
m4_define([libunivalue_extraversion], [])

dnl libtool versioning from libunivalue
m4_define([libunivalue_current], [m4_eval(100 * libunivalue_minor_version + libunivalue_micro_version - libunivalue_interface_age)])
m4_define([libunivalue_binary_age], [m4_eval(100 * libunivalue_minor_version + libunivalue_micro_version)])
m4_define([libunivalue_revision], [libunivalue_interface_age])
m4_define([libunivalue_age], [m4_eval(libunivalue_binary_age - libunivalue_interface_age)])
m4_define([libunivalue_version], [libunivalue_major_version().libunivalue_minor_version().libunivalue_micro_version()libunivalue_extraversion()])


AC_INIT([univalue], [1.0.2],
        [http://github.com/jgarzik/univalue/])

dnl make the compilation flags quiet unless V=1 is used
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_PREREQ(2.60)
AC_CONFIG_SRCDIR([lib/univalue.cpp])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])
AC_CONFIG_HEADERS([univalue-config.h])
AM_INIT_AUTOMAKE([subdir-objects foreign])

LIBUNIVALUE_MAJOR_VERSION=libunivalue_major_version
LIBUNIVALUE_MINOR_VERSION=libunivalue_minor_version
LIBUNIVALUE_MICRO_VERSION=libunivalue_micro_version
LIBUNIVALUE_INTERFACE_AGE=libunivalue_interface_age

# ABI version
# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
LIBUNIVALUE_CURRENT=libunivalue_current
LIBUNIVALUE_REVISION=libunivalue_revision
LIBUNIVALUE_AGE=libunivalue_age

AC_SUBST(LIBUNIVALUE_CURRENT)
AC_SUBST(LIBUNIVALUE_REVISION)
AC_SUBST(LIBUNIVALUE_AGE)

LT_INIT
LT_LANG([C++])

case $host in
  *mingw*)

     #pkgconfig does more harm than good with MinGW
     use_pkgconfig=no

     TARGET_OS=windows
     AC_CHECK_LIB([mingwthrd],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([kernel32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([user32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([gdi32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([comdlg32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([winspool],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([winmm],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([shell32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([comctl32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([ole32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([oleaut32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([uuid],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([rpcrt4],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([advapi32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([ws2_32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([mswsock],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([shlwapi],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([iphlpapi],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([crypt32],      [main],, AC_MSG_ERROR(lib missing))

     # -static is interpreted by libtool, where it has a different meaning.
     # In libtool-speak, it's -all-static.
     AX_CHECK_LINK_FLAG([[-static]],[LIBTOOL_APP_LDFLAGS="$LIBTOOL_APP_LDFLAGS -all-static"])

     AC_PATH_PROG([MAKENSIS], [makensis], none)
     if test x$MAKENSIS = xnone; then
       AC_MSG_WARN("makensis not found. Cannot create installer.")
     fi

     AC_PATH_TOOL(WINDRES, windres, none)
     if test x$WINDRES = xnone; then
       AC_MSG_ERROR("windres not found")
     fi

     CPPFLAGS="$CPPFLAGS -D_MT -DWIN32 -D_WINDOWS -DBOOST_THREAD_USE_LIB"
     LEVELDB_TARGET_FLAGS="-DOS_WINDOWS"
     if test "x$CXXFLAGS_overridden" = "xno"; then
       CXXFLAGS="$CXXFLAGS -w"
     fi
     case $host in
       i?86-*) WINDOWS_BITS=32 ;;
       x86_64-*) WINDOWS_BITS=64 ;;
       *) AC_MSG_ERROR("Could not determine win32/win64 for installer") ;;
     esac
     AC_SUBST(WINDOWS_BITS)

     dnl libtool insists upon adding -nostdlib and a list of objects/libs to link against.
     dnl That breaks our ability to build dll's with static libgcc/libstdc++/libssp. Override
     dnl its command here, with the predeps/postdeps removed, and -static inserted. Postdeps are
     dnl also overridden to prevent their insertion later.
     dnl This should only affect dll's.
     archive_cmds_CXX="\$CC -shared \$libobjs \$deplibs \$compiler_flags -static -o \$output_objdir/\$soname \${wl}--enable-auto-image-base -Xlinker --out-implib -Xlinker \$lib"
     postdeps_CXX=

     ;;
  *darwin*)
     TARGET_OS=darwin
     LEVELDB_TARGET_FLAGS="-DOS_MACOSX"
     if  test x$cross_compiling != xyes; then
       BUILD_OS=darwin
       AC_CHECK_PROG([PORT],port, port)
       if test x$PORT = xport; then
         dnl add default macports paths
         CPPFLAGS="$CPPFLAGS -isystem /opt/local/include"
         LIBS="$LIBS -L/opt/local/lib"
         if test -d /opt/local/include/db48; then
           CPPFLAGS="$CPPFLAGS -I/opt/local/include/db48"
           LIBS="$LIBS -L/opt/local/lib/db48"
         fi
       fi

       AC_PATH_PROGS([RSVG_CONVERT], [rsvg-convert rsvg],rsvg-convert)
       AC_CHECK_PROG([BREW],brew, brew)
       if test x$BREW = xbrew; then
         dnl These Homebrew packages may be keg-only, meaning that they won't be found
         dnl in expected paths because they may conflict with system files. Ask
         dnl Homebrew where each one is located, then adjust paths accordingly.
         dnl It's safe to add these paths even if the functionality is disabled by
         dnl the user (--without-wallet or --without-gui for example).

         openssl_prefix=`$BREW --prefix openssl 2>/dev/null`
         bdb_prefix=`$BREW --prefix berkeley-db4 2>/dev/null`
         qt5_prefix=`$BREW --prefix qt5 2>/dev/null`
         if test x$openssl_prefix != x; then
           PKG_CONFIG_PATH="$openssl_prefix/lib/pkgconfig:$PKG_CONFIG_PATH"
           export PKG_CONFIG_PATH
         fi
         if test x$bdb_prefix != x; then
           CPPFLAGS="$CPPFLAGS -I$bdb_prefix/include"
           LIBS="$LIBS -L$bdb_prefix/lib"
         fi
         if test x$qt5_prefix != x; then
           PKG_CONFIG_PATH="$qt5_prefix/lib/pkgconfig:$PKG_CONFIG_PATH"
           export PKG_CONFIG_PATH
         fi
       fi
     else
       case $build_os in
         *darwin*)
           BUILD_OS=darwin
           ;;
         *)
           AC_PATH_TOOL([INSTALLNAMETOOL], [install_name_tool], install_name_tool)
           AC_PATH_TOOL([OTOOL], [otool], otool)
           AC_PATH_PROGS([GENISOIMAGE], [genisoimage mkisofs],genisoimage)
           AC_PATH_PROGS([RSVG_CONVERT], [rsvg-convert rsvg],rsvg-convert)
           AC_PATH_PROGS([IMAGEMAGICK_CONVERT], [convert],convert)
           AC_PATH_PROGS([TIFFCP], [tiffcp],tiffcp)

           dnl libtool will try to strip the static lib, which is a problem for
           dnl cross-builds because strip attempts to call a hard-coded ld,
           dnl which may not exist in the path. Stripping the .a is not
           dnl necessary, so just disable it.
           old_striplib=
           ;;
       esac
     fi

     AX_CHECK_LINK_FLAG([[-Wl,-headerpad_max_install_names]], [LDFLAGS="$LDFLAGS -Wl,-headerpad_max_install_names"])
     CPPFLAGS="$CPPFLAGS -DMAC_OSX"
     OBJCXXFLAGS="$CXXFLAGS"
     ;;
   *linux*)
     TARGET_OS=linux
     LEVELDB_TARGET_FLAGS="-DOS_LINUX"
     ;;
   *freebsd*)
     LEVELDB_TARGET_FLAGS="-DOS_FREEBSD"
     ;;
   *openbsd*)
     LEVELDB_TARGET_FLAGS="-DOS_OPENBSD"
     ;;
   *)
     OTHER_OS=`echo ${host_os} | awk '{print toupper($0)}'`
     AC_MSG_WARN([Guessing LevelDB OS as OS_${OTHER_OS}, please check whether this is correct, if not add an entry to configure.ac.])
     LEVELDB_TARGET_FLAGS="-DOS_${OTHER_OS}"
     ;;
esac

if test x$use_pkgconfig = xyes; then
  m4_ifndef([PKG_PROG_PKG_CONFIG], [AC_MSG_ERROR(PKG_PROG_PKG_CONFIG macro not found. Please install pkg-config and re-run autogen.sh.)])
  m4_ifdef([PKG_PROG_PKG_CONFIG], [
  PKG_PROG_PKG_CONFIG
  if test x"$PKG_CONFIG" = "x"; then
    AC_MSG_ERROR(pkg-config not found.)
  fi
  ])
fi

if test x$use_extended_functional_tests != xno; then
  AC_SUBST(EXTENDED_FUNCTIONAL_TESTS, --extended)
fi

if test x$use_lcov = xyes; then
  if test x$LCOV = x; then
    AC_MSG_ERROR("lcov testing requested but lcov not found")
  fi
  if test x$GCOV = x; then
    AC_MSG_ERROR("lcov testing requested but gcov not found")
  fi
  if test x$PYTHON = x; then
    AC_MSG_ERROR("lcov testing requested but python not found")
  fi
  if test x$GENHTML = x; then
    AC_MSG_ERROR("lcov testing requested but genhtml not found")
  fi
  LCOV="$LCOV --gcov-tool=$GCOV"
  AX_CHECK_LINK_FLAG([[--coverage]], [LDFLAGS="$LDFLAGS --coverage"],
    [AC_MSG_ERROR("lcov testing requested but --coverage linker flag does not work")])
  AX_CHECK_COMPILE_FLAG([--coverage],[CXXFLAGS="$CXXFLAGS --coverage"],
    [AC_MSG_ERROR("lcov testing requested but --coverage flag does not work")])
  AC_DEFINE(USE_COVERAGE, 1, [Define this symbol if coverage is enabled])
  CXXFLAGS="$CXXFLAGS -Og"
fi

if test x$use_lcov_branch != xno; then
  AC_SUBST(LCOV_OPTS, "$LCOV_OPTS --rc lcov_branch_coverage=1")
fi

dnl Check for endianness
AC_C_BIGENDIAN

dnl Check for pthread compile/link requirements
AX_PTHREAD

# The following macro will add the necessary defines to ion-config.h, but
# they also need to be passed down to any subprojects. Pull the results out of
# the cache and add them to CPPFLAGS.
AC_SYS_LARGEFILE
# detect POSIX or GNU variant of strerror_r
AC_FUNC_STRERROR_R

if test x$ac_cv_sys_file_offset_bits != x &&
   test x$ac_cv_sys_file_offset_bits != xno &&
   test x$ac_cv_sys_file_offset_bits != xunknown; then
  CPPFLAGS="$CPPFLAGS -D_FILE_OFFSET_BITS=$ac_cv_sys_file_offset_bits"
fi

if test x$ac_cv_sys_large_files != x &&
   test x$ac_cv_sys_large_files != xno &&
   test x$ac_cv_sys_large_files != xunknown; then
  CPPFLAGS="$CPPFLAGS -D_LARGE_FILES=$ac_cv_sys_large_files"
fi

AX_CHECK_LINK_FLAG([[-Wl,--large-address-aware]], [LDFLAGS="$LDFLAGS -Wl,--large-address-aware"])

AX_GCC_FUNC_ATTRIBUTE([visibility])
AX_GCC_FUNC_ATTRIBUTE([dllexport])
AX_GCC_FUNC_ATTRIBUTE([dllimport])

if test x$use_glibc_compat != xno; then

  #glibc absorbed clock_gettime in 2.17. librt (its previous location) is safe to link
  #in anyway for back-compat.
  AC_CHECK_LIB([rt],[clock_gettime],, AC_MSG_ERROR(lib missing))

  #__fdelt_chk's params and return type have changed from long unsigned int to long int.
  # See which one is present here.
  AC_MSG_CHECKING(__fdelt_chk type)
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#ifdef _FORTIFY_SOURCE
                    #undef _FORTIFY_SOURCE
                  #endif
                  #define _FORTIFY_SOURCE 2
                  #include <sys/select.h>
     extern "C" long unsigned int __fdelt_warn(long unsigned int);]],[[]])],
    [ fdelt_type="long unsigned int"],
    [ fdelt_type="long int"])
  AC_MSG_RESULT($fdelt_type)
  AC_DEFINE_UNQUOTED(FDELT_TYPE, $fdelt_type,[parameter and return value type for __fdelt_chk])
else
  AC_SEARCH_LIBS([clock_gettime],[rt])
fi

if test x$TARGET_OS != xwindows; then
  # All windows code is PIC, forcing it on just adds useless compile warnings
  AX_CHECK_COMPILE_FLAG([-fPIC],[PIC_FLAGS="-fPIC"])
fi

if test x$use_hardening != xno; then
  AX_CHECK_COMPILE_FLAG([-Wstack-protector],[HARDENED_CXXFLAGS="$HARDENED_CXXFLAGS -Wstack-protector"])
  AX_CHECK_COMPILE_FLAG([-fstack-protector-all],[HARDENED_CXXFLAGS="$HARDENED_CXXFLAGS -fstack-protector-all"])

  AX_CHECK_PREPROC_FLAG([-D_FORTIFY_SOURCE=2],[
    AX_CHECK_PREPROC_FLAG([-U_FORTIFY_SOURCE],[
      HARDENED_CPPFLAGS="$HARDENED_CPPFLAGS -U_FORTIFY_SOURCE"
    ])
    HARDENED_CPPFLAGS="$HARDENED_CPPFLAGS -D_FORTIFY_SOURCE=2"
  ])

  AX_CHECK_LINK_FLAG([[-Wl,--dynamicbase]], [HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,--dynamicbase"])
  AX_CHECK_LINK_FLAG([[-Wl,--nxcompat]], [HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,--nxcompat"])
  AX_CHECK_LINK_FLAG([[-Wl,--high-entropy-va]], [HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,--high-entropy-va"])
  AX_CHECK_LINK_FLAG([[-Wl,-z,relro]], [HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,-z,relro"])
  AX_CHECK_LINK_FLAG([[-Wl,-z,now]], [HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,-z,now"])

  if test x$TARGET_OS != xwindows; then
    AX_CHECK_COMPILE_FLAG([-fPIE],[PIE_FLAGS="-fPIE"])
    AX_CHECK_LINK_FLAG([[-pie]], [HARDENED_LDFLAGS="$HARDENED_LDFLAGS -pie"])
  fi

  case $host in
    *mingw*)
       AC_CHECK_LIB([ssp],      [main],, AC_MSG_ERROR(lib missing))
    ;;
  esac
fi

dnl this flag screws up non-darwin gcc even when the check fails. special-case it.
if test x$TARGET_OS = xdarwin; then
  AX_CHECK_LINK_FLAG([[-Wl,-dead_strip]], [LDFLAGS="$LDFLAGS -Wl,-dead_strip"])
fi

AC_CHECK_HEADERS([endian.h sys/endian.h byteswap.h stdio.h stdlib.h unistd.h strings.h sys/types.h sys/stat.h sys/select.h sys/prctl.h execinfo.h])

AC_CHECK_DECLS([strnlen])

# Check for daemon(3), unrelated to --with-daemon (although used by it)
AC_CHECK_DECLS([daemon])

AC_CHECK_DECLS([le16toh, le32toh, le64toh, htole16, htole32, htole64, be16toh, be32toh, be64toh, htobe16, htobe32, htobe64],,,
		[#if HAVE_ENDIAN_H
                 #include <endian.h>
                 #elif HAVE_SYS_ENDIAN_H
                 #include <sys/endian.h>
                 #endif])

AC_CHECK_DECLS([bswap_16, bswap_32, bswap_64],,,
		[#if HAVE_BYTESWAP_H
                 #include <byteswap.h>
                 #endif])

AC_CHECK_DECLS([__builtin_clz, __builtin_clzl, __builtin_clzll])

dnl Check for MSG_NOSIGNAL
AC_MSG_CHECKING(for MSG_NOSIGNAL)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <sys/socket.h>]],
 [[ int f = MSG_NOSIGNAL; ]])],
 [ AC_MSG_RESULT(yes); AC_DEFINE(HAVE_MSG_NOSIGNAL, 1,[Define this symbol if you have MSG_NOSIGNAL]) ],
 [ AC_MSG_RESULT(no)]
)

dnl Check for MSG_DONTWAIT
AC_MSG_CHECKING(for MSG_DONTWAIT)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <sys/socket.h>]],
 [[ int f = MSG_DONTWAIT; ]])],
 [ AC_MSG_RESULT(yes); AC_DEFINE(HAVE_MSG_DONTWAIT, 1,[Define this symbol if you have MSG_DONTWAIT]) ],
 [ AC_MSG_RESULT(no)]
)

dnl Check for mallopt(M_ARENA_MAX) (to set glibc arenas)
AC_MSG_CHECKING(for mallopt M_ARENA_MAX)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <malloc.h>]],
 [[ mallopt(M_ARENA_MAX, 1); ]])],
 [ AC_MSG_RESULT(yes); AC_DEFINE(HAVE_MALLOPT_ARENA_MAX, 1,[Define this symbol if you have mallopt with M_ARENA_MAX]) ],
 [ AC_MSG_RESULT(no)]
)

dnl Check for malloc_info (for memory statistics information in getmemoryinfo)
AC_MSG_CHECKING(for getmemoryinfo)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <malloc.h>]],
 [[ int f = malloc_info(0, NULL); ]])],
 [ AC_MSG_RESULT(yes); AC_DEFINE(HAVE_MALLOC_INFO, 1,[Define this symbol if you have malloc_info]) ],
 [ AC_MSG_RESULT(no)]
)

AC_MSG_CHECKING([for visibility attribute])
AC_LINK_IFELSE([AC_LANG_SOURCE([
  int foo_def( void ) __attribute__((visibility("default")));
  int main(){}
  ])],
  [
    AC_DEFINE(HAVE_VISIBILITY_ATTRIBUTE,1,[Define if the visibility attribute is supported.])
    AC_MSG_RESULT(yes)
  ],
  [
    AC_MSG_RESULT(no)
    if test x$use_reduce_exports = xyes; then
      AC_MSG_ERROR([Cannot find a working visibility attribute. Use --disable-reduce-exports.])
    fi
  ]
)

# Check for different ways of gathering OS randomness
AC_MSG_CHECKING(for Linux getrandom syscall)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <unistd.h>
  #include <sys/syscall.h>
  #include <linux/random.h>]],
 [[ syscall(SYS_getrandom, nullptr, 32, 0); ]])],
 [ AC_MSG_RESULT(yes); AC_DEFINE(HAVE_SYS_GETRANDOM, 1,[Define this symbol if the Linux getrandom system call is available]) ],
 [ AC_MSG_RESULT(no)]
)

AC_MSG_CHECKING(for getentropy)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <unistd.h>]],
 [[ getentropy(nullptr, 32) ]])],
 [ AC_MSG_RESULT(yes); AC_DEFINE(HAVE_GETENTROPY, 1,[Define this symbol if the BSD getentropy system call is available]) ],
 [ AC_MSG_RESULT(no)]
)

AC_MSG_CHECKING(for getentropy via random.h)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <unistd.h>
 #include <sys/random.h>]],
 [[ getentropy(nullptr, 32) ]])],
 [ AC_MSG_RESULT(yes); AC_DEFINE(HAVE_GETENTROPY_RAND, 1,[Define this symbol if the BSD getentropy system call is available with sys/random.h]) ],
 [ AC_MSG_RESULT(no)]
)

AC_MSG_CHECKING(for sysctl KERN_ARND)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <sys/types.h>
  #include <sys/sysctl.h>]],
 [[ static const int name[2] = {CTL_KERN, KERN_ARND};
    sysctl(name, 2, nullptr, nullptr, nullptr, 0); ]])],
 [ AC_MSG_RESULT(yes); AC_DEFINE(HAVE_SYSCTL_ARND, 1,[Define this symbol if the BSD sysctl(KERN_ARND) is available]) ],
 [ AC_MSG_RESULT(no)]
)

# ensure backtrace() is found, check -lexecinfo if necessary
if test x$TARGET_OS != xwindows; then
  AC_SEARCH_LIBS([backtrace], [execinfo], [], [
    AC_MSG_ERROR([Unable to find backtrace()])
  ])
fi

# Check for reduced exports
if test x$use_reduce_exports = xyes; then
  AX_CHECK_COMPILE_FLAG([-fvisibility=hidden],[RE_CXXFLAGS="-fvisibility=hidden"],
  [AC_MSG_ERROR([Cannot set default symbol visibility. Use --disable-reduce-exports.])])
fi

LEVELDB_CPPFLAGS=
LIBLEVELDB=
LIBMEMENV=
AM_CONDITIONAL([EMBEDDED_LEVELDB],[true])
AC_SUBST(LEVELDB_CPPFLAGS)
AC_SUBST(LIBLEVELDB)
AC_SUBST(LIBMEMENV)

if test x$enable_wallet != xno; then
    dnl Check for libdb_cxx only if wallet enabled
    BITCOIN_FIND_BDB48
fi

dnl Check for libminiupnpc (optional)
if test x$use_upnp != xno; then
  AC_CHECK_HEADERS(
    [miniupnpc/miniwget.h miniupnpc/miniupnpc.h miniupnpc/upnpcommands.h miniupnpc/upnperrors.h],
    [AC_CHECK_LIB([miniupnpc], [main],[MINIUPNPC_LIBS=-lminiupnpc], [have_miniupnpc=no])],
    [have_miniupnpc=no]
  )
fi

BITCOIN_QT_INIT

dnl sets $bitcoin_enable_qt, $bitcoin_enable_qt_test, $bitcoin_enable_qt_dbus
BITCOIN_QT_CONFIGURE([$use_pkgconfig], [qt5])

if test x$build_bitcoin_utils$build_bitcoind$bitcoin_enable_qt$use_tests$use_bench = xnonononono; then
    use_boost=no
else
    use_boost=yes
fi

if test x$use_boost = xyes; then

dnl Minimum required Boost version
define(MINIMUM_REQUIRED_BOOST, 1.47.0)

dnl Check for boost libs
AX_BOOST_BASE([MINIMUM_REQUIRED_BOOST])
if test x$want_boost = xno; then
    AC_MSG_ERROR([[only libionconsensus can be built without boost]])
fi
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM
AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_THREAD
AX_BOOST_CHRONO

dnl Boost 1.56 through 1.62 allow using std::atomic instead of its own atomic
dnl counter implementations. In 1.63 and later the std::atomic approach is default.
m4_pattern_allow(DBOOST_AC_USE_STD_ATOMIC) dnl otherwise it's treated like a macro
BOOST_CPPFLAGS="-DBOOST_SP_USE_STD_ATOMIC -DBOOST_AC_USE_STD_ATOMIC $BOOST_CPPFLAGS"

if test x$use_reduce_exports = xyes; then
  AC_MSG_CHECKING([for working boost reduced exports])
  TEMP_CPPFLAGS="$CPPFLAGS"
  CPPFLAGS="$BOOST_CPPFLAGS $CPPFLAGS"
  AC_PREPROC_IFELSE([AC_LANG_PROGRAM([[
      @%:@include <boost/version.hpp>
    ]], [[
      #if BOOST_VERSION >= 104900
      // Everything is okay
      #else
      #  error Boost version is too old
      #endif
    ]])],[
      AC_MSG_RESULT(yes)
    ],[
    AC_MSG_ERROR([boost versions < 1.49 are known to be broken with reduced exports. Use --disable-reduce-exports.])
  ])
  CPPFLAGS="$TEMP_CPPFLAGS"
fi
fi

if test x$use_reduce_exports = xyes; then
    CXXFLAGS="$CXXFLAGS $RE_CXXFLAGS"
    AX_CHECK_LINK_FLAG([[-Wl,--exclude-libs,ALL]], [RELDFLAGS="-Wl,--exclude-libs,ALL"])
fi

if test x$use_tests = xyes; then

  if test x$HEXDUMP = x; then
    AC_MSG_ERROR(hexdump is required for tests)
  fi


  if test x$use_boost = xyes; then

  AX_BOOST_UNIT_TEST_FRAMEWORK

  dnl Determine if -DBOOST_TEST_DYN_LINK is needed
  AC_MSG_CHECKING([for dynamic linked boost test])
  TEMP_LIBS="$LIBS"
  LIBS="$LIBS $BOOST_LDFLAGS $BOOST_UNIT_TEST_FRAMEWORK_LIB"
  TEMP_CPPFLAGS="$CPPFLAGS"
  CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS"
  AC_LINK_IFELSE([AC_LANG_SOURCE([
       #define BOOST_TEST_DYN_LINK
       #define BOOST_TEST_MAIN
        #include <boost/test/unit_test.hpp>

       ])],
    [AC_MSG_RESULT(yes)]
    [TESTDEFS="$TESTDEFS -DBOOST_TEST_DYN_LINK"],
    [AC_MSG_RESULT(no)])
  LIBS="$TEMP_LIBS"
  CPPFLAGS="$TEMP_CPPFLAGS"

  fi
fi

if test x$use_boost = xyes; then

BOOST_LIBS="$BOOST_LDFLAGS $BOOST_SYSTEM_LIB $BOOST_FILESYSTEM_LIB $BOOST_PROGRAM_OPTIONS_LIB $BOOST_THREAD_LIB $BOOST_CHRONO_LIB"

dnl If boost (prior to 1.57) was built without c++11, it emulated scoped enums
dnl using c++98 constructs. Unfortunately, this implementation detail leaked into
dnl the abi. This was fixed in 1.57.

dnl When building against that installed version using c++11, the headers pick up
dnl on the native c++11 scoped enum support and enable it, however it will fail to
dnl link. This can be worked around by disabling c++11 scoped enums if linking will
dnl fail.
dnl BOOST_NO_SCOPED_ENUMS was changed to BOOST_NO_CXX11_SCOPED_ENUMS in 1.51.

TEMP_LIBS="$LIBS"
LIBS="$BOOST_LIBS $LIBS"
TEMP_CPPFLAGS="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS"
AC_MSG_CHECKING([for mismatched boost c++11 scoped enums])
AC_LINK_IFELSE([AC_LANG_PROGRAM([[
  #include <boost/config.hpp>
  #include <boost/version.hpp>
  #if !defined(BOOST_NO_SCOPED_ENUMS) && !defined(BOOST_NO_CXX11_SCOPED_ENUMS) && BOOST_VERSION < 105700
  #define BOOST_NO_SCOPED_ENUMS
  #define BOOST_NO_CXX11_SCOPED_ENUMS
  #define CHECK
  #endif
  #include <boost/filesystem.hpp>
  ]],[[
  #if defined(CHECK)
    boost::filesystem::copy_file("foo", "bar");
  #else
    choke;
  #endif
  ]])],
  [AC_MSG_RESULT(mismatched); BOOST_CPPFLAGS="$BOOST_CPPFLAGS -DBOOST_NO_SCOPED_ENUMS -DBOOST_NO_CXX11_SCOPED_ENUMS"], [AC_MSG_RESULT(ok)])
LIBS="$TEMP_LIBS"
CPPFLAGS="$TEMP_CPPFLAGS"

dnl Boost >= 1.50 uses sleep_for rather than the now-deprecated sleep, however
dnl it was broken from 1.50 to 1.52 when backed by nanosleep. Use sleep_for if
dnl a working version is available, else fall back to sleep. sleep was removed
dnl after 1.56.
dnl If neither is available, abort.
TEMP_LIBS="$LIBS"
LIBS="$BOOST_LIBS $LIBS"
TEMP_CPPFLAGS="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS"
AC_LINK_IFELSE([AC_LANG_PROGRAM([[
  #include <boost/thread/thread.hpp>
  #include <boost/version.hpp>
  ]],[[
  #if BOOST_VERSION >= 105000 && (!defined(BOOST_HAS_NANOSLEEP) || BOOST_VERSION >= 105200)
      boost::this_thread::sleep_for(boost::chrono::milliseconds(0));
  #else
   choke me
  #endif
  ]])],
  [boost_sleep=yes;
     AC_DEFINE(HAVE_WORKING_BOOST_SLEEP_FOR, 1, [Define this symbol if boost sleep_for works])],
  [boost_sleep=no])
LIBS="$TEMP_LIBS"
CPPFLAGS="$TEMP_CPPFLAGS"

if test x$boost_sleep != xyes; then
TEMP_LIBS="$LIBS"
LIBS="$BOOST_LIBS $LIBS"
TEMP_CPPFLAGS="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS"
AC_LINK_IFELSE([AC_LANG_PROGRAM([[
  #include <boost/version.hpp>
  #include <boost/thread.hpp>
  #include <boost/date_time/posix_time/posix_time_types.hpp>
  ]],[[
  #if BOOST_VERSION <= 105600
      boost::this_thread::sleep(boost::posix_time::milliseconds(0));
  #else
   choke me
  #endif
  ]])],
  [boost_sleep=yes; AC_DEFINE(HAVE_WORKING_BOOST_SLEEP, 1, [Define this symbol if boost sleep works])],
  [boost_sleep=no])
LIBS="$TEMP_LIBS"
CPPFLAGS="$TEMP_CPPFLAGS"
fi

if test x$boost_sleep != xyes; then
  AC_MSG_ERROR(No working boost sleep implementation found.)
fi

fi

if test x$use_pkgconfig = xyes; then
  : dnl
  m4_ifdef(
    [PKG_CHECK_MODULES],
    [
      PKG_CHECK_MODULES([SSL], [libssl],, [AC_MSG_ERROR(openssl  not found.)])
      PKG_CHECK_MODULES([CRYPTO], [libcrypto],,[AC_MSG_ERROR(libcrypto  not found.)])
      BITCOIN_QT_CHECK([PKG_CHECK_MODULES([PROTOBUF], [protobuf], [have_protobuf=yes], [BITCOIN_QT_FAIL(libprotobuf not found)])])
      if test x$use_qr != xno; then
        BITCOIN_QT_CHECK([PKG_CHECK_MODULES([QR], [libqrencode], [have_qrencode=yes], [have_qrencode=no])])
      fi
      if test x$build_bitcoin_utils$build_bitcoind$bitcoin_enable_qt$use_tests != xnononono; then
        PKG_CHECK_MODULES([EVENT], [libevent],, [AC_MSG_ERROR(libevent not found.)])
        if test x$TARGET_OS != xwindows; then
          PKG_CHECK_MODULES([EVENT_PTHREADS], [libevent_pthreads],, [AC_MSG_ERROR(libevent_pthreads not found.)])
        fi
      fi

      if test "x$use_zmq" = "xyes"; then
        PKG_CHECK_MODULES([ZMQ],[libzmq >= 4],
          [AC_DEFINE([ENABLE_ZMQ],[1],[Define to 1 to enable ZMQ functions])],
          [AC_DEFINE([ENABLE_ZMQ],[0],[Define to 1 to enable ZMQ functions])
           AC_MSG_WARN([libzmq version 4.x or greater not found, disabling])
           use_zmq=no])
      else
          AC_DEFINE_UNQUOTED([ENABLE_ZMQ],[0],[Define to 1 to enable ZMQ functions])
      fi
    ]
  )
else
  AC_CHECK_HEADER([openssl/crypto.h],,AC_MSG_ERROR(libcrypto headers missing))
  AC_CHECK_LIB([crypto],      [main],CRYPTO_LIBS=-lcrypto, AC_MSG_ERROR(libcrypto missing))

  AC_CHECK_HEADER([openssl/ssl.h],, AC_MSG_ERROR(libssl headers missing),)
  AC_CHECK_LIB([ssl],         [main],SSL_LIBS=-lssl, AC_MSG_ERROR(libssl missing))

  if test x$build_bitcoin_utils$build_bitcoind$bitcoin_enable_qt$use_tests != xnononono; then
    AC_CHECK_HEADER([event2/event.h],, AC_MSG_ERROR(libevent headers missing),)
    AC_CHECK_LIB([event],[main],EVENT_LIBS=-levent,AC_MSG_ERROR(libevent missing))
    if test x$TARGET_OS != xwindows; then
      AC_CHECK_LIB([event_pthreads],[main],EVENT_PTHREADS_LIBS=-levent_pthreads,AC_MSG_ERROR(libevent_pthreads missing))
    fi
  fi

  if test "x$use_zmq" = "xyes"; then
     AC_CHECK_HEADER([zmq.h],
       [AC_DEFINE([ENABLE_ZMQ],[1],[Define to 1 to enable ZMQ functions])],
       [AC_MSG_WARN([zmq.h not found, disabling zmq support])
        use_zmq=no
        AC_DEFINE([ENABLE_ZMQ],[0],[Define to 1 to enable ZMQ functions])])
     AC_CHECK_LIB([zmq],[zmq_ctx_shutdown],ZMQ_LIBS=-lzmq,
       [AC_MSG_WARN([libzmq >= 4.0 not found, disabling zmq support])
        use_zmq=no
        AC_DEFINE([ENABLE_ZMQ],[0],[Define to 1 to enable ZMQ functions])])
  else
    AC_DEFINE_UNQUOTED([ENABLE_ZMQ],[0],[Define to 1 to enable ZMQ functions])
  fi

  if test "x$use_zmq" = "xyes"; then
    dnl Assume libzmq was built for static linking
    case $host in
      *mingw*)
        ZMQ_CFLAGS="$ZMQ_CFLAGS -DZMQ_STATIC"
      ;;
    esac
  fi

  BITCOIN_QT_CHECK(AC_CHECK_LIB([protobuf] ,[main],[PROTOBUF_LIBS=-lprotobuf], BITCOIN_QT_FAIL(libprotobuf not found)))
  if test x$use_qr != xno; then
    BITCOIN_QT_CHECK([AC_CHECK_LIB([qrencode], [main],[QR_LIBS=-lqrencode], [have_qrencode=no])])
    BITCOIN_QT_CHECK([AC_CHECK_HEADER([qrencode.h],, have_qrencode=no)])
  fi
fi

save_CXXFLAGS="${CXXFLAGS}"
CXXFLAGS="${CXXFLAGS} ${CRYPTO_CFLAGS} ${SSL_CFLAGS}"
AC_CHECK_DECLS([EVP_MD_CTX_new],,,[AC_INCLUDES_DEFAULT
#include <openssl/x509_vfy.h>
])
CXXFLAGS="${save_CXXFLAGS}"

dnl univalue check

need_bundled_univalue=yes

if test x$build_bitcoin_utils$build_bitcoind$bitcoin_enable_qt$use_tests$use_bench = xnonononono; then
  need_bundled_univalue=no
else

if test x$system_univalue != xno ; then
  found_univalue=no
  if test x$use_pkgconfig = xyes; then
    : #NOP
    m4_ifdef(
      [PKG_CHECK_MODULES],
      [
        PKG_CHECK_MODULES([UNIVALUE],[libunivalue],[found_univalue=yes],[true])
      ]
    )
  else
    AC_CHECK_HEADER([univalue.h],[
      AC_CHECK_LIB([univalue],  [main],[
        UNIVALUE_LIBS=-lunivalue
        found_univalue=yes
      ],[true])
    ],[true])
  fi

  if test x$found_univalue = xyes ; then
    system_univalue=yes
    need_bundled_univalue=no
  elif test x$system_univalue = xyes ; then
    AC_MSG_ERROR([univalue not found])
  else
    system_univalue=no
  fi
fi

if test x$need_bundled_univalue = xyes ; then
  UNIVALUE_CFLAGS='-I$(srcdir)/univalue/include'
  UNIVALUE_LIBS='univalue/libunivalue.la'
fi

fi

AM_CONDITIONAL([EMBEDDED_UNIVALUE],[test x$need_bundled_univalue = xyes])
AC_SUBST(UNIVALUE_CFLAGS)
AC_SUBST(UNIVALUE_LIBS)

BITCOIN_QT_PATH_PROGS([PROTOC], [protoc],$protoc_bin_path)

AC_MSG_CHECKING([whether to build iond])
AM_CONDITIONAL([BUILD_BITCOIND], [test x$build_bitcoind = xyes])
AC_MSG_RESULT($build_bitcoind)

AC_MSG_CHECKING([whether to build utils (ion-cli ion-tx)])
AM_CONDITIONAL([BUILD_BITCOIN_UTILS], [test x$build_bitcoin_utils = xyes])
AC_MSG_RESULT($build_bitcoin_utils)

AC_MSG_CHECKING([whether to build libraries])
AM_CONDITIONAL([BUILD_BITCOIN_LIBS], [test x$build_bitcoin_libs = xyes])
if test x$build_bitcoin_libs = xyes; then
  AC_DEFINE(HAVE_CONSENSUS_LIB, 1, [Define this symbol if the consensus lib has been built])
  AC_CONFIG_FILES([libionconsensus.pc:libionconsensus.pc.in])
fi
AC_MSG_RESULT($build_bitcoin_libs)

AC_LANG_POP

if test "x$use_ccache" != "xno"; then
  AC_MSG_CHECKING(if ccache should be used)
  if test x$CCACHE = x; then
    if test "x$use_ccache" = "xyes"; then
      AC_MSG_ERROR([ccache not found.]);
    else
      use_ccache=no
    fi
  else
    use_ccache=yes
    CC="$ac_cv_path_CCACHE $CC"
    CXX="$ac_cv_path_CCACHE $CXX"
  fi
  AC_MSG_RESULT($use_ccache)
fi
if test "x$use_ccache" = "xyes"; then
    AX_CHECK_PREPROC_FLAG([-Qunused-arguments],[CPPFLAGS="-Qunused-arguments $CPPFLAGS"])
fi

dnl bignum value
set_bignum=$req_bignum
case $req_bignum in
auto)
  GMP_CHECK
  if test x"$has_gmp" != x"yes"; then
    AC_MSG_ERROR([gmp bignum automatically selected but libgmp is not available. Use depends,
    install libgmp or select an other bignum implementation (ONLY gmp is fully SUPPORTED)])
  else
    set_bignum=gmp
  fi
  ;;
gmp)
  GMP_CHECK
  if test x"$has_gmp" != x"yes"; then
    AC_MSG_ERROR([gmp bignum explicitly requested but libgmp is not available])
  fi
  ;;
*)
  AC_MSG_ERROR([invalid bignum implementation selection])
  ;;
esac

BUILD_EXEEXT=
case $build in
  *mingw*)
    BUILD_EXEEXT=".exe"
  ;;
esac

AC_CONFIG_FILES([
    Makefile
    pc/libunivalue.pc
    pc/libunivalue-uninstalled.pc])

AC_SUBST(LIBTOOL_APP_LDFLAGS)
AC_SUBST(BUILD_EXEEXT)
AC_OUTPUT

