#!/bin/bash
#----------------------------------------------------------
# You will need:
# - Qt 5.4 android_armv7 kit
# - Android SDK
# - Androig NDK
# - Current Java
# - ant
#----------------------------------------------------------
# Update with correct location for these
export ANDROID_HOME=/opt/android-sdk-linux
export ANDROID_SDK_ROOT=/opt/android-sdk-linux
export ANDROID_NDK_ROOT=/opt/android-ndk-r10c
export ANDROID_NDK_HOST=darwin-x86_64
export ANDROID_NDK_PLATFORM=/android-10
export ANDROID_NDK_TOOLCHAIN_PREFIX=arm-linux-androideabi
export ANDROID_NDK_TOOLCHAIN_VERSION=4.9
export ANDROID_NDK_TOOLS_PREFIX=arm-linux-androideabi
#----------------------------------------------------------
# To build it, run (replacing the path with where you have Qt installed)
#
# For a shadow build: (strongly recomended)
#
# >source android_environment.sh
# cd ../
# mkdir android_build
# cd android_build
# >~/local/Qt/5.4/android_armv7/bin/qmake -r -spec android-g++ CONFIG+=debug ../qgroundcontrol/qgroundcontrol.pro
# >make -j24
# >~/local/Qt/5.4/android_armv7/bin/androiddeployqt --input ./android-libqgroundcontrol.so-deployment-settings.json --output ./android-build --deployment bundled --android-platform android-22 --jdk /System/Library/Frameworks/JavaVM.framework/Versions/CurrentJDK/Home --verbose --ant /opt/local/bin/ant
#
# For an in place build (not recomended)
#
# >source android_environment.sh
# >~/local/Qt/5.4/android_armv7/bin/qmake -r -spec android-g++ CONFIG+=debug qgroundcontrol.pro
# >make -j24
# >~/local/Qt/5.4/android_armv7/bin/androiddeployqt --input ./android-libqgroundcontrol.so-deployment-settings.json --output ./android-build --deployment bundled --android-platform android-22 --jdk /System/Library/Frameworks/JavaVM.framework/Versions/CurrentJDK/Home --verbose --ant /opt/local/bin/ant
