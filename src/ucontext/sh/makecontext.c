/*
 * Copyright (c) 2020 Ariadne Conill <ariadne@dereferenced.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * This software is provided 'as is' and without any warranty, express or
 * implied.  In no event shall the authors be liable for any damages arising
 * from the use of this software.
 */

#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "defs.h"
#define _BSD_SOURCE
#include <ucontext.h>


extern void libucontext_trampoline(void);


void
libucontext_makecontext(ucontext_t *ucp, void (*func)(void), int argc, ...)
{
	greg_t *sp, *regp;
	va_list va;
	int i;

	/* set up and align the stack */
	sp = (greg_t *) (((uintptr_t) ucp->uc_stack.ss_sp + ucp->uc_stack.ss_size) & -4L);
	sp -= argc > 4 ? argc - 4 : 0;

	/* set up the context */
	ucp->uc_mcontext.gregs[REG_SP] = (greg_t) sp;
	ucp->uc_mcontext.pr = (greg_t) libucontext_trampoline;
	ucp->uc_mcontext.pc = (greg_t) func;
	ucp->uc_mcontext.gregs[8] = (greg_t) ucp->uc_link;

	/* pass up to four args in r4-r7, rest on stack */
	va_start(va, argc);

	regp = &ucp->uc_mcontext.gregs[4];

	for (i = 0; i < argc && i < 4; i++)
		*regp++ = va_arg(va, greg_t);

	for (; i < argc; i++)
		*sp++ = va_arg(va, greg_t);

	va_end(va);
}


extern __typeof(libucontext_makecontext) makecontext __attribute__((__weak__, __alias__("libucontext_makecontext")));
extern __typeof(libucontext_makecontext) __makecontext __attribute__((__weak__, __alias__("libucontext_makecontext")));

