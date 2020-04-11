# Created by: Andrew Thompson <thompsa@FreeBSD.org>
# $FreeBSD$

PORTNAME=	remarkable-devd
PORTVERSION=	1.0
CATEGORIES=	net
MASTER_SITES=	#
DISTFILES=      #

MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	Devd hotplug rules for Remarkable Tablet

LICENSE=	BSD2CLAUSE

NO_BUILD=	yes

USE_RC_SUBR=	remarkable

SUB_FILES=	pkg-message \
		remarkable.conf

PLIST_FILES=	etc/devd/remarkable.conf \
		etc/rc.d/remarkable
do-install:
	${INSTALL_DATA} ${WRKDIR}/remarkable.conf ${STAGEDIR}${PREFIX}/etc/devd/remarkable.conf
	${INSTALL_SCRIPT} ${WRKDIR}/remarkable ${STAGEDIR}${PREFIX}/etc/rc.d/remarkable

.include <bsd.port.mk>
