#define __LARGEFILE_SOURCE
#define __USE_LARGEFILE64
#define __USE_LARGEFILE64
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <setjmp.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#define __USE_GNU
#include <dlfcn.h>
#define __USE_GNU
#include <string.h>
//#include <execinfo.h> not in __EMSCRIPTEN__
#include <math.h>
#include <complex.h>
#include <float.h>
#include <fenv.h>
#include <dirent.h>
#include <signal.h>
#include <nl_types.h>
#include <termios.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <libgen.h>
//#include <netinet/ether.h>
#include <grp.h>
#include <sys/vfs.h>
#include <sys/timeb.h>
//#include <syslog.h>
#define __USE_LARGEFILE64
#include <sys/types.h>
#include <unistd.h>
#include <wctype.h>
#include <libintl.h>
#include <iconv.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/wait.h>
#define __XOPEN_SOURCE             /* See feature_test_macros(7) */
#define __USE_XOPEN
#include <wchar.h>
#include <langinfo.h>
#include <dirent.h>
#include <locale.h>
#include <sys/mman.h>
#include <pthread.h>

#include <fnmatch.h>
#define _LARGEFILE64_SOURCE
#define __USE_LARGEFILE64
#include <sys/types.h>
#include <unistd.h>
#include <sys/mount.h>
#include <poll.h>
#include <semaphore.h>
#include <sys/uio.h>

#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>

void SDL_Delay(uint32_t m);
void emscripten_sleep (unsigned int ms);
void __assert_fail(const char * assertion, const char * file, unsigned int line, const char * function);

#include "emu/x86emu_private.h"
#include "x86run.h"
#include "debug.h"

//#include "wrappedlibs.h"
//#include "wrapper.h"
//
//#include "librarian/library_private.h"
//#include "bridge.h"
//
//#undef LIBNAME
//#define LIBNAME libc
//const char* libcName =
//#ifdef ANDROID
//    "libc.so"
//#else
//    "libc.so.6"
//#endif
//    ;
//#include "wrapped/wrappedlib_init.h"
//#undef LIBNAME
//#define LIBNAME libm
//const char* libmName =
//#ifdef ANDROID
//    "libm.so"
//#else
//    "libm.so.6"
//#endif
//    ;
//#include "wrapped/wrappedlib_init.h"
//#undef LIBNAME
//#define LIBNAME libgl
//const char* libglName = "libGL.so.1";
//#include "wrapped/wrappedlib_init.h"
//#undef LIBNAME
//#define LIBNAME sdl2
//const char* sdl2Name = "libSDL2-2.0.so.0";
//#include "wrapped/wrappedlib_init.h"
////#undef LIBNAME
////#define LIBNAME libdl
////const char* libdlName =
////#ifdef ANDROID
////    "libdl.so"
////#else
////    "libdl.so.2"
////#endif
////    ;
////#include "wrapped/wrappedlib_init.h"
////#undef LIBNAME
////#define LIBNAME libpthread
////const char* libpthreadName = "libpthread.so.0";
////#include "wrapped/wrappedlib_init.h"
////#undef LIBNAME
////#define LIBNAME librt
////const char* librtName = "librt.so.1";
////#include "wrapped/wrappedlib_init.h"
////#undef LIBNAME
////const char* ldlinuxName = "ld-linux.so.3";
////#define LIBNAME ldlinux
////#define ALTNAME "ld-linux.so.2"
////#include "wrapped/wrappedlib_init.h"

