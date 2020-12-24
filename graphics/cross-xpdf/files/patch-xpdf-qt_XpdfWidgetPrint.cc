--- xpdf-qt/XpdfWidgetPrint.cc.orig	2019-09-25 19:54:33 UTC
+++ xpdf-qt/XpdfWidgetPrint.cc
@@ -21,7 +21,7 @@
 #elif defined(__APPLE__)
 #  include <CoreFoundation/CoreFoundation.h>
 #  include <ApplicationServices/ApplicationServices.h>
-#elif defined(__linux__)
+#elif defined(__linux__) || defined(__FreeBSD__)
 #  include "PSOutputDev.h"
 #  include <cups/cups.h>
 #endif
@@ -315,7 +315,7 @@ XpdfWidget::ErrorCode printPDF(PDFDoc *doc, QPrinter *
 // Linux
 //------------------------------------------------------------------------
 
-#elif defined(__linux__)
+#elif defined(__linux__) || defined(__FreeBSD__)
 
 static void fileOut(void *stream, const char *data, int len) {
   fwrite(data, 1, len, (FILE *)stream);
