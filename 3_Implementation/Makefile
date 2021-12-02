PROJ_NAME = Vehicle

BUILD_DIR = Build

SRC = project_main.cc

INC = -I inc

ifdef OS	# WINDOWS
# Correct the path based on OS
   FixPath = $(subst /,\,$1)
# Name of the compiler used
   CC = avr-gcc.exe
# Name of the elf to hex file converter used
   AVR_OBJ_CPY = avr-objcopy.exe
else #Linux
   ifeq ($(shell uname), Linux)
# Correct the path based on OS
      FixPath = $1				
# Name of the compiler used
	  CC = avr-gcc
# Name of the elf to hex file converter used
	  AVR_OBJ_CPY = avr-objcopy 
   endif
endif

all:$(BUILD_DIR)
# Compile the code and generate the ELF file
	$(CC) -c -std=gnu99 -g -Wall -Os -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000 $(INC) $(SRC) -o $(call FixPath,$(BUILD_DIR)/$(PROJ_NAME).elf)

$(BUILD_DIR):
# Create directory to store the built files
	mkdir $(BUILD_DIR)
