--- src/3rdparty/chromium/v8/src/api/api.cc.intermediate	2020-08-18 13:01:51 UTC
+++ src/3rdparty/chromium/v8/src/api/api.cc
@@ -113,7 +113,7 @@
 #include "src/wasm/wasm-result.h"
 #include "src/wasm/wasm-serialization.h"
 
-#if V8_OS_LINUX || V8_OS_MACOSX || V8_OS_FREEBSD
+#if V8_OS_LINUX || V8_OS_MACOSX || V8_OS_FREEBSD || V8_OS_DRAGONFLYBSD
 #include <signal.h>
 #include "include/v8-wasm-trap-handler-posix.h"
 #include "src/trap-handler/handler-inside-posix.h"
@@ -5653,7 +5653,7 @@ bool v8::V8::Initialize() {
   return true;
 }
 
-#if V8_OS_LINUX || V8_OS_MACOSX || V8_OS_OPENBSD || V8_OS_FREEBSD
+#if V8_OS_LINUX || V8_OS_MACOSX || V8_OS_OPENBSD || V8_OS_FREEBSD || V8_OS_DRAGONFLYBSD
 bool TryHandleWebAssemblyTrapPosix(int sig_code, siginfo_t* info,
                                    void* context) {
 #if V8_TARGET_ARCH_X64 && !V8_OS_ANDROID
