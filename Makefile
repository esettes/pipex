GREEN	= \033[0;32m
WHITE	= \033[0;37m
LGREEN	= \033[2;32m
LWHITE	= \033[2;37m
RESET	= \033[0m
GREY	= \033[1;30m

NAME	= pipex

NAME_B	= pipex_bonus

OS		=	$(shell uname -s)

SRCDIR	= ./src/
SRCNAMES	= $(shell ls $(SRCDIR) | grep -E ".+\.c")
SRC	= $(addprefix $(SRCDIR), $(SRCNAMES))
OBJDIR	= ./src/obj/
OBJS	= $(addprefix $(OBJDIR), $(SRCNAMES:.c=.o))

# Bonus ----------
SRCDIR_B	= ./bonus/src/
SRCNAMES_B	= $(shell ls $(SRCDIR_B) | grep -E ".+\.c")
SRC_B	= $(addprefix $(SRCDIR_B), $(SRCNAMES_B))
OBJDIR_B	= ./bonus/src/obj/
OBJS_B	= $(addprefix $(OBJDIR_B), $(SRCNAMES_B:.c=.o))
HEADERS_B	= -I include -I ./inc/libft/inc/ -I ./bonus/inc/headers/
# ----------------

LIBFT	= ./inc/libft/libft.a

HEADERS	= -I include -I ./inc/libft/inc/ -I ./inc/headers/

COMPS	= $(LIBFT)

CC	= clang
CFLAGS	= -g3 -Wall -Wextra -Werror #-fsanitize=address -Ofast -fno-omit-frame-pointer

ifeq ($(OS), Linux)
	VALGRIND = valgrind --tool=memcheck --leak-check=full --track-origins=yes -s
endif

all: obj $(COMPS) $(NAME)

bonus: obj_b $(COMPS) $(NAME_B)

obj:
	@mkdir -p $(OBJDIR)

obj_b:
	@mkdir -p $(OBJDIR_B)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@ $(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(NAME):	$(OBJS)
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(COMPS)
	@echo "${LWHITE}$(NAME) ${LGREEN}✓$(RESET)"
	@echo "${GREY}Compilation ${GREEN}[OK]$(RESET)"

# Bonus ----------
$(OBJDIR_B)%.o:$(SRCDIR_B)%.c
	@ $(CC) $(CFLAGS) $(HEADERS_B) -o $@ -c $<

$(NAME_B): $(OBJS_B)
	@ $(CC) $(CFLAGS) -o $(NAME_B) $(OBJS_B) $(COMPS)
	@echo "${LWHITE}$(NAME_B) ${LGREEN}✓$(RESET)"
	@echo "${GREY}Bonus compilation ${GREEN}[OK]$(RESET)"
# ----------------

$(LIBFT):
	@$(MAKE) -C $(dir $(LIBFT))

LD_DEBUG=all

n:
	@norminette ./src/*.c ./inc/headers/*.h ./inc/libft/inc/*.h ./inc/libft/src/*.c ./inc/libft/bonus/*.c ./bonus/src/*.c ./bonus/inc/headers/*.h

dbgfiles:
	@rm -rf *.dSYM
	@rm -rf *.DS_Store
	@echo "${LWHITE}Clean debug files... ${LGREEN}✓$(RESET)"

clean:	dbgfiles
	@echo "${LWHITE}Clean pipex... ${LGREEN}✓$(RESET)"
	@rm -rf ${OBJDIR}*.o
	@rm -rf ${OBJDIR_B}*.o
	@echo "${LWHITE}Clean Libft... ${LGREEN}✓$(RESET)"
	@$(MAKE) -C $(dir $(LIBFT)) clean

fclean: dbgfiles
	@rm -rf $(NAME)
	@rm -rf $(NAME_B)
	@echo "${LWHITE}Clean pipex... ${LGREEN}✓$(RESET)"
	@rm -rf ${OBJDIR}*.o
	@rm -rf ${OBJDIR_B}*.o
	@echo "${LWHITE}Clean Libft... ${LGREEN}✓$(RESET)"
	@$(MAKE) -C $(dir $(LIBFT)) fclean
	@echo "${GREY}Clean all ${GREEN}[OK]$(RESET)"
	@echo "\n"

re: fclean all

.PHONY: all fclean clean re
