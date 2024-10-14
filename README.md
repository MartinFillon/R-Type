# R-Type

R-type is a side scroller where you control a vessel and shoot ennemies randomly appearing.

## Install

### Windows

Please use the binaries provided in the latest release. Or build it yourself using cmake as per linux.

### Linux

For linux users you will need to build the project by yourself using these commands.

```sh
mkdir build
cd build
cmake ..
make
```

This will create two binaries `r-type_server` and `r-type_client`

## Running

Running the client is simple and just requires to have the config dir and assets dir at the same place in order to get the game working.

Running the server is the same process except you need to set the port as an argument eg:

```sh
./r-type_server 4242
```
Your tree should look like that
```sh
config/
assets/
r-type_server
r-type_client
```

## Devlopper Informations:

[Wiki](https://shimmer-shell-9d5.notion.site/10bcb71207cb80168e4ce5b06213eca4?v=67fe20e0cfec4c6cb69a95ce4eef6b8c) Containing everything you need to know to be able to develop on this project

## Co-Contributors

| [<img src="https://avatars.githubusercontent.com/u/77391472?v=4" width=85><br><sub>Ravenne Leopold</sub>](https://github.com/Ravriely) | [<img src="https://avatars.githubusercontent.com/u/114775771?v=4" width=85><br><sub>Martin Fillon</sub>](https://github.com/MartinFillon) | [<img src="https://avatars.githubusercontent.com/u/114899301?v=4" width=85><br><sub>Paul Bardeur</sub>](https://github.com/paulbardeur) | [<img src="https://avatars.githubusercontent.com/u/114470214?v=4" width=85><br><sub>Edward Lalande</sub>](https://github.com/edward-lalande) | [<img src="https://avatars.githubusercontent.com/u/91876984?v=4" width=85><br><sub>Timothee Plisson</sub>](https://github.com/timotheeplisson) |
| :------------------------------------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------------------------------------: |
