--- libobs/util/platform-nix.c.orig	2019-06-30 00:00:32 UTC
+++ libobs/util/platform-nix.c
@@ -34,14 +34,16 @@
 #include <sys/times.h>
 #include <sys/wait.h>
 #include <libgen.h>
-#ifdef __FreeBSD__
+#if defined(__FreeBSD__) || defined(__DragonFly__)
 #include <sys/param.h>
 #include <sys/queue.h>
 #include <sys/socket.h>
 #include <sys/user.h>
 #include <sys/sysctl.h>
 #include <unistd.h>
+#ifndef __DragonFly__
 #include <libprocstat.h>
+#endif
 #else
 #include <sys/resource.h>
 #endif
@@ -737,7 +739,7 @@ static void os_get_cores_internal(void)
 	dstr_free(&proc_phys_ids);
 	dstr_free(&proc_phys_id);
 	free(line);
-#elif defined(__FreeBSD__)
+#elif defined(__FreeBSD__) && !defined(__DragonFly__)
 	char *text = os_quick_read_utf8_file("/var/run/dmesg.boot");
 	char *core_count = text;
 	int packages = 0;
@@ -810,7 +812,7 @@ int os_get_logical_cores(void)
 	return logical_cores;
 }
 
-#ifdef __FreeBSD__
+#if defined(__FreeBSD__) || defined(__DragonFly__)
 uint64_t os_get_sys_free_size(void)
 {
 	uint64_t mem_free = 0;
@@ -838,8 +840,13 @@ bool os_get_proc_memory_usage(os_proc_me
 		return false;
 
 	usage->resident_size =
+#ifdef __DragonFly__
+			(uint64_t)kinfo.kp_vm_rssize * sysconf(_SC_PAGESIZE);
+	usage->virtual_size  = (uint64_t)kinfo.kp_vm_map_size;
+#else
 			(uint64_t)kinfo.ki_rssize * sysconf(_SC_PAGESIZE);
 	usage->virtual_size  = (uint64_t)kinfo.ki_size;
+#endif
 	return true;
 }
 
@@ -848,7 +855,11 @@ uint64_t os_get_proc_resident_size(void)
 	struct kinfo_proc kinfo;
 	if (!os_get_proc_memory_usage_internal(&kinfo))
 		return 0;
+#ifdef __DragonFly__
+	return (uint64_t)kinfo.kp_vm_rssize * sysconf(_SC_PAGESIZE);
+#else
 	return (uint64_t)kinfo.ki_rssize * sysconf(_SC_PAGESIZE);
+#endif
 }
 
 uint64_t os_get_proc_virtual_size(void)
@@ -856,7 +867,11 @@ uint64_t os_get_proc_virtual_size(void)
 	struct kinfo_proc kinfo;
 	if (!os_get_proc_memory_usage_internal(&kinfo))
 		return 0;
+#ifdef __DragonFly__
+	return (uint64_t)kinfo.kp_vm_map_size;
+#else
 	return (uint64_t)kinfo.ki_size;
+#endif
 }
 #else
 uint64_t os_get_sys_free_size(void) {return 0;}
