#include "test.h"

int main(int argc, char **argv)
{
    char input[] = "cat test.txt | grep \"baum hallo\" > output.txt";
    // char *input = argv[1];
    
    t_token *token = get_token(input);
    t_token *tmp = token;
    t_token *tmp2 = token;
    t_ast *ast = parse(&token);

    print_token(tmp);
    printf("\n\n");
    print_ast(ast);

    free_tokens(tmp2);
    free_ast(ast);
    return 0;
}