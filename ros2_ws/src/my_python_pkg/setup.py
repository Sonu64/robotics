from setuptools import find_packages, setup

package_name = 'my_python_pkg'

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
    maintainer='sonu',
    maintainer_email='sonusantu64@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            "py_node =  my_python_pkg.first_python_node:main",
            "robot_news_station = my_python_pkg.robot_news_station:main",
            "smartphone = my_python_pkg.smartphone:main"
            ,"number_publisher = my_python_pkg.number_publisher:main"
        ],
    },
)
