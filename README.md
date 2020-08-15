# ps1

> A simple compiled PS1 with Git integration, usable in any shell

## About

__ps1__ is a very small application that can serve as your `$PS1`
(or equivalent) in your shell.

It is opinionated and the format is currently hardcoded.

## Usage

As it is written in C and is compiled it should be usable in any shell.
To use in any Bourne descended shells you can simply:

    PS1='$(ps1)'

## Installation

The Git integration requires [`libgit2`](https://github.com/libgit2/libgit2#building-libgit2---using-cmake).
If it is available and if you also have `pkg-config` and `make` you can:

    # make install