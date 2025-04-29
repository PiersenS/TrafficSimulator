#!/bin/bash

sudo apt update

sudo apt install build-essential -y
sudo apt install libsfml-dev -y

sudo apt install git -y

mkdir PiersenPracticum
cd PiersenPracticum

git clone https://github.com/PiersenS/TrafficSimulator.git
