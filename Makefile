NAME = philo

MAKEFLAGS += --no-print-directory

# Repertoires
OBJ_DIR = object
SRC_DIR = src
INC_DIR = includes

# Chemins complets vers les fichiers source
SRC_FILES = $(SRC_DIR)/philo_utils.c \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/parsing.c \
			$(SRC_DIR)/routine.c \

# Chemins vers les fichiers objets correspondants
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

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

# Nettoyage des fichiers objets
clean:
	@echo "🧹 Nettoyage des fichiers objets..."
	@rm -rf $(OBJ_DIR)
	@echo "✅ Nettoyage terminé !"

# Nettoyage complet
fclean: clean
	@echo "🧹 Nettoyage complet..."
	@rm -f $(NAME)
	@echo "✅ Nettoyage complet terminé !"

# Règle pour tester les leaks rapidement
leaks: all
	valgrind --leak-check=full --show-leak-kinds=all ./minishell

# Recompilation complète
re: fclean all

# Cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re bonus
