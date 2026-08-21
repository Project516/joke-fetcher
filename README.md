# Joke Fetcher

This is a simple joke fetcher for `https://jokeapi.dev/` written in `C`.

**Offensive jokes are off by default, but we cannot verify the API's filter is 100% accurate!**
> See more info in the [options](#offensive)

## Setup 

### Debian

Run `apt-deps.sh` to install `cjson` and `libcurl`.

### Fedora

Run `dnf-deps.sh` to install `cjson` and `libcurl`.

Run `make` to build the project. 

### `Makefile` options

`make`: build the project
`make release`: build project for release
`make clean`: clean project

## Usage

Run `./joke-fetcher` to run the project.

Without arguments, the program runs in interactive mode and prompts for a category and offensive flag.

### Command-line options

```
joke-fetcher [OPTIONS]

  -c, --category <name>  Joke category (any, programming, misc,
                         dark, pun, spooky, christmas)
  -o, --offensive        Include offensive jokes
  -h, --help             Show help message
  -v, --version          Show version
```

Examples:

```
./joke-fetcher -c programming
./joke-fetcher --category pun --offensive
./joke-fetcher -c dark -o
```

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
`dnf-deps.sh`: Quick setup on Fedora machines
`format.sh`: Run `clang-format` on the codebase
`run.sh`: Quickly run `make` and the program

#### You can use `apt-deps.sh` on Codespaces for an easy setup!
