#!/bin/sh
# install required libraries on debian based systems (apt)
set -e

sudo apt update
sudo apt install -y libcurl4-openssl-dev libcjson-dev clang-format