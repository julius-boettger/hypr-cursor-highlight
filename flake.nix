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
    packages = eachSystem (system: pkgs: rec {
      default = hypr-cursor-highlight;
      hypr-cursor-highlight = pkgs.hyprland.stdenv.mkDerivation {
        pname = "hypr-cursor-highlight";
        version = "0.1";
        src = ./.;

        inherit (pkgs.hyprland) nativeBuildInputs;
        buildInputs = [ pkgs.hyprland ] ++ pkgs.hyprland.buildInputs;

        meta = {
          homepage = "https://github.com/julius-boettger/hypr-cursor-highlight";
          license = pkgs.lib.licenses.gpl3;
          inherit (pkgs.hyprland.meta) platforms;
        };
      };
    });

    devShells = eachSystem (system: pkgs: {
      default = pkgs.mkShell.override { inherit (pkgs.hyprland) stdenv; } {
        inputsFrom = [ self.packages.${system}.default ];
      };
    });
  };
}