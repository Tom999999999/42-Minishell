#include "minishell.h"

void demonstrate_readline_functions(void)
{
    char *input;

    while (1)
    {
        input = readline("\033[1;91m> \033[0;39m");

        if (!input)
        {
            printf("\nExiting...\n");
            break;
        }
        if (strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }

        if (strcmp(input, "clear") == 0)
        {
            rl_clear_history();
            printf("History cleared.\n");
            free(input);
            continue;
        }

        if (*input)
            add_history(input);

        printf("You entered: %s\n", input);
        free(input);
    }
}

int main() {
    demonstrate_readline_functions();
    return 0;
}