#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024
#define ITERATIONS 100000

K_MUTEX_DEFINE(lock);

volatile int shared_counter = 0;

void thread_fn(void *p1, void *p2, void *p3) {
    for (int i = 0; i < ITERATIONS; i++) {
        k_mutex_lock(&lock, K_FOREVER);
        shared_counter++;
        k_mutex_unlock(&lock);
    }    
}

// Equal priority threads with same behavior
K_THREAD_DEFINE(thread_1, STACK_SIZE, thread_fn, NULL, NULL, NULL,  2, 0, 0);
K_THREAD_DEFINE(thread_2, STACK_SIZE, thread_fn, NULL, NULL, NULL,  2, 0, 0);

int main(void) { 
    k_thread_join(thread_1, K_FOREVER);
    k_thread_join(thread_2, K_FOREVER);
    LOG_INF("Expected counter: %d", ITERATIONS*2);
    LOG_INF("Actual counter: %d", shared_counter);
    return 0;
}

