FROM ros:jazzy-ros-core

RUN apt-get update && apt-get install -y \
    python3-colcon-common-extensions \
    git \
    libopencv-* \
    python3-gpiozero \
    python3-serial \
    libopencv-dev gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-libcamera \
    build-essential \
    ros-jazzy-cv-bridge \
    ros-jazzy-camera-ros \
    libcamera-ipa libcamera-dev libcamera-*\
    git bc bison flex libssl-dev make meson \
    libcamera-dev \
    libudev-dev libyaml-dev libgnutls28-dev python3-yaml python3-ply python3-jinja2 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /ros2_ws
COPY ./src ./src
COPY ./scripts ./scripts

RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc