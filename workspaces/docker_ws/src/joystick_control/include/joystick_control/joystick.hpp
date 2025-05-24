#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>


struct axis_state {
    short x, y;
};


int read_event(int fd, struct js_event *event);

size_t get_axis_count(int fd);

/**
 * Returns the number of buttons on the controller or 0 if an error occurs.
 */
size_t get_button_count(int fd);

size_t get_axis_state(struct js_event *event, struct axis_state axes[3]);
