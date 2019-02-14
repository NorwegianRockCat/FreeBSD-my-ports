--- src/rosdep2/__init__.py.orig	2017-08-04 00:33:42 UTC
+++ src/rosdep2/__init__.py
@@ -64,10 +64,11 @@ def create_default_installer_context(verbose=False):
     from .platforms import pip
     from .platforms import gem
     from .platforms import redhat
+    from .platforms import freebsd
     from .platforms import slackware
     from .platforms import source
 
-    platform_mods = [arch, cygwin, debian, gentoo, opensuse, osx, redhat, slackware]
+    platform_mods = [arch, cygwin, debian, gentoo, opensuse, osx, redhat, slackware, freebsd]
     installer_mods = [source, pip, gem] + platform_mods
 
     context = InstallerContext()
