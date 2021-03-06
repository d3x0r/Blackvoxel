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
 * ZVoxelProcessor.h
 *
 *  Created on: 26 mars 2011
 *      Author: laurent
 */

#ifndef Z_ZVOXELPROCESSOR_H
#define Z_ZVOXELPROCESSOR_H

//#ifndef Z_ZVOXELPROCESSOR_H
//#  include "ZVoxelProcessor.h"
//#endif

#ifndef Z_ZTYPES_H
#  include "z/ZTypes.h"
#endif

#ifndef Z_ZOBJECT_H
#  include "z/ZObject.h"
#endif

#ifndef Z_ZWORLD_H
#  include "ZWorld.h"
#endif

#ifndef Z_ZACTORPHYSICS_H
#  include "ZActorPhysics.h"
#endif

#ifndef _SDL_thread_h
#  include "SDL2/SDL_thread.h"
#endif

#ifndef A_COMPILESETTINGS_H
#  include "ACompileSettings.h"
#endif

#ifndef Z_ZVOXELREACTOR_H
#  include "ZVoxelReactor.h"
#endif

#ifndef Z_ZHIGHPERFTIMER_H
#  include "ZHighPerfTimer.h"
#endif

#ifndef Z_ZEGMYSCATTER_H
#  include "ZEgmyScatter.h"
#endif

class ZGame;

class test {};

class ZVoxelProcessor : public ZObject
{
  public:
	bool ThreadProcessing; // set when thread is dispatched processing
  protected:
    ZVoxelWorld * World;
    ZActorPhysicEngine * PhysicEngine;
    bool ThreadContinue;
    void * Thread[6];
    ZGame * GameEnv;
    ZVoxelReactor VoxelReactor;
    ZEgmyScatter  EgmyScatter;
public:
    ZHighPerfTimer Timer;
    ZHighPerfTimer Timer_Compute;
protected:

    static int thread_func(void * Data);


    void MakeSectorTasks(ZVoxelSector * Sector);
    void MakeTasks();


    ZVector3L Player_Sector;
    ZVector3d Player_Position;
    ZVector3L Player_Voxel;

    double SectorEjectDistance;
  public:
    ZVoxelProcessor()
    {
      World = 0;
      PhysicEngine = 0;
      SectorEjectDistance = 1000000.0;
      Thread[0] = 0;
      ThreadContinue = false;
      GameEnv = 0;
    }

    ~ZVoxelProcessor()
    {

    }

    void SetWorld(ZVoxelWorld * World) { this->World = World; }
    void SetGameEnv(ZGame * GameEnv) { this->GameEnv = GameEnv; }
    void SetSectorEjectDistance(double SectorEjectDistance) { this->SectorEjectDistance = SectorEjectDistance; }

    void SetPlayerPosition(double x,double y, double z)
    {
		if( Player_Position )
		{
      Player_Position.x = x;
      Player_Position.y = y;
      Player_Position.z = z;
	  Player_Sector.x = (Long) (x/(GlobalSettings.VoxelBlockSize * 16.0));
      Player_Sector.y = (Long) (y/(GlobalSettings.VoxelBlockSize * 64.0));
      Player_Sector.z = (Long) (z/(GlobalSettings.VoxelBlockSize * 16.0));
      Player_Voxel.x = (Long)  (x/GlobalSettings.VoxelBlockSize);
      Player_Voxel.y = (Long)  (y/GlobalSettings.VoxelBlockSize);
      Player_Voxel.z = (Long)  (z/GlobalSettings.VoxelBlockSize);
		}
    }

    void Start()
    {
      VoxelReactor.Init(this->GameEnv);
      ThreadContinue = true;
      Thread[0] = (SDL_Thread * )SDL_CreateThread(thread_func, "thread_func", this);
      //Thread[1] = (SDL_Thread * )SDL_CreateThread(thread_func, "thread_func", this);
      //Thread[2] = (SDL_Thread * )SDL_CreateThread(thread_func, "thread_func", this);
      //Thread[3] = (SDL_Thread * )SDL_CreateThread(thread_func, "thread_func", this);
    }

    void End()
    {
      ThreadContinue = false;
	  while( ThreadProcessing )
			  Relinquish();
      if (Thread[0]) SDL_WaitThread((SDL_Thread*)Thread[0], NULL);

    }
};


#endif /* ZVOXELPROCESSOR_H_ */
