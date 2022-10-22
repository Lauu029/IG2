#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "Entity.h"
class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

  void createPlanetAvion();

  void createReloj();

  void createNoria();

  void compuebaColisiones();
  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSinbadNode = nullptr;
  Ogre::SceneNode* sReloj = nullptr;
  Ogre::SceneNode* sNoria = nullptr;
  Ogre::SceneNode* sAvion = nullptr;
  Ogre::SceneNode* Clock = nullptr;
  Ogre::SceneNode* Hours = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;
  Ogre::SceneNode* avionFicticio = nullptr;
  std::vector<SceneNode*> dronesAvispa; 
  OgreBites::Label* l;
};

#endif
