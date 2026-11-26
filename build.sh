#!/bin/bash

VERSION="$(git describe --tags --always --dirty)"
COMMIT="$(git rev-parse HEAD)"

docker build \
  --build-arg APP_VERSION="$VERSION" \
  --build-arg GIT_COMMIT="$COMMIT" \
  -t sheena:"$VERSION" \
  .
