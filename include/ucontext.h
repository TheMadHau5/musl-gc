#ifndef _UCONTEXT_H
#define _UCONTEXT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>
#include <sys/ucontext.h>

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#define NGREG (sizeof(gregset_t)/sizeof(greg_t))
#endif

int  getcontext(ucontext_t *);
void makecontext(ucontext_t *, void (*)(), int, ...);
int  setcontext(const ucontext_t *);
int  swapcontext(ucontext_t *, const ucontext_t *);

#ifdef __cplusplus
}
#endif
#endif