//void my__ITM_registerTMCloneTable(x86emu_t* emu, void* p, uint32_t s);
//void my__ITM_deregisterTMCloneTable(x86emu_t* emu, void* p);
//void my___cxa_finalize(x86emu_t* emu, void* p);
//void my___gmon_start__(x86emu_t *emu);
int my_printf(x86emu_t *emu, void* fmt, void* b, va_list V);
int32_t my___libc_start_main(x86emu_t* emu, int *(main) (int, char * *, char * *), int argc, char * * ubp_av, void (*init) (void), void (*fini) (void), void (*rtld_fini) (void), void (* stack_end)); // implemented in x86run_private.c
//int my_sprintf(x86emu_t* emu, void* buff, void * fmt, void * b, va_list V);
int my_asprintf(x86emu_t* emu, void** buff, void * fmt, void * b, va_list V);
int my_snprintf(x86emu_t* emu, void* buff, uint32_t s, void * fmt, void * b, va_list V);
void my___stack_chk_fail(x86emu_t* emu);
extern char** my___environ;
int my___fprintf_chk(x86emu_t *emu, void* F, void* fmt, void* b, va_list V);
FILE* my_fopen(x86emu_t* emu, const char* path, const char* mode);
FILE* my_fopen64(x86emu_t* emu, const char* path, const char* mode);
int my___fprintf_chk(x86emu_t *emu, void* F, void* fmt, void* b, va_list V);
int my___printf_chk(x86emu_t *emu, void* fmt, void* b, va_list V);
int my___snprintf_chk(x86emu_t* emu, void* buff, uint32_t s, void * fmt, void * b, va_list V);
int my___sprintf_chk(x86emu_t* emu, void* buff, void * fmt, void * b, va_list V);
int my___vfprintf_chk(x86emu_t *emu, void* F, void* fmt, void* b);
int my___vsnprintf_chk(x86emu_t* emu, void* buff, uint32_t s, void * fmt, void * b, va_list V);
int my_mprotect(x86emu_t* emu, void *addr, unsigned long len, int prot);
int32_t my___open(x86emu_t* emu, void* pathname, int32_t flags, uint32_t mode);
int32_t my__setjmp(x86emu_t* emu, /*struct __jmp_buf_tag __env[1]*/void *p);
int32_t my_open(x86emu_t* emu, void* pathname, int32_t flags, uint32_t mode);
int32_t my_open64(x86emu_t* emu, void* pathname, int32_t flags, uint32_t mode);
int32_t my_read(int fd, void* buf, uint32_t count);
int32_t my_readdir_r(x86emu_t* emu, void* dirp, void* entry, void** result);
int32_t my_readlink(x86emu_t* emu, void* path, void* buf, uint32_t sz);
void my___longjmp_chk(x86emu_t* emu, /*struct __jmp_buf_tag __env[1]*/void *p, int32_t __val);
void my_qsort(x86emu_t* emu, void* base, size_t nmemb, size_t size, void* fnc);
void my_qsort_r(x86emu_t* emu, void* base, size_t nmemb, size_t size, void* fnc, void* data);
void* my_fopencookie(x86emu_t* emu, void* cookie, void* mode, void* read, void* write, void* seek, void* close);
void* my_readdir(x86emu_t* emu, void* dirp);
void* my_dlopen(const char* filename, int flags);
int my_dlclose(void *handle);
void* my_dlsym(void *restrict handle, const char *restrict symbol);
int32_t my___register_atfork(x86emu_t *emu, void* prepare, void* parent, void* child, void* handle);
void* my___libc_dlopen_mode(x86emu_t* emu, void* name, int mode);
int32_t my_fcntl(x86emu_t* emu, int32_t a, int32_t b, uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4, uint32_t d5, uint32_t d6);
void* my___libc_dlsym(x86emu_t* emu, void* handle, void* name);
int my___xstat64(x86emu_t* emu, int v, void* path, void* buf);
char* my_dlerror(x86emu_t* emu);
int32_t my_execv(x86emu_t* emu, const char* path, char* const argv[]);
pid_t my_fork(x86emu_t* emu);
int my_fprintf(x86emu_t *emu, void* F, void* fmt, void* b, va_list V);
void* my_mmap(x86emu_t* emu, void *addr, unsigned long length, int prot, int flags, int fd, int offset);
int my_munmap(x86emu_t* emu, void* addr, unsigned long length);
int32_t my_nftw64(x86emu_t* emu, void* pathname, void* B, int32_t nopenfd, int32_t flags);
int my_pthread_create(x86emu_t *emu, void* t, void* attr, void* start_routine, void* arg) { return 1; }
void* my_realpath(x86emu_t* emu, void* path, void* resolved_path);
int my_sprintf(x86emu_t* emu, void* buff, void * fmt, void * b, va_list V);
int my___lxstat64(x86emu_t* emu, int v, void* name, void* buf);
int32_t my_execve(x86emu_t* emu, const char* path, char* const argv[], char* const envp[]);
int32_t my_fcntl64(x86emu_t* emu, int32_t a, int32_t b, uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4, uint32_t d5, uint32_t d6);
void* my_mmap64(x86emu_t* emu, void *addr, unsigned long length, int prot, int flags, int fd, int64_t offset);
int my_pthread_attr_destroy(x86emu_t* emu, void* attr);
int my_pthread_cond_timedwait(x86emu_t* emu, void* cond, void* mutex, void* abstime);
int my_pthread_cond_wait(x86emu_t* emu, void* cond, void* mutex);
int my_pthread_key_create(x86emu_t* emu, void* key, void* dtor);
int my_pthread_kill(x86emu_t* emu, void* thread, int sig);

int my_pthread_kill(x86emu_t* emu, void* thread, int sig) { return 1; }
int my_pthread_cond_timedwait(x86emu_t* emu, void* cond, void* mutex, void* abstime) { return 1; }
int my_pthread_cond_wait(x86emu_t* emu, void* cond, void* mutex) { return 1; }
int my_pthread_key_create(x86emu_t* emu, void* key, void* dtor) { return 1; }
int my_pthread_attr_destroy(x86emu_t* emu, void* attr) { return 1; }

//off64_t lseek64(int fd, off64_t offset, int whence);
off_t lseek64(int fd, off_t offset, int whence);
//ssize_t pread64(int fd, void * buf, size_t count, off64_t offset);
ssize_t pread64(int fd, void * buf, size_t count, off_t offset);

char * __realpath_chk(const char * path, char * resolved_path, size_t resolved_len);
int __isoc99_vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg);

//ssize_t splice(int fd_in, off64_t *off_in, int fd_out, off64_t *off_out, size_t len, unsigned int flags);
ssize_t splice(int fd_in, off_t *off_in, int fd_out, off_t *off_out, size_t len, unsigned int flags);
//ssize_t pwrite64 (int __fd, const void *__buf, size_t __n, __off64_t __offset);
ssize_t pwrite64 (int __fd, const void *__buf, size_t __n, off_t __offset);
struct dirent64 *readdir64 (DIR *__dirp);

#ifndef __EMSCRIPTEN_major__
void *pthread_getspecific(pthread_key_t key) { return NULL; }
int pthread_setspecific(pthread_key_t key, const void *value) { return 1;}
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr) { return 1; }
int pthread_mutexattr_init(pthread_mutexattr_t *attr) { return 1; }
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type) { return 1; }
int pthread_getattr_np(pthread_t thread, pthread_attr_t* attr) { return 1; }
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize) { return 1; }
int pthread_attr_getstack (const pthread_attr_t *__restrict __attr, void **__restrict __stackaddr, size_t *__restrict __stacksize) { return 1; }
int pthread_once(pthread_once_t *once_control, void (*init_routine)(void)) { return 1; }
int pthread_key_create(pthread_key_t *key, void (*destructor)(void*)) { return 1; }
//void _pthread_cleanup_pop_restore(void* buffer, int exec) {}
//void pthread_cleanup_pop(int execute) {}
void _pthread_cleanup_pop(void* buf, int i) {}
void _pthread_cleanup_push(void* buf, void (*fn) (void *), void * p) {}
int pthread_attr_setaffinity_np(pthread_attr_t *attr, size_t cpusetsize, const cpu_set_t* cpuset) { return 1; }
__cleanup_fct_attribute  void __pthread_register_cancel (__pthread_unwind_buf_t *__buf) {}
int pthread_setaffinity_np (pthread_t __th, size_t __cpusetsize, const cpu_set_t *__cpuset) { return 1; }
int pthread_getaffinity_np (pthread_t __th, size_t __cpusetsize, cpu_set_t *__cpuset) { return 1; }
int pthread_kill(pthread_t thread, int sig) { return 1; }
void _pthread_cleanup_push_defer (void* buffer, void (*routine) (void *), void *arg) {}
int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg) { return 1; }
int pthread_key_delete(pthread_key_t key) { return 1; }

