FROM ros:jazzy-ros-core

RUN apt-get update && apt-get install -y \
    python3-colcon-common-extensions \
    git \
    libopencv-* \
    python3-gpiozero \
    python3-serial \
    libopencv-dev gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-libcamera \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /ros2_ws
COPY ./src ./src
COPY ./scripts ./scripts

RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc