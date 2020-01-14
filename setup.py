from setuptools import setup, find_packages

setup(
    name="dynamixel_controller",
    version=0.1,
    packages=find_packages(),
    author="Hunter Halloran (Jyumpp)",
    author_email="hdh20267@uga.edu",
    package_data={
        '': ['*.json'],
    },
    url="https://github.com/Jyumpp/dynamixel-controller",
    keywords="dynamixel, dxl, dynamixel_sdk, motor controller",
    classifiers=[
        'License :: Apache License'
    ]
)
