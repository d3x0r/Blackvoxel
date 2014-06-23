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
 * ZScreen_Options_Mouse.cpp
 *
 *  Created on: 14 juin 2011
 *      Author: laurent
 */

#include "ZScreen_Options_Mouse.h"
#include <GL/glew.h>

ULong ZScreen_Options_Mouse::ProcessScreen(ZGame * GameEnv)
{
  ZVector2f Size;
  ZVector2f Pos;

  Pos.x = 0.0; Pos.y = GameEnv->ScreenResolution.y * 0.05f;

  // Clear Screen

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  GameEnv->GuiManager.RemoveAllFrames();

  // Frames on screen

  ZFrame_FontFrame Frame_MainTitle;
    Frame_MainTitle.SetDisplayText((char *)"MOUSE SETTINGS");
    Frame_MainTitle.SetStyle(GameEnv->TileSetStyles->GetStyle(2));
    Frame_MainTitle.GetTextDisplaySize(&Size);
    Frame_MainTitle.SetPosition(GameEnv->ScreenResolution.x / 2.0f - Size.x / 2.0f , Pos.y );
    Frame_MainTitle.SetSize(Size.x + 1.0,Size.y);
    Frame_MainTitle.TextureNum = 3;
    GameEnv->GuiManager.AddFrame(&Frame_MainTitle);
    Pos.y += Size.y + GameEnv->ScreenResolution.y * 0.10f;

    Pos.y += 32.0f + 16.0f;

  Pos.x = 0.0;
  ZFrame_FontFrame Frame_TitleMouseFactor;
    Frame_TitleMouseFactor.SetStyle(GameEnv->TileSetStyles->GetStyle(2));
    Frame_TitleMouseFactor.SetDisplayText("MOUSE FACTOR  ");
    Frame_TitleMouseFactor.GetTextDisplaySize(&Size);
    Frame_TitleMouseFactor.SetPosition(Pos.x, Pos.y);
    Frame_TitleMouseFactor.SetSize(Size.x + 1.0f, Size.y);
    GameEnv->GuiManager.AddFrame(&Frame_TitleMouseFactor);
    Pos.x += Size.x;

  ZFrame_NumericChoiceBox Frame_MouseFactor;
    Frame_MouseFactor.SetFontTileStyle(GameEnv->TileSetStyles->GetStyle(2));
    Frame_MouseFactor.SetGUITileset(GameEnv->GuiTileset);
    Frame_MouseFactor.SetPosition(Pos.x , Pos.y);
    Frame_MouseFactor.SetParameters(0.1,9.95, GameEnv->Settings_Hardware->Setting_MouseFactor,0.05, 2);
    Frame_MouseFactor.GetTextDisplaySize(&Size);
    Frame_MouseFactor.SetSize(Size.x + 1.0f, Size.y);
    GameEnv->GuiManager.AddFrame(&Frame_MouseFactor);
    Pos.y += 32.0f + GameEnv->ScreenResolution.y * 0.20f;

  ZFrame_FontFrame Frame_Save;
    Frame_Save.SetStyle(GameEnv->TileSetStyles->GetStyle(2));
    Frame_Save.SetDisplayText("SAVE");
    Frame_Save.GetTextDisplaySize(&Size);
    Frame_Save.SetPosition(GameEnv->ScreenResolution.x * 0.9f - Size.x -1.0f, GameEnv->ScreenResolution.y * 0.9f - Size.y);
    Frame_Save.SetSize(Size.x + 1.0f, Size.y);
    GameEnv->GuiManager.AddFrame(&Frame_Save);

    for (bool Loop = true; Loop; )
    {
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      Loop = GameEnv->EventManager.ProcessEvents();

      // if (Frame_MainTitle.Is_MouseClick()) {Loop = false; GameEnv->Settings_Hardware->Save(); exit(0); }


      if (Frame_MouseFactor.Is_ChoiceChanged())
      {
        GameEnv->Settings_Hardware->Setting_MouseFactor = Frame_MouseFactor.GetValue();
      }

      if (Frame_Save.Is_MouseClick()) { Loop = false; }

      GameEnv->GuiManager.Render();
      SDL_GL_SwapBuffers( );
      SDL_Delay(10);

    }
    GameEnv->GuiManager.RemoveAllFrames();

    GameEnv->Settings_Hardware->Save();

  return(CHOICE_QUIT);
}