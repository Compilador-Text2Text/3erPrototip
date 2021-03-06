FILE_SISTEMA = 2-Sistema

SISTEMA_O_		=			\
	$(SISTEMA_INICIALITZADOR_O_)		\
	$(SISTEMA_SISTEMA_O_)			\
	$(SISTEMA_SALTS_O_)			\
	$(SISTEMA_OPERADORS_O_)			\
	$(SISTEMA_MOSTRA_O_)			\

SISTEMA_INICIALITZADOR_C_ = $(FILE_SISTEMA)/inicialitza.c
SISTEMA_INICIALITZADOR_H_ = $(FILE_SISTEMA)/inicialitza.h
SISTEMA_INICIALITZADOR_O_ = $(OBJDIR)/system_init.o
SISTEMA_INICIALITZADOR_D_ = $(SISTEMA_INICIALITZADOR_C_)	\
	$(EXECUTOR_DESCRIPTOR_H_)				\
	$(SISTEMA_SISTEMA_H_)					\
	$(SISTEMA_SALTS_H_)					\
	$(SISTEMA_MOSTRA_H_)					\
	$(UTILS_BASIC_H_)					\

SISTEMA_SISTEMA_C_ = $(FILE_SISTEMA)/sistema.c
SISTEMA_SISTEMA_H_ = $(FILE_SISTEMA)/sistema.h
SISTEMA_SISTEMA_O_ = $(OBJDIR)/sistema_funcio.o
SISTEMA_SISTEMA_D_ = $(SISTEMA_SISTEMA_C_)	\
	$(SISTEMA_SISTEMA_H_)			\
	$(SISTEMA_INICIALITZADOR_H_)		\
	$(EXECUTOR_DESCRIPTOR_H_)		\

SISTEMA_SALTS_C_ = $(FILE_SISTEMA)/salts.c
SISTEMA_SALTS_H_ = $(FILE_SISTEMA)/salts.h
SISTEMA_SALTS_O_ = $(OBJDIR)/salts_funcio.o
SISTEMA_SALTS_D_ = $(SISTEMA_SALTS_C_)		\
	$(SISTEMA_SALTS_H_)			\
	$(SISTEMA_INICIALITZADOR_H_)		\
	$(EXECUTOR_DESCRIPTOR_H_)		\

SISTEMA_OPERADORS_C_ = $(FILE_SISTEMA)/operadors.c
SISTEMA_OPERADORS_H_ = $(FILE_SISTEMA)/operadors.h
SISTEMA_OPERADORS_O_ = $(OBJDIR)/operadors_funcio.o
SISTEMA_OPERADORS_D_ = $(SISTEMA_OPERADORS_C_)	\
	$(SISTEMA_OPERADORS_H_)			\
	$(SISTEMA_INICIALITZADOR_H_)		\
	$(EXECUTOR_DESCRIPTOR_H_)		\

SISTEMA_MOSTRA_C_ = $(FILE_SISTEMA)/mostra.c
SISTEMA_MOSTRA_H_ = $(FILE_SISTEMA)/mostra.h
SISTEMA_MOSTRA_O_ = $(OBJDIR)/mostra_funcio.o
SISTEMA_MOSTRA_D_ = $(SISTEMA_MOSTRA_C_)	\
	$(SISTEMA_MOSTRA_H_)			\
	$(SISTEMA_INICIALITZADOR_H_)		\
	$(EXECUTOR_DESCRIPTOR_H_)		\
