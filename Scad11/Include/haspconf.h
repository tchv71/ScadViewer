/*
 *
 *  HASPCONF.H - A general configuration header for the HASP C/C++ API.
 *
 *  Determines system configuration in order to declare the hasp() routine
 *  properly, and to define some constants needed for memory operations.
 *
 */

#ifndef HASPCONF_H_
#define HASPCONF_H_

#if !defined (HASP_H_)
#error Please include HASP.H instead of HASPCONF.H
#endif

/*
 **********************************************************************
 *
 *     U S E R    C O N F I G U R A B L E    S E C T I O N
 *
 *********************************************************************
 */

/*
 *  Note :
 *     For Maximum portability we recommend not to change the following.
 *     Use a command line #define or #define it before inclusion of "hasp.h"
 */

/* uncomment the following if you link with the hasp() routine dynamically */
/* #define HASP_DLL */

/* uncomment the following if you compile with a 32 bit compiler */
/* #define C_32BIT */

/* uncomment the following if you compile with a 16 bit compiler */
/* #define C_16BIT */

/*
 *********************************************************************
 *
 *     "A U T O"    C O N F I G U R A T I O N    S E C T I O N
 *
 *********************************************************************
 */

/*
 * Figure out 16Bit or 32Bit compiler.
 */

/*
 *  All Win32 compilers define the macro _WIN32
 */
#if defined (_WIN32)
#  define C_32BIT
#endif

/*
 *  Otherwise, check at "limits.h". Works fine with all Intel compilers.
 */
#if !defined (C_32BIT) && !defined (C_16BIT)
#  include <limits.h>
#  if UINT_MAX == USHRT_MAX
#    define C_16BIT
#  elif UINT_MAX == ULONG_MAX
#    define C_32BIT
#  endif
#endif

/*
 *  Verify that the above method worked.
 */
#if !defined(C_32BIT) && !defined(C_16BIT)
#error Unable to recognize 32 bit or 16 bit compiler.
#endif


#if defined (HASP_DLL)
#  if defined (C_32BIT)
#     define HASPAPI __stdcall
#  else
#     define HASPAPI far pascal
#  endif
#else
#  if defined (C_32BIT)
#     define HASPAPI
#  else
#     define HASPAPI _cdecl far
#  endif
#endif

/*
 * We must assure that FAR is defined well.
 */
#ifndef FAR
#  ifdef C_32BIT
#     define FAR
#  else
#     define FAR far
#  endif
#endif


#endif /* HASPCONF_H_ */

