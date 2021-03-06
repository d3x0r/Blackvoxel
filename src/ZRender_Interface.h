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
#ifndef Z_ZRENDER_INTERFACE_H
#define Z_ZRENDER_INTERFACE_H

//#ifndef Z_ZRENDER_BASIC_H
//#  include "ZRender_Basic.h"
//#endif

#ifndef Z_ZWORLD_H
#  include "ZWorld.h"
#endif

#ifndef Z_ZVOXELTYPE_H
#  include "ZVoxelType.h"
#endif

#ifndef Z_ZTEXTUREMANAGER_H
#  include "ZTextureManager.h"
#endif

#ifndef Z_ZSECTORSPHERE_H
#include "ZSectorSphere.h"
#endif

#ifndef Z_ZRENDER_SORTER_H
#  include "ZRender_Sorter.h"
#endif

#include "ZActor_Player.h"
#include "ZVoxelCuller.h"
#include "GL/glew.h"
extern GLuint TextureName[1024];



class ZRender_Interface_displaydata : public ZObject
{
  public:
    GLint DisplayList_Regular[6];
    GLint DisplayList_Transparent[6];

    ZRender_Interface_displaydata()
    {
		for( int i = 0; i < 6; i++ )
		{
      DisplayList_Regular[i] = 0;
      DisplayList_Transparent[i] = 0;
		}

    }
    ~ZRender_Interface_displaydata()
    {
		for( int i = 0; i < 6; i++ )
		{
			  if (DisplayList_Regular[i])     glDeleteLists(DisplayList_Regular[i], 1);
			  DisplayList_Regular[i] = 0;
			  if (DisplayList_Transparent[i]) glDeleteLists(DisplayList_Transparent[i], 1);
			  DisplayList_Transparent[i] = 0;
		}
    }

};

class ZGame;

class ZRender_Interface
{
  protected:
    ZVoxelWorld * World;
    ZVoxelTypeManager * VoxelTypeManager;
    ZTextureManager  * TextureManager;
public:
	PTRSZVAL current_gl_camera;
    ZCamera     * Camera;
protected:
	ZActor      * Actor;  // where the camera came from really...
    ZRayCast_out * PointedVoxel;
    ZRadius_Zoning RadiusZones;

    Long hRenderRadius;
    Long vRenderRadius;

    ULong Stat_RenderDrawFaces;
    ULong Stat_FaceTop;
    ULong Stat_FaceBottom;
    ULong Stat_FaceLeft;
    ULong Stat_FaceRight;
    ULong Stat_FaceFront;
    ULong Stat_FaceBack;

    ULong Stat_RefreshWaitingSectorCount;
    Long RefreshWaiters[64];
    Long RefreshToDo[64];

    // Display Dimension and aspect ratio

    ZVector2L ViewportResolution;
    double    VerticalFOV;
    double    FocusDistance;
    double    PixelAspectRatio;
    double    Optimisation_FCullingFactor;

    // Computed by render()
    double Frustum_V;
    double Frustum_H;
    double Aspect_Ratio;
    double Frustum_CullingLimit;
    ZVoxelCuller *voxelCuller;

  public:

    ZGame * GameEnv;

    ZSectorSphere SectorSphere;

    ULong BvProp_CrossHairType;
    bool  BvProp_DisplayCrossHair;
    bool  BvProp_DisplayVoxelSelector;

    ZRender_Sorter RenderSorter;

    ZRender_Interface()
    {
      hRenderRadius = 1;  // 8
      vRenderRadius = 1;  // 3
      World = 0;
      VoxelTypeManager = 0;
      TextureManager = 0;
      Stat_RenderDrawFaces = 0;
      Stat_FaceTop = 0;
      Stat_FaceFront = 0;
      Stat_FaceRight = 0;
      Stat_FaceLeft = 0;
      Stat_FaceBottom = 0;
      Stat_FaceBack = 0;
      PointedVoxel = 0;
      Camera = 0;
      GameEnv = 0;
      Stat_RefreshWaitingSectorCount = 0;
      BvProp_CrossHairType = 1;
      BvProp_DisplayCrossHair     = true;
      BvProp_DisplayVoxelSelector = true;
      ViewportResolution.x = 1920;
      ViewportResolution.y = 1200;
      VerticalFOV = 63.597825649;
      FocusDistance = 50.0;
      PixelAspectRatio = 1.0;
      Optimisation_FCullingFactor = 1.0;

      Frustum_V = 0.0;
      Frustum_H = 0.0;
      Aspect_Ratio = 0.0;
      Frustum_CullingLimit = 0.0;
    }

