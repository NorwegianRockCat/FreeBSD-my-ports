# $FreeBSD$

PORTNAME=	ros-rospkg
DISTVERSION=	1.1.4
CATEGORIES=	devel
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	trentonw@ifi.uio.no
COMMENT=	rospkg Python library for ROS

LICENSE=	BSD3CLAUSE

USES=	python
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}argparse>=1:devel/py-argparse \
		${PYTHON_PKGNAMEPREFIX}yaml>=3:devel/py-yaml
USE_PYTHON=	distutils autoplist
USE_GITHUB=	yes
GH_ACCOUNT=	ros-infrastructure
GH_PROJECT=	rospkg

.include <bsd.port.mk>
