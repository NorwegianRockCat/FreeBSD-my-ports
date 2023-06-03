PORTNAME=	scanbd
PORTVERSION=	1.5.1
CATEGORIES=	graphics
MASTER_SITES=	SF/${PORTNAME}/releases

MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	Scanbd is a scanner button daemon looking for scanner button pressed
WWW=	https://sourceforge.net/projects/scanbd/

LICENSE=	GPLv2

LIB_DEPENDS=	libdbus-1.so:devel/dbus \
		libudev.so:devel/libudev-devd \
		libconfuse.so:devel/libconfuse
RUN_DEPENDS=	bash:shells/bash \
		scanimage:graphics/sane-backends

USES=	gettext-runtime gmake pkgconfig shebangfix tar:tgz

WRKSRC=	${WRKDIR}/${PORTVERSION}

GNU_CONFIGURE=	yes

CONFIGURE_ARGS+=	--with-user --with-group

SHEBANG_GLOB= *.script

USE_RC_SUBR=	scanbd

SUB_FILES=	scanbd

post-install:
	${INSTALL_SCRIPT} ${WRKDIR}/scanbd ${STAGEDIR}${PREFIX}/etc/rc.d/scanbd

.include <bsd.port.mk>
