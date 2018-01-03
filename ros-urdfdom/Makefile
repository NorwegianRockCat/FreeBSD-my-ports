# $FreeBSD$

PORTNAME=	ros-urdfdom
DISTVERSION=	1.0.0
CATEGORIES=	devel

MAINTAINER=	trentonw@ifi.uio.no
COMMENT=	URDF parsers

LICENSE=	BSD3CLAUSE

LIB_DEPENDS+=libtinyxml.so:textproc/tinyxml \
	libconsole_bridge.so:sysutils/ros-console_bridge

WWW=	http://ros.org/wiki/urdf
USES=	cmake:outsource
USE_GITHUB=	yes
GH_ACCOUNT=	ros
GH_PROJECT=	urdfdom
GH_TAGNAME=	1.0.0

.include <bsd.port.mk>
