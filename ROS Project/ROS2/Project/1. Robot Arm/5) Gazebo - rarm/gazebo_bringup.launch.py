from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription, ExecuteProcess
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory, get_package_prefix
import os

def generate_launch_description():
    pkgPath = get_package_share_directory('robotic_arms_control')
    urdfFile = os.path.join(pkgPath, 'urdf', 'arms.urdf')
    
    # Gazebo model path 설정
    mesh_pkg_share_dir = os.pathsep + os.path.join(get_package_prefix('franka_description'), 'share')
    if 'GAZEBO_MODEL_PATH' in os.environ:
        os.environ['GAZEBO_MODEL_PATH'] += mesh_pkg_share_dir
    else:
        os.environ['GAZEBO_MODEL_PATH'] = mesh_pkg_share_dir

    # URDF 파일을 읽어 robot_description 파라미터로 설정
    with open(urdfFile, 'r') as infp:
        robot_desc = infp.read()

    # Gazebo launch
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('gazebo_ros'), 'launch'), '/gazebo.launch.py']),
        launch_arguments={'world': '/usr/share/gazebo-11/worlds/empty.world'}.items(),
    )

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_desc}],
    )

    spawn_entity = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        name='robot_spawner',
        output='screen',
        arguments=['-topic', 'robot_description', '-entity', 'armss'],
    )

    ros2_control_node = Node(
        package='controller_manager',
        executable='ros2_control_node',
        parameters=[{'robot_description': robot_desc},
                    os.path.join(pkgPath, 'config', 'arms_pos_controller.yaml')],
        output='screen',
    )

    return LaunchDescription([
        gazebo,
        robot_state_publisher,
        spawn_entity,
        ros2_control_node,
    ])