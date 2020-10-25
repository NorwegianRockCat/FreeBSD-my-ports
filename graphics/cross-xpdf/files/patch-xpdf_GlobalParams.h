--- xpdf/GlobalParams.h.orig	2020-10-25 16:03:29 UTC
+++ xpdf/GlobalParams.h
@@ -6,6 +6,32 @@
 //
 //========================================================================
 
+//========================================================================
+//
+// Modified under the Poppler project - http://poppler.freedesktop.org
+//
+// All changes made under the Poppler project to this file are licensed
+// under GPL version 2 or later
+//
+// Copyright (C) 2005, 2007-2010, 2012, 2015, 2017 Albert Astals Cid <aacid@kde.org>
+// Copyright (C) 2005 Jonathan Blandford <jrb@redhat.com>
+// Copyright (C) 2006 Takashi Iwai <tiwai@suse.de>
+// Copyright (C) 2006 Kristian Høgsberg <krh@redhat.com>
+// Copyright (C) 2007 Krzysztof Kowalczyk <kkowalczyk@gmail.com>
+// Copyright (C) 2009 Jonathan Kew <jonathan_kew@sil.org>
+// Copyright (C) 2009 Petr Gajdos <pgajdos@novell.com>
+// Copyright (C) 2009, 2011, 2012, 2014, 2015 William Bader <williambader@hotmail.com>
+// Copyright (C) 2010 Hib Eris <hib@hiberis.nl>
+// Copyright (C) 2011 Pino Toscano <pino@kde.org>
+// Copyright (C) 2012, 2017 Adrian Johnson <ajohnson@redneon.com>
+// Copyright (C) 2012 Thomas Freitag <Thomas.Freitag@alfa.de>
+// Copyright (C) 2013 Jason Crain <jason@aquaticape.us>
+//
+// To see a description of the changes please see the Changelog file that
+// came with your tarball or type make ChangeLog if you are building from git
+//
+//========================================================================
+
 #ifndef GLOBALPARAMS_H
 #define GLOBALPARAMS_H
 
@@ -223,6 +249,7 @@ class GlobalParams { (public)
 
   ~GlobalParams();
 
+	void scanEncodingDirs(const char *dataRoot);
   void setBaseDir(const char *dir);
   void setupBaseFonts(const char *dir);
 
@@ -388,6 +415,11 @@ class GlobalParams { (public)
   static const char *defaultTextEncoding;
 
 private:
+
+  void addCIDToUnicode(GString *collection, GString *fileName);
+  void addUnicodeMap(GString *encodingName, GString *fileName);
+  void addCMapDir(GString *collection, GString *dir);
+  void parseNameToUnicode2(GString *name);
 
   void createDefaultKeyBindings();
   void parseFile(GString *fileName, FILE *f);
