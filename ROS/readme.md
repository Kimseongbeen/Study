Installing ROS Noetic Ubuntu 20.04

https://wiki.ros.org/noetic/Installation/Ubuntu
위 주소에 들어가면 Ubuntu 20.04 환경에서 ROS를 설치하는 방법을 알 수 있습니다. 
또는 아래 터미널에서 다음 명령을 복사할 수 있습니다

1. Configure the source.list
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release
-sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt install curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc |
sudo apt-key add -
```
2. Install the desktop full version of ROS Noetic
```
sudo apt update
sudo apt install ros-noetic-desktop-full
```
3. Configure the environment to use and execute the ROS commands in a terminal
```
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```
4. Install the additional components to create and manage ROS applications
```
sudo apt install python3-rosdep python3-rosinstall
python3-rosinstall-generator python3-wstool build-essential
sudo rosdep init
rosdep update
```
