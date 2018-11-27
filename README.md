# IOT217 - Get Started on Amazon FreeRTOS

In this builder session, we will explore the Amazon FreeRTOS, by running example applications with esp32 development kit. Once we have our first hello world flash and running on the esp32, we will proceed to take a quick walk through of the codes.

# Steps	

1. Create AWS IoT Thing
1. Create Cloud9 instance
1. Configure Cloud9 environment
1. Download Amazon FreeRTOS
1. Configure Amazon FreeRTOS
1. Compile Amazon FreeRTOS
1. Download to local computer to flash to ESP32
Amazon FreeRTOS references

## Step 1 - Create AWS IoT Thing

1.	Login to AWS IoT Console https://console.aws.amazon.com/iot
1.	Create an IoT Policy
```
{
  "Statement": [
    {
      "Effect": "Allow",
      "Action": "iot:*",
      "Resource": "*"
    }
  ],
  "Version": "2012-10-17"
}
```
1.	Create an IoT Thing in Manage -> Things -> Create, choose Create a single thing
1.	Use a name, for example, esp32_reinvent, choose Next
1.	Choose Create certificate
1.	Download all the certificates
1.	Choose Activate
1.	Choose Attach a policy to attach policy from previous step
1.	Go to Settings and make a note of Custom endpoint

## Step 2 - Create Cloud9 instance

1.	Goto https://console.aws.amazon.com/cloud9
1.	Choose Create environment
1.	Enter a name, such as esp32-xtensa-c9, choose Next step
1.	Accept the default options
1.	Create a new instance for environment (EC2)
1.	t2.micro
1.	Choose Next step, Choose Create environment

## Step 3 - Configure Cloud9 environment

1.	`sudo yum -y update`
1.	`sudo yum groupinstall -y "Development tools”`
1.	Install GNU perfect, hash function generator
   1.	`sudo yum install –y gperf`
   1.	`sudo pip install serial`
1.	Download and create xtensa toolchain
   1.	`cd ~`
   1.	`wget https://dl.espressif.com/dl/xtensa-esp32-elf-linux64-1.22.0-73-ge28a011-5.2.0.tar.gz`
   1.	`tar xf xtensa-esp32-elf-linux64-1.22.0-73-ge28a011-5.2.0.tar.gz`
1.	`mkdir –p ~/bin`
1.	`ln -s ~/xtensa-esp32-elf/bin/* ~/bin/`

## Step 4 - Download Amazon FreeRTOS

1.	`cd ~/environment`
1.	`git clone https://github.com/aws/amazon-freertos.git`

## Step 5 – Configure Amazon FreeRTOS

Follow steps in https://github.com/aws/amazon-freertos/tree/master/tools/aws_config_quick_start#script-to-setup-the-aws-resources-through-command-line

## Step 6 - Compile Amazon FreeRTOS

1.	`cd ~/environment/amazon-freertos/demos/espressif/esp32_devkitc_esp_wrover_kit/make`
1.	Run `make`

## Step 7 – Download to local computer to flash to ESP32

1.	Download Cloud9 project
1.	Extract the compressed file
1.	The compiled binary is in amazon-freertos/demos/espressif/esp32_devkitc_esp_wrover_kit/make/build/aws_demos.bin
1.	Install the esptool to flash the image
1.	`sudo pip install esptool`
1.	`esptool.py -p /dev/cu.SLAB_USBtoUART -b 115200 write_flash --flash_mode dio --flash_size 2MB 0x20000 amazon-freertos/demos/espressif/esp32_devkitc_esp_wrover_kit/make/build/aws_demos.bin`
1.	`miniterm.py /dev/cu.SLAB_USBtoUART 115200`

## What's next?

1. Explore other demos in [amazon-freertos/demos/common/demo_runner/aws_demo_runner.c](https://github.com/aws/amazon-freertos/blob/master/demos/common/demo_runner/aws_demo_runner.c)

## Amazon FreeRTOS references

* Amazon FreeRTOS Documentation
   * https://docs.aws.amazon.com/freertos/index.html#lang/en_us
* Connect Microcontroller-Based Devices to the Cloud with Amazon FreeRTOS and Espressif ESP32
   * https://aws.amazon.com/blogs/apn/connect-microcontroller-based-devices-to-the-cloud-with-amazon-freertos-and-espressif-esp32/


