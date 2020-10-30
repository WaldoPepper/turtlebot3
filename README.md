# ROBOTIS TurtleBot3
ROBOTIS e-Manual for TurtleBot3: http://turtlebot3.robotis.com/

## Install ROS Kinetic (predefined image)
For details, look at
https://emanual.robotis.com/docs/en/platform/turtlebot3/raspberry_pi_3_setup/#raspberry-pi-3-setup

Image used
```
image_rpi_20190429.img.zip
```
Burn the image to a SD card. Afterwards add two files to the `boot` partititon:

- An empty  file `ssh`
- A file named `wpa_supplicant.conf` with the contents
```
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=DE

network={
 ssid="<Name of your wireless LAN>"
 psk="<Password for your wireless LAN>"
}
```

### After initial boot
To make  `ifconfig´ available
```
apt-get install net-tools 
```

Set up an SMB Server (optional)
```
sudo apt update
sudo apt install samba

sudo nano /etc/samba/smb.conf [do your magic here]

sudo service smbd restart
sudo service smbd status

sudo smbpasswd -a pi
```

### Bringup
For details, look at
https://emanual.robotis.com/docs/en/platform/turtlebot3/bringup/#ros-1-bringup
```
roslaunch turtlebot3_bringup turtlebot3_robot.launch
roslaunch turtlebot3_bringup turtlebot3_rpicamera.launch
```

## Install ROS Melodic (Ubuntu Mate Bionic 18.04)
Image used
```
ubuntu-mate-18.04.2-beta1-desktop-armhf+raspi-ext4.img
```

### After initial boot
```
sudo apt-get update
sudo apt-get upgrade
```

### In case of upgrade errors
If any upgrade error occur, look what's missing
```
apt list --upgradable
``` 
and than try to install the listed files seperatly, like
```
sudo apt install fwupd
sudo apt install fwupdate
sudo apt install libfwup1
```
Ignore `linux-firmware-raspi2` and reboot.


### Enable ssh
Use `sudo raspi-config` to enable ssh. If ssh Keys are missing use
```
sudo /usr/bin/ssh-keygen - A
```

If the ssh option is not present in raspi-config do the following
```
sudo apt install openssh-server
sudo systemctl enable ssh.service
```

### Expand file system
Use `sudo raspi-config` to expand the file system

### Enable booting into CLI
Use `sudo raspi-config` to enable booting into CLI

### Install ROS Melodic for Turtlebot3
```
sudo apt-get update
sudo apt-get upgrade
```

Get the install script and execute
```
wget https://raw.githubusercontent.com/ROBOTIS-GIT/robotis_tools/master/install_ros_melodic_rp3.sh && chmod 755 ./install_ros_melodic_rp3.sh && bash ./install_ros_melodic_rp3.sh
```

Clone the necessary repos
```
cd ~/catkin_ws/src
git clone https://github.com/ROBOTIS-GIT/hls_lfcd_lds_driver.git
git clone https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git
git clone https://github.com/ROBOTIS-GIT/turtlebot3.git
```

Remove unneeded components
```
cd ~/catkin_ws/src/turtlebot3
rm -r turtlebot3_description/ turtlebot3_teleop/ turtlebot3_navigation/ turtlebot3_slam/ turtlebot3_example/
```

Get rosserial
```
sudo apt-get install ros-melodic-rosserial-python ros-melodic-tf
```

Make the components
```
source ~/.bashrc
cd ~/catkin_ws && catkin_make -j1
```

Set the USB access rights
```
rosrun turtlebot3_bringup create_udev_rules
```

Install & initialize rosdep
``` 
sudo apt-get install python-rosdep
sudo rosdep init
rosdep update
``` 

Source the environment
```
source ~/.bashrc
```

Test it...
``` 
roslaunch turtlebot3_bringup turtlebot3_robot.launch
``` 


### Enable pi camera
Enable camera with `sudo raspi-config` and test it with
´´´
raspistill -o test.jpg
´´´


### Clone & build raspicam_node
Install prerquisites
```
sudo apt-get install ros-melodic-compressed-image-transport ros-melodic-camera-info-manager
sudo apt-get install ros-melodic-diagnostic-updater
sudo apt install libraspberrypi-dev
```

Clone the repo from git
```
cd ~/catkin_ws/src
git clone https://github.com/UbiquityRobotics/raspicam_node.git
```

Edit `raspicam_node/package.xml` with
```
nano src/raspicam_node/package.xml
```
and uncomment thes two lines
```
<!-- <depend>libraspberrypi0</depend> -->
<!-- <depend>libraspberrypi-dev</depend> -->
```

Check dependencies
```
cd ~/catkin_ws
rosdep install --from-paths src --ignore-src -y
```

Source environment & build
```
source ~/.bashrc
cd ~/catkin_ws && catkin_make
```

### Test raspicam_node
```
roslaunch turtlebot3_bringup turtlebot3_rpicamera.launch
```


### intel RealSense
```
export ROS_VER=kinetic 
sudo apt-get install ros-$ROS_VER-realsense2-camera
```