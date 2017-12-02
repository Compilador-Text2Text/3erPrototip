FILE_UTILS = 9-Útils

UTILS_O_	=				\
	$(UTILS_BASIC_O_)			\

UTILS_BASIC_C_ = $(FILE_UTILS)/bàsic.c
UTILS_BASIC_H_ = $(FILE_UTILS)/bàsic.h
UTILS_BASIC_O_ = $(OBJDIR)/util_bàsic.o
UTILS_BASIC_D_ = $(UTILS_BASIC_C_)		\
	$(UTILS_BASIC_H_)			\
