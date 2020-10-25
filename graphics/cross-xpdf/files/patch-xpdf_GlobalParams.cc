--- xpdf/GlobalParams.cc.orig	2020-10-25 16:03:39 UTC
+++ xpdf/GlobalParams.cc
@@ -6,6 +6,43 @@
 //
 //========================================================================
 
+//========================================================================
+//
+// Modified under the Poppler project - http://poppler.freedesktop.org
+//
+// All changes made under the Poppler project to this file are licensed
+// under GPL version 2 or later
+//
+// Copyright (C) 2005 Martin Kretzschmar <martink@gnome.org>
+// Copyright (C) 2005, 2006 Kristian Høgsberg <krh@redhat.com>
+// Copyright (C) 2005, 2007-2010, 2012, 2015, 2017 Albert Astals Cid <aacid@kde.org>
+// Copyright (C) 2005 Jonathan Blandford <jrb@redhat.com>
+// Copyright (C) 2006, 2007 Jeff Muizelaar <jeff@infidigm.net>
+// Copyright (C) 2006 Takashi Iwai <tiwai@suse.de>
+// Copyright (C) 2006 Ed Catmur <ed@catmur.co.uk>
+// Copyright (C) 2007 Krzysztof Kowalczyk <kkowalczyk@gmail.com>
+// Copyright (C) 2007, 2009 Jonathan Kew <jonathan_kew@sil.org>
+// Copyright (C) 2009 Petr Gajdos <pgajdos@novell.com>
+// Copyright (C) 2009, 2011, 2012, 2015 William Bader <williambader@hotmail.com>
+// Copyright (C) 2009 Kovid Goyal <kovid@kovidgoyal.net>
+// Copyright (C) 2010, 2012 Hib Eris <hib@hiberis.nl>
+// Copyright (C) 2010 Patrick Spendrin <ps_ml@gmx.de>
+// Copyright (C) 2010 Jakub Wilk <jwilk@jwilk.net>
+// Copyright (C) 2011 Pino Toscano <pino@kde.org>
+// Copyright (C) 2011 Koji Otani <sho@bbr.jp>
+// Copyright (C) 2012 Yi Yang <ahyangyi@gmail.com>
+// Copyright (C) 2012, 2017 Adrian Johnson <ajohnson@redneon.com>
+// Copyright (C) 2012 Thomas Freitag <Thomas.Freitag@alfa.de>
+// Copyright (C) 2012 Peter Breitenlohner <peb@mppmu.mpg.de>
+// Copyright (C) 2013, 2014 Jason Crain <jason@aquaticape.us>
+// Copyright (C) 2017 Christoph Cullmann <cullmann@kde.org>
+// Copyright (C) 2017 Jean Ghali <jghali@libertysurf.fr>
+//
+// To see a description of the changes please see the Changelog file that
+// came with your tarball or type make ChangeLog if you are building from git
+//
+//========================================================================
+
 #include <aconf.h>
 
 #ifdef USE_GCC_PRAGMAS
@@ -1267,6 +1304,81 @@ void GlobalParams::parseLine(char *buf, GString *fileN
   deleteGList(tokens, GString);
 }
 
+void GlobalParams::scanEncodingDirs(const char *dataRoot) {
+  GDir *dir;
+  GDirEntry *entry;
+
+  // allocate buffer large enough to append "/nameToUnicode"
+  size_t bufSize = strlen(dataRoot) + strlen("/nameToUnicode") + 1;
+  char *dataPathBuffer = new char[bufSize];
+
+  snprintf(dataPathBuffer, bufSize, "%s/nameToUnicode", dataRoot);
+  dir = new GDir(dataPathBuffer, gTrue);
+  while (entry = dir->getNextEntry(), entry != NULL) {
+      if (!entry->isDir()) {
+          parseNameToUnicode2(entry->getFullPath());
+      }
+      delete entry;
+  }
+  delete dir;
+
+  snprintf(dataPathBuffer, bufSize, "%s/cidToUnicode", dataRoot);
+  dir = new GDir(dataPathBuffer, gFalse);
+  while (entry = dir->getNextEntry(), entry != NULL) {
+      addCIDToUnicode(entry->getName(), entry->getFullPath());
+      delete entry;
+  }
+  delete dir;
+
+  snprintf(dataPathBuffer, bufSize, "%s/unicodeMap", dataRoot);
+  dir = new GDir(dataPathBuffer, gFalse);
+  while (entry = dir->getNextEntry(), entry != NULL) {
+      addUnicodeMap(entry->getName(), entry->getFullPath());
+      delete entry;
+  }
+  delete dir;
+
+  snprintf(dataPathBuffer, bufSize, "%s/cMap", dataRoot);
+  dir = new GDir(dataPathBuffer, gFalse);
+  while (entry = dir->getNextEntry(), entry != NULL) {
+      addCMapDir(entry->getName(), entry->getFullPath());
+      toUnicodeDirs->append(entry->getFullPath()->copy());
+      delete entry;
+  }
+  delete dir;
+
+  delete[] dataPathBuffer;
+}
+
+void GlobalParams::parseNameToUnicode2(GString *name) {
+  char *tok1, *tok2;
+  FILE *f;
+  char buf[256];
+  int line;
+  Unicode u;
+  char *tokptr;
+
+  if (!(f = openFile(name->getCString(), "r"))) {
+    error(errIO, -1, "Couldn't open 'nameToUnicode' file '{0:t}'",
+          name);
+    return;
+  }
+  line = 1;
+  while (getLine(buf, sizeof(buf), f)) {
+    tok1 = strtok_r(buf, " \t\r\n", &tokptr);
+    tok2 = strtok_r(NULL, " \t\r\n", &tokptr);
+    if (tok1 && tok2) {
+      sscanf(tok1, "%x", &u);
+      nameToUnicode->add(tok2, u);
+    } else {
+      error(errConfig, -1, "Bad line in 'nameToUnicode' file ({0:t}:{1:d})",
+            name, line);
+    }
+    ++line;
+  }
+  fclose(f);
+}
+
 void GlobalParams::parseNameToUnicode(GList *tokens, GString *fileName,
 				      int line) {
   GString *name;
@@ -1301,6 +1413,36 @@ void GlobalParams::parseNameToUnicode(GList *tokens, G
     ++line2;
   }
   fclose(f);
+}
+
+void GlobalParams::addCIDToUnicode(GString *collection,
+                                   GString *fileName) {
+    GString *old;
+
+    if ((old = (GString *)cidToUnicodes->remove(collection))) {
+        delete old;
+    }
+    cidToUnicodes->add(collection->copy(), fileName->copy());
+}
+
+void GlobalParams::addUnicodeMap(GString *encodingName, GString *fileName)
+{
+    GString *old;
+
+    if ((old = (GString *)unicodeMaps->remove(encodingName))) {
+        delete old;
+    }
+    unicodeMaps->add(encodingName->copy(), fileName->copy());
+}
+
+void GlobalParams::addCMapDir(GString *collection, GString *dir) {
+    GList *list;
+
+    if (!(list = (GList *)cMapDirs->lookup(collection))) {
+        list = new GList();
+        cMapDirs->add(collection->copy(), list);
+    }
+    list->append(dir->copy());
 }
 
 void GlobalParams::parseCIDToUnicode(GList *tokens, GString *fileName,
