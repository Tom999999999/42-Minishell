#include "test.h"

int main(void)
{
    char input[] = "cat test.txt | grep \"baum hallo\" > output.txt";
    
    t_token *token = get_token(input);
    t_token *tmp = token;
    t_ast *ast = parse(&token);

    print_token(tmp);
    printf("\n\n");
    print_ast(ast);

    free_tokens(token);
    free_ast(ast);
    return 0;
}