from setuptools import find_packages, setup

package_name = 'acg_resources_panda_trajectory_generation'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer=['Beniamino Squitieri'],
    maintainer_email=['b.squitieri@studenti.unisa.it'],
    description='The data_generator_executable.py script is a ROS 2 node developed for generating square trajectories and writing them to rosbag files',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'data_generator_executable = acg_resources_panda_trajectory_generation.data_generator_executable:main',

        ],
    },
    
)
