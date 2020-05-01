# Created by: Trenton Schulz <trueos@norwegianrockcat.com>
# $FreeBSD$

PORTNAME=	jotta-cli
PORTVERSION=	0.6.24251
CATEGORIES=	net
MASTER_SITES=	https://repo.jotta.us/archives/freebsd/${ARCH:S|amd64|amd64|:S|i386|386|}/

DISTNAME=	${PORTNAME}-${PORTVERSION}_freebsd_${ARCH:S|amd64|amd64|:S|i386|386|}

MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	Jotta Cloud Daemon and Command-Line Interface

LICENSE=	UNKNOWN
LICENSE_NAME=	"Jottacloud Terms and Service"
LICENSE_TEXT=	"JottaCloud has its own terms and conditions available at https://www.jottacloud.com/en/terms.html"
LICENSE_PERMS=	dist-mirror no-dist-sell pkg-mirror no-pkg-sell auto-accept

RUN_DEPENDS=	${LOCALBASE}/share/certs/ca-root-nss.crt:security/ca_root_nss

RESTRICTED=	yes
USERS=	jottad
GROUPS=	jottad

NO_BUILD=	yes

ONLY_FOR_ARCHS=	amd64 i386

USE_RC_SUBR=	jottad

SUB_FILES=	pkg-message \
		jottad

do-install:
	${INSTALL_SCRIPT} ${WRKDIR}/jottad ${STAGEDIR}${PREFIX}/etc/rc.d/jottad
	${INSTALL_PROGRAM} ${WRKDIR}/usr/bin/jotta-cli ${STAGEDIR}${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKDIR}/usr/bin/jottad ${STAGEDIR}${PREFIX}/sbin
	${MKDIR} ${STAGEDIR}/var/lib/jottad
	${MKDIR} ${STAGEDIR}${PREFIX}/etc/jottad
	${INSTALL_DATA} ${WRKDIR}/etc/jottad/config.ini ${STAGEDIR}${PREFIX}/etc/jottad/config.ini.sample

.include <bsd.port.mk>
