--- fetch_xulrunner.sh.orig	2017-12-25 18:49:24.604721000 -0600
+++ fetch_xulrunner.sh	2017-11-21 05:16:25.461850000 -0600
@@ -1,4 +1,4 @@
-#!/bin/bash
+#!/usr/local/bin/bash
 set -euo pipefail
 
 # Copyright (c) 2011  Zotero
@@ -26,7 +26,7 @@
 	cat >&2 <<DONE
 Usage: $0 -p platforms
 Options
- -p PLATFORMS        Platforms to build (m=Mac, w=Windows, l=Linux)
+ -p PLATFORMS        Platforms to build (m=Mac, w=Windows, l=Linux f=FreeBSD)
 DONE
 	exit 1
 }
@@ -34,6 +34,7 @@
 BUILD_MAC=0
 BUILD_WIN32=0
 BUILD_LINUX=0
+BUILD_FREEBSD=0
 while getopts "p:" opt; do
 	case $opt in
 		p)
@@ -43,6 +44,7 @@
 					m) BUILD_MAC=1;;
 					w) BUILD_WIN32=1;;
 					l) BUILD_LINUX=1;;
+					f) BUILD_FREEBSD=1;;
 					*)
 						echo "$0: Invalid platform option ${OPTARG:i:1}"
 						usage
@@ -55,7 +57,7 @@
 done
 
 # Require at least one platform
-if [[ $BUILD_MAC == 0 ]] && [[ $BUILD_WIN32 == 0 ]] && [[ $BUILD_LINUX == 0 ]]; then
+if [[ $BUILD_MAC == 0 ]] && [[ $BUILD_WIN32 == 0 ]] && [[ $BUILD_LINUX == 0 ]] && [[ $BUILD_FREEBSD == 0 ]]; then
 	usage
 fi
 
@@ -159,6 +161,26 @@
 	cd ..
 	
 	rm "Firefox%20Setup%20$GECKO_VERSION.exe"
+fi
+
+
+if [ $BUILD_FREEBSD == 1 ]; then
+	GECKO_VERSION="esr-52.4.1_5,1" 
+	DOWNLOAD_URL="https://ftp.mozilla.org/pub/firefox/releases/$GECKO_VERSION"
+	rm -rf firefox
+	rm -rf freebsd-pkg-foo
+	
+	#curl -O "$DOWNLOAD_URL/linux-i686/en-US/firefox-$GECKO_VERSION.tar.bz2"
+	sudo pkg fetch -y firefox-$GECKO_VERSION
+	mkdir freebsd-pkg-foo
+	tar -xf /usr/local/tmp/firefox-$GECKO_VERSION.txz --strip-components 3 -C freebsd-pkg-foo
+	mv freebsd-pkg-foo/lib/firefox firefox
+	rm -rf firefox-x86_64
+	mv firefox firefox-x86_64
+	cd firefox-x86_64
+	modify_omni
+	extract_devtools
+	cd ..
 fi
 
 if [ $BUILD_LINUX == 1 ]; then
@@ -187,4 +209,4 @@
 	rm "firefox-$GECKO_VERSION.tar.bz2"
 fi
 
-echo Done
\ No newline at end of file
+echo Done
