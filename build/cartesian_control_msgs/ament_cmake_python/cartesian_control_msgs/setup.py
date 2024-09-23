from setuptools import find_packages
from setuptools import setup

setup(
    name='cartesian_control_msgs',
    version='0.0.1',
    packages=find_packages(
        include=('cartesian_control_msgs', 'cartesian_control_msgs.*')),
)
