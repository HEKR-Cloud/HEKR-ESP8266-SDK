#ifndef __ESP_UPGRADE__
#define __ESP_UPGRADE__


void  start_check_update(void);
void  check_update_task(void *arg);
void  start_update(char *bin_dir);
#endif