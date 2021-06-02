cmake_minimum_required(VERSION 3.0)

option(USE_CCACHE "Set to ON to use ccache if present in the system" ${USE_CCACHE})
option(HAVE_TRACE "Set to ON to have Trace ability (needs ZydisInfo library)" ${HAVE_TRACE})
option(NOLOADADDR "Set to ON to avoid fixing the load address of Box86" ${NO_LOADAADR})
option(NOGETCLOCK "Set to ON to avoid using clock_gettime with CLOCK_MONOTONIC_COARSE for RDTSC opcode (use gltimeofday instead)" ${NOGETCLOCK})
option(NOGIT "Set to ON if not building from a git clone repo (like when building from a zip download from github)" ${NOGIT})
option(LD80BITS "Set to ON if host device have 80bits long double (i.e. i386)" ${LD80BITS})
option(NOALIGN "Set to ON if host device doesn't need re-align (i.e. i386)" ${NOALIGN})
option(SYSV_VARARG "Set to ON if host device uses SysVR4 vararg calling convention" ${SYSV_VARARG})

if(${CMAKE_VERSION} VERSION_LESS "3.12.2")
    find_package(PythonInterp 3)
    if(NOT PYTHONINTERP_FOUND)
        message( FATAL_ERROR "You need a Python interpretor, CMake will exit." )
    endif()
    if(${PYTHON_VERSION_MAJOR} LESS 3)
        message( FATAL_ERROR "You need a Python 3 interpretor, CMake will exit." )
    endif()
else()
    find_package(Python3)
    if(NOT Python3_Interpreter_FOUND)
        message( FATAL_ERROR "You need a Python interpretor, CMake will exit." )
    endif()
    set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE} CACHE INTERNAL "The Python3 executable" FORCE)
endif()

project(box86 C ASM)

enable_testing()

set(default_build_type "RelWithDebInfo")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

#if(TOJS)
#  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/wasm")
#else()
#  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/native")
#endif()

if(NOGIT)
    add_definitions(-DNOGIT)
endif()

if(BOX86LIB)
    set(BOX86 box86)
elseif(HAVE_TRACE)
    set(BOX86 box86t)
else()
    set(BOX86 box86)
endif()


set(BOX86_ELF_ADDRESS "0x62800000")

if(LD80BITS)
    add_definitions(-DHAVE_LD80BITS)
endif()

if(NOALIGN)
    add_definitions(-DNOALIGN)
endif()

if(HAVE_TRACE)
    add_definitions(-DHAVE_TRACE)
endif()

if(SYSV_VARARG)
  add_definitions(-DSYSV_VARARG)
endif()

if(NOGETCLOCK)
    add_definitions(-DNOGETCLOCK)
endif()

if(BOX86LIB)
    add_definitions(-DBUILD_LIB)
    if(BOX86DYNAMIC)
        add_definitions(-DBUILD_DYNAMIC)
    endif()
    add_definitions(-fPIC)
    if(NOT BOX86_ROOT)
        message(FATAL_ERROR "BOX86_ROOT not set when build as lib")
    endif()
else()
    set(BOX86_ROOT ${CMAKE_SOURCE_DIR})
endif()


add_definitions(-std=gnu11 -funwind-tables -fvisibility=hidden)

if(USE_CCACHE)
    find_program(CCACHE_FOUND ccache)
    if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    endif()
endif()

include_directories(
    "${BOX86_ROOT}/src/include"
    "${BOX86_ROOT}/src"
    "${BOX86_ROOT}/src/wrapped/generated"
)

# git_head.h is a generated file
set_source_files_properties(
    "${BOX86_ROOT}/src/git_head.h"
    PROPERTIES GENERATED TRUE
    HEADER_FILE_ONLY TRUE)

set(ELFLOADER_SRC
    "${BOX86_ROOT}/src/main.c"
    "${BOX86_ROOT}/src/box86context.c"
    "${BOX86_ROOT}/src/build_info.c"
    #"${BOX86_ROOT}/src/custommem.c"
    "${BOX86_ROOT}/src/tools/bridge.c"
    "${BOX86_ROOT}/src/tools/pathcoll.c"
    "${BOX86_ROOT}/src/tools/fileutils.c"
    #"${BOX86_ROOT}/src/tools/callback.c"
    "${BOX86_ROOT}/src/tools/box86stack.c"
    #"${BOX86_ROOT}/src/tools/my_cpuid.c"
    #"${BOX86_ROOT}/src/tools/wine_tools.c"
    "${BOX86_ROOT}/src/elfs/elfloader.c"
    "${BOX86_ROOT}/src/elfs/elfparser.c"
    "${BOX86_ROOT}/src/elfs/elfload_dump.c"
    "${BOX86_ROOT}/src/librarian/library.c"
    "${BOX86_ROOT}/src/librarian/librarian.c"
    "${BOX86_ROOT}/src/librarian/dictionnary.c"
    "${BOX86_ROOT}/src/librarian/symbols.c"
    "${BOX86_ROOT}/src/emu/x86emu.c"
    "${BOX86_ROOT}/src/emu/x86run.c"
    "${BOX86_ROOT}/src/emu/x86run66.c"
    "${BOX86_ROOT}/src/emu/x86run660f.c"
    "${BOX86_ROOT}/src/emu/x86run_private.c"
    "${BOX86_ROOT}/src/emu/x86syscall.c"
    "${BOX86_ROOT}/src/emu/x86primop.c"
    "${BOX86_ROOT}/src/emu/x86trace.c"
    "${BOX86_ROOT}/src/emu/x86int3.c"
    "${BOX86_ROOT}/src/emu/x86tls.c"
    "${BOX86_ROOT}/src/emu/x87emu_private.c"
    "${BOX86_ROOT}/src/emu/x87run.c"
    #"${BOX86_ROOT}/src/libtools/auxval.c"
    #"${BOX86_ROOT}/src/libtools/myalign.c"
    #"${BOX86_ROOT}/src/libtools/myalign64.c"
    #"${BOX86_ROOT}/src/libtools/myfts.c"
    #"${BOX86_ROOT}/src/libtools/signals.c"
    #"${BOX86_ROOT}/src/libtools/threads.c"
    #"${BOX86_ROOT}/src/libtools/vkalign.c"
    #"${BOX86_ROOT}/src/dynarec/dynarec.c"
    "${BOX86_ROOT}/src/wrapped/generated/wrapper.c"
    #"${BOX86_ROOT}/src/libtools/sdl1rwops.c"
    "${BOX86_ROOT}/src/libtools/sdl2rwops.c"
    "${BOX86_ROOT}/src/browser/browser.c"
)
set(WRAPPEDS
    "${BOX86_ROOT}/src/wrapped/wrappedlibc.c"
    "${BOX86_ROOT}/src/wrapped/wrappedlibgl.c"
    "${BOX86_ROOT}/src/wrapped/wrappedlibm.c"
    "${BOX86_ROOT}/src/wrapped/wrappedsdl2.c"
    "${BOX86_ROOT}/src/wrapped/wrappedlibdl.c"
    "${BOX86_ROOT}/src/wrapped/wrappedlibrt.c"
    "${BOX86_ROOT}/src/wrapped/wrappedlibpthread.c"
    "${BOX86_ROOT}/src/wrapped/wrappedldlinux.c"
    )


# If BOX86_ROOT contains a ".c", the build breaks...
string(REPLACE ".c" "_private.h" MODROOT ${BOX86_ROOT})
set(WRAPPEDS_HEAD "")
foreach(A ${WRAPPEDS})
    string(REPLACE ".c" "_private.h" C ${A})
    string(REPLACE "${MODROOT}" "${BOX86_ROOT}" B ${C})
    set(WRAPPEDS_HEAD ${WRAPPEDS_HEAD} ${B})
    set_source_files_properties(${A} PROPERTIES OBJECT_DEPENDS ${B})
endforeach()

set(WRAPPER "${BOX86_ROOT}/src/wrapped/generated/wrapper.c" "${BOX86_ROOT}/src/wrapped/generated/wrapper.h")

add_custom_command(
    OUTPUT "${BOX86_ROOT}/src/wrapped/generated/functions_list.txt"
    COMMAND "${PYTHON_EXECUTABLE}" "${BOX86_ROOT}/rebuild_wrappers.py" 
    "${BOX86_ROOT}" 
    "PANDORA" "HAVE_LD80BITS" "NOALIGN" "HAVE_TRACE" "POWERPCLE" "ANDROID" "__EMSCRIPTEN__" "--"
    ${WRAPPEDS_HEAD}
    MAIN_DEPENDENCY "${BOX86_ROOT}/rebuild_wrappers.py"
    DEPENDS ${WRAPPEDS} ${WRAPPEDS_HEAD}
    BYPRODUCTS ${WRAPPER}
)

add_custom_target(WRAPPERS DEPENDS "${BOX86_ROOT}/src/wrapped/generated/functions_list.txt")

    add_custom_command(
        OUTPUT "${BOX86_ROOT}/src/git_head.h"
        COMMAND bash -c "echo \\\#define GITREV \\\"$(git rev-parse --short HEAD)\\\">\"${BOX86_ROOT}/src/git_head.h\""
        DEPENDS ${ELFLOADER_SRC} ${WRAPPEDS}
        VERBATIM)

add_executable(${BOX86} ${ELFLOADER_SRC} ${WRAPPEDS} "${BOX86_ROOT}/src/git_head.h")
#add_executable(${BOX86} ${ELFLOADER_SRC} "${BOX86_ROOT}/src/git_head.h")
add_dependencies(${BOX86} WRAPPERS)

target_link_libraries(${BOX86} m SDL2 GL)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -Wl,--unresolved-symbols=ignore-in-shared-libs")
#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -Wl,--unresolved-symbols=ignore-in-object-files")
#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -Wl,--unresolved-symbols=ignore-all")
#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -Wl,--gc-sections  -ffunction-sections -fdata-sections")

