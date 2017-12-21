--- src/rosdep2/platforms/freebsd.py.orig	2017-08-04 00:33:42 UTC
+++ src/rosdep2/platforms/freebsd.py
@@ -28,60 +28,55 @@
 
 # Original from cygwin.py by Tingfan Wu tingfan@gmail.com
 # Modified for FreeBSD by Rene Ladan rene@freebsd.org
+# Updated for FreeBSD with pkg by Trenton Schulz trentonw@ifi.Io.no
 
 import os
 import subprocess
 
 from rospkg.os_detect import OS_FREEBSD
 
+from .pip import PIP_INSTALLER
+from .gem import GEM_INSTALLER
 from .source import SOURCE_INSTALLER
-from ..installers import Installer
+from ..installers import PackageManagerInstaller
+from ..shell_utils import read_stdout
 
-PKG_ADD_INSTALLER = 'pkg_add'
+PKG_INSTALLER = 'pkg'
 
 def register_installers(context):
-    context.set_installer(PKG_ADD_INSTALLER, PkgAddInstaller())
+    context.set_installer(PKG_INSTALLER, PkgInstaller())
     
 def register_platforms(context):
     context.add_os_installer_key(OS_FREEBSD, SOURCE_INSTALLER)
-    context.add_os_installer_key(OS_FREEBSD, PKG_ADD_INSTALLER)
-    context.set_default_os_installer_key(OS_FREEBSD, lambda self: PKG_ADD_INSTALLER)
+    context.add_os_installer_key(OS_FREEBSD, PKG_INSTALLER)
+    context.add_os_installer_key(OS_FREEBSD, PIP_INSTALLER)
+    context.set_default_os_installer_key(OS_FREEBSD, lambda self: PKG_INSTALLER)
 
-def pkg_info_detect_single(p):
+def pkg_detect_single(p, exec_fn):
     if p == "builtin":
         return True
-    # The next code is a lot of hassle, but there is no
-    # better way in FreeBSD using just the base tools
     portname = p
-    if p == "gtk20":
-        portname = "gtk-2.\*"
-    elif p == "py-gtk2":
-        portname = "py27-gtk-2.\*"
-    elif p[:9] in ["autoconf2", "automake1"]:
-        portname = p[:8] + "-" + p[8] + "." + p[9:] + "\*"
-    elif p[:3] == "py-":
-        portname = "py27-" + p[3:] + "\*"
-    else:
-        portname = p + "-\*"
-    pop = subprocess.Popen("/usr/sbin/pkg_info -qE " + portname, shell=True)
-    return os.waitpid(pop.pid, 0)[1] == 0 # pkg_info -E returns 0 if pkg installed, 1 if not
+    cmd = ['/usr/bin/pkg', 'query', '%n', p]
+    std_out = exec_fn(cmd)
+    return std_out.split() != []
 
-def pkg_info_detect(packages):
-    return [p for p in packages if pkg_info_detect_single(p)]
+def pkg_detect(packages, exec_fn=None):
+    if exec_fn is None:
+        exec_fn = read_stdout
+    return [p for p in packages if pkg_detect_single(p, exec_fn)]
 
-class PkgAddInstaller(Installer):
+class PkgInstaller(PackageManagerInstaller):
     """
     An implementation of the Installer for use on FreeBSD-style
     systems.
     """
 
     def __init__(self):
-        super(PkgAddInstaller, self).__init__(pkg_info_detect)
+        super(PkgInstaller, self).__init__(pkg_detect)
 
     def get_install_command(self, resolved, interactive=True, reinstall=False, quiet=False):
         packages = self.get_packages_to_install(resolved, reinstall=reinstall)        
         if not packages:
             return []
         else:
-            #pkg_add does not have a non-interactive command
-            return [self.elevate_priv(['/usr/sbin/pkg_add', '-r'])+packages]
+            return [self.elevate_priv(['/usr/sbin/pkg', 'install', '-y'])+packages]
