set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(ARCH "x86_64")

# set(FLAGS_COMMON "-ffreestanding -fno-stack-protector -fno-pic -mabi=sysv -mno-80387 -mno-mmx -mno-3dnow -mno-sse -mno-sse2 -mno-red-zone -mcmodel=kernel")
set(CMAKE_C_FLAGS "-g -fsanitize=undefined -ffreestanding -fno-stack-protector -fno-pic -mabi=sysv -mno-80387 -mno-mmx -mno-3dnow -mno-sse -mno-sse2 -mno-red-zone -mcmodel=kernel")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -m64")
set(CMAKE_EXE_LINKER_FLAGS "-ffreestanding -nostdlib -Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/cf/${ARCH}-k.ld")


set(CMAKE_ASM_COMPILER "${ARCH}-elf-gcc")
set(CMAKE_C_COMPILER "${ARCH}-elf-gcc")

set(CMAKE_ASM_FLAGS "-ffreestanding ${CMAKE_ASM_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS "-ffreestanding ${CMAKE_C_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_INIT "-nostartfiles -nostdlib -melf_x86_64 -zmax-page-size=0x1000 -static") #-target ${ARCH}-linux-elf 

#if(APPLE)
#	set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -fuse-ld=lld")
#endif()