FROM ros:jazzy-ros-core
RUN apt-get update

RUN apt-get install -y \
    python3-colcon-common-extensions \
    git \
    libopencv-* \
    python3-gpiozero \
    python3-serial \
    libopencv-dev gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-libcamera \
    build-essential \
    ros-jazzy-cv-bridge

RUN apt-get install -y \
    ros-jazzy-camera-ros

RUN apt-get install -y \
    libcamera-ipa libcamera-dev

RUN apt-get install -y \
    libcamera-*

RUN apt-get install -y \
    git bc bison flex libssl-dev make meson \
    libcamera-dev \
    libudev-dev libyaml-dev libgnutls28-dev python3-yaml python3-ply python3-jinja2


# RUN git clone https://github.com/raspberrypi/libcamera.git
# WORKDIR /libcamera
# RUN meson setup build -Dpipelines=rpi/vc4 -Dipas=rpi/vc4
# RUN ninja -C build
# RUN ninja -C build install


# ENV LIBCAMERA_IPA_MODULE_PATH=/usr/share/libcamera
# ENV LIBCAMERA_IPA_MODULE_PATH=/usr/lib/aarch64-linux-gnu/libcamera

RUN rm -rf /var/lib/apt/lists/*

WORKDIR /ros2_ws
COPY ./src ./src
COPY ./scripts ./scripts

RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc