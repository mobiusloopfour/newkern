set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(ARCH "x86_64")

set(FLAGS_COMMON "-target x86_64-elf-none-pc -g -fsanitize=undefined -m64 -march=native -fno-PIC -ffreestanding -mno-red-zone -nostdinc -mcmodel=kernel -mno-sse3 -mno-ssse3 -mno-sse4.1 -mno-sse4.2 -mno-sse4 -mno-sse4a -mno-3dnow -mno-avx -mno-avx2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAGS_COMMON}")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
# set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -fuse-ld=lld")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-nostdlib -target ${ARCH}-linux-elf ")
set(CMAKE_EXE_LINKER_FLAGS "-m64 -nostdlib -mcmodel=kernel -fno-PIC -no-pie -Wl,-z,max-page-size=0x1000,-n,-T,${CMAKE_CURRENT_SOURCE_DIR}/cf/${ARCH}-k.ld")


set(CMAKE_ASM_COMPILER "${ARCH}-elf-gcc")
set(CMAKE_C_COMPILER "clang")

set(CMAKE_ASM_FLAGS "-D ASM ${CMAKE_ASM_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS "-ffreestanding ${CMAKE_C_FLAGS}" CACHE STRING "" FORCE)
#-target ${ARCH}-linux-elf 