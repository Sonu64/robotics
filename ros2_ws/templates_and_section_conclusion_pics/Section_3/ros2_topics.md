# ROS 2 Topics

## Overview

A **topic** is a named bus over which ROS nodes exchange messages. It provides a unidirectional data stream between a publisher (sender) and one or more subscribers (receivers).

## Key Characteristics

- **Named Bus**: Topics have unique names (e.g., `freq_98.7`, `freq_101.3`, `car_location`) that identify the communication channel
- **Publisher/Subscriber Model**: Unidirectional communication where publishers send data and subscribers receive it
- **Anonymous Communication**: Publishers and subscribers don't need to know each other's identities
- **Typed Messages**: Each topic has a defined message type that structure the data being published
- **Language Agnostic**: Topics can be written in Python, C++, or other languages directly inside ROS nodes
- **Multiple Connections**: A single node can have multiple publishers and subscribers for different topics simultaneously

## Example Use Cases

- **freq_98.7**: A music/audio topic that multiple devices can subscribe to
- **freq_101.3**: Another broadcast channel (e.g., radio frequency) for vehicle locations
- **car_location**: GPS topic containing latitude and longitude data from a car publisher to a monitoring station subscriber

## Why Topics?

Topics decouple nodes from each other—nodes don't need to know about one another. They simply publish or subscribe to topics of interest, making the system flexible and scalable.