int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset) { return 1; }
int pthread_detach(pthread_t thread) { return 1; }
int pthread_join(pthread_t thread, void **retval) { return 1; }
int pthread_cancel(pthread_t thread) { return 1; }
int sem_post(sem_t *sem) { return -1; }
int sem_destroy(sem_t *sem) { return -1; }
int sem_init(sem_t *sem, int pshared, unsigned int value) { return -1; }
int sem_wait(sem_t *sem) { return -1; }

//void x86Syscall(x86emu_t *emu) {}
#else
long syscall(long number, ...) { return 0; }
int clone(int (*fn)(void *), void *stack, int flags, void *arg, ...  /* pid_t *parent_tid, void *tls, pid_t *child_tid */ ) { return -1; }
#endif

int shm_open(const char *name, int oflag, mode_t mode) { return -1; }
int shm_unlink(const char *name) { return -1; }

int timer_create(clockid_t clockid, struct sigevent *restrict sevp, timer_t *restrict timerid) { return -1; }

uint32_t RunFunctionWithEmu(x86emu_t *emu, int QuitOnLongJump, uintptr_t fnc, int nargs, ...) { return 0; }
uint32_t RunFunction(box86context_t *context, uintptr_t fnc, int nargs, ...) { return 0; }
uint64_t RunFunction64(box86context_t *context, uintptr_t fnc, int nargs, ...) { return 0; }
//int my_setcontext(x86emu_t* emu, void* ucp) { return 0; }
void InitFTSMap(box86context_t* context) {}
void FreeFTSMap(box86context_t* context) {}
void CleanStackSize(box86context_t* context) {}
void freeALProcWrapper(box86context_t* context) {}
void init_pthread_helper() {}
void init_signal_helper(box86context_t* context) {}
void fini_pthread_helper(box86context_t* context) {}
void fini_signal_helper() {}

//void FreeDLPrivate(dlprivate_t **lib) {}
//dlprivate_t *NewDLPrivate() { return NULL; }
//void freeGLProcWrapper(box86context_t* context) {}

static uintptr_t* auxval_start = NULL;

int init_auxval(int argc, const char **argv, const char **env) {
    // auxval vector is after envs...
    while(*env)
        env++;
    auxval_start = (uintptr_t*)(env+1);
    return 0;
}

unsigned long real_getauxval(unsigned long type)
{
    if(!auxval_start)
        return 0;
    uintptr_t* p = auxval_start;
    while(*p) {
        if(*p == type)
            return p[1];
        p+=2;
    }
    return 0;
}

void UnalignStat64(const void* source, void* dest) {}
void UnalignStatFS64(const void* source, void* dest) {}
void UnalignFlock64(void* dest, void* source) {}
void AlignFlock64(void* dest, void* source) {}

void* customMalloc(size_t size)
{
  return malloc(size);
}

void* customCalloc(size_t n, size_t size)
{
  return calloc(n, size);
}

void* customRealloc(void* p, size_t size)
{
  return realloc(p, size);
}

void customFree(void* p)
{
  free(p);
}

void init_custommem_helper(box86context_t* ctx) {}
void fini_custommem_helper(box86context_t *ctx) {}
int unlockCustommemMutex() { return 0; }
void relockCustommemMutex(int locks) {}
void setProtection(uintptr_t addr, uintptr_t size, uint32_t prot) {}
uint32_t getProtection(uintptr_t addr) { return 0; }
void updateProtection(uintptr_t addr, uintptr_t size, uint32_t prot) {}

#ifdef __EMSCRIPTEN_major__
//const unsigned short * * __ctype_b_loc (void) { return NULL; }
//const int32_t * * __ctype_toupper_loc(void) { return NULL; }
//const int32_t * * __ctype_tolower_loc(void) { return NULL; }
#endif

x86emu_t* theEmu;
void thread_set_emu(x86emu_t* emu) { theEmu = emu; }
x86emu_t* thread_get_emu() { return theEmu; }

//void* my_dlopen(const char* filename, int flags) 
//{
//  printf("my_dlopen --> %s\n", filename);
//  return (void*) 1; 
//}
//int my_dlclose(void *handle) { return 0; }
//char* my_dlerror(void) { return 0; }
//void* my_dlsym(void *restrict handle, const char *restrict symbol) { return 0; }
void obstackSetup() {}

void* my_prepare_thread(x86emu_t *emu, void* f, void* arg, int ssize, void** pet) { return NULL; }
void* my_vkGetInstanceProcAddr(x86emu_t* emu, void* instance, void* name) { return NULL; }
int checkUnlockMutex(void* m) { return 1; }

void** my_GetGTKDisplay() { return NULL; }
void** my_GetGthreadsGotInitialized() { return NULL; }
void* GetJmpBuf() { return NULL; }

int my_setcontext(x86emu_t* emu, void* ucp) { return 0; }
void emit_signal(x86emu_t* emu, int sig, void* addr, int code) {}
int my_syscall_sigaction(x86emu_t* emu, int signum, const void* act, void* oldact, int sigsetsize) { return 0; }
int my_sigaction(x86emu_t* emu, int signum, const void* act, void* oldact) { return 0; }

void my_cpuid(x86emu_t* emu, uint32_t tmp32u) {}
int DynaRun(x86emu_t* emu) { Run(emu, 0); return 0; }

//char *MY__dcgettext(const char *domainname, const char *msgid, int category)
//{
//  __dcgettext(domainname, msgid, category);
//};

