# dwl - dwm for Wayland

## This is My Fork of DWL The Wayland Compoistor With Patches

![DWL](dwl.jpg)

There are a few dependencies that DWL needs in order to run on your system.

### Void Linux

`sudo xbps-install -S wlroots wlroots-devel wayland-protocols wbg wlr-randr xdg-desktop-portal-wlr`

### Arch Linux

`sudo pacman -S wlroots wayland-protocols wbg wlr-randr xdg-desktop-portal-wlr`

The background image is set with wbg.

If you have numerous screens, you can configure them using wlr-randr.

### Patches

- Allways Center
- Attach Bottom
- Auto Start
- Per Tag
- Restart dwl
- Swallow
- Vanity gaps

### Installing DWL

In order to install dwl on your system.

1- clone the repo `git clone https://github.com/elbachir-one/dwl`.

2- cd in to the cloned repo `cd dwl/` .

3- run `make` .

4- run `sudo make clean install` .

After that, you can reboot your system by typing dwl in the tty.

NOTE: Since DWL doesn't include a bar by default,
you'll need to pick one you like and set it up on your own.
One more thing: you need to install a terminal emulator and a program launcher,
such as bmenu or dmenu for Wayland, which is the one I use.

### Installing Dmenu-Wayland

Install dependencies: meson and ninja

```bash
git clone https://github.com/nyyManni/dmenu-wayland.git
cd dmenu-wayland
mkdir build && meson build
ninja -C build
sudo ninja -C build install
```

### Keybindings

Modkey = Alt |

Modkey + p -> to launch dmenu-wayland |

Modkey + Shift + Return -> start the terminal (alacritty) |

Modkey + Shift + q -> restart dwl |

Modkey + Shift + c -> close programes |

NOTE: Feel free to change this configuration however you want.

### Thank You
