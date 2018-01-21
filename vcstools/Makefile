# $FreeBSD$

PORTNAME=	vcstools
DISTVERSION=	0.1.40
CATEGORIES=	devel

MAINTAINER=	trentonw@ifi.uio.no
COMMENT= 	Python library for interacting with various VCS systems

LICENSE=	BSD3CLAUSE

WWW=	http://wiki.ros.org/vcstools
USES=	python
#py27_LIB_DEPENDS=	devel/vcstools
#py27_LIB_DEPENDS=	devel/py-yaml
#py36_LIB_DEPENDS=	devel/vcstools
#py36_LIB_DEPENDS=	devel/py-yaml
USE_PYHTON=	distutils autoplist
USE_GITHUB=	yes
GH_ACCOUNT=	vcstools
GH_PROJECT=	vcstools
GH_TAGNAME=	0.1.40

do-install:
	(cd ${WRKSRC} && python setup.py install --root ${STAGEDIR})

.include <bsd.port.mk>
