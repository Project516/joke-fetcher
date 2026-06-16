# joke-fetcher

## Setup 

### Debian

Run `apt-deps.sh` to install `cjson` and `libcurl`.


### Fedora

Install required dependencies (`cjson` and `libcurl`):

```
sudo dnf install cjson cjson-devel libcurl libcurl-devel
```

Run `make` to build the project. 

### `Makefile` options

`make`: build the project
`make release`: build project for release
`make clean`: clean project

## Usage

run `./joke-fetcher` to run the project.