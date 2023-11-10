make && make clean && valgrind \
            --leak-check=full \
            --track-origins=yes \
            --log-file=val_log.txt \
            ./minishell

			            #--show-leak-kinds=all \