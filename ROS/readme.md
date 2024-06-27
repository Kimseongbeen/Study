Installing ROS Noetic Ubuntu 20.04
Here you can find the official guide on how to install ROS Noetic on Ubuntu 20.04.
Alternatively you can copy in the terminal the following commands
1. Configure the source.list
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release
-sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt install curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc |
sudo apt-key add -
2. Install the desktop full version of ROS Noetic
sudo apt update
sudo apt install ros-noetic-desktop-full
3. Configure the environment to use and execute the ROS commands in a terminal
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
4. Install the additional components to create and manage ROS applications
sudo apt install python3-rosdep python3-rosinstall
python3-rosinstall-generator python3-wstool build-essential
sudo rosdep init
rosdep update