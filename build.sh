rm -rf .build
platformio ci --lib="." --board=d1_mini examples/basic/basic.ino --build-dir .build --keep-build-dir
platformio ci --lib="." --board=d1_mini examples/basic/basic.ino --build-dir .build --keep-build-dir