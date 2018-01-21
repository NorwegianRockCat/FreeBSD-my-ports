# $FreeBSD$

PORTNAME=	ros-rosinstall_generator
DISTVERSION=	0.1.13
CATEGORIES=	devel

MAINTAINER=	trentonw@ifi.uio.no
COMMENT=	Generator tool for a ROS install distro

LICENSE=	BSD3CLAUSE

WWW=	http://github.com/ros-infrastructure/rosinstall_generator
USES=	python
#py27_LIB_DEPENDS=	devel/py-argparse
#py27_LIB_DEPENDS=	devel/py-yaml
#py36_LIB_DEPENDS=	devel/py-argparse
#py36_LIB_DEPENDS=	devel/py-yaml
USE_PYHTON=	distutils autoplist
USE_GITHUB=	yes
GH_ACCOUNT=	ros-infrastructure
GH_PROJECT=	rosinstall_generator
GH_TAGNAME=	0.1.13

do-install:
	(cd ${WRKSRC} && python setup.py install --root ${STAGEDIR})

.include <bsd.port.mk>
