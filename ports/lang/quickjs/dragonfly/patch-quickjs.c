The malloc_usable_size() is not exposed in libc on purpose.

--- quickjs.c.intermediate	2021-03-12 08:04:36.000000000 +0000
+++ quickjs.c
@@ -1663,7 +1663,7 @@ static inline size_t js_def_malloc_usabl
     return malloc_size(ptr);
 #elif defined(_WIN32)
     return _msize(ptr);
-#elif defined(EMSCRIPTEN)
+#elif defined(EMSCRIPTEN) || defined(__DragonFly__)
     return 0;
 #elif defined(__linux__)
     return malloc_usable_size(ptr);
@@ -1737,7 +1737,7 @@ static const JSMallocFunctions def_mallo
     malloc_size,
 #elif defined(_WIN32)
     (size_t (*)(const void *))_msize,
-#elif defined(EMSCRIPTEN)
+#elif defined(EMSCRIPTEN) || defined(__DragonFly__)
     NULL,
 #elif defined(__linux__)
     (size_t (*)(const void *))malloc_usable_size,
