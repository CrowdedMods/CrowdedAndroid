# Building from the source
It's very hard, idk why you need it (i don't recommend trying to make android mods using this as an example, it's not worth it)

## Requiremnets
- android ndk (latest)
- CMake
- GCC compiler (MinGW)
- [Il2CppDumper](https://github.com/Perfare/Il2CppDumper)
- [Apktool](https://ibotpeaches.github.io/Apktool/) v2.4.1 (the most stable version, you can try any other)
- i hope that's all

# Warning
aarch64 is not supported yet (WIP), so if you see anything related to x64 - ignore it

# Prelude
1. Clone the repo
2. Decode Among Us via [apktool](https://ibotpeaches.github.io/Apktool/)
3. Dump the game with [Il2CppDumper](https://github.com/Perfare/Il2CppDumper)
3.1 Use `lib/armeabi-v7/libil2cpp.so` (from apktool's output) as an executable and `assets/bin/Data/Managed/Metadata/global-metadata.dat` as a metadata file
4. Move dumped `il2cpp.h` to `src/gamedata`
5. Build or get a release of [DobbyHook](https://github.com/jmpews/Dobby/) (both armeabi-v7a and arm64-v8a)
5.1 Put its `.a` libs in `lib/ARCH_NAME/`
6. Setup your `NDK_ROOT` environment
## Building
### Using VS code/any other IDE extensions
Just press configure and then build
### Using CLI
```sh
mkdir build && cd build
cmake -G "MinGW Makesfiles" ..
cmake --build
```
As for now you need to do it twice for both arches, also they have the same file and directory name so look up for overriding. To change arch go to `CMakeLists.txt` and switch `ANDROID_ABI` between `armeabi-v7a` and `arm64-v8a` (very usable yes)

# Injecting in Among Us apk
1. Move your new `libcmod.so` lib from `build` to `decodedAmongUsDir/lib/ARCH_NAME/`
2. Change package name in `AndroidManifest.xml` so it won't override original game
2.1 Also you can change app name/icon, but it's not in this instruction
3. Open `smali/com/unity3d/player/UnityPlayerActivity.smali` with any text editor
3.1 Find line `.method protected onCreate(Landroid/os/Bundle;)V`. That's where you should inject your lib. I don't know the best ways yet, so I use `libLoader` from [Android-Hooking-Template](https://github.com/joeyjurjens/Android-Hooking-Template/) (you can see injecting guide right there)
4. Build your modified apk with apktool
5. Sign it if you don't have root
6. Install and test !