//  SuperTux
//  Copyright (C) 2018 Ingo Ruhnke <grumbel@gmail.com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "video/gl/gl20_context.hpp"

#include "video/glutil.hpp"
#include "video/color.hpp"
#include "video/gl/gl_texture.hpp"

#ifndef USE_OPENGLES2

GL20Context::GL20Context()
{
}

GL20Context::~GL20Context()
{
}

void
GL20Context::bind()
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glEnable(GL_BLEND);
}

void
GL20Context::ortho(float width, float height, bool vflip)
{
  assert_gl();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (vflip)
  {
    glOrtho(0, width,
            height, 0,
            -1, 1);
  }
  else
  {
    glOrtho(0, width,
            0, height,
            -1, 1);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  assert_gl();
}

void
GL20Context::blend_func(GLenum src, GLenum dst)
{
  glBlendFunc(src, dst);
}

void
GL20Context::set_positions(const float* data, size_t size)
{
  assert_gl();
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, data);
  assert_gl();
}

void
GL20Context::set_texcoords(const float* data, size_t size)
{
  assert_gl();
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, 0, data);
  assert_gl();
}

void
GL20Context::set_texcoord(float u, float v)
{
  assert_gl();
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  assert_gl();
}

void
GL20Context::set_colors(const float* data, size_t size)
{
  assert_gl();
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(4, GL_FLOAT, 0, data);
  assert_gl();
}

void
GL20Context::set_color(const Color& color)
{
  assert_gl();
  glDisableClientState(GL_COLOR_ARRAY);
  glColor4f(color.red, color.green, color.blue, color.alpha);
  assert_gl();
}

void
GL20Context::bind_texture(const Texture& texture, const Texture* displacement_texture)
{
  assert_gl();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, static_cast<const GLTexture&>(texture).get_handle());
  assert_gl();
}

void
GL20Context::bind_no_texture()
{
  assert_gl();
  glDisable(GL_TEXTURE_2D);
  assert_gl();
}

void
GL20Context::draw_arrays(GLenum type, GLint first, GLsizei count)
{
  assert_gl();
  glDrawArrays(type, first, count);
  assert_gl();
}

#endif

/* EOF */
