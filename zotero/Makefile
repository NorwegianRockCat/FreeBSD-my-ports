# Created by: Trenton Schulz <trentonw@ifi.uio.no>
# $FreeBSD$

PORTNAME=	zotero
PORTVERSION=	5.0.28
CATEGORIES=	deskutils

MAINTAINER=	trentonw@ifi.uio.no
COMMENT=	Tool to collect, organize, cite, and share your research sources

LICENSE=	AGPLv3

WWW=	https://www.zotero.org
USE_GITHUB=	YES
GH_TUPLE=	zotero:zotero-build:b330e8e:build \
		zotero:zotero-standalone-build:5.0.26:standalonebuild \
		zotero:translators:8a9cf2d:translators/translators \
		zotero:bundled-styles:665b7f5:styles/styles \
		citation-style-language:locales:ed11f07:csl/chrome/content/zotero/locale/csl \
		egh:zotero-transfw:b820c6d:transfw \
		zotero:zotero-libreoffice-integration:c1f6d8d:libreoffice \
		zotero:zotero-word-for-mac-integration:b9e1527:macword \
		zotero:zotero-word-for-windows-integration:106f9e41:winword

BUILD_DEPENDS+=	bash:shells/bash \
		npm:www/npm \

LIB_DEPENDS+=	libv4l2.so:multimedia/libv4l \
		libgraphite2.so:graphics/graphite2 \
		libharfbuzz.so:print/harfbuzz \
		libogg.so:audio/libogg \
		libvorbis.so:audio/libvorbis \
		libdbus-glib-1.so:devel/dbus-glib \
		libdbus-1.so:devel/dbus \
		libstartup-notification-1.so:x11/startup-notification

USE_XORG+=	xcb
USE_GECKO=	gecko
USE_MOZILLA=	libxul
PATCH_WRKSRC	= ${WRKDIR}

INSTALL_TARGET=	install-strip

post-extract:
	${MV} ${WRKSRC_transfw}/* ${WRKSRC_build}/xpi/zotero-transfw
	${MV} ${WRKSRC_libreoffice}/* ${WRKSRC_standalonebuild}/modules/zotero-libreoffice-integration
	${MV} ${WRKSRC_winword}/* ${WRKSRC_standalonebuild}/modules/zotero-word-for-windows-integration
	${MV} ${WRKSRC_macword}/* ${WRKSRC_standalonebuild}/modules/zotero-word-for-mac-integration
	${LN} -s ${WRKSRC} ${WRKDIR}/zotero-client
	${LN} -s ${WRKSRC_build} ${WRKDIR}/zotero-build

do-configure:
	cd ${WRKSRC} && \
		npm i

do-build:
	cd ${WRKSRC} && \
		npm run build
	cd ${WRKSRC_standalonebuild} && \
		./fetch_xulrunner.sh -p f
	cd ${WRKSRC_standalonebuild} && \
		./scripts/dir_build

pre-install:
	${RM} ${WRKSRC_standalonebuild}/staging/Zotero_freebsd-amd64/extensions/zoteroOpenOfficeIntegration@zotero.org/scripts/symlink_sdk.orig

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/zotero
	(cd ${WRKSRC_standalonebuild}/staging/Zotero_freebsd-${ARCH} && ${COPYTREE_BIN} . ${STAGEDIR}${PREFIX}/lib/zotero)
	(cd ${STAGEDIR}${PREFIX}/bin && ${LN} -sf ../lib/zotero/zotero zotero)

.include <bsd.port.mk>
