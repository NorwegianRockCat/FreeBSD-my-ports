# Created by: Trenton Schulz <trentonw@ifi.uio.no>
# $FreeBSD$

PORTNAME=	zotero
PORTVERSION=	5.0.93
CATEGORIES=	deskutils

MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	Tool to collect, organize, cite, and share your research sources

LICENSE=	AGPLv3

WWW=	https://www.zotero.org

BUILD_DEPENDS+=	bash:shells/bash \
		zip:archivers/zip \
		rsync:net/rsync \
		npm:www/npm-node10

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
USE_GNOME+=glib20 gtk20 atk pango gdkpixbuf2 cairo
USE_GITHUB=	YES
GH_TUPLE=	zotero:zotero-build:468b2a1:build \
		zotero:zotero-standalone-build:64abfb6:standalonebuild \
		zotero:translators:dc09a7c:translators/translators \
		zotero:bundled-styles:12b178d:styles/styles \
		zotero:zotero-schema:68ad875:schema \
		citation-style-language:locales:914e058:csl/chrome/content/zotero/locale/csl \
		egh:zotero-transfw:bd55dc1:transfw \
		zotero:zotero-libreoffice-integration:440ce92:libreoffice \
		zotero:zotero-word-for-mac-integration:da72454:macword \
		zotero:zotero-word-for-windows-integration:c551c2e:winword

PATCH_WRKSRC=	${WRKDIR}

INSTALL_TARGET=	install-strip

post-extract:
	${MV} ${WRKSRC_transfw}/* ${WRKSRC_build}/xpi/zotero-transfw
	${MV} ${WRKSRC_libreoffice}/* ${WRKSRC_standalonebuild}/modules/zotero-libreoffice-integration
	${MV} ${WRKSRC_winword}/* ${WRKSRC_standalonebuild}/modules/zotero-word-for-windows-integration
	${MV} ${WRKSRC_macword}/* ${WRKSRC_standalonebuild}/modules/zotero-word-for-mac-integration
	${MV} ${WRKSRC_schema}/* ${WRKSRC}/resource/schema/global
	${LN} -s ${WRKSRC} ${WRKDIR}/zotero-client
	${LN} -s ${WRKSRC_build} ${WRKDIR}/zotero-build

do-configure:
	cd ${WRKSRC} && \
		npm i

do-build:
	cd ${WRKSRC} && \
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
