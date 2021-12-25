# hires-emu

Simple tool to emulate high-resolution wheel scroll.

## Build instructions

```bash
$ meson builddir
$ ninja -C builddir
```

Requires ncurses and libevdev as dependencies.

## How to use it

```bash
$ sudo ./builddir/hires-emu
High-resolution scroll emulator
Press 'u' to scroll up
Press 'd' to scroll down
Press 'q' to quit
```
