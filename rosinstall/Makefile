# $FreeBSD$

PORTNAME=	rosinstall
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTVERSION=	0.7.7
CATEGORIES=	devel

MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	Command-line tools for maintaining a workspace of projects from multiple version-control systems, tailored for ROS.

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=	python
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}argparse>=1:devel/py-argparse \
		${PYTHON_PKGNAMEPREFIX}yaml>=3:devel/py-yaml
USE_PYTHON=	distutils autoplist
USE_GITHUB=	yes
GH_ACCOUNT=	vcstools
GH_PROJECT=	rosinstall

.include <bsd.port.mk>
