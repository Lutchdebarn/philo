NAME = philo

MAKEFLAGS += --no-print-directory

# Repertoires
OBJ_DIR = object

# Chemins complets vers les fichiers source
SRC_FILES = src/philo.c
			src/philo_utils.c

# Chemins vers les fichiers objets correspondants
OBJS = $(patsubst $(OBJ_DIR)/%.o,$(SRC_FILES))

# Configurations de bases
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

# Chemins d'inclusion communs
INCLUDES = -I
LIBRARIES = -lft

# Custom
COMPILE_MSG = @printf "."

# Rules
all: $(NAME)

# Compilation de l'exécutable principal
$(NAME): $(OBJS)
	$(COMPILE_MSG)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBRARIES) -o $(NAME)
	@echo "\n✅ Compilation terminée pour minishell !"

# Règle pour créer les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(COMPILE_MSG)

# Nettoyage des fichiers objets
clean:
	@echo "🧹 Nettoyage des fichiers objets..."
	@rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@echo "✅ Nettoyage terminé !"

# Nettoyage complet
fclean: clean
	@echo "🧹 Nettoyage complet..."
	@rm -f $(NAME)
	@echo "✅ Nettoyage complet terminé !"

# Règle pour tester les leaks rapidement
leaks: all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

# Recompilation complète
re: fclean all

# Cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re bonus
