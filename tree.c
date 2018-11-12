#include "lem_in.h"

t_tree	*ft_tree_new(void const *content, size_t content_size)
{
	t_tree *new;

	if (!(new = (t_tree*)ft_memalloc(sizeof(t_tree))))
		return (NULL);
	new->parent = NULL;
	new->siblings = NULL;
	new->children = NULL;
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if (!(new->content = ft_memalloc(content_size)))
			return (NULL);
		ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	return (new);
}

void	ft_tree_addsibling(t_tree **tree, t_tree *sibling)
{
	if (sibling)
	{
		sibling->siblings = (*tree);
		(*tree) = sibling;
	}
}

/*void	ft_tree_addchild(t_tree **tree, t_tree *child)*/


void	ft_tree_free(t_tree **tree)
{
	if (!tree || !(*tree))
		return ;
	while ((*tree)->parent)
		(*tree) = (*tree)->parent;
	ft_tree_free(&(*tree)->siblings);
	ft_tree_free(&(*tree)->children);
	free((*tree)->content);
	ft_memdel((void**)tree);
}
