# R-Type

R-Type is an Epitech project where we have to create a Game Engine, we decided then to create an ECS (Entity Component System) to recreate the R-Type game.
So as to prove the richness of our game engine we made two POCs (Street fighter for the fight, cinamtics and gravity and one in 3D with gravity and object).

Our game engine can read components in the form of .so at runtime, generate entities via .json configuration files, systems to manage cinematics, colisions, 2D/3D movement, parallax, 2D/3D gravity, animations, boss management via configuration files (and therefore levels too), 2D shooting, invincibility and punching as well as 2D kicking.

## Install

### Windows

Please use the binaries provided in the latest release. Or build it yourself using cmake as per linux.

### Linux

For linux users you will need to build the project by yourself using these commands.

```sh
mkdir build
cd build
cmake ..
make install
```

This will create two binaries `r-type_server` and `r-type_client` and install the config and assets under `XDG_CONFIG_HOME`

## Running

Running the client is simple and just requires to run the binary without any arguments.

Running the server is the same process except you need to set the port as an argument eg:

```sh
r-type_server 4242
```

## Devlopper Informations:

[Wiki](https://shimmer-shell-9d5.notion.site/10bcb71207cb80168e4ce5b06213eca4?v=67fe20e0cfec4c6cb69a95ce4eef6b8c) Containing everything you need to know to be able to develop on this project

## Co-Contributors

| [<img src="https://avatars.githubusercontent.com/u/77391472?v=4" width=85><br><sub>Ravenne Leopold</sub>](https://github.com/Ravriely) | [<img src="https://avatars.githubusercontent.com/u/114775771?v=4" width=85><br><sub>Martin Fillon</sub>](https://github.com/MartinFillon) | [<img src="https://avatars.githubusercontent.com/u/114899301?v=4" width=85><br><sub>Paul Bardeur</sub>](https://github.com/paulbardeur) | [<img src="https://avatars.githubusercontent.com/u/114470214?v=4" width=85><br><sub>Edward Lalande</sub>](https://github.com/edward-lalande) | [<img src="https://avatars.githubusercontent.com/u/91876984?v=4" width=85><br><sub>Timothee Plisson</sub>](https://github.com/timotheeplisson) |
| :------------------------------------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------------------------------------: |
