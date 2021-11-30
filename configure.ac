AC_PREREQ([2.71])
AC_INIT([Kernel],[0.1],[scratch.joint-0i@icloud.com])

AC_CANONICAL_BUILD

AC_SUBST(build_configargs)
AC_SUBST(build_configdirs)

dnl Because we don't have a -lc
LDFLAGS="-nostdlib"
CFLAGS="-nostdlib -ffreestanding"

AC_PROG_CC
AC_PROG_CXX
AM_PROG_AS

dnl Want C99

AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES(size_t)
AC_CONFIG_HEADERS([sys/config.h])

dnl Want all flags

AX_CHECK_COMPILE_FLAG([-m32],
  [AX_APPEND_FLAG([-m32])],
  [AC_MSG_WARN([-m32 not supported])
])

AX_CHECK_COMPILE_FLAG([-march=i686],
  [AX_APPEND_FLAG([-march=i686])],
  [AC_MSG_WARN([-march=i686 not supported])
])


AX_CHECK_COMPILE_FLAG([-fno-builtin],
  [AX_APPEND_FLAG([-fno-builtin])],
  [AC_MSG_WARN([-fno-builtin not supported])
])


AX_CHECK_COMPILE_FLAG([-fstrength-reduce],
  [AX_APPEND_FLAG([-fstrength-reduce])],
  [AC_MSG_WARN([-fstrength-reduce not supported])
])

AX_CHECK_COMPILE_FLAG([-fomit-frame-pointer],
  [AX_APPEND_FLAG([-fomit-frame-pointer])],
  [AC_MSG_WARN([-fomit-frame-pointer not supported])
])

AX_CHECK_COMPILE_FLAG([-finline-functions],
  [AX_APPEND_FLAG([-finline-functions])],
  [AC_MSG_WARN([-finline-functions not supported])
])

AX_CHECK_COMPILE_FLAG([-nostdinc],
  [AX_APPEND_FLAG([-nostdinc])],
  [AC_MSG_WARN([-nostdinc not supported])
])

AX_CHECK_COMPILE_FLAG([-fno-stack-protector],
  [AX_APPEND_FLAG([-fno-stack-protector])],
  [AC_MSG_WARN([-fno-stack-protector not supported])
])

AX_CHECK_COMPILE_FLAG([-mno-red-zone],
  [AX_APPEND_FLAG([-mno-red-zone])],
  [AC_MSG_WARN([-mno-red-zone not supported])
])


AX_CHECK_COMPILE_FLAG([-fleading-underscore],
  [AX_APPEND_FLAG([-fleading-underscore ])],
  [AC_MSG_ERROR([-fleading-underscore  not supported])
])

AX_CHECK_COMPILE_FLAG([-ffreestanding],
  [AX_APPEND_FLAG([-ffreestanding])],
  [AC_MSG_WARN([-ffreestanding not supported])
])

AX_CHECK_COMPILE_FLAG([-nostdlib],
  [AX_APPEND_FLAG([-nostdlib])],
  [AC_MSG_WARN([-nostdlib not supported])
])

AX_CHECK_COMPILE_FLAG([-std=gnu17],
  [AX_APPEND_FLAG([-std=gnu17])],
  [AC_MSG_WARN([-std=gnu17 not supported])
])

AC_CHECK_PROG(MANGEN, [groff troff roff], yes)
AS_IF([test x"$MANGEN" != x"yes"], [AC_MSG_ERROR([`groff' or `troff' is needed to display interactive manpages])])

AC_CHECK_PROG(QEMU, [qemu-system-x86_64], yes)
AS_IF([test x"$QEMU" != x"yes"], [AC_MSG_ERROR([`qemu-system-*' for the target is needed to display interactive manpages])])

AC_CHECK_PROG(MORE, [more], yes)
AS_IF([test x"$MORE" != x"yes"], [AC_MSG_ERROR([`more' (the program) is needed to display interactive manpages])])

AM_INIT_AUTOMAKE
AC_CONFIG_FILES([
    Makefile
])

AC_OUTPUT