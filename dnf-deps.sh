#!/bin/sh
# install required libraries on fedora based systems (dnf)
set -e

sudo dnf install -y libcurl-devel cjson-devel clang-format