    void SetWorld           ( ZVoxelWorld * World );
    void SetCamera          ( ZCamera * Camera );
	void SetActor           ( ZActor * Actor );

    void SetVoxelTypeManager( ZVoxelTypeManager * Manager );
    void SetTextureManager  ( ZTextureManager * Manager ) { this->TextureManager = Manager; }
    void SetPointedVoxel    ( ZRayCast_out * Pvoxel)         { this->PointedVoxel = Pvoxel; }
    void SetViewportResolution(ZVector2L &Resolution) { ViewportResolution = Resolution; }
    void SetVerticalFOV(double VFov)                  { VerticalFOV = VFov; }
    void SetPixelAspectRatio(double AspectRatio = 1.0){ PixelAspectRatio = AspectRatio; }
    void SetSectorCullingOptimisationFactor(double CullingOptimisationFactor = 1.0) { Optimisation_FCullingFactor = CullingOptimisationFactor; }



    void Init();
    void Cleanup() { }
    Bool LoadVoxelTexturesToGPU(PTRSZVAL psvInit);
    Bool LoadTexturesToGPU(PTRSZVAL psvInit);


    void Render_DebugLine       ( ZVector3d & Start, ZVector3d & End);
	void Render_EmptySector(int x, int y, int z, float r, float g, float b);

	void Render_VoxelSelector   (ZVoxelCoords * SelectedVoxel, float r, float g, float b);
	void EmitFaces				( ZVoxelType ** VoxelTypeTable, UShort &VoxelType, UShort &prevVoxelType, ULong info
							  , Long x, Long y, Long z
							  , Long Sector_Display_x, Long Sector_Display_y, Long Sector_Display_z );
    void MakeSectorRenderingData(ZVoxelSector * Sector);
    void MakeSectorRenderingData_Sorted(ZVoxelSector * Sector);
    virtual void Render( bool use_external_matrix ) = 0;
	virtual ZVoxelCuller *GetCuller( ) = 0;



    void SetRenderSectorRadius(Long Horizontal, Long Vertical)
    {
      hRenderRadius = Horizontal;
      vRenderRadius = Vertical;
      RadiusZones.SetSize(hRenderRadius * 2 + 1, vRenderRadius * 2 + 1,hRenderRadius * 2 + 1);
      // RadiusZones.DrawZones( 5.0, 3.5, 3.0, 2.0 );
      RadiusZones.DrawZones(5.0,1);
      RadiusZones.DrawZones(3.5,2);
      RadiusZones.DrawZones(3.0,3);
      RadiusZones.DrawZones(2.0,4);
      //RadiusZones.DebugOut();
      SectorSphere.Init(Horizontal, Vertical);
    }

    void SetGameEnv( ZGame * GameEnv ) { this->GameEnv = GameEnv;  }

    void FreeDisplayData(ZVoxelSector * Sector);

    // void RenderSector2(ZVoxelSector * Sector);

    inline bool Is_PointVisible(ZMatrix &TransformParam, ZVector3d * const Point)
    {
      ZVector3d Cv;
	  ZVector3d Cv2 = *Point - TransformParam.origin();
      bool Visible;
	  return true;
	  TransformParam.ApplyInverseRotation( Cv, Cv2 );

      // Translation and Rotation
      //Cv.Transform(TransformParam);

      // Projection

      Cv.x = Cv.x / Cv.z * FocusDistance;  // Number replaced by FocusDistance was 50.0
      Cv.y = Cv.y / Cv.z * FocusDistance;

      // Visibility test

      Visible = (
                     (Cv.z > 0.0)
                  && (Cv.x < Frustum_CullingLimit && Cv.x >-Frustum_CullingLimit) // Number replaced by Frustum_CullingLimit was 50.0
                  && (Cv.y < Frustum_CullingLimit && Cv.y >-Frustum_CullingLimit) //
                );

      return(Visible);
    }





    void ComputeAndSetAspectRatio(double VerticalFOV, double PixelAspectRatio, ZVector2L & ViewportResolution);

};


#endif
