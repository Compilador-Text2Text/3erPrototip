include 0-Inicialitzador/GNU.mk
include 1-Executor/GNU.mk
include 2-Sistema/GNU.mk
include 9-Útils/GNU.mk

##################################################
#                     General                    #
##################################################
CLEAN	= clean
OBJDIR	= ../Bin
LIBS	= -Wall -g -o
LIBS_O_	= -c		\
	  $(LIBS)
LIBS_E_	= -l m		\
	  $(LIBS)

MAIN_INTERPRET	= $(OBJDIR)/interpret
MAIN_C_		= main.c
MAIN_O_		= $(OBJDIR)/main.o
MAIN_D_		= $(MAIN_C_)			\
	$(INICIALITZADOR_INICIALITZA_H_)	\
	$(UTILS_BASIC_H_)			\

MAIN_INTERPRET_D_ = $(MAIN_O_)	\
	$(INICIALITZADOR_O_)	\
	$(EXECUTOR_O_)		\
	$(SISTEMA_O_)		\
	$(UTILS_O_)		\

all: $(MAIN_INTERPRET)
##################################################
#                     Carpeta                    #
##################################################
ALL = $(MAIN_INTERPRET) $(MAIN_INTERPRET_D_)
$(ALL): | $(OBJDIR)
$(OBJDIR):
	mkdir $(OBJDIR)

##################################################
#                 Inicialitzador                 #
##################################################
$(INICIALITZADOR_INICIALITZA_O_): $(INICIALITZADOR_INICIALITZA_D_)
	gcc $(INICIALITZADOR_INICIALITZA_C_) $(LIBS_O_) $(INICIALITZADOR_INICIALITZA_O_)

##################################################
#                    Executor                    #
##################################################
$(EXECUTOR_DESCRIPTOR_O_): $(EXECUTOR_DESCRIPTOR_D_)
	gcc $(EXECUTOR_DESCRIPTOR_C_) $(LIBS_O_) $(EXECUTOR_DESCRIPTOR_O_)

##################################################
#                     Sistema                    #
##################################################
$(SISTEMA_INICIALITZADOR_O_): $(SISTEMA_INICIALITZADOR_D_)
	gcc $(SISTEMA_INICIALITZADOR_C_) $(LIBS_O_) $(SISTEMA_INICIALITZADOR_O_)

$(SISTEMA_SISTEMA_O_): $(SISTEMA_SISTEMA_D_)
	gcc $(SISTEMA_SISTEMA_C_) $(LIBS_O_) $(SISTEMA_SISTEMA_O_)

$(SISTEMA_SALTS_O_): $(SISTEMA_SALTS_D_)
	gcc $(SISTEMA_SALTS_C_) $(LIBS_O_) $(SISTEMA_SALTS_O_)

$(SISTEMA_OPERADORS_O_): $(SISTEMA_OPERADORS_D_)
	gcc $(SISTEMA_OPERADORS_C_) $(LIBS_O_) $(SISTEMA_OPERADORS_O_)

##################################################
#                    Intèrpret                   #
##################################################
$(MAIN_O_): $(MAIN_D_)
	gcc $(MAIN_C_) $(LIBS_O_) $(MAIN_O_)

$(MAIN_INTERPRET): $(MAIN_INTERPRET_D_)
	gcc $(MAIN_INTERPRET_D_) $(LIBS_E_) $(MAIN_INTERPRET)

##################################################
#                      Útils                     #
##################################################
$(UTILS_BASIC_O_): $(UTILS_BASIC_D_)
	gcc $(UTILS_BASIC_C_) $(LIBS_O_) $(UTILS_BASIC_O_)

$(UTILS_PILA_O_): $(UTILS_PILA_D_)
	gcc $(UTILS_PILA_C_) $(LIBS_O_) $(UTILS_PILA_O_)

$(CLEAN):
	rm $(ALL) -f

.PHONY: all $(CLEAN) d
