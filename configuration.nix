{ config, lib, pkgs, ... }:
{
  imports = [ ./hardware-configuration.nix ];
  nixpkgs.config.allowUnfree = true;
  # boot
  boot.loader.systemd-boot.enable = true;
  boot.loader.efi.canTouchEfiVariables = true;
  # rede
  networking.networkmanager.enable = true;
  # locale
  time.timeZone = "America/Campo_Grande";
  # audio
  services.pipewire = {
    enable = true;
    alsa.enable = true;
    pulse.enable = true;
  };
  # input
  services.libinput.enable = true;
  services.dbus.enable = true;
  # flatpak
  services.flatpak.enable = true;
  xdg.portal = {
    enable = true;
    extraPortals = [ pkgs.xdg-desktop-portal-wlr ];
    config.common.default = "*";
  };
  # autologin tty1
  services.getty.autologinUser = "obeskrov";
  # swap
  swapDevices = [{
    device = "/swapfile";
    size = 4096;
  }];
  # gpu
  hardware.graphics.enable = true;
  # cursor
  environment.variables = {
    XCURSOR_THEME = "macOS";
    XCURSOR_SIZE  = "24";
  };
  # usuario
  users.users.obeskrov = {
    isNormalUser = true;
    extraGroups = [ "wheel" "video" "audio" "input" ];
  };
  environment.systemPackages = with pkgs; [
    neovim foot
    git wget htop fastfetch
    bemenu waybar wlr-randr
    brave
    mpv imv swaybg
    thunar evince
    pavucontrol
    discord spotify
    brightnessctl playerctl
    apple-cursor
    grim slurp swappy
    xdg-user-dirs xdg-utils
    wev
    gnumake gcc
    pkg-config
    libinput
    wayland
    libxkbcommon
    gnome-themes-extra
    bash-language-server
    nil
  ];
  fonts.packages = with pkgs; [
    nerd-fonts.jetbrains-mono
    noto-fonts
    noto-fonts-color-emoji
  ];
  fonts.fontconfig.defaultFonts = {
    serif     = [ "Noto Serif" ];
    sansSerif = [ "Noto Sans" ];
    monospace = [ "JetBrainsMono Nerd Font" ];
    emoji     = [ "Noto Color Emoji" ];
  };
  nix.settings.experimental-features = [ "nix-command" "flakes" ];
  system.nixos.label = "i-love-femboys";
  networking.hostName = "i-love-femboys";
  boot.loader.systemd-boot.configurationLimit = 5;
  system.stateVersion = "25.11";
}
