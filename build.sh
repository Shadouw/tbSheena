#!/bin/bash

VERSION="$(git describe --tags --always --dirty)"
COMMIT="$(git rev-parse HEAD)"

echo VERSION: $VERSION
echo COMMIT: $COMMIT

docker build \
  --build-arg APP_VERSION="$VERSION" \
  --build-arg GIT_COMMIT="$COMMIT" \
  -t sheena:"$VERSION" \
  .
