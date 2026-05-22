# Crow2D-Boilerplate

This is a boilerplate template repo to make it easier to start developing games with Crow2D

## Prerequisites

In order to use this template you need:

- [Git bash](https://gitforwindows.org/)
- [Crow2D SDK](https://github.com/ModelStudioDev/Crow2D/releases)

- (Optional- See [Removing node](#removing-node)) [Node.js](https://nodejs.org/es)

## Usage

1. Create a repo from this template
2. Clone it
3. Search and replace "Assteroids" for the name of your game.
4. Create a `local.cmake` file and add your patth to the [Crow2D SDK](https://github.com/ModelStudioDev/Crow2D/releases), someting like

```cmake
set(CROW2D_SDK_PATH "D:/Apps/Crow2D/Crow2D/out/Crow2D_SDK")
```

5. (Optional) Run `npm install`
6. Done!

## Dev enviroment

This repo provides some helpfull bash scripts to aid you.
To start developing you NEED to open the folder from a developer command prompt _(Optionaly inject the env yourself)_

The main available scripts/commands are:

- [watch.sh](./scripts/watch.sh) - `bash scripts/watch.sh [-n]`: <br>This will spin up a watcher and constantly re-launch the game when a change is detected. The `-n` flag will make the program compile, but prevent the launch of the exe. The compilled game will live in `build/dev`

- [release.sh](./scripts/release.sh) - `bash scripts/release.sh`: <br>This will configure and compile the release version of the game. The release will live in `build/release`. It will also ready the exportable game (The actuall game files for consumers). The final clean build is found in `out/`. This is the folder you should distribute

## FAQ

### Removing node

This template uses node and npm in order to provide a better UI developing experience. It comes pre-configured to use TypeScript and SCSS. I understand that is not for everyone. To remove all node dependencies simply remove the following files and folders:

- [package.json](./package.json)
- [package-lock.json](./package-lock.json)
- [tsconfig.jsoon](./tsconfig.json)
- [nodemon.json](./nodemon.json)
- [ts](./ts)
- [scss](./scss/)

_If you want you can remove node_modules from the gitignote_

### Watch.sh error: x The system cannot find the file specified

This usually means the watcher is being launched with a search flag that does not exist.

This is usally caused by the deletion of the assets folder (which is watched). To fix it, ether re-create the folder, or go to the [watch.sh](./scripts/watch.sh) script and remove the `-w [missing folder]` Replacing, of course `[missing folder]` with the directory you are missing.
