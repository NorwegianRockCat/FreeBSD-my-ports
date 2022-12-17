--- zotero-standalone-build-fd20ee4/fetch_xulrunner.sh.orig	2020-10-27 06:43:41 UTC
+++ zotero-standalone-build-fd20ee4/fetch_xulrunner.sh
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
 DONE
 	exit 1
 }
@@ -34,6 +34,7 @@ DONE
 BUILD_MAC=0
 BUILD_WIN32=0
 BUILD_LINUX=0
+BUILD_FREEBSD=0
 while getopts "p:s" opt; do
 	case $opt in
 		p)
@@ -43,6 +44,7 @@ while getopts "p:s" opt; do
 					m) BUILD_MAC=1;;
 					w) BUILD_WIN32=1;;
 					l) BUILD_LINUX=1;;
+					f) BUILD_FREEBSD=1;;
 					*)
 						echo "$0: Invalid platform option ${OPTARG:i:1}"
 						usage
@@ -55,7 +57,7 @@ while getopts "p:s" opt; do
 done
 
 # Require at least one platform
-if [[ $BUILD_MAC == 0 ]] && [[ $BUILD_WIN32 == 0 ]] && [[ $BUILD_LINUX == 0 ]]; then
+if [[ $BUILD_MAC == 0 ]] && [[ $BUILD_WIN32 == 0 ]] && [[ $BUILD_LINUX == 0 ]] && [[ $BUILD_FREEBSD == 0 ]]; then
 	usage
 fi
 
@@ -199,6 +201,24 @@ if [ $BUILD_MAC == 1 ]; then
 	if [ ! -e "Firefox $GECKO_VERSION MacOS.zip" ]; then
 		rm "MacOS.zip"
 	fi
+fi
+
+if [ $BUILD_FREEBSD == 1 ]; then
+    GECKO_VERSION="esr-60.8.0_4,1"
+    rm -rf firefox
+    rm -rf freebsd-pkg-foo
+
+    cp $WRKDIR/../firefox-$GECKO_VERSION.pkg $WRKDIR
+    mkdir freebsd-pkg-foo
+    tar -xf $WRKDIR/firefox-$GECKO_VERSION.pkg --strip-components 3 -C freebsd-pkg-foo
+    mv freebsd-pkg-foo/lib/firefox firefox
+    arch=amd64
+    rm -rf firefox-$arch
+    mv firefox firefox-$arch
+    cd firefox-$arch
+    modify_omni freebsd
+    extract_devtools
+    cd ..
 fi
 
 if [ $BUILD_WIN32 == 1 ]; then
