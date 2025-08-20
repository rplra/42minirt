/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:01:32 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/20 14:46:41 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "scene.h"

/*	window	*/
// # define WIN_WIDTH		600
// # define WIN_HEIGHT		400

# define WIN_WIDTH		800
# define WIN_HEIGHT		600

// # define WIN_WIDTH		1000
// # define WIN_HEIGHT		800

// # define WIN_WIDTH		2880
// # define WIN_HEIGHT		2160

/*	menu	*/
# if WIN_HEIGHT <=		400
#  define MENU			"asset/menu/menu-400.xpm"
#  define PANEL_WIDTH	133
# elif WIN_HEIGHT <=	600
#  define MENU			"asset/menu/menu-600.xpm"
#  define PANEL_WIDTH	199
# elif WIN_HEIGHT <=	800
#  define MENU			"asset/menu/menu-800.xpm"
#  define PANEL_WIDTH	266
# elif WIN_HEIGHT <=	2160
#  define MENU			"asset/menu/menu-2160.xpm"
#  define PANEL_WIDTH	720
# endif


/*	img-assets	*/
# define LOADBAR		"asset/load-600.xpm"
# define INTRO			"asset/intro.xpm"
# define LOADBAR_W		135
# define INTRO_W		400

/*	label-assets	*/
# define LABEL_W		200
# define LABEL_H		30
# if WIN_HEIGHT <= 		400
#  define LABEL_C		"asset/label/camera_400.xpm"
#  define LABEL_L		"asset/label/light_400.xpm"
#  define LABEL_PL		"asset/label/plane_400.xpm"
#  define LABEL_SP		"asset/label/sphere_400.xpm"
#  define LABEL_CY		"asset/label/cylinder_400.xpm"

# elif WIN_HEIGHT <=	600
#  define LABEL_C		"asset/label/camera_600.xpm"
#  define LABEL_L		"asset/label/light_600.xpm"
#  define LABEL_PL		"asset/label/plane_600.xpm"
#  define LABEL_SP		"asset/label/sphere_600.xpm"
#  define LABEL_CY		"asset/label/cylinder_600.xpm"

# elif WIN_HEIGHT <=	800
#  define LABEL_C		"asset/label/camera_800.xpm"
#  define LABEL_L		"asset/label/light_800.xpm"
#  define LABEL_PL		"asset/label/plane_800.xpm"
#  define LABEL_SP		"asset/label/sphere_800.xpm"
#  define LABEL_CY		"asset/label/cylinder_800.xpm"

# elif WIN_HEIGHT <=	2160
#  define LABEL_C		"asset/label/camera_2160.xpm"
#  define LABEL_L		"asset/label/light_2160.xpm"
#  define LABEL_PL		"asset/label/plane_2160.xpm"
#  define LABEL_SP		"asset/label/sphere_2160.xpm"
#  define LABEL_CY		"asset/label/cylinder_2160.xpm"
# endif

/*	digit-assets	*/
# define DIGIT_W		200
# define DIGIT_H		30
# if WIN_HEIGHT <=		400
#  define DIGIT_0		"asset/digit/0_400.xpm"
#  define DIGIT_1		"asset/digit/1_400.xpm"
#  define DIGIT_2		"asset/digit/2_400.xpm"
#  define DIGIT_3		"asset/digit/3_400.xpm"
#  define DIGIT_4		"asset/digit/4_400.xpm"
#  define DIGIT_5		"asset/digit/5_400.xpm"
#  define DIGIT_6		"asset/digit/6_400.xpm"
#  define DIGIT_7		"asset/digit/7_400.xpm"
#  define DIGIT_8		"asset/digit/8_400.xpm"
#  define DIGIT_9		"asset/digit/9_400.xpm"

