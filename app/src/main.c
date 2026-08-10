#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024

void t_high_fn(void *p1, void *p2, void *p3) {
    while (1) {
        LOG_INF("T_HIGH running");
        k_msleep(100);
    }
}

void t_med_fn(void *p1, void *p2, void *p3) {
    while (1) {
        LOG_INF("T_MED running");
        k_msleep(200);
    }
}

void t_low_fn(void *p1, void *p2, void *p3) {
    while (1) {
        LOG_INF("T_LOW running");
        k_msleep(300);
    }
}

void t_coop_fn(void *p1, void *p2, void *p3) {
    while (1) {
        int sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += i;
            LOG_INF("%d BUSY WORK %d", i, sum);
        }
        k_yield();
    }
}

K_THREAD_DEFINE(thread_high, STACK_SIZE, t_high_fn, NULL, NULL, NULL,  3, 0, 0);
K_THREAD_DEFINE(thread_med , STACK_SIZE, t_med_fn , NULL, NULL, NULL,  5, 0, 0);
K_THREAD_DEFINE(thread_low , STACK_SIZE, t_low_fn , NULL, NULL, NULL,  7, 0, 0);
K_THREAD_DEFINE(thread_coop, STACK_SIZE, t_coop_fn, NULL, NULL, NULL, -1, 0, 0);

int main(void) { return 0; }

