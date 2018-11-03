# Created by: Trenton Schulz <trueos@norwegianrockcat.com>
# $FreeBSD$

PORTNAME=	ibm-plex
DISTVERSION=	1.2.1
CATEGORIES=	x11-fonts
MASTER_SITES=	https://github.com/IBM/plex/releases/download/v${DISTVERSION}/
DISTNAME=	OpenType

MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	IBM Plex Typeface

LICENSE=	OFL11

USES=		fonts
USES+=		zip
USE_XORG=	x11

NO_ARCH=	yes
NO_BUILD=	yes

do-install:
	@${MKDIR} ${STAGEDIR}${FONTSDIR}
	${FIND} ${WRKDIR}/OpenType -type f -name \*.otf | while read f; do \
		${INSTALL_DATA} $$f ${STAGEDIR}${FONTSDIR} ; done

.include <bsd.port.mk>