//void * MY__memcpy_chk(void * dest, const void * src, size_t len, size_t destlen)
//{
//  return __memcpy_chk(dest, src, len, destlen);
//}
//
//void * MY__memmove_chk(void * dest, const void * src, size_t len, size_t destlen)
//{
//  return __memmove_chk(dest, src, len, destlen);
//}
//
//char * MY__strcpy_chk(char * dest, const char * src, size_t destlen)
//{
//  return __strcpy_chk(dest, src, destlen);
//}


static void do_nothing() {}
void* dlopen(const char* filename, int flags) 
{
  //printf_log(LOG_DEBUG, "dlopen --> %s\n", filename);
  printf("dlopen --> %s\n", filename);
  return (void*) 1; 
}
int dlclose(void *handle) { return 0; }
int dladdr(const void *__address, Dl_info* __info) { return 0; }
char* dlerror(void) { return 0; }
//void obstackSetup() {}
//int shm_open(const char *name, int oflag, mode_t mode) { return -1; }
//int shm_unlink(const char *name) { return -1; }
//long syscall(long number, ...) { return 0; }


//#include "librarian/library_private.h"
//#include "wrapper.h"
//#include "bridge.h"
//
//#undef LIBNAME
//#define LIBNAME libc
//const char* libcName =
//#ifdef ANDROID
//    "libc.so"
//#else
//    "libc.so.6"
//#endif
//    ;
//#include "wrapped/wrappedlib_init.h"
//
//const char* libglName = "libGL.so.1";
//#undef LIBNAME
//#define LIBNAME libgl
//#include "wrapped/wrappedlib_init.h"
//
//const char* sdl2Name = "libSDL2-2.0.so.0";
//#undef LIBNAME
//#define LIBNAME sdl2
//#include "wrapped/wrappedlib_init.h"
//
//const char* libmName =
//#ifdef ANDROID
//    "libm.so"
//#else
//    "libm.so.6"
//#endif
//    ;
//#undef LIBNAME
//#define LIBNAME libm
//#include "wrapped/wrappedlib_init.h"

