#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>


#define TEST_DEVICE_NAME "hires-emu test device"


int main(int argc, char **argv)
{
	int err;
	int fd, uifd;
	struct libevdev *dev;
	struct libevdev_uinput *uidev;

	fd = open("/dev/input/event0", O_RDONLY);
	if (fd < 0)
		return -errno;

	err = libevdev_new_from_fd(fd, &dev);
	if (err != 0)
		return err;

	uifd = open("/dev/uinput", O_RDWR);
	if (uifd < 0)
		return -errno;

	libevdev_set_name(dev, TEST_DEVICE_NAME);
	libevdev_enable_event_type(dev, EV_SYN);
	libevdev_enable_event_type(dev, EV_REL);
	libevdev_enable_event_code(dev, EV_REL, REL_X, NULL);
	libevdev_enable_event_code(dev, EV_REL, REL_Y, NULL);
	libevdev_enable_event_code(dev, EV_REL, REL_WHEEL, NULL);
	libevdev_enable_event_code(dev, EV_REL, REL_HWHEEL, NULL);
	libevdev_enable_event_code(dev, EV_REL, REL_WHEEL_HI_RES, NULL);
	libevdev_enable_event_code(dev, EV_REL, REL_HWHEEL_HI_RES, NULL);
	libevdev_enable_event_code(dev, EV_KEY, BTN_LEFT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, BTN_RIGHT, NULL);

	err = libevdev_uinput_create_from_device(dev, uifd, &uidev);
	if (err != 0)
		return err;

	sleep(1);

	err = libevdev_uinput_write_event(uidev, EV_REL, REL_WHEEL_HI_RES, 15);
	if (err != 0)
		return err;

	err = libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
	if (err != 0)
		return err;

	libevdev_uinput_destroy(uidev);
	libevdev_free(dev);
	close(uifd);
	close(fd);

	return 0;
}
