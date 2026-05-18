# nixos-backup

my personal nixos dotfiles — minimal wayland setup built around dwl.

![setup](setupkk.png)

---

## stack

| role | tool |
|---|---|
| os | NixOS 26.05 (flakes) |
| wm | dwl (wayland, tiling) |
| bar | waybar |
| terminal | foot |
| launcher | bemenu |
| editor | neovim |
| browser | brave |
| files | thunar |
| audio | pipewire + pavucontrol |
| screenshots | grim + slurp |
| wallpaper | swaybg |

---

## keybinds

`Super` = Windows key

### apps

| key | action |
|---|---|
| `Super + Enter` | terminal (foot) |
| `Super + D` | launcher (bemenu) |
| `Super + W` | wallpaper selector |
| `Super + B` | browser (brave) |
| `Super + E` | file manager (thunar) |
| `Super + V` | volume control (pavucontrol) |
| `Super + Shift + D` | discord |
| `Super + Shift + S` | spotify |
| `Super + Shift + X` | sober (roblox) |
| `Super + Ctrl + S` | screenshot de área |

### window management

| key | action |
|---|---|
| `Super + Q` | fechar janela |
| `Super + J / K` | navegar entre janelas |
| `Super + H / L` | redimensionar área principal |
| `Super + Shift + Space` | toggle floating |
| `Super + Shift + F` | toggle fullscreen |
| `Super + I` | toggle waybar |
| `Super + Tab` | alternar para tag anterior |

### layouts

| key | layout |
|---|---|
| `Super + T` | tiling |
| `Super + F` | floating |
| `Super + M` | monocle |

### tags (workspaces)

| key | action |
|---|---|
| `Super + 1-5` | ir para tag |
| `Super + Ctrl + 1-5` | mostrar tag adicional |
| `Super + Shift + 1-5` | mover janela para tag |
| `Super + 0` | mostrar todas as tags |

### mouse

| combo | action |
|---|---|
| `Super + botão esquerdo` | mover janela |
| `Super + botão direito` | redimensionar janela |
| `Super + botão do meio` | toggle floating |

### mídia e sistema

| key | action |
|---|---|
| `XF86AudioRaiseVolume` | volume + |
| `XF86AudioLowerVolume` | volume - |
| `XF86AudioMute` | mute |
| `XF86MonBrightnessUp/Down` | brilho |
| `XF86AudioPlay/Next/Prev` | controle de mídia |
| `Super + Shift + Q` | sair do dwl |

---

## structure

```
nixos-backup/
├── configuration.nix   # system config
├── flake.nix           # flake inputs (nixpkgs + home-manager)
├── flake.lock
├── home.nix            # home-manager config
├── config.h            # dwl keybinds + rules
├── nvim/
│   └── init.lua        # neovim (lazy + lsp + treesitter)
├── waybar/
│   ├── config
│   └── style.css
├── fastfetch/
│   └── config.jsonc
├── foot/
│   └── foot.ini
└── bin/
    └── screenshot-swappy
```

---

## install

```bash
git clone https://github.com/taakenvx/nixos-backup
cd nixos-backup
sudo cp configuration.nix flake.nix flake.lock home.nix /etc/nixos/
sudo nixos-rebuild switch --flake /etc/nixos#nixos
```

dwl precisa ser compilado manualmente — veja `config.h` para dependências.
