# $FreeBSD$

PORTNAME=	ros-rosinstall_generator
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTVERSION=	0.1.13
CATEGORIES=	devel

MAINTAINER=	trentonw@ifi.uio.no
COMMENT=	Generator tool for a ROS install distro

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

USES=	python
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}argparse>=1:devel/py-argparse \
		${PYTHON_PKGNAMEPREFIX}yaml>=3:devel/py-yaml
USE_PYTHON=	distutils autoplist
USE_GITHUB=	yes
GH_ACCOUNT=	ros-infrastructure
GH_PROJECT=	rosinstall_generator

.include <bsd.port.mk>
