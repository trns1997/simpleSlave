#ifndef MAIN_CPP_HPP_
#define MAIN_CPP_HPP_

#ifdef __cplusplus
extern "C" {
#endif

void init_threads();
void tick_polled();
void tick_1ms();
void tick_10ms();

#ifdef __cplusplus
}
#endif

#endif
