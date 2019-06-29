--- zotero-standalone-build-3f4913f/build.sh.orig	2018-04-20 20:27:58 UTC
+++ zotero-standalone-build-3f4913f/build.sh
@@ -1,4 +1,4 @@
-#!/bin/bash -e
+#!/usr/local/bin/bash -e

 # Copyright (c) 2011  Zotero
 #                     Center for History and New Media
@@ -62,6 +62,7 @@ ZIP_FILE=""
 BUILD_MAC=0
 BUILD_WIN32=0
 BUILD_LINUX=0
+BUILD_FREEBSD=0
 PACKAGE=1
 DEVTOOLS=0
 while getopts "d:f:p:c:tse" opt; do
@@ -78,6 +79,7 @@ while getopts "d:f:p:c:tse" opt; do
 				case ${OPTARG:i:1} in
 					m) BUILD_MAC=1;;
 					w) BUILD_WIN32=1;;
+					f) BUILD_FREEBSD=1;;
 					l) BUILD_LINUX=1;;
 					*)
 						echo "$0: Invalid platform option ${OPTARG:i:1}"
@@ -113,7 +115,7 @@ elif [[ -n "$SOURCE_DIR" ]] && [[ -n "$ZIP_FILE" ]]; t
 fi

 # Require at least one platform
-if [[ $BUILD_MAC == 0 ]] && [[ $BUILD_WIN32 == 0 ]] && [[ $BUILD_LINUX == 0 ]]; then
+if [[ $BUILD_MAC == 0 ]] && [[ $BUILD_WIN32 == 0 ]] && [[ $BUILD_LINUX == 0 ]] && [[ $BUILD_FREEBSD == 0 ]]; then
 	usage
 fi

@@ -542,6 +544,71 @@ if [ $BUILD_LINUX == 1 ]; then
 			rm -f "$DIST_DIR/Zotero-${VERSION}_linux-$arch.tar.bz2"
 			cd "$STAGE_DIR"
 			tar -cjf "$DIST_DIR/Zotero-${VERSION}_linux-$arch.tar.bz2" "Zotero_linux-$arch"
+		fi
+	done
+fi
+
+# FreeBSD
+if [ $BUILD_FREEBSD == 1 ]; then
+	for arch in "amd64"; do
+		RUNTIME_PATH=`eval echo '$FREEBSD_'$arch'_RUNTIME_PATH'`
+
+		# Set up directory
+		echo 'Building Zotero_freebsd-'$arch
+		APPDIR="$STAGE_DIR/Zotero_freebsd-$arch"
+		rm -rf "$APPDIR"
+		mkdir "$APPDIR"
+
+		# Merge relevant assets from Firefox
+		cp -r "$RUNTIME_PATH/"!(application.ini|browser|defaults|devtools-files|crashreporter|crashreporter.ini|firefox-bin|precomplete|removed-files|run-mozilla.sh|update-settings.ini|updater|updater.ini) "$APPDIR"
+
+		# Use our own launcher that calls the original Firefox executable with -app
+		mv "$APPDIR"/firefox "$APPDIR"/zotero-bin
+		cp "$CALLDIR/linux/zotero" "$APPDIR"/zotero
+
+		# Copy Ubuntu launcher files
+		cp "$CALLDIR/linux/zotero.desktop" "$APPDIR"
+		cp "$CALLDIR/linux/set_launcher_icon" "$APPDIR"
+
+		# Use our own updater, because Mozilla's requires updates signed by Mozilla
+		#cp "$CALLDIR/linux/updater-$arch" "$APPDIR"/updater
+
+		cp -R "$BUILD_DIR/zotero/"* "$BUILD_DIR/application.ini" "$APPDIR"
+
+		# Modify platform-specific prefs
+		perl -pi -e 's/pref\("browser\.preferences\.instantApply", false\);/pref\("browser\.preferences\.instantApply", true);/' "$BUILD_DIR/zotero/defaults/preferences/prefs.js"
+		perl -pi -e 's/%GECKO_VERSION%/'"$GECKO_VERSION_LINUX"'/g' "$BUILD_DIR/zotero/defaults/preferences/prefs.js"
+
+		# Add Unix-specific Standalone assets
+		cd "$CALLDIR/assets/unix"
+		zip -0 -r -q "$APPDIR/zotero.jar" *
+
+		# Add devtools
+		if [ $DEVTOOLS -eq 1 ]; then
+			cp -r "$RUNTIME_PATH"/devtools-files/chrome/* "$APPDIR/chrome/"
+			cp "$RUNTIME_PATH/devtools-files/components/interfaces.xpt" "$APPDIR/components/"
+		fi
+
+		# Add word processor plug-ins
+		mkdir "$APPDIR/extensions"
+		cp -RH "$CALLDIR/modules/zotero-libreoffice-integration" "$APPDIR/extensions/zoteroOpenOfficeIntegration@zotero.org"
+		perl -pi -e 's/\.SOURCE<\/em:version>/.SA.'"$VERSION"'<\/em:version>/' "$APPDIR/extensions/zoteroOpenOfficeIntegration@zotero.org/install.rdf"
+		echo
+		echo -n "$ext Version: "
+		perl -ne 'print and last if s/.*<em:version>(.*)<\/em:version>.*/\1/;' "$APPDIR/extensions/zoteroOpenOfficeIntegration@zotero.org/install.rdf"
+		echo
+		rm -rf "$APPDIR/extensions/zoteroOpenOfficeIntegration@zotero.org/.git"
+
+		# Delete extraneous files
+		find "$APPDIR" -depth -type d -name .git -exec rm -rf {} \;
+		find "$APPDIR" \( -name .DS_Store -or -name update.rdf \) -exec rm -f {} \;
+		find "$APPDIR/extensions" -depth -type d -name build -exec rm -rf {} \;
+
+		if [ $PACKAGE == 1 ]; then
+			# Create tar
+			rm -f "$DIST_DIR/Zotero-${VERSION}_freebsd-$arch.tar.bz2"
+			cd "$STAGE_DIR"
+			tar -cjf "$DIST_DIR/Zotero-${VERSION}_freebsd-$arch.tar.bz2" "Zotero_freebsd-$arch"
 		fi
 	done
 fi
