#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    mkgen.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 11:08:14 by nbouteme          #+#    #+#              #
#    Updated: 2016/02/23 13:42:35 by nbouteme         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ifndef SRC
SRC := $(shell ls | grep \\.c$)
endif
LIBS =
DEPS =
$(foreach s,$(SRC), $(eval DEPS += $(shell gcc -MM $s -Ilibft/includes |\
										   tr -d \\\\ | sed s/$(basename $s).o:\ $s// |\
										   tr ' ' '\n' | grep '^libft' | sort | uniq |\
										   cut -d '/' -f 4 | sed s/\\.h//)))
OBUILDLIBS := $(DEPS)
.SUFFIXES:
CC = gcc
WFLAGS = -Wall -Wextra -Werror
CFLAGS = $(OPTS)
OBJ = $(SRC:.c=.o)
ECHO = echo
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
ECHO = echo -e
endif
UNIQ := $(shell mktemp)
$(shell make -s -C libft OBUILDLIBS="$(OBUILDLIBS)" > $(UNIQ))
include $(UNIQ)
DEP += mlx
LDEP += minilibx
PDEP += minilibx
INCDIRS += -Ilibft/includes
$(eval LIBDIRS += $(addprefix -L,$(LDEP)))
$(eval LIBS += $(DEP))

all:
	$(foreach dep,$(PDEP), $(if $(shell make -C $(dep) CFLAGS=$(CFLAGS) &> /dev/null), $(eval )))
	@$(MAKE) -s $(NAME)
%.o: %.c
	@$(CC) $(WFLAGS) $(CFLAGS) $(INCDIRS) -c $^
	@$(ECHO) "\033[0;32m[✓] Built C object" $@
$(NAME): $(OBJ)
	@$(ECHO) "\033[0;34m--------------------------------"
	@ld -o $(NAME) -r $(OBJ) -Llibft -lft
	@$(ECHO) "\033[0;31m[✓] Linked C library" $(NAME)
clean:
	@/bin/rm -rf $(OBJ)
	@$(ECHO) "\033[0;33m[✓] Removed object files" $(OBJ)
fclean: clean
	@/bin/rm -rf $(NAME)
	@$(ECHO) "\033[0;33m[✓] Removed executable" $(NAME)
re: fclean
	@$(MAKE) all
.PHONY: clean fclean re cleandeps fcleandeps $(PHONY)
