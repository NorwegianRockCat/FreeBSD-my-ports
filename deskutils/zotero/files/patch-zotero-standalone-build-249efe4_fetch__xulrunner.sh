--- zotero-standalone-build-249efe4/fetch_xulrunner.sh.orig	2020-07-08 09:59:53 UTC
+++ zotero-standalone-build-249efe4/fetch_xulrunner.sh
@@ -1,4 +1,4 @@
-#!/bin/bash
+#!/usr/local/bin/bash
 set -euo pipefail
 
 # Copyright (c) 2011  Zotero
@@ -26,7 +26,7 @@ function usage {
 	cat >&2 <<DONE
 Usage: $0 -p platforms [-s]
 Options
- -p PLATFORMS        Platforms to build (m=Mac, w=Windows, l=Linux)
+ -p PLATFORMS        Platforms to build (m=Mac, w=Windows, l=Linux f=FreeBSD)
  -s                  Skip download; Firefox must already be extracted in xulrunner/ directory
 DONE
 	exit 1
@@ -35,6 +35,7 @@ DONE
 BUILD_MAC=0
 BUILD_WIN32=0
 BUILD_LINUX=0
+BUILD_FREEBSD=0
 skip_download=0
 while getopts "p:s" opt; do
 	case $opt in
@@ -45,6 +46,7 @@ while getopts "p:s" opt; do
 					m) BUILD_MAC=1;;
 					w) BUILD_WIN32=1;;
 					l) BUILD_LINUX=1;;
+					f) BUILD_FREEBSD=1;;
 					*)
 						echo "$0: Invalid platform option ${OPTARG:i:1}"
 						usage
@@ -61,7 +63,7 @@ while getopts "p:s" opt; do
 done
 
 # Require at least one platform
-if [[ $BUILD_MAC == 0 ]] && [[ $BUILD_WIN32 == 0 ]] && [[ $BUILD_LINUX == 0 ]]; then
+if [[ $BUILD_MAC == 0 ]] && [[ $BUILD_WIN32 == 0 ]] && [[ $BUILD_LINUX == 0 ]] && [[ $BUILD_FREEBSD == 0 ]]; then
 	usage
 fi
 
@@ -219,6 +221,24 @@ if [ $BUILD_WIN32 == 1 ]; then
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
