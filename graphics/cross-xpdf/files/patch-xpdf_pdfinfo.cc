--- xpdf/pdfinfo.cc.orig	2019-09-25 19:54:33 UTC
+++ xpdf/pdfinfo.cc
@@ -111,6 +111,13 @@ int main(int argc, char *argv[]) {
 
   // parse args
   fixCommandLine(&argc, &argv);
+  if (argc!=3 || argv[1][0]=='-' || argv[2][0]=='-') {
+      fprintf(stderr,"This is a custom xpdf pdfinfo build. Please use the original version!\n%s\n%s\npdfinfo <PDF-file> <output-file>\n",
+	      xpdfVersion, xpdfCopyright);
+      return 1;
+  } else {
+      freopen( argv[argc-1], "w", stdout); argc--;
+  }
   ok = parseArgs(argDesc, &argc, argv);
   if (!ok || argc != 2 || printVersion || printHelp) {
     fprintf(stderr, "pdfinfo version %s\n", xpdfVersion);
