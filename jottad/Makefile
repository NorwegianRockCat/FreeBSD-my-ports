# Created by: Trenton Schulz <trueos@norwegianrockcat.com>
# $FreeBSD$

PORTNAME=	jotta-cli
PORTVERSION=	0.4.4986
CATEGORIES=	net

MASTER_SITES=	https://repo.jotta.us/archives/freebsd/${ARCH}/
DISTNAME=	${PORTNAME}-${PORTVERSION}_freebsd_${ARCH}


MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	Jotta Cloud Daemon and Command-Line Interface

LICENSE=	UNKNOWN
LICENSE_NAME=	"Jottacloud Terms and Service"
LICENSE_PERMS=	dist-mirror no-dist-sell pkg-mirror no-pkg-sell auto-accept
LICENSE_TEXT=	"JottaCloud has its own terms and conditions available at https://www.jottacloud.com/en/terms.html"

RESTRICTED=	yes
USERS=	jottad
GROUPS=	jottad

RUN_DEPENDS=	${LOCALBASE}/share/certs/ca-root-nss.crt:security/ca_root_nss

NO_BUILD=	yes

do-install:
	${CP} ${PATCHDIR}/jottad ${STAGEDIR}${PREFIX}/etc/rc.d/jottad
	${MV} ${WRKDIR}/usr/bin/jotta-cli ${STAGEDIR}${PREFIX}/bin
	${MV} ${WRKDIR}/usr/bin/jottad ${STAGEDIR}${PREFIX}/sbin
	${MV} ${WRKDIR}/usr/share/* ${STAGEDIR}${PREFIX}/share
	${MV} ${WRKDIR}/etc/* ${STAGEDIR}${PREFIX}/etc

.include <bsd.port.mk>
