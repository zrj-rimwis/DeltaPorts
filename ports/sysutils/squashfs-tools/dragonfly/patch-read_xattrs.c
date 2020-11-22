--- read_xattrs.c.orig	2014-03-09 05:31:59 UTC
+++ read_xattrs.c
@@ -31,10 +31,16 @@
 #include <stdio.h>
 #include <string.h>
 
+#if defined(__DragonFly__)
+#include <sys/endian.h>
+#endif
+
 #ifndef linux
+#ifndef __BYTE_ORDER
 #define __BYTE_ORDER BYTE_ORDER
 #define __BIG_ENDIAN BIG_ENDIAN
 #define __LITTLE_ENDIAN LITTLE_ENDIAN
+#endif
 #else
 #include <endian.h>
 #endif
