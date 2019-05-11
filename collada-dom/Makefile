# $FreeBSD$

PORTNAME=	collada-dom
DISTVERSION=	2.5.0
CATEGORIES=	devel

MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	COLLADA Document Object Model (DOM) C++ Library
LIB_DEPENDS+=	libminizip.so:archivers/minizip \
		libpcre.so:devel/pcre \
		libboost_filesystem.so:devel/boost-libs \
		libboost_system.so:devel/boost-libs \

USE_GNOME+=	libxml2


LICENSE=	MIT

USES=	cmake

USE_GITHUB=	yes
GH_ACCOUNT=	rdiankov
GH_PROJECT=	collada-dom
GH_TAGNAME=	v${DISTVERSIONPREFIX}${DISTVERSION}${DISTVERSIONSUFFIX}

.include <bsd.port.mk>
