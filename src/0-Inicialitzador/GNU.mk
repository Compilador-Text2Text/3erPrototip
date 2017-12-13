FILE_INICIALITZADOR = 0-Inicialitzador

INICIALITZADOR_O_	=			\
	$(INICIALITZADOR_INICIALITZA_O_)	\
	$(INICIALITZADOR_ALLIBERA_O_)		\

INICIALITZADOR_INICIALITZA_C_ = $(FILE_INICIALITZADOR)/inicialitza.c
INICIALITZADOR_INICIALITZA_H_ = $(FILE_INICIALITZADOR)/inicialitza.h
INICIALITZADOR_INICIALITZA_O_ = $(OBJDIR)/inicialitza.o
INICIALITZADOR_INICIALITZA_D_ =	$(INICIALITZADOR_INICIALITZA_C_)	\
	$(LEXIC_OBJECTE_H_)						\
	$(SINTACTIC_SHUTING_YARD_ALGORITHM_H_)				\
	$(DEPURADOR_DEPURADOR_H_)					\
	$(UTILS_PILA_H_)						\
	$(UTILS_BASIC_H_)						\

INICIALITZADOR_ALLIBERA_C_ = $(FILE_INICIALITZADOR)/allibera.c
INICIALITZADOR_ALLIBERA_H_ = $(FILE_INICIALITZADOR)/allibera.h
INICIALITZADOR_ALLIBERA_O_ = $(OBJDIR)/allibera.o
INICIALITZADOR_ALLIBERA_D_ = $(INICIALITZADOR_ALLIBERA_C_)		\
	$(EXECUTOR_DESCRIPTOR_H_)					\
	$(UTILS_BASIC_H_)						\
