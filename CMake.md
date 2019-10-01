1. clone the Amazon FreeRTOS repository with sub-modules `git clone git@github.com:aws/amazon-freertos.git --recurse-submodules`
2. Edit the file `tools/aws_config_quick_start/configuration.json` and run the quick start from `tools/aws_config_quick_start/`
```
$ cd ${AFR_ROOT}/tools/aws_config_quick_start/
$ vi configuration.json
$ python SetupAWS.py setup
```
3. Go to the root of the repository
4. Create the `makefile` using CMake `cmake -DVENDOR=espressif -DBOARD=esp32_wrover_kit -DCOMPILER=xtensa-esp32 -S . -B build`
5. Runs the make in the `build/` folder
```
$ make all -j4
```
6. Change the esptool to be executable `$ chmod +rx ./vendors/espressif/esp-idf/components/esptool_py/esptool/esptool.py`
7. Flash the build and monitor `python ./vendors/espressif/esp-idf/tools/idf.py flash monitor -p /dev/cu.SLAB_USBtoUART -B build`
