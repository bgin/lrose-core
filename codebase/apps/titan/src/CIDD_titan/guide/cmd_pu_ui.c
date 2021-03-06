/*
 * cmd_pu_ui.c - User interface object initialization functions.
 * This file was generated by `gxv' from `cmd_pu.G'.
 * DO NOT EDIT BY HAND.
 */

#include <stdio.h>
#include <sys/param.h>
#include <sys/types.h>
#include <xview/xview.h>
#include <xview/canvas.h>
#include <xview/panel.h>
#include <xview/scrollbar.h>
#include <xview/svrimage.h>
#include <xview/termsw.h>
#include <xview/text.h>
#include <xview/tty.h>
#include <xview/xv_xrect.h>
#include "cmd_pu_ui.h"

/*
 * Initialize an instance of object `cmd_pu'.
 */
cmd_pu_cmd_pu_objects *
cmd_pu_cmd_pu_objects_initialize(cmd_pu_cmd_pu_objects *ip, Xv_opaque owner)
{
	if (!ip && !(ip = (cmd_pu_cmd_pu_objects *) calloc(1, sizeof (cmd_pu_cmd_pu_objects))))
		return (cmd_pu_cmd_pu_objects *) NULL;
	if (!ip->cmd_pu)
		ip->cmd_pu = cmd_pu_cmd_pu_cmd_pu_create(ip, owner);
	if (!ip->controls1)
		ip->controls1 = cmd_pu_cmd_pu_controls1_create(ip, ip->cmd_pu);
	if (!ip->cmd_st)
		ip->cmd_st = cmd_pu_cmd_pu_cmd_st_create(ip, ip->controls1);
	return ip;
}

/*
 * Create object `cmd_pu' in the specified instance.
 */
Xv_opaque
cmd_pu_cmd_pu_cmd_pu_create(cmd_pu_cmd_pu_objects *ip, Xv_opaque owner)
{
	Xv_opaque	obj;
	
	obj = xv_create(owner, FRAME_CMD,
		XV_KEY_DATA, INSTANCE, ip,
		XV_WIDTH, 79,
		XV_HEIGHT, 71,
		XV_LABEL, "Command Menu",
		XV_SHOW, FALSE,
		FRAME_SHOW_FOOTER, FALSE,
		FRAME_SHOW_RESIZE_CORNER, FALSE,
		FRAME_CMD_PUSHPIN_IN, FALSE,
		NULL);
	xv_set(xv_get(obj, FRAME_CMD_PANEL), WIN_SHOW, FALSE, NULL);
	return obj;
}

/*
 * Create object `controls1' in the specified instance.
 */
Xv_opaque
cmd_pu_cmd_pu_controls1_create(cmd_pu_cmd_pu_objects *ip, Xv_opaque owner)
{
	Xv_opaque	obj;
	
	obj = xv_create(owner, PANEL,
		XV_KEY_DATA, INSTANCE, ip,
		XV_X, 0,
		XV_Y, 0,
		XV_WIDTH, WIN_EXTEND_TO_EDGE,
		XV_HEIGHT, WIN_EXTEND_TO_EDGE,
		WIN_BORDER, FALSE,
		NULL);
	return obj;
}

/*
 * Create object `cmd_st' in the specified instance.
 */
Xv_opaque
cmd_pu_cmd_pu_cmd_st_create(cmd_pu_cmd_pu_objects *ip, Xv_opaque owner)
{
	extern void		cmd_proc(Panel_item, int, Event *);
	Xv_opaque	obj;
	
	obj = xv_create(owner, PANEL_CHOICE,
		XV_KEY_DATA, INSTANCE, ip,
		XV_X, 0,
		XV_Y, 4,
		PANEL_CHOICE_NCOLS, 1,
		PANEL_LAYOUT, PANEL_HORIZONTAL,
		PANEL_CHOOSE_NONE, FALSE,
		PANEL_NOTIFY_PROC, cmd_proc,
		PANEL_CHOICE_STRING, 0, "Item",
		NULL);
	return obj;
}

