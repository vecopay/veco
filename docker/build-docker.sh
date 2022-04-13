#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-vecopay/vecod-develop}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/vecod docker/bin/
cp $BUILD_DIR/src/veco-cli docker/bin/
cp $BUILD_DIR/src/veco-tx docker/bin/
strip docker/bin/vecod
strip docker/bin/veco-cli
strip docker/bin/veco-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker
