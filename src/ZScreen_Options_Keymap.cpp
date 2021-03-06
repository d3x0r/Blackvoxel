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
 * ZScreen_Options_Keymap.cpp
 *
 *  Created on: 15 juin 2011
 *      Author: laurent
 */

#include "ZScreen_Options_Keymap.h"
#include <GL/glew.h>

ULong ZScreen_Options_Keymap::ProcessScreen(ZGame * GameEnv)
{
  ZVector2f Size,Size2;
  ZVector2f Pos;
  ZVector2f Start;
  ULong i;

  if( GameEnv->prior_page_up != GameEnv->page_up )
  {
	  GameEnv->prior_page_up = GameEnv->page_up;
  Start.x = GameEnv->ScreenResolution.x * 0.05f;
  Start.y = GameEnv->ScreenResolution.y * 0.05f;

  Pos.x = Start.x; Pos.y = Start.y;

  // Clear Screen

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  GameEnv->GuiManager.RemoveAllFrames();

  // Frames on screen

    Frame_MainTitle.SetDisplayText((char *)"KEYMAP SETTINGS ");
    Frame_MainTitle.SetStyle(GameEnv->TileSetStyles->GetStyle(2));
    Frame_MainTitle.GetTextDisplaySize(&Size);
    Frame_MainTitle.SetPosition(GameEnv->ScreenResolution.x / 2.0f - Size.x / 2.0f , Pos.y );
    Frame_MainTitle.SetSize(Size.x + 1.0,Size.y);
    Frame_MainTitle.TextureNum = 3;
    GameEnv->GuiManager.AddFrame(&Frame_MainTitle);
    Pos.y += Size.y + GameEnv->ScreenResolution.y * 0.10f;
    Pos.y += 32.0f + 16.0f;


  Title[0] = "MOVE FORWARD";   Value[0] = &GameEnv->Settings_Hardware->Setting_Key_MoveForward;
  Title[1] = "MOVE BACKWARD";  Value[1] = &GameEnv->Settings_Hardware->Setting_Key_MoveBackward;
  Title[2] = "MOVE LEFT";      Value[2] = &GameEnv->Settings_Hardware->Setting_Key_MoveLeft;
  Title[3] = "MOVE RIGHT";     Value[3] = &GameEnv->Settings_Hardware->Setting_Key_MoveRight;
  Title[4] = "MOVE UP";        Value[4] = &GameEnv->Settings_Hardware->Setting_Key_MoveUp;
  Title[5] = "MOVE DOWN";      Value[5] = &GameEnv->Settings_Hardware->Setting_Key_MoveDown;
  Title[6] = "JUMP";           Value[6] = &GameEnv->Settings_Hardware->Setting_Key_Jump;
  Title[7] = "INVENTORY";      Value[7] = &GameEnv->Settings_Hardware->Setting_Key_Inventory;

  float MaxTitleWidth = 0.0;
  for(i=0;i<NumLines;i++)
  {
    Pos.x = Start.x;
    if (GameEnv->ScreenResolution.y > 800.0f ) KeyTitle[i].SetStyle(GameEnv->TileSetStyles->GetStyle(2));
    else                                      KeyTitle[i].SetStyle(GameEnv->TileSetStyles->GetStyle(3));
    KeyTitle[i].SetDisplayText(Title[i]);
    KeyTitle[i].GetTextDisplaySize(&Size);
    KeyTitle[i].SetPosition(Pos.x, Pos.y);
    KeyTitle[i].SetSize(Size.x,Size.y);
    GameEnv->GuiManager.AddFrame(&KeyTitle[i]);
    Position[i].x = Pos.x; Position[i].y = Pos.y;
    if (Size.x > MaxTitleWidth) MaxTitleWidth = Size.x;

    KeyChooser[i].SetFontTileStyle(GameEnv->TileSetStyles->GetStyle(3));
    KeyChooser[i].GetTextDisplaySize(&Size2);
    KeyChooser[i].SetPosition(800.0f,Pos.y + Size.y /2.0f - Size2.y/2.0f);
    KeyChooser[i].SetSize(Size2.x,Size2.y);
    KeyChooser[i].SetTexture(5);
    KeyChooser[i].SetKey(*Value[i]);
    KeyChooser[i].Show_Frame(true);
    GameEnv->GuiManager.AddFrame(&KeyChooser[i]);
    Pos.y = Pos.y + Size.y;
  }


  for (i=0;i<NumLines;i++) { KeyChooser[i].SetPosition(Position[i].x + MaxTitleWidth + GameEnv->ScreenResolution.x / 15.0f,Position[i].y + Size.y /2.0f - Size2.y/2.0f); }


    Frame_Save.SetStyle(GameEnv->TileSetStyles->GetStyle(2));
    Frame_Save.SetDisplayText("SAVE");
    Frame_Save.GetTextDisplaySize(&Size);
    Frame_Save.SetPosition(GameEnv->ScreenResolution.x * 0.9f - Size.x -1.0f, GameEnv->ScreenResolution.y * 0.9f - Size.y);
    Frame_Save.SetSize(Size.x + 1.0f, Size.y);
    GameEnv->GuiManager.AddFrame(&Frame_Save);
}

    //for (bool Loop = true; Loop; )
    {
      //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      //Loop = GameEnv->EventManager.ProcessEvents();

      // if (Frame_MainTitle.Is_MouseClick()) {Loop = false; GameEnv->Settings_Hardware->Save(); exit(0); }

      for (i=0;i<NumLines;i++) if ( KeyChooser[i].Is_KeyChanged() ) *Value[i] = KeyChooser[i].GetKey();



      if (Frame_Save.Is_MouseClick()) { return CHOICE_QUIT; }

      //GameEnv->GuiManager.Render();
      //SDL_GL_SwapBuffers( );
	  //SDL_GL_SwapWindow(GameEnv->screen);
	  //SDL_Delay(10);

    }
    //GameEnv->GuiManager.RemoveAllFrames();

    //GameEnv->Settings_Hardware->Save();

  return -1;
}
