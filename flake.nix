{
  inputs = {
    hyprland.url = "git+https://github.com/hyprwm/Hyprland?submodules=1";
    nixpkgs.follows = "hyprland/nixpkgs";
    systems.follows = "hyprland/systems";
  };

  outputs = { self, hyprland, nixpkgs, systems, ... }:
  let
    eachSystem = nixpkgs.lib.genAttrs (import systems);
  in
  {
    devShells = eachSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        default = pkgs.mkShell {
          inputsFrom  = [ hyprland.packages.${system}.hyprland ];
          buildInputs = [ hyprland.packages.${system}.hyprland ];
        };
      }
    );
  };
}