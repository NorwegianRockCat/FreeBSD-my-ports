# Created by: Trenton Schulz <trentonw@ifi.uio.no>
# $FreeBSD$

PORTNAME=	zotero
PORTVERSION=	5.0.28
CATEGORIES=	print

MAINTAINER=	trentonw@ifi.uio.no
COMMENT=	Tool to collect, organize, cite, and share your research sources.

LICENSE=	AGPLv3

WWW=	https://www.zotero.org
USE_GITHUB=	YES
GH_TUPLE=	zotero:zotero-build:b330e8e:build \
		zotero:zotero-standalone-build:5.0.26:standalonebuild \
		zotero:translators:8a9cf2d:translators/translators \
		zotero:bundled-styles:665b7f5:styles/styles \
		citation-style-language:locales:ed11f07:csl/chrome/content/zotero/locale/csl \

BUILD_DEPENDS=	bash:shells/bash \
		npm:www/npm \

PATCH_WRKSRC	= ${WRKSRC_standalonebuild}
USE_FIREFOX_BUILD=	52

do-configure:
	cd ${WRKSRC} && \
		npm i


.include <bsd.port.mk>
