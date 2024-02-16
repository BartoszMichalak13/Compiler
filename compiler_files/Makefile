# Shell
RM := rm -rf

# DIRS
# IDIR  := ./inc
# SDIR  := ./src
# VMDIR := ./vm
# TDIR  := ./test
# IDIR  := .
# SDIR  := .
# VMDIR := .
# TDIR  := .


# COMPI, DEFAULT G++
CXX ?= g++
LEX := flex
YAC := bison

CXX_STD   = -std=c++17
CXX_OPT   = -O3
CXX_FLAGS =
CXX_WARNS =

ifeq ($(CXX),clang++)
	CXX_WARNS += -Weverything
else ifneq (, $(filter $(CC), cc gcc))
	CXX_WARNS += -Wall -Wextra
endif

ifeq ("$(origin DEBUG)", "command line")
	GGDB := -ggdb3
else
	GGDB :=
endif

CXX_FLAGS += $(CXX_STD) $(CXX_OPT) $(GGDB) $(CXX_WARNS)

EXEC = kompilator
SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=%.o)
LIBS = fl

H_INC := $(foreach d, , -I$d)
L_INC := $(foreach l, $(LIB), -l$l)

all: compiler 

.PHONY:compiler
compiler: $(EXEC)

parser_tab.c parser_tab.h: parser.ypp
	$(YAC) --debug -Wall --defines=parser_tab.h parser.ypp -o parser_tab.c

parser_lex.yy.c: parser.l parser_tab.h
	$(LEX) -o $@ parser.l

%.o:%.cpp _FORCE
	$(CXX) $(CXX_FLAGS) $(H_INC) -c $< -o $@

_FORCE:


$(EXEC): parser_lex.yy.c parser_tab.c parser_tab.h $(OBJ)
	$(CXX) $(CXX_FLAGS) $(H_INC) parser_tab.c parser_lex.yy.c $(OBJ) $(L_INC) -o $@

# .PHONY:vm
# vm:
# 	@cd && $(MAKE) --no-print-directory

# .PHONY:test
# test: compiler vm
# 	@cd  && ./tests.sh

# .PHONY:clean
# clean:
# 	$(RM) parser_tab.h
# 	$(RM) parser_tab.c
# 	$(RM) parser_lex.yy.c
# 	$(RM) $(OBJ)
# 	$(RM) $(EXEC)
# 	@cd $(VMDIR) && $(MAKE) cleanall --no-print-directory