# elif WIN_HEIGHT <= 	600
#  define DIGIT_0		"asset/digit/0_600.xpm"
#  define DIGIT_1		"asset/digit/1_600.xpm"
#  define DIGIT_2		"asset/digit/2_600.xpm"
#  define DIGIT_3		"asset/digit/3_600.xpm"
#  define DIGIT_4		"asset/digit/4_600.xpm"
#  define DIGIT_5		"asset/digit/5_600.xpm"
#  define DIGIT_6		"asset/digit/6_600.xpm"
#  define DIGIT_7		"asset/digit/7_600.xpm"
#  define DIGIT_8		"asset/digit/8_600.xpm"
#  define DIGIT_9		"asset/digit/9_600.xpm"

# elif WIN_HEIGHT <=	800
#  define DIGIT_0 		"asset/digit/0_800.xpm"
#  define DIGIT_1		"asset/digit/1_800.xpm"
#  define DIGIT_2		"asset/digit/2_800.xpm"
#  define DIGIT_3		"asset/digit/3_800.xpm"
#  define DIGIT_4		"asset/digit/4_800.xpm"
#  define DIGIT_5		"asset/digit/5_800.xpm"
#  define DIGIT_6		"asset/digit/6_800.xpm"
#  define DIGIT_7		"asset/digit/7_800.xpm"
#  define DIGIT_8		"asset/digit/8_800.xpm"
#  define DIGIT_9		"asset/digit/9_800.xpm"

# elif WIN_HEIGHT <=	2160
#  define DIGIT_0 		"asset/digit/0_2160.xpm"
#  define DIGIT_1		"asset/digit/1_2160.xpm"
#  define DIGIT_2		"asset/digit/2_2160.xpm"
#  define DIGIT_3		"asset/digit/3_2160.xpm"
#  define DIGIT_4		"asset/digit/4_2160.xpm"
#  define DIGIT_5		"asset/digit/5_2160.xpm"
#  define DIGIT_6		"asset/digit/6_2160.xpm"
#  define DIGIT_7		"asset/digit/7_2160.xpm"
#  define DIGIT_8		"asset/digit/8_2160.xpm"
#  define DIGIT_9		"asset/digit/9_2160.xpm"
# endif

/*	info-assets	*/
# define INFO_W			200
# define INFO_H			30
# if WIN_HEIGHT <=		400
#  define INFO_POS 		"asset/info/pos_400.xpm"
#  define INFO_ROT 		"asset/info/rot_400.xpm"
#  define INFO_DOT 		"asset/info/dot_400.xpm"
#  define INFO_COMMA 	"asset/info/comma_400.xpm"
#  define INFO_MINUS 	"asset/info/minus_400.xpm"

# elif WIN_HEIGHT <=	600
#  define INFO_POS 		"asset/info/pos_600.xpm"
#  define INFO_ROT 		"asset/info/rot_600.xpm"
#  define INFO_DOT 		"asset/info/dot_600.xpm"
#  define INFO_COMMA 	"asset/info/comma_600.xpm"
#  define INFO_MINUS 	"asset/info/minus_600.xpm"

# elif WIN_HEIGHT <=	800
#  define INFO_POS 		"asset/info/pos_800.xpm"
#  define INFO_ROT 		"asset/info/rot_800.xpm"
#  define INFO_DOT 		"asset/info/dot_800.xpm"
#  define INFO_COMMA 	"asset/info/comma_800.xpm"
#  define INFO_MINUS 	"asset/info/minus_800.xpm"

# elif WIN_HEIGHT <=	2160
#  define INFO_POS 		"asset/info/pos_2160.xpm"
#  define INFO_ROT 		"asset/info/rot_2160.xpm"
#  define INFO_DOT 		"asset/info/dot_2160.xpm"
#  define INFO_COMMA 	"asset/info/comma_2160.xpm"
#  define INFO_MINUS 	"asset/info/minus_2160.xpm"
# endif

