--- wmcube.c.intermediate	2021-03-09 12:08:25.000000000 +0000
+++ wmcube.c
@@ -1223,7 +1223,11 @@ int calc_cpu_total()
 #elif defined FREEBSD
 #include <nlist.h>
 #include <fcntl.h>
+#ifdef __DragonFly__
+#include <sys/resource.h>
+#else
 #include <sys/dkstat.h>
+#endif
 #include <sys/sysctl.h>
 
 int init_calc_cpu()
