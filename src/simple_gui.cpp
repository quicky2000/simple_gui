#include "simple_gui.h"
#include <iostream>
#include <assert.h>

//------------------------------------------------------------------------------
simple_gui::simple_gui(void):
  m_screen(NULL),
  m_coef(20)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
      std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl ;
    }
}

//------------------------------------------------------------------------------
void simple_gui::createWindow(uint32_t p_width,uint32_t p_height)
{
  const SDL_VideoInfo *l_video_info = SDL_GetVideoInfo();
  
  assert(l_video_info);
#if SDL_COMPILEDVERSION >= SDL_VERSIONNUM(1, 2, 14)
  std::cout << "Current resolution : " << l_video_info->current_w << "x" << l_video_info->current_h << " with Pixel Format " << ((uint32_t)l_video_info->vfmt->BitsPerPixel) << " bits per pixel" << std::endl ;
  m_coef = (l_video_info->current_w / p_width < l_video_info->current_h / p_height ? l_video_info->current_w / p_width : l_video_info->current_h / p_height );
#else
  m_coef = (1900 / p_width < 1130 / p_height ? 1900 / p_width : 1130 / p_height );
#endif
  if(!m_coef) m_coef =1 ;
  std::cout << "coef = " << m_coef << std::endl ;
  
  
  p_width = p_width * m_coef;
  p_height = p_height * m_coef;
  m_screen = SDL_SetVideoMode(p_width,p_height,32,SDL_SWSURFACE);
  if(m_screen == NULL)
    {
      std::cout << "Unable to set video mode to " << p_width << "*"<< p_height << "*32" << std::endl ;
      SDL_Quit();
    }
}

//------------------------------------------------------------------------------
simple_gui::~simple_gui(void)
{
  SDL_Quit();
}

//------------------------------------------------------------------------------
void simple_gui::setPixel(uint32_t p_x,uint32_t p_y,uint32_t p_color)
  {
    if ( SDL_MUSTLOCK(m_screen) )
      {
	if ( SDL_LockSurface(m_screen) < 0 )
	  {
	    exit(-1);
	  }
      }
    for(uint32_t l_x = p_x * m_coef;l_x < m_coef *(p_x + 1);++l_x)
      {
	for(uint32_t l_y = p_y * m_coef;l_y < m_coef *(p_y + 1);++l_y)
	  {
	    uint32_t *l_bufp = (uint32_t *)m_screen->pixels + l_y * m_screen->pitch/4 + l_x;
	    *l_bufp = p_color;
	  }
      }
	  
    if ( SDL_MUSTLOCK(m_screen) )
      {
	SDL_UnlockSurface(m_screen);
      }

  }

//EOF
