FILE_SEMANTIC = 5-Semàntic

SEMANTIC_O_		=			\
	$(SEMANTIC_SEMANTICA_O_)		\

SEMANTIC_SEMANTICA_C_ = $(FILE_SEMANTIC)/semàntic.c
SEMANTIC_SEMANTICA_H_ = $(FILE_SEMANTIC)/semàntic.h
SEMANTIC_SEMANTICA_O_ = $(OBJDIR)/semàntic.o
SEMANTIC_SEMANTICA_D_ = $(SEMANTIC_SEMANTICA_C_)	\
	$(EXECUTOR_DESCRIPTOR_H_)			\
	$(DEPURADOR_DEPURADOR_H_)			\
	$(UTILS_PILA_H_)				\
