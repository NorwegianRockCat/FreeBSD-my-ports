# $FreeBSD$

PORTNAME=	ros-catkin_pkg
DISTVERSION=	0.4.0
CATEGORIES=	devel

MAINTAINER=	trentonw@ifi.uio.no
COMMENT=	Standard Python library for the catkin build system

LICENSE=	BSD3CLAUSE

WWW=	http://github.com/ros/catkin
USES=	python
py27_LIB_DEPENDS=	devel/py-argparse
#py27_LIB_DEPENDS=	devel/py-yaml
py36_LIB_DEPENDS=	devel/py-argparse
#py36_LIB_DEPENDS=	devel/py-yaml
USE_PYHTON=	distutils autoplist
USE_GITHUB=	yes
GH_ACCOUNT=	ros-infrastructure
GH_PROJECT=	catkin_pkg
GH_TAGNAME=	0.4.0

do-install:
	(cd ${WRKSRC} && python setup.py install --root ${STAGEDIR})

.include <bsd.port.mk>
