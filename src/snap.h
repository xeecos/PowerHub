#pragma once
void snap_init();
void snap_run();
void snap_add_task(int frames = 1, int delay = 0, int exposure = 1, int during = 1);
void snap_cancel_task();
int snap_get_frames();
int snap_get_current();