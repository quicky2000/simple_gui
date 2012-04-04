#ifndef _SIMPLE_GUI_H_
#define _SIMPLE_GUI_H_

#include "SDL/SDL.h"
#include <stdint.h>

class simple_gui
{
public:
  simple_gui(void);

  void createWindow(uint32_t p_width,uint32_t p_height);

  inline uint32_t getColorCode(uint8_t r,uint8_t g,uint8_t b);
  inline void get_RGB_code(uint32_t p_color,uint8_t & r,uint8_t & g,uint8_t & b);
  inline void refresh(void);

  virtual ~simple_gui(void);
  void setPixel(uint32_t p_x,uint32_t p_y,uint32_t p_color);
  uint32_t get_pixel(uint32_t p_x,uint32_t p_y)const;
private:
  SDL_Surface *m_screen;
  uint32_t m_coef;
};

uint32_t simple_gui::getColorCode(uint8_t r,uint8_t g,uint8_t b)
{
  return SDL_MapRGB(m_screen->format,r,g,b);
}

void simple_gui::get_RGB_code(uint32_t p_color,uint8_t & r,uint8_t & g,uint8_t & b)
{
  SDL_GetRGB(p_color,m_screen->format,&r,&g,&b); 
}

void simple_gui::refresh(void)
{
  SDL_UpdateRect(m_screen,0,0,0,0);
}



#endif /* _SIMPLE_GUI_H_ */
