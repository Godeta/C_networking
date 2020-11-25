# ==========================================
#   Makefile for my networking in C project, it uses Unity for the test
#   Unity Project - A Test Framework for C
# ==========================================

#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

C_COMPILER=gcc
ifeq ($(shell uname -s), Darwin)
C_COMPILER=clang
endif
# where the unity files for testing are located
UNITY_ROOT=./lib

# to see precisely the errors and warnings
CFLAGS=-std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
#CFLAGS += -Wno-misleading-indentation

# output file
TARGET_BASE1=all_tests
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
TARGET2 = networkingC
# the files for the test
SRC_FILES1=\
  $(UNITY_ROOT)/unity.c \
  $(UNITY_ROOT)/unity_fixture.c \
  src/usefulFunctions.c \
  src/TCP.c \
  test/TestUsefulFunc.c \
  test/TestTCP.c \
  test/test_runners/TestUsefulFunc_Runner.c \
  test/test_runners/TestTCP_Runner.c \
  test/test_runners/all_tests.c
# the files for the program
SRC_FILES2=\
  $(UNITY_ROOT)/unity.c \
  $(UNITY_ROOT)/unity_fixture.c \
  src/usefulFunctions.c \
  src/TCP.c \
  src/main.c
INC_DIRS=-Isrc -I$(UNITY_ROOT)
SYMBOLS=-DUNITY_FIXTURE_NO_EXTRAS

# when we execute make all
all: clean default

# when we execute make, compile the tests -> execute them, compile the program
default:
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1)
	- ./$(TARGET1) -v
	- $(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES2) -o $(TARGET2)

# compile only the tests into all_tests.out
tests:
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1)

# erase the compiled elements
clean:
	$(CLEANUP) $(TARGET1) && $(CLEANUP) $(TARGET2)

ci: CFLAGS += -Werror
ci: default
