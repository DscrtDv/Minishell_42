make && make clean && valgrind \
            --leak-check=full \
            --track-origins=yes \
            --show-leak-kinds=all \
            --log-file=val_log.txt \
            ./minishell