FILE_DEPURADOR = 6-Depurador

DEPURADOR_O_		=			\
	$(DEPURADOR_DEPURADOR_O_)		\

DEPURADOR_DEPURADOR_C_ = $(FILE_DEPURADOR)/depurador.c
DEPURADOR_DEPURADOR_H_ = $(FILE_DEPURADOR)/depurador.h
DEPURADOR_DEPURADOR_O_ = $(OBJDIR)/depurador.o
DEPURADOR_DEPURADOR_D_ = $(DEPURADOR_DEPURADOR_C_)	\
	$(DEPURADOR_DEPURADOR_H_)			\
	$(EXECUTOR_DESCRIPTOR_H_)			\
