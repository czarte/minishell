https://drive.google.com/file/d/1Jm3Dao2GkvsnJDgX9gBWmau3-ba3Bm-G/view?usp=sharing

readline suppression command:
`valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -s --log-file=logfile.log ./minishell`

show new leaks and suppress already suppressed:
`valgrind --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --suppressions=readline.supp ./minishell`
