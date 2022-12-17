--- zotero-6.0.18/scripts/pdf-worker.js.orig	2022-08-27 12:07:39 UTC
+++ zotero-6.0.18/scripts/pdf-worker.js
@@ -33,7 +33,7 @@ async function getPDFWorker(signatures) {
 			);
 		}
 		catch (e) {
-			await exec('npm ci', { cwd: modulePath });
+			await exec('npm ci --legacy-peer-dep', { cwd: modulePath });
 			await exec('npm run build', { cwd: modulePath });
 			await fs.copy(path.join(modulePath, 'build', 'worker.js'), path.join(targetDir, 'worker.js'));
 		}
