--- zotero-6.0.13/scripts/pdf-reader.js.orig	2022-08-27 12:06:06 UTC
+++ zotero-6.0.13/scripts/pdf-reader.js
@@ -36,7 +36,7 @@ async function getPDFReader(signatures) {
 			await fs.remove(path.join(targetDir, 'zotero'));
 		}
 		catch (e) {
-			await exec('npm ci', { cwd: modulePath });
+			await exec('npm ci --legacy-peer-dep', { cwd: modulePath });
 			await exec('npm run build', { cwd: modulePath });
 			await fs.copy(path.join(modulePath, 'build', 'zotero'), targetDir);
 		}
