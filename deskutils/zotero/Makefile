# Created by: Trenton Schulz <trentonw@ifi.uio.no>
# $FreeBSD$

PORTNAME=	zotero
PORTVERSION=	6.0.13
CATEGORIES=	deskutils

MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	Tool to collect, organize, cite, and share your research sources

LICENSE=	AGPLv3

WWW=	https://www.zotero.org

BUILD_DEPENDS+=	bash:shells/bash \
		zip:archivers/zip \
		rsync:net/rsync \
		npm:www/npm

LIB_DEPENDS+=	libv4l2.so:multimedia/libv4l \
		libgraphite2.so:graphics/graphite2 \
		libharfbuzz.so:print/harfbuzz \
		libogg.so:audio/libogg \
		libvorbis.so:audio/libvorbis \
		libdbus-glib-1.so:devel/dbus-glib \
		libdbus-1.so:devel/dbus \
		libstartup-notification-1.so:x11/startup-notification \
		libicui18n.so:devel/icu \
		libicuuc.so:devel/icu \
		libffi.so:devel/libffi \
		libplds4.so:devel/nspr \
		libplc4.so:devel/nspr \
		libnspr4.so:devel/nspr \
		libfreetype.so:print/freetype2 \
		libfontconfig.so:x11-fonts/fontconfig \
		libpng16.so:graphics/png \
		libhunspell-1.7.so:textproc/hunspell \
		libevent.so:devel/libevent \
		libvpx.so:multimedia/libvpx \
		libssl3.so:security/nss \
		libsmime3.so:security/nss \
		libnss3.so:security/nss

USES+=gnome jpeg sqlite desktop-file-utils shebangfix python xorg
USE_XORG+=xt x11 xcb pixman xext xrender xdamage xfixes xcomposite
USE_GNOME+=glib20 gtk20 atk pango gdkpixbuf2 cairo gtk30
USE_GITHUB=	YES

GH_TUPLE=       \
		zotero:utilities:d4e514c:zotero_utilities/chrome/content/zotero/xpcom/translate/modules/utilities \
                zotero:zotero-schema:628358f04b967a7669063cc3713d6fe593750570:zotero_zotero_schema/chrome/content/zotero/xpcom/utilities/resource/schema/global \
                zotero:translators:4207a89:zotero_translators/translators \
                citation-style-language:locales:e637746677fd1f600173e07b561f0388284ae39b:citation_style_language_locales/chrome/content/zotero/locale/csl \
                zotero:bundled-styles:d7d906e:zotero_bundled_styles/styles \
                zotero:zotero-schema:16209600854fd472fc3188290b2228dec9c19adc:zotero_zotero_schema/resource/schema/global \
                gildas-lormeau:SingleFile:45519bb2f7ee2ddce85382eea1b7b3aceca43fc2:gildas_lormeau_SingleFile/resource/SingleFile \
                zotero:pdf-reader:7f17b3e:zotero_pdf_reader/pdf-reader \
                zotero:pdf-worker:a5b612c866b11b3625605e840cc1d27d610b65e7:zotero_pdf_worker/pdf-worker \
                zotero:note-editor:5920f9674eeef6da5b43128248b82033cbd0c471:zotero_note_editor/note-editor \
                zotero:utilities:4d8d7d3e92cbc3b4d62b82478e212a6f63b9a35f:zotero_utilities/chrome/content/zotero/xpcom/utilities \
                zotero:translate:1de1a0e56d2b7d7a93e75d3cbe426aa3ad4291d3:zotero_translate/chrome/content/zotero/xpcom/translate \
                behdad:fonttools:8388a2e:behdad_fonttools/pdf-reader/pdf.js/test/ttx/fonttools-code \
                zotero:pdf.js:7ea75b5:zotero_pdf_js/pdf-reader/pdf.js \
		zotero:zotero-build:00e854c:build \
		zotero:zotero-standalone-build:4486a69:standalonebuild \
		egh:zotero-transfw:bd55dc1:transfw \
		zotero:zotero-libreoffice-integration:8e12c06:libreoffice \
		zotero:zotero-word-for-mac-integration:ab97a23:macword \
		zotero:zotero-word-for-windows-integration:1e34709:winword

PATCH_WRKSRC=	${WRKDIR}

INSTALL_TARGET=	install-strip

