# $FreeBSD$

PORTNAME=	ros-wstool
DISTVERSION=	0.1.17
CATEGORIES=	devel
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	trueos@norwegianrockcat.com
COMMENT=	A tool for managing a workspace of multiple heterogenous SCM repositories

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=	python

RUN_DEPENDS= 	${PYTHON_PKGNAMEPREFIX}ros-vcstools>=0:devel/ros-vcstools@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}yaml>=3:devel/py-yaml@${PY_FLAVOR} 

USE_PYTHON=	distutils autoplist
USE_GITHUB=	yes
GH_ACCOUNT=	vcstools
GH_PROJECT=	wstool

.include <bsd.port.mk>
