# Joke Fetcher

This is a simple joke fetcher for `https://jokeapi.dev/` written in `C`.

**Offensive jokes are off by default, but we cannot verify the API's filter is 100% accurate!**
> See more info in the [options](#offensive)

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

### Options

#### Joke Categories

There are 7 joke categories:

* Any
* Programming
* Misc
* Dark
* Pun
* Spooky
* Christmas

#### Offensive

Decide if you want to get offensive jokes (off by default).

> **The API has some crazy offensive jokes. You have been warned.**


## Development

We use `gcc` to compile this program. Clang may work, but it has not been tested, and the `Makefile` calls for `gcc`. Make sure to have `gcc` installed.

### Scripts

There are shell scripts included in the repository to speed up development.

`apt-deps.sh`: Quick setup on Debian machines
`format.sh`: Run `clang-format` on the codebase
`run.sh`: Quickly run `make` and the program

#### You can use `apt-deps.sh` on Codespaces for an easy setup!
