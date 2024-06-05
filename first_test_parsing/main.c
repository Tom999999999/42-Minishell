#include "test.h"


int main(void)
{
    int i = 1;
    char input[] = "cat test.txt | grep \"baum hallo\" > output.txt";
    t_token *token = get_token(input);
    t_token *head = token;

    while (head)
	{
        printf("token %d, type:%s		value: %s\n", i, token_type_to_string(head->type), head->value);
        i++;
        head = head->next;
    }

    t_ast *ast = parse(&token);
    print_ast(ast);

    free_tokens(head);
    free_ast(ast);
    return 0;
}