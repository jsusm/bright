# Bright
CLI utility written in pure c for increasing and decreasin the screen brightness
in logarithmic scale using brightnessctl command

## Requirements
This program uses brightnessctl comamand if you dont have it
installed or it doesn't work with your hardware this program
will not work in your machine.

## Usage
```bash
bright i # increase brightness

bright d # increase decrease

bright # display current brightness
```

## Installing
Clone the repo and install with make

```bash
git clone https://github.com/jsusm/bright bright
cd bright
make install
```

## Uninstall
```bash
make uninstall
```
