## ROBOTIS e-Manual for TurtleBot3
- [ROBOTIS e-Manual for TurtleBot3](http://turtlebot3.robotis.com/)

## HowTo

### Setup PC ###

docker run -it -e DISPLAY=192.168.0.44:0.0 -v C:/Daten/docker_turtlebot3_root:/root --network host --privileged --name docker_ros_turtlebot3 osrf/ros:kinetic-desktop-full

https://emanual.robotis.com/docs/en/platform/turtlebot3/pc_setup/#pc-setup

apt-get install net-tools (make  "ifconfig" available)


### Setup SBC ###

https://emanual.robotis.com/docs/en/platform/turtlebot3/raspberry_pi_3_setup/#raspberry-pi-3-setup

create boot image

create file "ssh":
(empty)

create file "wpa_supplicant.conf":
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=DE

network={
 ssid="<Name of your wireless LAN>"
 psk="<Password for your wireless LAN>"
}


### SMB Server ###

sudo apt update
sudo apt install samba

sudo nano /etc/samba/smb.conf
sudo service smbd restart
sudo service smbd status
sudo smbpasswd -a pi


### Bringup ###

https://emanual.robotis.com/docs/en/platform/turtlebot3/bringup/#ros-1-bringup

roslaunch turtlebot3_bringup turtlebot3_robot.launch

roslaunch turtlebot3_bringup turtlebot3_rpicamera.launch

