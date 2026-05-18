{ config, pkgs, ... }:
{
  home.username = "obeskrov";
  home.homeDirectory = "/home/obeskrov";
  home.stateVersion = "25.11";

  programs.home-manager.enable = true;
}
