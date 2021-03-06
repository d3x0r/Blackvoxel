/*
 * This file is part of Blackvoxel.
 *
 * Copyright 2010-2014 Laurent Thiebaut & Olivia Merle
 *
 * Blackvoxel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Blackvoxel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
 * ZScreen_Main.h
 *
 *  Created on: 28 mai 2011
 *      Author: laurent
 */

#ifndef Z_ZSCREEN_MAIN_H
#define Z_ZSCREEN_MAIN_H

//#ifndef Z_ZSCREEN_MAIN_H
//#  include "ZScreen_Main.h"
//#endif

#ifndef Z_ZGUI_H
#  include "ZGui.h"
#endif

#ifndef Z_GUI_FONTFRAME_H
#  include "ZGui_FontFrame.h"
#endif

#ifndef Z_ZGAME_H
#  include "ZGame.h"
#endif

class ZScreen_Main : public ZScreen
{
private:
	  ZFrame TitleBackground;
  ZFrame Title;
    ZVector2f Title_Size;
  ZFrame_FontFrame Frame_Version;
    ZVector2f Version_Size;
  ZFrame_FontFrame Frame_PlayGame;
    ZVector2f PlayGame_Size;
  ZFrame_FontFrame Frame_Options;
    ZVector2f Options_Size;
  ZFrame_FontFrame Frame_Quit;
    ZVector2f Frame_Size;

  public:
    enum { CHOICE_QUIT, CHOICE_OPTIONS, CHOICE_PLAYGAME, CHOICE_NONE };

    virtual ULong ProcessScreen(ZGame * GameEnv);
};




#endif /* Z_ZSCREEN_MAIN_H */
