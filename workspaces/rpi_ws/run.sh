#!/bin/bash
# sudo docker run -it --rm --privileged --net=host -v /dev:/dev -v /run/udev:/run/udev:ro --tmpfs /dev/shm:exec --name ros ros-jazzy-pi

sudo docker run -it --rm \
  --privileged \
  --net=host \
  --ipc=host \
  -v /dev:/dev \
  -v /run/udev:/run/udev \
  -v /usr/share/libcamera:/usr/share/libcamera \
  -v /usr/lib/aarch64-linux-gnu/libcamera:/usr/lib/aarch64-linux-gnu/libcamera \
  --device /dev/dma_heap/linux,cma:/dev/dma_heap/linux,cma \
  --device /dev/dma_heap/system:/dev/dma_heap/system \
  --tmpfs /dev/shm:exec \
  --name ros ros-jazzy-pi