if(TOJS)
  #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-format -g  -gsource-map --source-map-base http://localhost:8000/")
  #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-format -s WASM=0 --use-preload-plugins")
  #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-format -s WASM=0 --memory-init-file 0")
  #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-format")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-format -isystem ${BOX86_ROOT}/src/browser/")
  #target_link_libraries(${BOX86} m rt pthread)
  #target_link_libraries(${BOX86} m rt pthread SDL2 GL)

  #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -include ${BOX86_ROOT}/src/browser/override.h -s USE_SDL=2 --preload-file dir@/ --pre-js pre.js -s ALLOW_MEMORY_GROWTH=1 -s ASYNCIFY")
  #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -include ${BOX86_ROOT}/src/browser/override.h -s USE_SDL=2 --pre-js ${BOX86_ROOT}/src/pre.js -s ALLOW_MEMORY_GROWTH=1 -s ASYNCIFY")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -include ${BOX86_ROOT}/src/browser/override.h -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -s ASYNCIFY -Oz")

  #configure_file("${BOX86_ROOT}/src/browser/box86.html" "box86.html" COPYONLY)
  ##configure_file("/home/raoof/playground/bin/temp" "dir/temp" COPYONLY)
  ##configure_file("/home/raoof/playground/bin/tetris" "dir/tetris" COPYONLY)
  ##configure_file("/home/raoof/playground/bin/tetris" "dir/tetris" COPYONLY)
  ##configure_file("/usr/lib/i386-linux-gnu/libGL.so.1" "dir/libGL.so.1" COPYONLY)
  ##configure_file("/usr/lib/i386-linux-gnu/libSDL2-2.0.so.0" "dir/libSDL2-2.0.so.0" COPYONLY)
  ##configure_file("/lib/i386-linux-gnu/libm.so.6" "dir/libm.so.6" COPYONLY)
  ##configure_file("/lib/i386-linux-gnu/libc.so.6" "dir/libc.so.6" COPYONLY)

  ##file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/pre.js" ${PREJSSTR})
  ##add_custom_target(PREJS DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/pre.js")
  ##add_custom_target(PREJS DEPENDS "${BOX86_ROOT}/src/pre.js")

  #add_custom_target(HTML DEPENDS "${BOX86_ROOT}/src/browser/box86.html")
  ##add_dependencies(${BOX86} PREJS HTML)
  #add_dependencies(${BOX86} HTML)

  ##set_target_properties(${BOX86} PROPERTIES LINK_FLAGS "--embed-file tetris -s ASSERTIONS=1 ")
  ##set_target_properties(${BOX86} PROPERTIES LINK_FLAGS "--embed-file tetris --pre-js pre.js -s ASSERTIONS=1 -s USE_SDL=2 -s MAIN_MODULE=1 -s EXPORT_ALL=1 -fPIC")
  ##set_target_properties(${BOX86} PROPERTIES LINK_FLAGS "--embed-file tetris --pre-js pre.js -s USE_SDL=2")

  ##execute_process(COMMAND objcopy --redefine-sym dlopen=MYdlopen --redefine-sym dlsym=MYdlsym --redefine-sym dlclose=MYdlclose /usr/lib/i386-linux-gnu/libdl.a ${CMAKE_CURRENT_BINARY_DIR}/mylibdl.a)
  ##execute_process(COMMAND objcopy --redefine-sym dlopen=__wrap_dlopen --redefine-sym dlsym=__wrap_dlsym --redefine-sym dlclose=__wrap_dlclose /usr/lib/i386-linux-gnu/libdl.a ${CMAKE_CURRENT_BINARY_DIR}/mylibdl.a)
  ##execute_process(COMMAND emcc --no-entry --relocatable ${CMAKE_CURRENT_BINARY_DIR}/mylibdl.a -o ${CMAKE_CURRENT_BINARY_DIR}/mylibdl.wasm -s RELOCATABLE=1)

  ##set_target_properties(${BOX86} PROPERTIES LINK_FLAGS "--embed-file tetris --embed-file libGL.so.1 --embed-file libSDL2-2.0.so.0 --embed-file libm.so.6 --embed-file libc.so.6 --pre-js pre.js -s USE_SDL=2 mylibdl.wasm --wrap=dlopen --wrap=dlclose --wrap=dlsym")
  ##set_target_properties(${BOX86} PROPERTIES LINK_FLAGS "--preload-file dir --pre-js pre.js -s USE_SDL=2 mylibdl.wasm --wrap=dlopen --wrap=dlclose --wrap=dlsym")
  ##set_target_properties(${BOX86} PROPERTIES LINK_FLAGS "--preload-file dir@/ --pre-js pre.js -s mylibdl.wasm --wrap=dlopen --wrap=dlclose --wrap=dlsym")
  ##set_target_properties(${BOX86} PROPERTIES LINK_FLAGS "--preload-file dir@/ --pre-js pre.js -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -s SAFE_HEAP=1 -s WARN_UNALIGNED=1 -Wcast-align -Wover-aligned")
  ##set_target_properties(${BOX86} PROPERTIES LINK_FLAGS "--preload-file dir@/ --pre-js pre.js -s USE_SDL=2 -s ASSERTIONS=2 -s WARN_UNALIGNED=1 -s TOTAL_MEMORY=67108864 -s STACK_OVERFLOW_CHECK=1 -fsanitize=undefined")

  add_custom_command(
      OUTPUT "box86.html"
      #COMMAND bash -c "\"sed -e '/_BOX86JS_/r box86.js' -e '/_BOX86JS_/d' ${BOX86_ROOT}/src/browser/box86.html > box86.html ; htmlSize=$(printf '%014d\\n' `cat box86.html | wc -c`) ; wasmSize=$(printf '%014d\\n' `cat box86.wasm | wc -c`) ; sed -i -e \\\"s/_14W_HTMLSIZE_/$htmlSize/g\\\"  -e \\\"s/_14W_WASMSIZE_/$wasmSize/g\\\" box86.html ; cat box86.wasm >> box86.html\""
      COMMAND bash "${BOX86_ROOT}/bundle_box86_html.sh" ${BOX86_ROOT}
      MAIN_DEPENDENCY "${BOX86_ROOT}/src/browser/box86.html"
  )

  add_custom_target(HTML DEPENDS "box86.html")
  add_dependencies(${BOX86} HTML)


  #set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(CMAKE_EXECUTABLE_SUFFIX ".js")
else()
  #target_link_libraries(${BOX86} m dl rt pthread)
  #target_link_libraries(${BOX86} m rt pthread SDL2 GL)
  #target_link_libraries(${BOX86} m SDL2 GL)
endif()
