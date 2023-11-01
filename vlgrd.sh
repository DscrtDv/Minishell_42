make && make clean && valgrind \
            --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --log-file=val_log.txt \
            ./minishell