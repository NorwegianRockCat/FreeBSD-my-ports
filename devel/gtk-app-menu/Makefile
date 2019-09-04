# $FreeBSD$

PORTNAME=	appmenu-gtk-module
DISTVERSION=	0.7.1
CATEGORIES=	devel

MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	GTK module for putting application menubar in a global menubar

LICENSE=	LGPL3
LICENSE_FILE=	${WRKSRC}/subprojects/appmenu-gtk-module/LICENSE

USES=	cmake:outsource

CMAKE_SOURCE_PATH=	${WRKSRC}/subprojects/appmenu-gtk-module

USE_GNOME=	gtk30 glib20 gtk20

USE_GITLAB=	yes
GL_ACCOUNT=	vala-panel-project
GL_PROJECT=	vala-panel-appmenu
GL_COMMIT=	3801c081f674bda881f410fc7a71157285189b56

.include <bsd.port.mk>
