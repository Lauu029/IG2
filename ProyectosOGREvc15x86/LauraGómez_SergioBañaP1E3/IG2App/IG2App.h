#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "Entity.h"
#include "checkML.h"
class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

  void CreateBombaRioSinbadScene();

  void CreateSinbadScene();

  //void createPlanetAvion();

  //void createReloj();

  //void createNoria();

  //void compuebaColisiones();


  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSinbadNode = nullptr;

  //scenes
  //Ogre::SceneNode* sReloj = nullptr;
  //Ogre::SceneNode* sNoria = nullptr;
  //Ogre::SceneNode* sAvion = nullptr;
  Ogre::SceneNode* sSinbad = nullptr;
  Ogre::SceneNode* sBomba = nullptr;

  //clock
  //Ogre::SceneNode* mClock = nullptr;
  //Ogre::SceneNode* mHours = nullptr;

  //drones
  //int nNumDron = 0;
  //Dron* mEnt_dron = nullptr;
  //std::vector<pair<SceneNode*, Dron*>> mDronesAvispa;
  //Ogre::SceneNode* mAvionFicticio = nullptr;

  OgreBites::CameraMan* mCamMgr = nullptr;
  //OgreBites::Label* l;
};

#endif
