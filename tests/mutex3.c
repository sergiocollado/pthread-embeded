/*
 * mutex3.c
 *
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads-embedded (PTE) - POSIX Threads Library for embedded systems
 *      Copyright(C) 2008 Jason Schmidlapp
 *
 *      Contact Email: jschmidlapp@users.sourceforge.net
 *
 *
 *      Based upon Pthreads-win32 - POSIX Threads Library for Win32
 *      Copyright(C) 1998 John E. Bossom
 *      Copyright(C) 1999,2005 Pthreads-win32 contributors
 *
 *      Contact Email: rpj@callisto.canberra.edu.au
 *
 *      The original list of contributors to the Pthreads-win32 project
 *      is contained in the file CONTRIBUTORS.ptw32 included with the
 *      source code distribution. The list can also be seen at the
 *      following World Wide Web location:
 *      http://sources.redhat.com/pthreads-win32/contributors.html
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library in the file COPYING.LIB;
 *      if not, write to the Free Software Foundation, Inc.,
 *      59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 *
 * --------------------------------------------------------------------------
 *
 * Declare a static mutex object, lock it, trylock it,
 * and then unlock it again.
 *
 * Depends on API functions:
 *	pthread_mutex_lock()
 *	pthread_mutex_trylock()
 *	pthread_mutex_unlock()
 */

#include <stdio.h>
#include <stdlib.h>

#include "test.h"

static pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

static int washere = 0;

static void * func(void * arg)
{
  assert(pthread_mutex_trylock(&mutex1) == EBUSY);

  washere = 1;

  return 0;
}

int
pthread_test_mutex3()
{
  pthread_t t;

  mutex1 = PTHREAD_MUTEX_INITIALIZER;

  assert(pthread_mutex_lock(&mutex1) == 0);

  assert(pthread_create(&t, NULL, func, NULL) == 0);
  assert(pthread_join(t, NULL) == 0);

  assert(pthread_mutex_unlock(&mutex1) == 0);

  assert(washere == 1);

  assert(pthread_mutex_destroy(&mutex1) == 0);

  return 0;
}
