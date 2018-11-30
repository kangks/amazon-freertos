# IOT217 - Get Started on Amazon FreeRTOS

In this builder session, we will explore the Amazon FreeRTOS, by running example applications with esp32 development kit. Once we have our first hello world flash and running on the esp32, we will proceed to take a quick walk through of the codes.

# Steps	

1. Create Cloud9 instance
1. Configure Cloud9 environment
1. Download Amazon FreeRTOS
1. Configure Amazon FreeRTOS
1. Compile Amazon FreeRTOS
1. Download to local computer to flash to ESP32
Amazon FreeRTOS references

## Step 1 - Create Cloud9 instance

1.	Goto https://console.aws.amazon.com/cloud9
1.	Choose Create environment
1.	Enter a name, such as esp32-xtensa-c9, choose Next step
1.	Accept the default options
1.	Create a new instance for environment (EC2)
1.	t2.micro
1.	Choose Next step, Choose Create environment

## Step 2 - Configure Cloud9 environment

1.	`sudo yum -y update`
1.	`sudo yum groupinstall -y "Development tools"`
1.	Install GNU perfect, hash function generator
   1.	`sudo yum install –y gperf`
   1.	`sudo pip install serial`
1.	Download and create xtensa toolchain
   1.	`cd ~`
   1.	`wget https://dl.espressif.com/dl/xtensa-esp32-elf-linux64-1.22.0-73-ge28a011-5.2.0.tar.gz`
   1.	`tar xf xtensa-esp32-elf-linux64-1.22.0-73-ge28a011-5.2.0.tar.gz`
1.	`mkdir –p ~/bin`
1.	`ln -s ~/xtensa-esp32-elf/bin/* ~/bin/`

## Step 3 - Download Amazon FreeRTOS

1.	`cd ~/environment`
1.	`git clone https://github.com/aws/amazon-freertos.git`

## Step 4 – Configure Amazon FreeRTOS

The configure.json can be found in `amazon-freertos/tools/aws_config_quick_start/` in your Cloud9 environment. Double click the file from the file explorer at the left hand side to open the editor.

<img src="https://github.com/kangks/amazon-freertos/blob/master/images/cloud9_edit.png" width="30%" height="30%">

WiFi settings for the reInvent2018 as below:

```
{
    "afr_source_dir":"/home/ec2-user/environment/amazon-freertos/",
    "thing_name":"esp32_reInvent2018",
    "wifi_ssid":"Condensate",
    "wifi_password":"TheFinalCountdown",
    "wifi_security":"eWiFiSecurityWPA2"
}
```

To setup your Thing, and update credentials file, go to `amazon-freertos/tools/aws_config_quick_start/`, type the command `python SetupAWS.py setup`

What this step does it, it will create an IoT Thing in the AWS IoT Core, and download the device certificates, and insert into the `aws_clientcredential_keys.h`

For more details of quick start can be found in https://github.com/aws/amazon-freertos/tree/master/tools/aws_config_quick_start#script-to-setup-the-aws-resources-through-command-line

## Step 5 - Compile Amazon FreeRTOS

1.	`cd ~/environment/amazon-freertos/demos/espressif/esp32_devkitc_esp_wrover_kit/make`
1.	Run `make`

## Step 6 – Download to local computer to flash to ESP32

1.	In Cloud9, expand the file explorer at the left hand side, go to `~/environment/amazon-freertos/demos/espressif/esp32_devkitc_esp_wrover_kit/make/build` folder, right click on the following files to download to local computer
    1. aws_demos.bin
    1. bootloader/bootloader.bin
    1. partitions_example.bin

<img src="https://github.com/kangks/amazon-freertos/blob/master/images/cloud9_download.png" width="30%" height="30%">

### Flashing Amazon FreeRTOS compiled firmware to your ESP32 board 

1. Download and install Silicon Labs [CP2104 drivers](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)