/*	menu sel/info-alignment	*/
# if WIN_HEIGHT <=			400
#  define DY				2
#  define LD				30
#  define LX				2.45
#  define LY				15
#  define IX				1.02
#  define IY				4
#  define IY_OFFSET			-3
#  define IDX				1.07
#  define POSX				20
#  define ROTX				22
#  define OFFSET			4
#  define SPACE_OFFSET		0.5
#  define DOT_OFFSET		1.5	

# elif WIN_HEIGHT <=		600
#  define DY				3
#  define LD				53
#  define LX				2.45
#  define LY				20
#  define IX				1.028
#  define IY				8
#  define IY_OFFSET			0
#  define IDX				1.073
#  define POSX				23
#  define ROTX				26
#  define OFFSET			6
#  define SPACE_OFFSET		1.0
#  define DOT_OFFSET		2.0

# elif WIN_HEIGHT <=		800
#  define DY				3		// obj id ht
#  define LD				65		// obj id alignment
#  define LX				2.45	// label alignment	
#  define LY				25		// label height; > == higher
#  define IX				1.035	// info alignment
#  define IY				10		// rot height from pos	
#  define IY_OFFSET			0
#  define IDX				1.072
#  define POSX				26		// pos xpm alignment
#  define ROTX				30		// rot xpm alignment
#  define OFFSET			8		// digit offset
#  define SPACE_OFFSET		1.5		// space after comma
#  define DOT_OFFSET		2.5	

# elif WIN_HEIGHT <=		2160
#  define DY				7	
#  define LD				170		
#  define LX				2.45	
#  define LY				68		
#  define IX				1.035	
#  define IY				37		
#  define IY_OFFSET			0		// info offset from label (gap btw label and info)
#  define IDX				1.066	// info digit
#  define POSX				69		
#  define ROTX				80		
#  define OFFSET			20		
#  define SPACE_OFFSET		4.05
#  define DOT_OFFSET		6.75
# endif

/*	math constant	*/
# define EPSILON			0.00001

/*	ambient	*/
# define AMBIENT_RATIO_MIN	0.0
# define AMBIENT_RATIO_MAX	1.0

/*	colour	*/
# define COL_MIN	0
# define COL_MAX	255

# define BLACK		0x000000  // (0, 0, 0)
# define GREEN		0x00FF00  // (0, 255, 0)
# define YELLOW		0xFFFF00  // (255, 255, 0)
# define BLUE		0x0000FF  // (0, 0, 255)
# define MAGENTA	0xFF00FF  // (255, 0, 255)
# define CYAN		0x00FFFF  // (0, 255, 255)
# define WHITE		0xFFFFFF  // (255, 255, 255)
# define GREY		0x808080  // (128, 128, 128)

/*	vector	*/
# define VEC_MIN	-1
# define VEC_MAX	1

/*	camera	*/
# define FOV_MIN	0
# define FOV_MAX	180
# define DEFOC_ANG	0
# define DEFOC_XX	0
# define DEFOC_XY	0
# define DEFOC_XZ	0
# define DEFOC_YX	0
# define DEFOC_YY	0
# define DEFOC_YZ	0
# define FOCUS_DIST	1

/*	light	*/
# define LIGHT_BRIGHTNESS_MIN	0.0
# define LIGHT_BRIGHTNESS_MAX	1.0
# define LIGHT_RADIUS			0.5	// change to 2 for shadow.rt (default = 0.5)

/*	plane	*/
# define PLANE_X				-8
# define PLANE_Y				8

/*	material	*/
# define MAT_TYPE				DIFFUSE
# define MAT_SPECULAR			0.5
# define MAT_REFLECT			0.5
# define MAT_FUZZ				0.2

/*	sample	*/
# define SAMPLE_SOFT_SHADOW		15  // > == softer shadow
# define SAMPLE_RAY_BOUNCE		5	// > == more realistic lighting
# define SAMPLE_PER_PIXEL		100	// > == smoother img
# define SAMPLE_PREVIEW			2

#endif