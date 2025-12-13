função setup_redirections(cmd):

    // ===== HEREDOC =====
    se cmd.heredoc > 0:
        para cada delimitador em cmd.limits:
            ler linha do usuário
            parar quando linha == delimitador
            escrever conteúdo em um pipe ou arquivo temporário
        guardar fd de leitura final em cmd.heredoc_fd
        redirecionar STDIN para cmd.heredoc_fd
        fechar cmd.heredoc_fd

    // ===== INPUT REDIRECTION (<) =====
    se cmd.input existe:
        para cada arquivo em cmd.input:
            abrir arquivo em modo leitura
            redirecionar STDIN para esse fd
            fechar fd
        // apenas o último arquivo fica ativo

    // ===== OUTPUT REDIRECTION (>, >>) =====
    se cmd.output existe:
        para cada arquivo em cmd.output:
            se for append:
                abrir com APPEND
            senão:
                abrir com TRUNC
            redirecionar STDOUT para esse fd
            fechar fd
        // apenas o último arquivo fica ativo

    retornar