2. Connect your ESP32 DevKitC board to the laptop using provided USB cable and identify which port it is connected to
On Windows it will be ```COM3``` for example, on Mac OS typically it enumerated as ```/dev/tty.SLAB_USBtoUART``` and on Linux most likely ```/dev/ttyUSB0```

3. Install [esptool](https://github.com/espressif/esptool) and flash the firware

#### Windows
1. Download binary from [here](https://dl.espressif.com/dl/esptool-2.3.1-windows.zip)
1. Drop it to the subfolder that already in your PATH or add subfolder you placed esptool to your PATH variable
1. Open Commnd Prompt and execute following command (from the directory you places 3 downloaded files):
```
esptool --chip esp32 --port COM3 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 bootloader.bin 0x20000 aws_demos.bin 0x8000 partitions_example.bin
```

#### Mac/Linux
1. Install esptool.py:
```bash
sudo pip install esptool pyserial
```
2. Execute following command from the directory you placed 3 downloaded files and monitor the flashing process:
```bash
esptool.py -p /dev/cu.SLAB_USBtoUART -b 115200 write_flash --flash_mode dio --flash_size detect 0x20000 aws_demos.bin 0x1000 bootloader.bin 0x8000 partitions_example.bin
```
```bash
esptool.py v2.5.1
Serial port /dev/cu.SLAB_USBtoUART
Connecting........__
Detecting chip type... ESP32
Chip is ESP32D0WDQ5 (revision 1)
Features: WiFi, BT, Dual Core
MAC: 24:0a:c4:23:dc:4c
Uploading stub...
Running stub...
Stub running...
Configuring flash size...
Auto-detected Flash size: 4MB
Compressed 598640 bytes to 379167...
Wrote 598640 bytes (379167 compressed) at 0x00020000 in 33.4 seconds (effective 143.2 kbit/s)...
Hash of data verified.
Flash params set to 0x0220
Compressed 21968 bytes to 13053...
Wrote 21968 bytes (13053 compressed) at 0x00001000 in 1.2 seconds (effective 152.4 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 119...
Wrote 3072 bytes (119 compressed) at 0x00008000 in 0.0 seconds (effective 1484.1 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
```

### Monitor code execution through the serial console

#### Windows

1. You can download putty from http://www.putty.org/ or http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html

#### Mac/Linux

1. Use ```miniterm.py``` to see the ESP32 console

```
miniterm.py /dev/cu.SLAB_USBtoUART 115200
```

## What's next?

1. Explore other demos in [amazon-freertos/demos/common/demo_runner/aws_demo_runner.c](https://github.com/aws/amazon-freertos/blob/master/demos/common/demo_runner/aws_demo_runner.c)
1. If you have [ESP32 Wrover Kit](https://www.amazon.com/ESP32-WROVER-KIT-Board-Espressif-Colour-Display/dp/B071ZLSB2D), try to add a simple blinky task with [blink.c](https://github.com/kangks/amazon-freertos/blob/master/demos/common/demo_runner/blink.c)
1. Change the `demos/common/mqtt/aws_hello_world.c` to send out JSON messages (https://github.com/kangks/amazon-freertos/commit/7026f498a4d36a33318fd5ca34c0cedc9701559d#diff-0fd7d733c1846926ba690ef532bd4f1d), and use the AWS IoT Rule Engine to extract the message

## Amazon FreeRTOS references

* Amazon FreeRTOS Documentation
   * https://docs.aws.amazon.com/freertos/index.html#lang/en_us
* Connect Microcontroller-Based Devices to the Cloud with Amazon FreeRTOS and Espressif ESP32
   * https://aws.amazon.com/blogs/apn/connect-microcontroller-based-devices-to-the-cloud-with-amazon-freertos-and-espressif-esp32/
* Try out Amazon FreeRTOS BLE
   * https://aws.amazon.com/blogs/iot/using-bluetooth-low-energy-with-amazon-freertos-on-espressif-esp32/


