# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/25 19:56:18 by lucasdebarn       #+#    #+#              #
#    Updated: 2026/03/27 09:49:21 by lucasdebarn      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_BONUS = philo_bonus

MAKEFLAGS += --no-print-directory

# Repertoires
OBJ_DIR = object
OBJ_DIR_BONUS = object_bonus
SRC_DIR = src
SRC_DIR_BONUS = src_bonus
INC_DIR = includes


# Chemins complets vers les fichiers source
SRC_FILES = $(SRC_DIR)/setup_data.c \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/parsing.c \
			$(SRC_DIR)/routine.c \
			$(SRC_DIR)/routine_utils.c \
			$(SRC_DIR)/clean_up.c

SRC_FILE_BONUS = $(SRC_DIR_BONUS)/setup_data_bonus.c \
			$(SRC_DIR_BONUS)/main.c \
			$(SRC_DIR_BONUS)/parsing_bonus.c \
			$(SRC_DIR_BONUS)/routine_bonus.c \
			$(SRC_DIR_BONUS)/routine_bonus2.c \
			$(SRC_DIR_BONUS)/utils_bonus.c

# Chemins vers les fichiers objets correspondants
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJS_BONUS = $(patsubst $(SRC_DIR_BONUS)/%.c,$(OBJ_DIR_BONUS)/%.o,$(SRC_FILE_BONUS))

# Configurations de bases
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -pthread

# Chemins d'inclusion communs
INCLUDES = -I$(INC_DIR)

GREEN	= \033[0;32m
RESET	= \033[0m

# Custom
COMPILE_MSG = @printf "."

# Rules
all: $(NAME)

# Compilation de l'exécutable principal
$(NAME): $(OBJS)
	$(COMPILE_MSG)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)\n✅ Compilation terminée pour $(NAME) !$(RESET)"

# Règle pour créer les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(COMPILE_MSG)

bonus: $(NAME_BONUS)

# Compilation de l'exécutable bonus
$(NAME_BONUS): $(OBJS_BONUS)
	$(COMPILE_MSG)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
	@echo "$(GREEN)\n✅ Compilation terminée pour $(NAME_BONUS) !$(RESET)"

# Règle pour créer les fichiers objets_bonus
$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(COMPILE_MSG)

# Nettoyage des fichiers objets
clean:
	@echo "🧹 Nettoyage des fichiers objets..."
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@echo "✅ Nettoyage terminé !"

# Nettoyage complet
fclean: clean
	@echo "🧹 Nettoyage complet..."
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "✅ Nettoyage complet terminé !"

# Règle pour tester les leaks rapidement
leaks: all
	valgrind --leak-check=full --show-leak-kinds=all ./minishell

# Recompilation complète
re: fclean all

# Cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re bonus