void* dlsym(void *restrict handle, const char *restrict symbol)
{
  if ( !strcmp("SDL_Delay", symbol) ) 
  #if defined(__EMSCRIPTEN__) && defined(__EMSCRIPTEN_major__)
    return &emscripten_sleep;
  #else
    return &SDL_Delay;
  #endif

  if ( !strcmp("my__ITM_deregisterTMCloneTable", symbol) ) return &do_nothing;
  if ( !strcmp("my___cxa_finalize", symbol) ) return &do_nothing;
  if ( !strcmp("my___gmon_start__", symbol) ) return &do_nothing;
  if ( !strcmp("my__ITM_registerTMCloneTable", symbol) ) return &do_nothing;

  if ( !strcmp("my___libc_start_main", symbol) ) return &my___libc_start_main;
  if ( !strcmp("my_printf", symbol) ) return &my_printf;
  //if ( !strcmp("my___asprintf", symbol) ) return &my_asprintf;
  if ( !strcmp("my_snprintf", symbol) ) return &my_snprintf;

  // tcc
  //if ( !strcmp("__dcgettext", symbol) ) return &__dcgettext;
  //if ( !strcmp("__memcpy_chk", symbol) ) return &MY__memcpy_chk;
  //if ( !strcmp("__memmove_chk", symbol) ) return &MY__memmove_chk;
  //if ( !strcmp("__strcpy_chk", symbol) ) return &MY__strcpy_chk;
  if ( !strcmp("my___environ", symbol) ) return &my___environ;
  if ( !strcmp("my___fprintf_chk", symbol) ) return &my___fprintf_chk;
  if ( !strcmp("my___longjmp_chk", symbol) ) return &my___longjmp_chk;
  if ( !strcmp("my___printf_chk", symbol) ) return &my___printf_chk;
  if ( !strcmp("my___snprintf_chk", symbol) ) return &my___snprintf_chk;
  if ( !strcmp("my___sprintf_chk", symbol) ) return &my___sprintf_chk;
  if ( !strcmp("my___stack_chk_fail", symbol) ) return &my___stack_chk_fail;
  if ( !strcmp("my___vfprintf_chk", symbol) ) return &my___vfprintf_chk;
  if ( !strcmp("my___vsnprintf_chk", symbol) ) return &my___vsnprintf_chk;
  if ( !strcmp("my__setjmp", symbol) ) return &my__setjmp;
  if ( !strcmp("my_fopen", symbol) ) return &my_fopen;
  if ( !strcmp("my_mprotect", symbol) ) return &my_mprotect;
  if ( !strcmp("my_open", symbol) ) return &my_open;
  if ( !strcmp("my_qsort", symbol) ) return &my_qsort;
  if ( !strcmp("my_read", symbol) ) return &my_read;
  if ( !strcmp("my_sigaction", symbol) ) return &my_sigaction;
  if ( !strcmp("my_dlopen", symbol) ) return &my_dlopen;
  if ( !strcmp("my_dlclose", symbol) ) return &my_dlclose;
  if ( !strcmp("my_dlsym", symbol) ) return &my_dlsym;
  if ( !strcmp("my___register_atfork", symbol) ) return &my___register_atfork;
  if ( !strcmp("my___libc_dlopen_mode", symbol) ) return &my___libc_dlopen_mode;
  if ( !strcmp("my_fcntl", symbol) ) return &my_fcntl;
  if ( !strcmp("my___libc_dlsym", symbol) ) return &my___libc_dlsym;

  if ( !strcmp("my___lxstat64", symbol) ) return &my___lxstat64;
  if ( !strcmp("my_execve", symbol) ) return &my_execve;
  if ( !strcmp("my_fcntl64", symbol) ) return &my_fcntl64;
  if ( !strcmp("my_mmap64", symbol) ) return &my_mmap64;
  if ( !strcmp("my_pthread_attr_destroy", symbol) ) return &my_pthread_attr_destroy;
  if ( !strcmp("my_pthread_cond_timedwait", symbol) ) return &my_pthread_cond_timedwait;
  if ( !strcmp("my_pthread_cond_wait", symbol) ) return &my_pthread_cond_wait;
  if ( !strcmp("my_pthread_key_create", symbol) ) return &my_pthread_key_create;
  if ( !strcmp("my_pthread_kill", symbol) ) return &my_pthread_kill;
  
  if ( !strcmp("_ITM_addUserCommitAction", symbol) ) return &do_nothing;

  //if ( !strcmp("__gmon_start__", symbol) ) return &do_nothing;
  //if ( !strcmp("__libc_start_main", symbol) ) return &do_nothing;
  //if ( !strcmp("_ITM_addUserCommitAction", symbol) ) return &do_nothing;
  //if ( !strcmp("mprotect", symbol) ) return &do_nothing;

  //if ( !strcmp("_ITM_deregisterTMCloneTable", symbol) ) return &do_nothing;
  //if ( !strcmp("__cxa_finalize", symbol) ) return &do_nothing;
  //if ( !strcmp("__gmon_start__", symbol) ) return &do_nothing;
  //if ( !strcmp("_ITM_registerTMCloneTable", symbol) ) return &do_nothing;

  if ( !strcmp("dlopen", symbol) ) return &dlopen;
  if ( !strcmp("puts", symbol) ) return &puts;
  if ( !strcmp("printf", symbol) ) return &printf;
  if ( !strcmp("fprintf", symbol) ) return &fprintf;
  if ( !strcmp("vfprintf", symbol) ) return &vfprintf;
  if ( !strcmp("fputs", symbol) ) return &fputs;
  if ( !strcmp("fputc", symbol) ) return &fputc;
  if ( !strcmp("fopen", symbol) ) return &fopen;
  if ( !strcmp("fclose", symbol) ) return &fclose;
  if ( !strcmp("fread", symbol) ) return &fread;
  if ( !strcmp("fwrite", symbol) ) return &fwrite;
  if ( !strcmp("fseek", symbol) ) return &fseek;
  if ( !strcmp("ftell", symbol) ) return &ftell;
  if ( !strcmp("fflush", symbol) ) return &fflush;
  if ( !strcmp("fdopen", symbol) ) return &fdopen;
  if ( !strcmp("remove", symbol) ) return &remove;
  if ( !strcmp("unlink", symbol) ) return &unlink;
  if ( !strcmp("execvp", symbol) ) return &execvp;
  if ( !strcmp("sprintf", symbol) ) return &sprintf;
  if ( !strcmp("snprintf", symbol) ) return &snprintf;
  if ( !strcmp("vsnprintf", symbol) ) return &vsnprintf;
  if ( !strcmp("strlen", symbol) ) return &strlen;
  if ( !strcmp("strcpy", symbol) ) return &strcpy;
  if ( !strcmp("strcmp", symbol) ) return &strcmp;
  if ( !strcmp("strncmp", symbol) ) return &strncmp;
  if ( !strcmp("strchr", symbol) ) return &strchr;
  if ( !strcmp("strrchr", symbol) ) return &strrchr;
  if ( !strcmp("strstr", symbol) ) return &strstr;
  if ( !strcmp("strcat", symbol) ) return &strcat;
  if ( !strcmp("strtol", symbol) ) return &strtol;
  if ( !strcmp("strtoll", symbol) ) return &strtoll;
  if ( !strcmp("strtoul", symbol) ) return &strtoul;
  if ( !strcmp("strtoull", symbol) ) return &strtoull;
  if ( !strcmp("strtof", symbol) ) return &strtof;
  if ( !strcmp("strtod", symbol) ) return &strtod;
  if ( !strcmp("strtold", symbol) ) return &strtold;
  if ( !strcmp("atoi", symbol) ) return &atoi;
  if ( !strcmp("qsort", symbol) ) return &qsort;
  if ( !strcmp("ldexp", symbol) ) return &ldexp;
  if ( !strcmp("__errno_location", symbol) ) return &__errno_location;
  if ( !strcmp("mprotect", symbol) ) return &mprotect;
  if ( !strcmp("getenv", symbol) ) return &getenv;
  if ( !strcmp("getcwd", symbol) ) return &getcwd;
  if ( !strcmp("gettimeofday", symbol) ) return &gettimeofday;
  if ( !strcmp("time", symbol) ) return &time;
  if ( !strcmp("localtime", symbol) ) return &localtime;
  if ( !strcmp("exit", symbol) ) return &exit;
  if ( !strcmp("close", symbol) ) return &close;
  if ( !strcmp("open", symbol) ) return &open;
  if ( !strcmp("read", symbol) ) return &read;
  if ( !strcmp("lseek", symbol) ) return &lseek;
  if ( !strcmp("dlopen", symbol) ) return &dlopen;
  if ( !strcmp("dlclose", symbol) ) return &dlclose;
  if ( !strcmp("dlsym", symbol) ) return &dlsym;
  if ( !strcmp("rand", symbol) ) return &rand;
  if ( !strcmp("sqrtf", symbol) ) return &sqrtf;
  if ( !strcmp("pow", symbol) ) return &pow;
  if ( !strcmp("cos", symbol) ) return &cos;
  if ( !strcmp("sin", symbol) ) return &sin;
  if ( !strcmp("fmin", symbol) ) return &fmin;
  if ( !strcmp("log2", symbol) ) return &log2;
  if ( !strcmp("malloc", symbol) ) return &malloc;
  if ( !strcmp("realloc", symbol) ) return &realloc;
  if ( !strcmp("free", symbol) ) return &free;
  if ( !strcmp("memmove", symbol) ) return &memmove;
  if ( !strcmp("memcpy", symbol) ) return &memcpy;
  if ( !strcmp("memset", symbol) ) return &memset;
  if ( !strcmp("memcmp", symbol) ) return &memcmp;
  if ( !strcmp("getuid", symbol) ) return &getuid;
  if ( !strcmp("fsync", symbol) ) return &fsync;
  if ( !strcmp("sigfillset", symbol) ) return &sigfillset;
  if ( !strcmp("fdatasync", symbol) ) return &fdatasync;
  if ( !strcmp("calloc", symbol) ) return &calloc;
  //if ( !strcmp("__mempcpy", symbol) ) return &__mempcpy;
  if ( !strcmp("__assert_fail", symbol) ) return &__assert_fail;

  if ( !strcmp("SDL_Init", symbol) ) return &SDL_Init;
  if ( !strcmp("SDL_GetError", symbol) ) return &SDL_GetError;
  if ( !strcmp("SDL_CreateWindow", symbol) ) return &SDL_CreateWindow;
  if ( !strcmp("SDL_GL_CreateContext", symbol) ) return &SDL_GL_CreateContext;
  if ( !strcmp("SDL_PollEvent", symbol) ) return &SDL_PollEvent;
  if ( !strcmp("SDL_GL_SwapWindow", symbol) ) return &SDL_GL_SwapWindow;
  if ( !strcmp("SDL_GetPerformanceCounter", symbol) ) return &SDL_GetPerformanceCounter;
  if ( !strcmp("SDL_GetPerformanceFrequency", symbol) ) return &SDL_GetPerformanceFrequency;
  if ( !strcmp("SDL_SetWindowTitle", symbol) ) return &SDL_SetWindowTitle;
  if ( !strcmp("SDL_Quit", symbol) ) return &SDL_Quit;
  if ( !strcmp("SDL_AllocRW", symbol) ) return &SDL_AllocRW;
  if ( !strcmp("SDL_FreeRW", symbol) ) return &SDL_FreeRW;
  if ( !strcmp("SDL_RWclose", symbol) ) return &SDL_RWclose;
  if ( !strcmp("SDL_LogMessageV", symbol) ) return &SDL_LogMessageV;
  if ( !strcmp("SDL_UnloadObject", symbol) ) return &SDL_UnloadObject;

  if ( !strcmp("glClearColor", symbol) ) return &glClearColor;
  if ( !strcmp("glClear", symbol) ) return &glClear;
  if ( !strcmp("glCreateProgram", symbol) ) return &glCreateProgram;
  if ( !strcmp("glCreateShader", symbol) ) return &glCreateShader;
  if ( !strcmp("glShaderSource", symbol) ) return &glShaderSource;
  if ( !strcmp("glCompileShader", symbol) ) return &glCompileShader;
  if ( !strcmp("glGetShaderiv", symbol) ) return &glGetShaderiv;
  if ( !strcmp("glGetShaderInfoLog", symbol) ) return &glGetShaderInfoLog;
  if ( !strcmp("glAttachShader", symbol) ) return &glAttachShader;
  if ( !strcmp("glLinkProgram", symbol) ) return &glLinkProgram;
  if ( !strcmp("glGetProgramiv", symbol) ) return &glGetProgramiv;
  if ( !strcmp("glDeleteShader", symbol) ) return &glDeleteShader;
  if ( !strcmp("glGetProgramInfoLog", symbol) ) return &glGetProgramInfoLog;
  if ( !strcmp("glGetAttribLocation", symbol) ) return &glGetAttribLocation;
  if ( !strcmp("glGetUniformLocation", symbol) ) return &glGetUniformLocation;
  if ( !strcmp("glGenVertexArrays", symbol) ) return &glGenVertexArrays;
  if ( !strcmp("glBindVertexArray", symbol) ) return &glBindVertexArray;
  if ( !strcmp("glGenBuffers", symbol) ) return &glGenBuffers;
  if ( !strcmp("glBindBuffer", symbol) ) return &glBindBuffer;
  if ( !strcmp("glBufferData", symbol) ) return &glBufferData;
  if ( !strcmp("glVertexAttribPointer", symbol) ) return &glVertexAttribPointer;
  if ( !strcmp("glEnableVertexAttribArray", symbol) ) return &glEnableVertexAttribArray;
  if ( !strcmp("glUniform1i", symbol) ) return &glUniform1i;
  if ( !strcmp("glUseProgram", symbol) ) return &glUseProgram;
  if ( !strcmp("glUniform4fv", symbol) ) return &glUniform4fv;
  if ( !strcmp("glUniformMatrix4fv", symbol) ) return &glUniformMatrix4fv;
  if ( !strcmp("glLineWidth", symbol) ) return &glLineWidth;
  if ( !strcmp("glDrawArrays", symbol) ) return &glDrawArrays;
  if ( !strcmp("glEnable", symbol) ) return &glEnable;
  if ( !strcmp("glBlendFunc", symbol) ) return &glBlendFunc;
  if ( !strcmp("glViewport", symbol) ) return &glViewport;
  if ( !strcmp("glGenTextures", symbol) ) return &glGenTextures;
  if ( !strcmp("glActiveTexture", symbol) ) return &glActiveTexture;
  if ( !strcmp("glBindTexture", symbol) ) return &glBindTexture;
  if ( !strcmp("glTexParameteri", symbol) ) return &glTexParameteri;
  if ( !strcmp("glTexImage2D", symbol) ) return &glTexImage2D;
  if ( !strcmp("glGetError", symbol) ) return &glGetError;
  if ( !strcmp("glValidateProgram", symbol) ) return &glValidateProgram;
  if ( !strcmp("glPixelStorei", symbol) ) return &glPixelStorei;
  //if ( !strcmp("glXGetProcAddress", symbol) ) return &glXGetProcAddress;

  if ( !strcmp("mktime", symbol) ) return &mktime;
  if ( !strcmp("strftime", symbol) ) return &strftime;
  if ( !strcmp("gmtime", symbol) ) return &gmtime;
  if ( !strcmp("putchar", symbol) ) return &putchar;
  if ( !strcmp("gmtime", symbol) ) return &gmtime;
  if ( !strcmp("strftime", symbol) ) return &strftime;
  if ( !strcmp("mktime", symbol) ) return &mktime;
  if ( !strcmp("putchar", symbol) ) return &putchar;
  if ( !strcmp("_IO_file_stat", symbol) ) return &do_nothing;

  // gcc
  if ( !strcmp("stderr", symbol) ) return &stderr;
  if ( !strcmp("stdout", symbol) ) return &stdout;
  if ( !strcmp("stdin", symbol) ) return &stdin;
  if ( !strcmp("strerror", symbol) ) return &strerror;
  if ( !strcmp("vsscanf", symbol) ) return &vsscanf;
  //if ( !strcmp("__dcgettext", symbol) ) return &__dcgettext;
  //if ( !strcmp("__memmove_chk", symbol) ) return &__memmove_chk;
  if ( !strcmp("sigemptyset", symbol) ) return &sigemptyset;
  //if ( !strcmp("freopen64", symbol) ) return &freopen64;
  if ( !strcmp("dup2", symbol) ) return &dup2;
  if ( !strcmp("strcspn", symbol) ) return &strcspn;
  if ( !strcmp("_exit", symbol) ) return &_exit;
  if ( !strcmp("abort", symbol) ) return &abort;
  if ( !strcmp("access", symbol) ) return &access;
  if ( !strcmp("asctime", symbol) ) return &asctime;
  if ( !strcmp("bindtextdomain", symbol) ) return &bindtextdomain;
  if ( !strcmp("closedir", symbol) ) return &closedir;
  if ( !strcmp("dgettext", symbol) ) return &dgettext;
  if ( !strcmp("feof", symbol) ) return &feof;
  if ( !strcmp("ferror", symbol) ) return &ferror;
  if ( !strcmp("fgetc", symbol) ) return &fgetc;
  if ( !strcmp("fgets", symbol) ) return &fgets;
  if ( !strcmp("fileno_unlocked", symbol) ) return &fileno_unlocked;
  //if ( !strcmp("fputs_unlocked", symbol) ) return &fputs_unlocked;
  if ( !strcmp("fread_unlocked", symbol) ) return &fread_unlocked;
  //if ( !strcmp("freopen64", symbol) ) return &freopen64;
  if ( !strcmp("fwrite_unlocked", symbol) ) return &fwrite_unlocked;
  if ( !strcmp("getpagesize", symbol) ) return &getpagesize;
  if ( !strcmp("getpid", symbol) ) return &getpid;
  //if ( !strcmp("getrlimit64", symbol) ) return &getrlimit64;
  if ( !strcmp("gettext", symbol) ) return &gettext;
  if ( !strcmp("iconv", symbol) ) return &iconv;
  if ( !strcmp("iconv_close", symbol) ) return &iconv_close;
  if ( !strcmp("iconv_open", symbol) ) return &iconv_open;
  if ( !strcmp("ioctl", symbol) ) return &ioctl;
  if ( !strcmp("isatty", symbol) ) return &isatty;
  if ( !strcmp("kill", symbol) ) return &kill;
  if ( !strcmp("mbstowcs", symbol) ) return &mbstowcs;
  if ( !strcmp("memchr", symbol) ) return &memchr;
  if ( !strcmp("ngettext", symbol) ) return &ngettext;
  if ( !strcmp("nl_langinfo", symbol) ) return &nl_langinfo;
  if ( !strcmp("opendir", symbol) ) return &opendir;
  if ( !strcmp("pipe", symbol) ) return &pipe;
  if ( !strcmp("putc", symbol) ) return &putc;
  if ( !strcmp("putenv", symbol) ) return &putenv;
  //if ( !strcmp("readdir64", symbol) ) return &readdir64;
  if ( !strcmp("sbrk", symbol) ) return &sbrk;
  if ( !strcmp("setenv", symbol) ) return &setenv;
  if ( !strcmp("setlocale", symbol) ) return &setlocale;
  //if ( !strcmp("setrlimit64", symbol) ) return &setrlimit64;
  if ( !strcmp("sleep", symbol) ) return &sleep;
  if ( !strcmp("stpcpy", symbol) ) return &stpcpy;
  if ( !strcmp("strcasecmp", symbol) ) return &strcasecmp;
  if ( !strcmp("strdup", symbol) ) return &strdup;
  if ( !strcmp("strncasecmp", symbol) ) return &strncasecmp;
  if ( !strcmp("strncpy", symbol) ) return &strncpy;
  if ( !strcmp("strnlen", symbol) ) return &strnlen;
  if ( !strcmp("strsignal", symbol) ) return &strsignal;
  if ( !strcmp("strtok", symbol) ) return &strtok;
  //if ( !strcmp("strverscmp", symbol) ) return &strverscmp;
  if ( !strcmp("system", symbol) ) return &system;
  if ( !strcmp("textdomain", symbol) ) return &textdomain;
  if ( !strcmp("ungetc", symbol) ) return &ungetc;
  if ( !strcmp("unsetenv", symbol) ) return &unsetenv;
  if ( !strcmp("wait4", symbol) ) return &wait4;
  if ( !strcmp("waitpid", symbol) ) return &waitpid;
  if ( !strcmp("wcswidth", symbol) ) return &wcswidth;
  if ( !strcmp("write", symbol) ) return &write;

  if ( !strcmp("basename", symbol) ) return &basename;
  if ( !strcmp("chmod", symbol) ) return &chmod;
  if ( !strcmp("fileno", symbol) ) return &fileno;
  if ( !strcmp("fnmatch", symbol) ) return &fnmatch;
  if ( !strcmp("fseeko", symbol) ) return &fseeko;
  if ( !strcmp("link", symbol) ) return &link;
  if ( !strcmp("mkdir", symbol) ) return &mkdir;
  if ( !strcmp("mkdtemp", symbol) ) return &mkdtemp;
  if ( !strcmp("my___xstat64", symbol) ) return &my___xstat64;
  if ( !strcmp("my_dlerror", symbol) ) return &my_dlerror;
  if ( !strcmp("my_execv", symbol) ) return &my_execv;
  if ( !strcmp("my_fopen64", symbol) ) return &my_fopen64;
  if ( !strcmp("my_fork", symbol) ) return &my_fork;
  if ( !strcmp("my_fprintf", symbol) ) return &my_fprintf;
  if ( !strcmp("my_mmap", symbol) ) return &my_mmap;
  if ( !strcmp("my_munmap", symbol) ) return &my_munmap;
  if ( !strcmp("my_nftw64", symbol) ) return &my_nftw64;
  if ( !strcmp("my_open64", symbol) ) return &my_open64;
  if ( !strcmp("my_pthread_create", symbol) ) return &my_pthread_create;
  if ( !strcmp("my_readlink", symbol) ) return &my_readlink;
  if ( !strcmp("my_realpath", symbol) ) return &my_realpath;
  if ( !strcmp("my_sprintf", symbol) ) return &my_sprintf;
  if ( !strcmp("pause", symbol) ) return &pause;
  if ( !strcmp("perror", symbol) ) return &perror;
  //if ( !strcmp("gnu_dev_makedev", symbol) ) return &gnu_dev_makedev;
  if ( !strcmp("lseek64", symbol) ) return &lseek64;
  if ( !strcmp("pread64", symbol) ) return &pread64;
  if ( !strcmp("rmdir", symbol) ) return &rmdir;
  if ( !strcmp("symlink", symbol) ) return &symlink;


  if ( !strcmp("__isoc99_vsscanf", symbol) ) return &__isoc99_vsscanf;
  //if ( !strcmp("__memcpy_chk", symbol) ) return &MY__memcpy_chk;
  //if ( !strcmp("__realpath_chk", symbol) ) return &__realpath_chk;
  if ( !strcmp("chdir", symbol) ) return &chdir;
  if ( !strcmp("clock_gettime", symbol) ) return &clock_gettime;
  if ( !strcmp("geteuid", symbol) ) return &geteuid;
  if ( !strcmp("getgid", symbol) ) return &getgid;
  //if ( !strcmp("mount", symbol) ) return &mount;
  if ( !strcmp("poll", symbol) ) return &poll;
  if ( !strcmp("posix_memalign", symbol) ) return &posix_memalign;
  if ( !strcmp("pthread_attr_init", symbol) ) return &pthread_attr_init;
  if ( !strcmp("pthread_attr_setstacksize", symbol) ) return &pthread_attr_setstacksize;
  if ( !strcmp("pthread_cancel", symbol) ) return &pthread_cancel;
  if ( !strcmp("pthread_cond_broadcast", symbol) ) return &pthread_cond_broadcast;
  if ( !strcmp("pthread_cond_destroy", symbol) ) return &pthread_cond_destroy;
  if ( !strcmp("pthread_cond_init", symbol) ) return &pthread_cond_init;
  if ( !strcmp("pthread_cond_signal", symbol) ) return &pthread_cond_signal;
  if ( !strcmp("pthread_detach", symbol) ) return &pthread_detach;
  if ( !strcmp("pthread_getspecific", symbol) ) return &pthread_getspecific;
  if ( !strcmp("pthread_join", symbol) ) return &pthread_join;
  if ( !strcmp("pthread_key_delete", symbol) ) return &pthread_key_delete;
  if ( !strcmp("pthread_mutex_destroy", symbol) ) return &pthread_mutex_destroy;
  if ( !strcmp("pthread_mutex_init", symbol) ) return &pthread_mutex_init;
  if ( !strcmp("pthread_mutex_lock", symbol) ) return &pthread_mutex_lock;
  if ( !strcmp("pthread_mutex_unlock", symbol) ) return &pthread_mutex_unlock;
  if ( !strcmp("pthread_self", symbol) ) return &pthread_self;
  if ( !strcmp("pthread_setcancelstate", symbol) ) return &pthread_setcancelstate;
  if ( !strcmp("pthread_setspecific", symbol) ) return &pthread_setspecific;
  if ( !strcmp("pthread_sigmask", symbol) ) return &pthread_sigmask;
  if ( !strcmp("pwrite64", symbol) ) return &pwrite64;
  if ( !strcmp("readdir64", symbol) ) return &readdir64;
  if ( !strcmp("recvmsg", symbol) ) return &recvmsg;
  if ( !strcmp("sem_destroy", symbol) ) return &sem_destroy;
  if ( !strcmp("sem_init", symbol) ) return &sem_init;
  if ( !strcmp("sem_post", symbol) ) return &sem_post;
  if ( !strcmp("sem_wait", symbol) ) return &sem_wait;
  if ( !strcmp("setreuid", symbol) ) return &setreuid;
  if ( !strcmp("setsid", symbol) ) return &setsid;
  if ( !strcmp("setuid", symbol) ) return &setuid;
  if ( !strcmp("sigaddset", symbol) ) return &sigaddset;
  if ( !strcmp("sigprocmask", symbol) ) return &sigprocmask;
  if ( !strcmp("socketpair", symbol) ) return &socketpair;
  //if ( !strcmp("splice", symbol) ) return &splice;
  //if ( !strcmp("umount2", symbol) ) return &umount2;
  if ( !strcmp("writev", symbol) ) return &writev;

  //#include "wrapped/wrappedlib_undefs.h"
  //#undef QUOTE
  //#define QUOTE(M) #M
  //#define GO(N, W) W N();
  //#define GOW(N, W) GO(N, W)
  //#define GOM(N, W) GO(N, W)
  //#define GOS(N, W) GO(N, W)
  //#define GO2(N, W, O) GO(N, W)
  //#define DATA(N, S) GO(N, W)
  //#define DATAV(N, S) GO(N, W)
  //#define DATAB(N, S) GO(N, W)
  //#define DATAM(N, S) GO(N, W)
  //#undef GO
  //#define GO(N, W) if ( !strcmp( #N , symbol) ) return &N;
  //#include "wrapped/wrappedlibc_private.h"
  //#include "wrapped/wrappedlibm_private.h"
  //#include "wrapped/wrappedlibgl_private.h"
  //#include "wrapped/wrappedsdl2_private.h"
  //#undef GO

  printf("not implemented: %s\n", symbol);
  return &do_nothing;
  //return (void*) 0;
}
