# Bright
A CLI utility written in pure C for increasing and decreasing screen brightness on a logarithmic scale, using the `brightnessctl` command.

## Requirements

This program uses the `brightnessctl` command. If you don't have it installed, or if it doesn't work with your hardware, this program will not work on your machine.

## Usage

```bash
# Increase brightness
bright i

# Decrease brightness
bright d

# Display current brightness
bright
```

## Installing

To install, clone the repository and use `make`.

```bash
git clone https://github.com/jsusm/bright bright
cd bright
sudo make install
```

## Uninstalling

```bash
sudo make uninstall
```
