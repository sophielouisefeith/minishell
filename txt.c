static t_ll_sprite	*ll_add_new_front(t_base *base, double y, double x)
{
	t_ll_sprite		*new_node;

	new_node = ll_create_node(base, y, x);
	base->head = new_node;
	return (base->head);
}

static t_ll_sprite	*ll_create_node(t_base *base, double y, double x)
{
	t_ll_sprite		*new_node;

	new_node = (t_ll_sprite *)malloc(sizeof(t_ll_sprite));
	if (!new_node)
		error_distr(base, 6);
	new_node->x = x;
	new_node->next = base->head;
	return (new_node);
}