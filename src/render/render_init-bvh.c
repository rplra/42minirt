/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init-bvh.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:27:52 by hsim              #+#    #+#             */
/*   Updated: 2025/07/09 11:45:00 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
 * initializes res to (0,0)
 * bbox value of obj (ranges frm 0 to argc) will be stored in res[3]
 */
void	get_bbox_val(t_obj *obj, int argc, t_interval res[3])
{
	int	x;

	x = -1;
	// init_bbox(res);
	assign_bbox(obj[0].bbox, res);
	/*debug*/printf("get_bbox_val:ac:%d\n", argc);
	while (++x < argc)
	{
		/*debug*/printf("x:%d\n", x);
		// /*debug*/printf("%d :", x);
		// /*debug*/debug_print_bbox("get_bbox_val", obj[x].bbox);
		update_aabb_box(res, obj[x].bbox, res);
	}
}

// static
/* returns the axis where the difference between max-min is largest */
int	longest_axis(t_interval bbox[3])
{
	int	n[3];

	n[X] = bbox[X].max - bbox[X].min;
	n[Y] = bbox[Y].max - bbox[Y].min;
	n[Z] = bbox[Z].max - bbox[Z].min;

	if (n[X] > n[Y] && n[X] > n[Z])
		return (X);
	else if (n[Y] > n[X] && n[Y] > n[Z])
		return (Y);
	return (Z);
}

// &obj[mid]
// t_bvh_tree	*build_bvh_tree(t_obj node[2], t_rt *vars, int argc, bool (*func)(t_obj, t_obj))
t_bvh_tree	*build_bvh_tree(t_obj *obj, t_uint *seed, int argc, int id[2], bool (*func[3])(t_obj, t_obj))
{
	int			half[2];
	int			mid;
	int			axis;
	t_bvh_tree	*bvh;
	// t_interval	box[2][3];

	bvh = (t_bvh_tree *)malloc(sizeof(t_bvh_tree));
	mid = (argc / 2);
	// mid = ((argc[1] - argc[0]) / 2);
	/*debug*/printf("id: %d~%d, argc:%d, diff:%d\n", id[0], id[1], argc, id[1]-id[0]);
	// /*debug*/printf("\nargc:%d to %d, mid:%d - %d\n", argc[0], argc[1], mid[1], argc[1]-mid[1]);

	// init_bbox(bvh->bbox);
	// assign_bbox(obj[0].bbox, bvh->bbox);

	// get_bbox_val(obj, mid, box[L]);	//0-2
	// get_bbox_val(&obj[mid], argc - mid, box[R]);	//2-4 -1
	// update_aabb_box(box[L], box[R], bvh->bbox);

	get_bbox_val(obj, argc, bvh->bbox);
	/*debug*/debug_print_bbox("fin_box", bvh->bbox);
	/*debug*/printf("\n");

	// if (id[1] - id[0] <= 0)
	if (argc <= 0)
	{
		/*debug*/printf("hello\n");
		return (NULL);
	}
	// if ((id[1] - id[0] == 1) || (id[1] - id[0] == 2))
	if ((argc == 1) || (argc == 2))
	{
		/*debug*/printf("return %d~%d\n-------\n", id[0], id[1]);
		bvh->id[L] = id[0];
		bvh->type[L] = obj[0].type;
		bvh->left = &obj[0];
		// if (id[1] - id[0] == 1)
		if (argc == 1)
		{
			bvh->id[R] = id[0];
			bvh->type[R] = obj[0].type;
			bvh->right = &obj[0];
		}
		else
		{
			bvh->id[R] = id[1] - 1;
			bvh->type[R] = obj[1].type;
			bvh->right = &obj[1];
		}
	}
	else
	{
		/*debug*/printf("else\n");
		// axis = rand_int(seed, 0, 2);
		axis = longest_axis(bvh->bbox);
		/*debug*/printf("merge_sort: ac:%d, id_dif:%d\n", argc, id[1] - id[0]);
		merge_sort(obj, argc, func[axis]);
		bvh->type[L] = BVH;
		bvh->type[R] = BVH;
		bvh->id[L] = -1;
		bvh->id[R] = -1;

		half[0] = id[0];		//0-2, 2-5 |  5/2=2, 5-(5/2)=5-2=3
		//3-6: 3+ (1)=4: 3-4, 4-6 | 4-6: 4+(1)=5: 4-5, 5-6
		half[1] = id[0] + ((id[1] - id[0]) / 2); //2 (mid)
		//mid = half[1]-half[0]
		/*debug*/printf("|ac[L]: %d~%d %d\n", half[0], half[1], mid);
		bvh->left = build_bvh_tree(obj, seed, mid, half, func);
		// mid, argc-mid
		
		//argc = half[1]
		//mid = half[1]/2

		/* ********************************************************* */
		//mid = half[1] - half[0];
		//half[1] = ((id[1] - id[0]) / 2) - mid
		half[0] = half[1];		//2
		half[1] = id[1];		//4
		/*debug*/printf("|ac[R]: %d~%d\n", half[0], half[1]);
		/*debug*/printf("mid: %d, %d\n\n", mid, argc-mid); //both are half[1]
		bvh->right = build_bvh_tree(&obj[mid], seed, argc-mid, half, func);
		// bvh->right = build_bvh_tree(&obj[mid], seed, argc - mid, func);
	}
	return (bvh);
}

/* build a bvh tree with objects list */
void	init_bvh_node(t_rt *vars)
{
	int	id[2];

	bool (*box_compare[3])(t_obj, t_obj);
	init_box_compare(box_compare);
	id[0] = 0;
	id[1] = vars->obj_count;
	vars->bvh = build_bvh_tree(\
vars->obj, &vars->seed, vars->obj_count, id, box_compare);
}
