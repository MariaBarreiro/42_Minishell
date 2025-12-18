#include "../header.h"

void    setup_redirections(t_cmd_block *cmd)
{
	int		i;
	char	*line;
	int		fd[2];

	if (cmd->heredoc > 0)
	{
		i = 0;
		pipe(fd);
		close(fd[0]);
		while (cmd->limits[i])
		{
			line = readline(">");
			if (ft_strcmp(line, cmd->limits[i]))
			{
				free(line);
				return ;
			}
			ft_putstr_fd(line, fd[1]);
			free(line);
		}
	}
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
}
