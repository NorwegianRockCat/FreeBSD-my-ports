--- src/rosdep2/catkin_support.py.orig	2017-08-04 00:33:42 UTC
+++ src/rosdep2/catkin_support.py
@@ -27,20 +27,23 @@ from .platforms.debian import APT_INSTALLER
 from .platforms.osx import BREW_INSTALLER
 from .platforms.pip import PIP_INSTALLER
 from .platforms.redhat import YUM_INSTALLER
+from .platforms.freebsd import PKG_INSTALLER
 from .rep3 import download_targets_data
 from .rosdistrohelper import get_targets
 from .rospkg_loader import DEFAULT_VIEW_KEY
 from .sources_list import get_sources_list_dir, DataSourceMatcher, SourcesListLoader
 
+
 class ValidationFailed(Exception):
     pass
 
+
 def call(command, pipe=None):
     """
     Copy of call() function from catkin-generate-debian to mimic output
     """
     working_dir = '.'
-    #print('+ cd %s && ' % working_dir + ' '.join(command))
+    # print('+ cd %s && ' % working_dir + ' '.join(command))
     process = Popen(command, stdout=pipe, stderr=pipe, cwd=working_dir)
     output, unused_err = process.communicate()
     retcode = process.poll()
@@ -49,6 +52,7 @@ def call(command, pipe=None):
     if pipe:
         return output
 
+
 def get_ubuntu_targets(rosdistro):
     """
     Get a list of Ubuntu distro codenames for the specified ROS
@@ -64,16 +68,18 @@ def get_ubuntu_targets(rosdistro):
         targets_data['electric'] = {'ubuntu': legacy_targets['electric']}
     return targets_data[rosdistro]['ubuntu']
 
+
 def get_installer(installer_name):
     """ Expected installers APT_INSTALLER, YUM_INSTALLER, ..."""
 
     installer_context = create_default_installer_context()
     return installer_context.get_installer(installer_name)
 
+
 def resolve_for_os(rosdep_key, view, installer, os_name, os_version):
     """
     Resolve rosdep key to dependencies.
-    
+
     :param os_name: OS name, e.g. 'ubuntu'
 
     :raises: :exc:`rosdep2.ResolutionError`
@@ -110,8 +116,8 @@ def get_catkin_view(rosdistro_name, os_name, os_versio
         raise ValidationFailed("""rosdep database does not have any sources.
 Please make sure you have a valid configuration in:
 \t%s
-"""%(sources_list_dir))
-    
+""" % (sources_list_dir))
+
     # for vestigial reasons, using the roskg loader, but we're only
     # actually using the backend db as resolution is not resource-name based
     lookup = RosdepLookup.create_from_rospkg(sources_loader=sources_loader)
