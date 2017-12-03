FILE_UTILS = 9-Útils

UTILS_O_	=				\
	$(UTILS_BASIC_O_)			\
	$(UTILS_PILA_O_)			\

UTILS_BASIC_C_ = $(FILE_UTILS)/bàsic.c
UTILS_BASIC_H_ = $(FILE_UTILS)/bàsic.h
UTILS_BASIC_O_ = $(OBJDIR)/util_bàsic.o
UTILS_BASIC_D_ = $(UTILS_BASIC_C_)		\
	$(UTILS_BASIC_H_)			\

UTILS_PILA_C_ = $(FILE_UTILS)/pila.c
UTILS_PILA_H_ = $(FILE_UTILS)/pila.h
UTILS_PILA_O_ = $(OBJDIR)/util_pila.o
UTILS_PILA_D_ = $(UTILS_PILA_C_)		\
	$(UTILS_PILA_H_)			\
	$(UTILS_BASIC_H_)			\
