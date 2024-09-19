/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/17 18:02:45 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	print_t_executor_print_array(char **arr)
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

void	print_t_executor_cont_2(t_executor *pt)
{
	if (pt->infile)
		printf("infile:\t%s\n", pt->infile);
	else
		printf("infile:\tNULL\n");
	if (pt->outfile)
		printf("outfile:\t%s\n", pt->outfile);
	else
		printf("outfile:\tNULL\n");
	if (pt->dlmtr)
		printf("dlmtr:\t%s\n", pt->dlmtr);
	else
		printf("dlmtr\tNULL\n");
	printf("========\n\n");
}

void	print_t_executor_cont_1(t_executor *pt)
{
	if (pt->argv)
	{
		printf("argv:\n");
		print_t_executor_print_array(pt->argv);
	}
	else
		printf("argv:\tNULL\n");
	if (pt->path)
	{
		printf("path:\n");
		print_t_executor_print_array(pt->path);
	}
	else
		printf("path:\tNULL\n");
	print_t_executor_cont_2(pt);
}

void	print_t_executor_cont(t_list *ltmp, t_executor *pt)
{
	if (pt->pwd)
		printf("pwd:\t%s\n", pt->pwd);
	else
		printf("pwd:\tNULL\n");
	if (pt->home)
		printf("home:\t%s\n", pt->home);
	else
		printf("home:\tNULL\n");
	if (ltmp)
	{
		printf("comm:\n");
		while (ltmp)
		{
			print_t_executor_print_array((char **) ltmp->content);
			ltmp = ltmp->next;
		}
	}
	else
		printf("comm:\tNULL\n");
	print_t_executor_cont_1(pt);
}

void	print_t_executor(t_executor *pt)
{
	t_list	*ltmp;

	if (pt->debug)
	{
		ltmp = pt->comm;
		printf("\n====    PT    ====\n");
		printf("debug:\t%i\n", pt->debug);
		printf("heredoc:\t%i\n", pt->heredoc);
		printf("heredoc_rl:\t%i\n", pt->heredoc_rl);
		printf("append:\t%i\n", pt->append);
		printf("c_pi:\t%i\n", pt->c_pi);
		printf("file_fd[0]:\t%i\nfile_fd[1]: %i\n", pt->filefd[0],
			pt->filefd[1]);
		printf("it:\t%i\n", pt->it);
		printf("end:\t%i\n", pt->end);
		printf("fsucc:\t%i\n", pt->fsucc);
		printf("status:\t%i\n", pt->status);
		printf("psucc:\t%i\n", pt->psucc);
		if (pt->pid)
			printf("pid:\t%i\n", *pt->pid);
		else
			printf("pid:\rNULL\n");
		print_t_executor_cont(ltmp, pt);
	}
}
