# $FreeBSD$

PORTNAME=	rosinstall
DISTVERSION=	0.7.7
CATEGORIES=	devel

MAINTAINER=	trentonw@ifi.uio.no
COMMENT=	Command-line tools for maintaining a workspace of projects from multiple version-control systems, tailored for ROS.

LICENSE=	BSD3CLAUSE

WWW=	http://docs.ros.org/independent/api/rosinstall/html
USES=	python
#py27_LIB_DEPENDS=	devel/py-argparse
#py27_LIB_DEPENDS=	devel/py-yaml
#py36_LIB_DEPENDS=	devel/py-argparse
#py36_LIB_DEPENDS=	devel/py-yaml
USE_PYHTON=	distutils autoplist
USE_GITHUB=	yes
GH_ACCOUNT=	vcstools
GH_PROJECT=	rosinstall
GH_TAGNAME=	0.7.7

do-install:
	(cd ${WRKSRC} && python setup.py install --root ${STAGEDIR})

.include <bsd.port.mk>
