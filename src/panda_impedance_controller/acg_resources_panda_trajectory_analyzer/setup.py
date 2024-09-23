from setuptools import find_packages, setup

package_name = 'acg_resources_panda_trajectory_analyzer'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    package_data={
        package_name: ['resource/acg_resources_panda_trajectory_analyzer/*'],
    },
    install_requires=['setuptools', 'cartesian_control_msgs', 'scipy'],
    zip_safe=True,
    maintainer='Beniamino Squitieri',
    maintainer_email='b.squitieri@studenti.unisa.it',
    description='A robot-agnostic module for utility tools',
    license='BSD',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'trajectory_analyzer = acg_resources_panda_trajectory_analyzer.trajectory_analyzer:main'
        ],
    },
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
)
