--- goo/gfile.h.orig	2020-10-25 16:03:54 UTC
+++ goo/gfile.h
@@ -8,6 +8,27 @@
 //
 //========================================================================
 
+//========================================================================
+//
+// Modified under the Poppler project - http://poppler.freedesktop.org
+//
+// All changes made under the Poppler project to this file are licensed
+// under GPL version 2 or later
+//
+// Copyright (C) 2006 Kristian Høgsberg <krh@redhat.com>
+// Copyright (C) 2009, 2011, 2012 Albert Astals Cid <aacid@kde.org>
+// Copyright (C) 2009 Kovid Goyal <kovid@kovidgoyal.net>
+// Copyright (C) 2013 Adam Reichold <adamreichold@myopera.com>
+// Copyright (C) 2013, 2017 Adrian Johnson <ajohnson@redneon.com>
+// Copyright (C) 2014 Bogdan Cristea <cristeab@gmail.com>
+// Copyright (C) 2014 Peter Breitenlohner <peb@mppmu.mpg.de>
+// Copyright (C) 2017 Christoph Cullmann <cullmann@kde.org>
+//
+// To see a description of the changes please see the Changelog file that
+// came with your tarball or type make ChangeLog if you are building from git
+//
+//========================================================================
+
 #ifndef GFILE_H
 #define GFILE_H
 
@@ -27,6 +48,8 @@
 #else
 #  include <unistd.h>
 #  include <sys/types.h>
+#include <dirent.h>
+
 #endif
 #include "gtypes.h"
 
@@ -116,5 +139,81 @@ extern GFileOffset gftell(FILE *f);
 // On Windows, this gets the Unicode command line and converts it to
 // UTF-8.  On other systems, this is a nop.
 extern void fixCommandLine(int *argc, char **argv[]);
+
+
+//------------------------------------------------------------------------
+// GooFile
+//------------------------------------------------------------------------
+
+class GooFile
+{
+public:
+	static GooFile *open(GString *fileName);
+
+#ifdef _WIN32
+	static GooFile *open(const wchar_t *fileName);
+
+  ~GooFile() { CloseHandle(handle); }
+
+private:
+  GooFile(HANDLE handleA): handle(handleA) {}
+  HANDLE handle;
+#else
+	~GooFile() { close(fd); }
+
+private:
+	GooFile(int fdA) : fd(fdA) {}
+	int fd;
+#endif // _WIN32
+};
+
+//------------------------------------------------------------------------
+// GDir and GDirEntry
+//------------------------------------------------------------------------
+
+class GDirEntry {
+public:
+
+	GDirEntry(char *dirPath, char *nameA, GBool doStat);
+	~GDirEntry();
+	GString *getName() { return name; }
+	GString *getFullPath() { return fullPath; }
+	GBool isDir() { return dir; }
+
+private:
+	GDirEntry(const GDirEntry &other);
+	GDirEntry& operator=(const GDirEntry &other);
+
+	GString *name;		// dir/file name
+	GString *fullPath;
+	GBool dir;			// is it a directory?
+};
+
+class GDir {
+public:
+
+	GDir(char *name, GBool doStatA = gTrue);
+	~GDir();
+	GDirEntry *getNextEntry();
+	void rewind();
+
+private:
+	GDir(const GDir &other);
+	GDir& operator=(const GDir &other);
+
+	GString *path;		// directory path
+	GBool doStat;			// call stat() for each entry?
+#if defined(_WIN32)
+	WIN32_FIND_DATAA ffd;
+  HANDLE hnd;
+#elif defined(ACORN)
+#elif defined(MACOS)
+#else
+	DIR *dir;			// the DIR structure from opendir()
+#ifdef VMS
+	GBool needParent;		// need to return an entry for [-]
+#endif
+#endif
+};
 
 #endif
