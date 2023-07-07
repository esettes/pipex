GREEN	= \033[0;32m
WHITE	= \033[0;37m
LGREEN	= \033[2;32m
LWHITE	= \033[2;37m
RESET	= \033[0m
GREY	= \033[1;30m

NAME	= pipex

OS		=	$(shell uname -s)

SRCDIR	= ./src/
SRCNAMES	= $(shell ls $(SRCDIR) | grep -E ".+\.c")
SRC	= $(addprefix $(SRCDIR), $(SRCNAMES))
OBJDIR	= ./src/obj/
OBJS	= $(addprefix $(OBJDIR), $(SRCNAMES:.c=.o))

LIBFT	= ./inc/libft/libft.a

HEADERS	= -I include -I ./inc/libft/inc/ -I ./inc/headers/

COMPS	= $(LIBFT)

CC	= clang
CFLAGS	= -g3 #-fsanitize=address #-Wall -Wextra -Werror # -Ofast -fno-omit-frame-pointer

ifeq ($(OS), Linux)
	VALGRIND = valgrind --tool=memcheck --leak-check=full --track-origins=yes -s
endif

all: obj $(COMPS) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@ $(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(NAME):	$(OBJS)
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(COMPS)
	@echo "${LWHITE}$(NAME) ${LGREEN}✓$(RESET)"
	@echo "${GREY}Compilation ${GREEN}[OK]$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(dir $(LIBFT))

LD_DEBUG=all

n:
	@norminette ./src/*.c ./inc/headers/*.h ./inc/libft/inc/*.h ./inc/libft/src/*.c ./inc/libft/bonus/*.c

dbgfiles:
	@rm -rf *.dSYM
	@rm -rf *.DS_Store
	@echo "${LWHITE}Clean debug files... ${LGREEN}✓$(RESET)"

clean:	dbgfiles
	@echo "${LWHITE}Clean pipex... ${LGREEN}✓$(RESET)"
	@rm -rf ${OBJDIR}*.o
	@echo "${LWHITE}Clean Libft... ${LGREEN}✓$(RESET)"
	@$(MAKE) -C $(dir $(LIBFT)) clean

fclean: dbgfiles
	@rm -rf $(NAME)
	@echo "${LWHITE}Clean pipex... ${LGREEN}✓$(RESET)"
	@rm -rf ${OBJDIR}*.o
	@echo "${LWHITE}Clean Libft... ${LGREEN}✓$(RESET)"
	@$(MAKE) -C $(dir $(LIBFT)) fclean
	@echo "${GREY}Clean all ${GREEN}[OK]$(RESET)"
	@echo "\n"

re: fclean all

.PHONY: all fclean clean re
