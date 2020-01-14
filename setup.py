from setuptools import setup, find_packages

setup(
    name="dynamixel_controller",
    version=0.3,
    packages=find_packages(),
    author="Hunter Halloran (Jyumpp)",
    author_email="hdh20267@uga.edu",
    package_data={
        '': ['*.json'],
    },
    install_requires=[
        'setuptools',
    ],
    download_url='https://github.com/Jyumpp/dynamixel-controller/archive/dynamixel_controller-0.3.tar.gz',
    url="https://github.com/Jyumpp/dynamixel-controller",
    keywords="dynamixel, dxl, dynamixel_sdk, motor controller",
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Libraries',
        'License :: OSI Approved :: Apache Software License',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
    ]
)
