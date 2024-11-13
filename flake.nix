{
  inputs = {
    hyprland.url = "git+https://github.com/hyprwm/Hyprland?submodules=1&ref=refs/tags/v0.45.0";
    nixpkgs.follows = "hyprland/nixpkgs";
    systems.follows = "hyprland/systems";
  };

  outputs = { self, hyprland, nixpkgs, systems, ... }:
  let
    eachSystem = fn: nixpkgs.lib.genAttrs (import systems) (system: fn system (import nixpkgs {
      inherit system;
      overlays = [ hyprland.overlays.hyprland-packages ];
    }));
  in
  {
    devShells = eachSystem (system: pkgs: {
      default = pkgs.mkShell.override { inherit (pkgs.hyprland) stdenv; } {
        inputsFrom  = [ pkgs.hyprland ];
        buildInputs = [ pkgs.hyprland ];
        nativeBuildInputs = with pkgs; [ pkg-config meson ninja ];
      };
    });
  };
}