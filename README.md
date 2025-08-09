<div align=center style='text-align: center'>
    <img src='https://img.shields.io/github/repo-size/Evilur/httpc?style=for-the-badge'/>
    <img src='https://img.shields.io/github/v/release/Evilur/httpc?style=for-the-badge'/>
    <br>
    <img src='https://img.shields.io/github/license/Evilur/httpc?color=%230CD94E&style=for-the-badge'/>
    <img src='https://img.shields.io/github/last-commit/Evilur/httpc?color=%230CD94E&style=for-the-badge'/>
</div>

## httpc
**httpc** - is a simple zero-conf http 1.1 server to use instead of the python 
http.server. It distributed as a binary or a source code for running on any 
platform where other servers cannot be run

## Usage
To use this program, just run:
```bash
# To run http server on 8000 port
httpc 8000

# Without arguments - 8000 port is default
httpc
```

## Installation
You can go to the [release](https://github.com/Evilur/httpc/releases) page
and download one of the .deb packages

Also, this package is available on [AUR](https://aur.archlinux.org/packages/httpc)

And, of course, you can build it from source

## Building from source
#### Unix Makefiles
If you are able to use the `make` command on you target machine,
you can just run in the root of this repo:
```bash
make clean install
```
This command will install a program to your machine. 
You can also configure the path of the program to install to:
```bash
make clean install BINPREFIX=YOUR_PATH
```
#### Without make
If you can't use make, just run this commands in the root of this repo:
```BASH
gcc src/*.c -o httpc
cp httpc YOUR_PATH
```

## Tips and Tricks
By default, linux doesn't allow you listen port which is less than 1024 
without root privileges. So you can't just run:
```bash
httpc 80

# You need to use sudo
sudo httpc 80
```
But if you run this command, it allows you to listen 80 port without sudo:
```bash
sudo setcap 'cap_net_bind_service=+ep' PATH_TO_BINARY

# Example
sudo setcap 'cap_net_bind_service=+ep' /usr/bin/httpc
```