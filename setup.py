################################################################################
# Copyright 2020 Hunter Halloran
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

from setuptools import setup, find_packages

setup(
    name="dynamixel_controller",
    version='0.5.1',
    packages=find_packages(),
    author="Hunter Halloran (Jyumpp)",
    author_email="hdh20267@uga.edu",
    package_data={
        '': ['*.json'],
    },
    install_requires=[
        'setuptools',
    ],
    download_url='https://github.com/Jyumpp/dynamixel-controller/archive/dynamixel_controller-0.5.1.tar.gz',
    url="https://github.com/Jyumpp/dynamixel-controller",
    keywords="dynamixel, dxl, dynamixel_sdk, motor controller",
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Libraries',
        'License :: OSI Approved :: Apache Software License',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
    ]
)
