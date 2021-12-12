set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
cmake_minimum_required(VERSION 3.21)
project(FreeKernel C ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(SOURCE_FILES
	"ke/kmain.c"
	"ke/panic.c"
	"ke/def_video.c"
	"ke/digmb.c"
	"ke/printf.c"
	"kd64/stty.c"
)

set(UBSAN_SRC
	"san/abort.c"
	"san/add_overflow.c"
	"san/bounds.c"
	"san/cfi.c"
	"san/divrem_overflow.c"
	"san/float_cast.c"
	"san/function_type.c"
	"san/invalid.c"
	"san/neg_overflow.c"
	"san/pointer_overflow.c"
	"san/non_null.c"
	"san/return.c"
	"san/shift_oob.c"
	"san/sub_overflow.c"
	"san/type_mismatch.c"
	"san/unreachable.c"
	"san/var_arg.c"
)

set(SOURCE_FILES
	"${SOURCE_FILES}"
	"hals/hal${ARCH}/boot.S"
	"hals/hal${ARCH}/conflow.c"
)

include_directories(
	"${CMAKE_SOURCE_DIR}/inc"
)

add_compile_definitions(KERNEL)
add_executable(FreeKernel.elf ${SOURCE_FILES})
set_property(TARGET FreeKernel.elf PROPERTY C_STANDARD 17)

add_library(ubsan ${UBSAN_SRC})

target_link_libraries(FreeKernel.elf PUBLIC ubsan)

add_custom_command(OUTPUT ${CMAKE_SOURCE_DIR}/disk.iso
  COMMAND rm -rf bin || true
	COMMAND mkdir -p ${CMAKE_SOURCE_DIR}/bin
	COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/FreeKernel.elf ${CMAKE_SOURCE_DIR}/cf/limine.cfg ${CMAKE_SOURCE_DIR}/limine/limine.sys ${CMAKE_SOURCE_DIR}/limine/limine-cd.bin ${CMAKE_SOURCE_DIR}/limine/limine-eltorito-efi.bin ${CMAKE_SOURCE_DIR}/bin/
	COMMAND xorriso -as mkisofs -b limine-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-eltorito-efi.bin -efi-boot-part --efi-boot-image --protective-msdos-label ${CMAKE_SOURCE_DIR}/bin -o ${CMAKE_SOURCE_DIR}/disk.iso
	COMMAND ${CMAKE_SOURCE_DIR}/limine/limine-install ${CMAKE_SOURCE_DIR}/disk.iso
	COMMAND rm -rf ${CMAKE_SOURCE_DIR}/bin
)

add_custom_target(iso DEPENDS "${CMAKE_SOURCE_DIR}/disk.iso" "FreeKernel.elf")