from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # 패키지 이름
    pkg_description = get_package_share_directory('robotic_arms_control')
    # urdf 파일 이름 설정
    urdf_file = os.path.join(pkg_description, "urdf", 'arms.urdf')

    # Read the URDF file
    with open(urdf_file, 'r') as file:
        urdf_content = file.read()

    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="RSP",
        output="screen",
        parameters=[{'robot_description': urdf_content}]
    )
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz_gui",
        output="screen"
    )

    # Return the LaunchDescription
    return LaunchDescription([
        robot_state_publisher_node,
        rviz_node
    ])

if __name__ == '__main__':
    generate_launch_description()