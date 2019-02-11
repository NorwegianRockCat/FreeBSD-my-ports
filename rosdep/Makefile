# $FreeBSD$

PORTNAME=	ros-rosdep
DISTVERSION=	0.11.8
CATEGORIES=	devel
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	Multi-package manager system dependency tool for ROS

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}ros-catkin_pkg>=0.4.0:devel/ros-catkin_pkg@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}ros-rosinstall>=0.7.7:devel/rosinstall@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}yaml>=3:devel/py-yaml
USES= 	python

USE_PYTHON=	autoplist distutils

USE_GITHUB=	yes
GH_ACCOUNT=	ros-infrastructure
GH_PROJECT=	rosdep

.include <bsd.port.mk>
