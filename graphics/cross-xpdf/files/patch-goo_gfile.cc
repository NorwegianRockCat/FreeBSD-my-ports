--- goo/gfile.cc.orig	2020-10-25 16:04:04 UTC
+++ goo/gfile.cc
@@ -8,6 +8,30 @@
 //
 //========================================================================
 
+//========================================================================
+//
+// Modified under the Poppler project - http://poppler.freedesktop.org
+//
+// All changes made under the Poppler project to this file are licensed
+// under GPL version 2 or later
+//
+// Copyright (C) 2006 Takashi Iwai <tiwai@suse.de>
+// Copyright (C) 2006 Kristian Høgsberg <krh@redhat.com>
+// Copyright (C) 2008 Adam Batkin <adam@batkin.net>
+// Copyright (C) 2008, 2010, 2012, 2013 Hib Eris <hib@hiberis.nl>
+// Copyright (C) 2009, 2012, 2014 Albert Astals Cid <aacid@kde.org>
+// Copyright (C) 2009 Kovid Goyal <kovid@kovidgoyal.net>
+// Copyright (C) 2013 Adam Reichold <adamreichold@myopera.com>
+// Copyright (C) 2013, 2017 Adrian Johnson <ajohnson@redneon.com>
+// Copyright (C) 2013 Peter Breitenlohner <peb@mppmu.mpg.de>
+// Copyright (C) 2013 Thomas Freitag <Thomas.Freitag@alfa.de>
+// Copyright (C) 2017 Christoph Cullmann <cullmann@kde.org>
+//
+// To see a description of the changes please see the Changelog file that
+// came with your tarball or type make ChangeLog if you are building from git
+//
+//========================================================================
+
 #include <aconf.h>
 
 #ifdef _WIN32
@@ -26,6 +50,8 @@
 #  include <string.h>
 #  if !defined(VMS) && !defined(ACORN)
 #    include <pwd.h>
+#include <dirent.h>
+
 #  endif
 #  if defined(VMS) && (__DECCXX_VER < 50200000)
 #    include <unixlib.h>
