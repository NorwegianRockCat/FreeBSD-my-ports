--- zotero-standalone-build-90a781b/fetch_xulrunner.sh.orig	2019-12-02 00:27:47.000000000 +0100
+++ zotero-standalone-build-90a781b/fetch_xulrunner.sh	2019-12-10 20:55:29.936017000 +0100
@@ -1,4 +1,4 @@
-#!/bin/bash
+#!/usr/local/bin/bash
 set -euo pipefail
 
 # Copyright (c) 2011  Zotero
@@ -26,7 +26,7 @@
 	cat >&2 <<DONE
 Usage: $0 -p platforms [-s]
 Options
- -p PLATFORMS        Platforms to build (m=Mac, w=Windows, l=Linux)
+ -p PLATFORMS        Platforms to build (m=Mac, w=Windows, l=Linux f=FreeBSD)
  -s                  Skip download; Firefox must already be extracted in xulrunner/ directory
 DONE
 	exit 1
@@ -35,6 +35,7 @@
 BUILD_MAC=0
 BUILD_WIN32=0
 BUILD_LINUX=0
+BUILD_FREEBSD=0
 skip_download=0
 while getopts "p:s" opt; do
 	case $opt in
@@ -45,6 +46,7 @@
 					m) BUILD_MAC=1;;
 					w) BUILD_WIN32=1;;
 					l) BUILD_LINUX=1;;
+					f) BUILD_FREEBSD=1;;
 					*)
 						echo "$0: Invalid platform option ${OPTARG:i:1}"
 						usage
@@ -61,7 +63,7 @@
 done
 
 # Require at least one platform
-if [[ $BUILD_MAC == 0 ]] && [[ $BUILD_WIN32 == 0 ]] && [[ $BUILD_LINUX == 0 ]]; then
+if [[ $BUILD_MAC == 0 ]] && [[ $BUILD_WIN32 == 0 ]] && [[ $BUILD_LINUX == 0 ]] && [[ $BUILD_FREEBSD == 0 ]]; then
 	usage
 fi
 
@@ -216,6 +218,24 @@
 	if [ $skip_download -eq 0 ]; then
 		rm "Firefox%20Setup%20$GECKO_VERSION.exe"
 	fi
+fi
+
+if [ $BUILD_FREEBSD == 1 ]; then
+    GECKO_VERSION="esr-60.8.0_4,1"
+    rm -rf firefox
+    rm -rf freebsd-pkg-foo
+
+    cp $WRKDIR/../firefox-$GECKO_VERSION.txz $WRKDIR
+    mkdir freebsd-pkg-foo
+    tar -xf $WRKDIR/firefox-$GECKO_VERSION.txz --strip-components 3 -C freebsd-pkg-foo
+    mv freebsd-pkg-foo/lib/firefox firefox
+    arch=amd64
+    rm -rf firefox-$arch
+    mv firefox firefox-$arch
+    cd firefox-$arch
+    modify_omni freebsd
+    extract_devtools
+    cd ..
 fi
 
 if [ $BUILD_LINUX == 1 ]; then
@@ -255,4 +275,4 @@
 	fi
 fi
 
-echo Done
\ No newline at end of file
+echo Done
