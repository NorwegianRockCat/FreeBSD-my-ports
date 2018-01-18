# $FreeBSD$

PORTNAME=	ros-rosdistro
DISTVERSION=	0.6.4
CATEGORIES=	devel

MAINTAINER=	trentonw@ifi.uio.no
COMMENT=	Tools to work with catkinized rosdistro files

LICENSE=	BSD3CLAUSE

WWW=	http://github.com/ros-infrastructure/rosdistro
USES=	python
USE_PYHTON=	distutils autoplist
USE_GITHUB=	yes
GH_ACCOUNT=	ros-infrastructure
GH_PROJECT=	rosdistro
GH_TAGNAME=	0.6.4

do-install:
	(cd ${WRKSRC} && python setup.py install --root ${STAGEDIR})

.include <bsd.port.mk>