@@ -713,5 +739,186 @@ void fixCommandLine(int *argc, char **argv[]) {
   (*argv)[argcw] = NULL;
 
   LocalFree(argvw);
+#endif
+}
+
+//------------------------------------------------------------------------
+// GooFile
+//------------------------------------------------------------------------
+
+#ifdef _WIN32
+
+GooFile* GooFile::open(GString *fileName) {
+  HANDLE handle = CreateFileA(fileName->getCString(),
+                              GENERIC_READ,
+                              FILE_SHARE_READ | FILE_SHARE_WRITE,
+                              NULL,
+                              OPEN_EXISTING,
+                              FILE_ATTRIBUTE_NORMAL, NULL);
+
+  return handle == INVALID_HANDLE_VALUE ? NULL : new GooFile(handle);
+}
+
+GooFile* GooFile::open(const wchar_t *fileName) {
+  HANDLE handle = CreateFileW(fileName,
+                              GENERIC_READ,
+                              FILE_SHARE_READ | FILE_SHARE_WRITE,
+                              NULL,
+                              OPEN_EXISTING,
+                              FILE_ATTRIBUTE_NORMAL, NULL);
+
+  return handle == INVALID_HANDLE_VALUE ? NULL : new GooFile(handle);
+}
+
+#else
+
+GooFile* GooFile::open(GString *fileName) {
+#ifdef VMS
+    int fd = ::open(fileName->getCString(), Q_RDONLY, "ctx=stm");
+#else
+    int fd = ::open(fileName->getCString(), O_RDONLY);
+#endif
+
+    return fd < 0 ? NULL : new GooFile(fd);
+}
+
+#endif // _WIN32
+
+//------------------------------------------------------------------------
+// GDir and GDirEntry
+//------------------------------------------------------------------------
+
+GDirEntry::GDirEntry(char *dirPath, char *nameA, GBool doStat) {
+#ifdef VMS
+    char *p;
+#elif defined(_WIN32)
+    DWORD fa;
+#elif defined(ACORN)
+#else
+    struct stat st;
+#endif
+
+    name = new GString(nameA);
+    dir = gFalse;
+    fullPath = new GString(dirPath);
+    appendToPath(fullPath, nameA);
+    if (doStat) {
+#ifdef VMS
+        if (!strcmp(nameA, "-") ||
+	((p = strrchr(nameA, '.')) && !strncmp(p, ".DIR;", 5)))
+      dir = gTrue;
+#elif defined(ACORN)
+#else
+#ifdef _WIN32
+        fa = GetFileAttributesA(fullPath->getCString());
+    dir = (fa != 0xFFFFFFFF && (fa & FILE_ATTRIBUTE_DIRECTORY));
+#else
+        if (stat(fullPath->getCString(), &st) == 0)
+            dir = S_ISDIR(st.st_mode);
+#endif
+#endif
+    }
+}
+
+GDirEntry::~GDirEntry() {
+    delete fullPath;
+    delete name;
+}
+
+GDir::GDir(char *name, GBool doStatA) {
+    path = new GString(name);
+    doStat = doStatA;
+#if defined(_WIN32)
+    GString *tmp;
+
+  tmp = path->copy();
+  tmp->append("/*.*");
+  hnd = FindFirstFileA(tmp->getCString(), &ffd);
+  delete tmp;
+#elif defined(ACORN)
+#elif defined(MACOS)
+#else
+    dir = opendir(name);
+#ifdef VMS
+    needParent = strchr(name, '[') != NULL;
+#endif
+#endif
+}
+
+GDir::~GDir() {
+    delete path;
+#if defined(_WIN32)
+    if (hnd != INVALID_HANDLE_VALUE) {
+    FindClose(hnd);
+    hnd = INVALID_HANDLE_VALUE;
+  }
+#elif defined(ACORN)
+#elif defined(MACOS)
+#else
+    if (dir)
+        closedir(dir);
+#endif
+}
+
+GDirEntry *GDir::getNextEntry() {
+    GDirEntry *e = NULL;
+
+#if defined(_WIN32)
+    if (hnd != INVALID_HANDLE_VALUE) {
+    e = new GDirEntry(path->getCString(), ffd.cFileName, doStat);
+    if (!FindNextFileA(hnd, &ffd)) {
+      FindClose(hnd);
+      hnd = INVALID_HANDLE_VALUE;
+    }
+  }
+#elif defined(ACORN)
+#elif defined(MACOS)
+#elif defined(VMS)
+    struct dirent *ent;
+  if (dir) {
+    if (needParent) {
+      e = new GDirEntry(path->getCString(), "-", doStat);
+      needParent = gFalse;
+      return e;
+    }
+    ent = readdir(dir);
+    if (ent) {
+      e = new GDirEntry(path->getCString(), ent->d_name, doStat);
+    }
+  }
+#else
+    struct dirent *ent;
+    if (dir) {
+        do {
+            ent = readdir(dir);
+        }
+        while (ent && (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")));
+        if (ent) {
+            e = new GDirEntry(path->getCString(), ent->d_name, doStat);
+        }
+    }
+#endif
+
+    return e;
+}
+
+void GDir::rewind() {
+#ifdef _WIN32
+    GString *tmp;
+
+  if (hnd != INVALID_HANDLE_VALUE)
+    FindClose(hnd);
+  tmp = path->copy();
+  tmp->append("/*.*");
+  hnd = FindFirstFileA(tmp->getCString(), &ffd);
+  delete tmp;
+#elif defined(ACORN)
+#elif defined(MACOS)
+#else
+    if (dir)
+        rewinddir(dir);
+#ifdef VMS
+    needParent = strchr(path->getCString(), '[') != NULL;
+#endif
 #endif
 }
