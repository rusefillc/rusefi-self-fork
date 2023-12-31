#!/bin/bash

echo "java version"
java -version

echo "Building java console"
pwd
cd java_tools
./gradlew :ui:shadowJar
cd ..

[ -e java_console_binary/rusefi_console.jar ] || { echo "CONSOLE COMPILATION FAILED"; exit 1; }
echo "java console looks good"

echo "Building TS plugin"
cd java_tools
./gradlew :ts_plugin_launcher:shadowJar
cd ..

[ -e java_tools/ts_plugin_launcher/build/jar/rusefi_ts_plugin_launcher.jar ] || { echo "PLUGIN COMPILATION FAILED"; exit 1; }
echo "TS plugin looks good"