# There is some sort of things that are going wrong with pdf-reader. So, do so playing around since I'm unsure what is going wrong
post-extract:
	${MV} ${WRKSRC_transfw}/* ${WRKSRC_build}/xpi/zotero-transfw
	${MV} ${WRKSRC_libreoffice}/* ${WRKSRC_standalonebuild}/modules/zotero-libreoffice-integration
	${MV} ${WRKSRC_winword}/* ${WRKSRC_standalonebuild}/modules/zotero-word-for-windows-integration
	${MV} ${WRKSRC_macword}/* ${WRKSRC_standalonebuild}/modules/zotero-word-for-mac-integration
	${CP} -R ${WRKSRC_zotero_pdf_reader}/pdf.js ${WRKSRC}/pdf-worker
	${MV} ${WRKSRC}/pdf-reader/pdf.js ${WRKSRC}/pdf-reader/pdf.js.unsure
	${CP} -R ${WRKSRC_zotero_pdf_reader}/pdf-reader*/ ${WRKSRC}/pdf-reader
	${RMDIR} ${WRKSRC}/pdf-reader/pdf.js
	${MV} ${WRKSRC}/pdf-reader/pdf.js.unsure ${WRKSRC}/pdf-reader/pdf.js
	${LN} -s ${WRKSRC} ${WRKDIR}/zotero-client
	${LN} -s ${WRKSRC_build} ${WRKDIR}/zotero-build

do-configure:
	PUPPETEER_SKIP_CHROMIUM_DOWNLOAD=true cd ${WRKSRC} && \
		npm install --legacy-peer-dep

do-build:
	PUPPETEER_SKIP_CHROMIUM_DOWNLOAD=true cd ${WRKSRC} && \
		npm run build
	cd ${WRKSRC_standalonebuild} && \
		${SETENV} WRKDIR=${WRKDIR} ./fetch_xulrunner.sh -p f
	cd ${WRKSRC_standalonebuild} && \
		./scripts/dir_build

pre-install:
	${RM} ${WRKSRC_standalonebuild}/staging/Zotero_freebsd-amd64/extensions/zoteroOpenOfficeIntegration@zotero.org/scripts/symlink_sdk.orig

do-install:
.for dir in chrome components defaults dictionaries
	${MKDIR} ${STAGEDIR}${PREFIX}/share/zotero/${dir}
	(cd ${WRKSRC_standalonebuild}/staging/Zotero_freebsd-${ARCH}/${dir} && ${COPYTREE_SHARE} . ${STAGEDIR}${PREFIX}/share/zotero/${dir})
.endfor
.for dir in extensions
	${MKDIR} ${STAGEDIR}${PREFIX}/share/zotero/${dir}
	(cd ${WRKSRC_standalonebuild}/staging/Zotero_freebsd-${ARCH}/${dir} && ${COPYTREE_BIN} . ${STAGEDIR}${PREFIX}/share/zotero/${dir})
.endfor
.for bin in zotero-bin plugin-container
	${INSTALL_PROGRAM} ${WRKSRC_standalonebuild}/staging/Zotero_freebsd-${ARCH}/${bin} ${STAGEDIR}${PREFIX}/share/zotero
.endfor
.for lib in liblgpllibs.so libmozavcodec.so libmozavutil.so libmozgtk.so libmozwayland.so libxul.so
	${INSTALL_LIB} ${WRKSRC_standalonebuild}/staging/Zotero_freebsd-${ARCH}/${lib} ${STAGEDIR}${PREFIX}/share/zotero
.endfor
.for script in zotero
	${INSTALL_SCRIPT} ${WRKSRC_standalonebuild}/staging/Zotero_freebsd-${ARCH}/${script} ${STAGEDIR}${PREFIX}/share/zotero
.endfor
.for data in application.ini chrome.manifest dependentlibs.list omni.ja platform.ini updater.ini zotero.jar
	${INSTALL_DATA} ${WRKSRC_standalonebuild}/staging/Zotero_freebsd-${ARCH}/${data} ${STAGEDIR}${PREFIX}/share/zotero
.endfor
	${MKDIR} ${STAGEDIR}${PREFIX}/share/zotero/gmp-clearkey/0.1
	${INSTALL_LIB} ${WRKSRC_standalonebuild}/staging/Zotero_freebsd-${ARCH}/gmp-clearkey/0.1/libclearkey.so ${STAGEDIR}${PREFIX}/share/zotero/gmp-clearkey/0.1
	${INSTALL_DATA} ${WRKSRC_standalonebuild}/staging/Zotero_freebsd-${ARCH}/zotero.desktop ${STAGEDIR}${PREFIX}/share/applications
	${RLN} ${STAGEDIR}${PREFIX}/share/zotero/zotero ${STAGEDIR}${PREFIX}/bin/zotero

.include <bsd.port.mk>
