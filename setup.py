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
    install_requires=[
        'json',
        'pkg_resources',
    ],
    download_url='https://github.com/Jyumpp/dynamixel-controller/archive/v_01.tar.gz',
    url="https://github.com/Jyumpp/dynamixel-controller",
    keywords="dynamixel, dxl, dynamixel_sdk, motor controller",
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Build Tools',
        'License :: Apache License'
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
    ]
)
