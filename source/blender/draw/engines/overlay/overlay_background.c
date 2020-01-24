/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Copyright 2020, Blender Foundation.
 */

/** \file
 * \ingroup draw_engine
 */

#include "DRW_render.h"

#include "overlay_private.h"

void OVERLAY_background_cache_init(OVERLAY_Data *vedata)
{
  OVERLAY_PassList *psl = vedata->psl;
  DefaultTextureList *dtxl = DRW_viewport_texture_list_get();

  DRWState state = DRW_STATE_WRITE_COLOR;
  DRW_PASS_CREATE(psl->background_ps, state);

  GPUShader *sh = OVERLAY_shader_background();
  DRWShadingGroup *grp = DRW_shgroup_create(sh, psl->background_ps);
  DRW_shgroup_uniform_block(grp, "globalsBlock", G_draw.block_ubo);
  DRW_shgroup_uniform_texture_ref(grp, "colorBuf", &dtxl->color);
  DRW_shgroup_call_procedural_triangles(grp, NULL, 1);
}

void OVERLAY_background_draw(OVERLAY_Data *vedata)
{
  OVERLAY_PassList *psl = vedata->psl;

  if (DRW_state_is_fbo()) {
    /* TODO(fclem) Drawing the background inside the overlay buffer will become a problem
     * once we cache the overlay result.
     * Because the render can change / refine the alpha chanel. */
    DRW_draw_pass(psl->background_ps);
  }
}
