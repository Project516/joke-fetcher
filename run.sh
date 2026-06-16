#!/bin/sh
set -e

make || exit 1

./joke-fetcher