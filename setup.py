################################################################################
# Copyright 2020 University of Georgia Bio-Sensing and Instrumentation Lab
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

# Author: Hunter Halloran (Jyumpp)

from setuptools import setup, find_packages

setup(
    name="dynamixel_controller",
    version='0.8.2',
    packages=find_packages(),
    author="Hunter Halloran (Jyumpp)",
    author_email="hdh20267@uga.edu",
    package_data={
        '': ['*.json'],
    },
    install_requires=[
        'setuptools',
        'pyserial',
        'deprecation',
    ],
    description="A new tool for operating Dynamixel series motors!",
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    download_url='https://github.com/UGA-BSAIL/dynamixel-controller/archive/dynamixel_controller-0.8.2.tar.gz',
    url="https://github.com/UGA-BSAIL/dynamixel-controller",
    keywords="dynamixel, dxl, dynamixel_sdk, motor controller, robotis, motor, robot",
    classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Libraries',
        'License :: OSI Approved :: Apache Software License',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
    ]
)
