# Created by: Trenton Schulz <trentonw@ifi.uio.no>
# $FreeBSD$

PORTNAME=	zotero
PORTVERSION=	6.0.18
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
		zotero:utilities:3143d55:zotero_utilities/chrome/content/zotero/xpcom/translate/modules/utilities \
                zotero:zotero-schema:c9f6c78:zotero_zotero_schema/chrome/content/zotero/xpcom/utilities/resource/schema/global \
                zotero:translators:8c9da9b034a851c2d22e15aa3c31206d1f2b0f06:zotero_translators/translators \
                citation-style-language:locales:e243665390f80c67487df7295938680142bb9570:citation_style_language_locales/chrome/content/zotero/locale/csl \
                zotero:bundled-styles:d230dc72e9e0622bbf89eb83a223f89bc6ff07f0:zotero_bundled_styles/styles \
                zotero:zotero-schema:c9f6c78:zotero_zotero_schema/resource/schema/global \
                gildas-lormeau:SingleFile:0496d2d682babca16f7f2bf56f9428448cd9961f:gildas_lormeau_SingleFile/resource/SingleFile \
                zotero:pdf-reader:c549f77:zotero_pdf_reader/pdf-reader \
                zotero:pdf-worker:e9160562148a52edac5e1623133833f139ea1cb9:zotero_pdf_worker/pdf-worker \
                zotero:note-editor:093ff40b1c011579e98e5266c9762979bcd8059d:zotero_note_editor/note-editor \
                zotero:utilities:3143d55:zotero_utilities/chrome/content/zotero/xpcom/utilities \
                zotero:translate:586a893ee2e0b4e6d5c6afeac3dada8fb1ac556f:zotero_translate/chrome/content/zotero/xpcom/translate \
                fonttools:fonttools:66a3ec90713375aec5a95d1698ef1521fd432918:fonttools_fonttools/pdf-reader/pdf.js/test/ttx/fonttools-code \
                zotero:pdf.js:fdde957:zotero_pdf_js/pdf-reader/pdf.js \
		zotero:zotero-build:00e854c:build \
		zotero:zotero-standalone-build:fd20ee4:standalonebuild \
		egh:zotero-transfw:bd55dc1:transfw \
		zotero:zotero-libreoffice-integration:1d747aad99ef48099cc23ab8904b2b84f919e07b:libreoffice \
		zotero:zotero-word-for-mac-integration:ce04963:macword \
		zotero:zotero-word-for-windows-integration:c8a6407:winword

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
