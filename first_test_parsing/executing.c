function evaluate(node):
    if node.type == N_COMMAND:
        execute_command(node.arguments)
    elif node.type == N_PIPE:
        left_result = evaluate(node.left)
        right_result = evaluate(node.right)
        pipe(left_result, right_result)
    elif node.type == N_GREAT:
        left_result = evaluate(node.left)
        write_to_file(left_result, node.filename)
    elif node.type == N_AND:
        left_result = evaluate(node.left)
        if left_result == true:
            return evaluate(node.right)
        else:
            return false
    elif node.type == N_OR:
        left_result = evaluate(node.left)
        if left_result == true:
            return true
        else:
            return evaluate(node.right)
