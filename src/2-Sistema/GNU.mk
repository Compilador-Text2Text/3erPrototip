FILE_SISTEMA = 2-Sistema

SISTEMA_O_		=			\
	$(SISTEMA_INICIALITZADOR_O_)		\

SISTEMA_INICIALITZADOR_C_ = $(FILE_SISTEMA)/inicialitza.c
SISTEMA_INICIALITZADOR_H_ = $(FILE_SISTEMA)/inicialitza.h
SISTEMA_INICIALITZADOR_O_ = $(OBJDIR)/sistem_init.o
SISTEMA_INICIALITZADOR_D_ = $(SISTEMA_INICIALITZADOR_C_)	\
