# $FreeBSD$

PORTNAME=	wstool
DISTVERSION=	0.1.17
CATEGORIES=	devel

MAINTAINER=	trentonw@ifi.uio.no
COMMENT=	A tool for managing a workspace of multiple heterogenous SCM repositories

LICENSE=	BSD3CLAUSE

WWW=	https://github.com/vcstools/wstool
USES=	python
#py27_LIB_DEPENDS=	devel/py-argparse
#py27_LIB_DEPENDS=	devel/py-yaml
#py36_LIB_DEPENDS=	devel/py-argparse
#py36_LIB_DEPENDS=	devel/py-yaml
USE_PYHTON=	distutils autoplist
USE_GITHUB=	yes
GH_ACCOUNT=	vcstools
GH_PROJECT=	wstool
GH_TAGNAME=	0.1.17

do-install:
	(cd ${WRKSRC} && python setup.py install --root ${STAGEDIR})

.include <bsd.port.mk>
