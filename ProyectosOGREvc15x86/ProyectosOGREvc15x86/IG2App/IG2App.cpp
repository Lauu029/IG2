#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	//else if (evt.keysym.sym == SDLK_???)

	return true;
}

void IG2App::shutdown()
{
	mShaderGenerator->removeSceneManager(mSM);
	mSM->removeRenderQueueListener(mOverlaySystem);

	mRoot->destroySceneManager(mSM);

	delete mTrayMgr;  mTrayMgr = nullptr;
	delete mCamMgr; mCamMgr = nullptr;

	// do not forget to call the base 
	IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
	// do not forget to call the base first
	IG2ApplicationContext::setup();

	mSM = mRoot->createSceneManager();

	// register our scene with the RTSS
	mShaderGenerator->addSceneManager(mSM);

	mSM->addRenderQueueListener(mOverlaySystem);

	mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	addInputListener(mTrayMgr);

	addInputListener(this);
	setupScene();
}

void IG2App::setupScene(void)
{
	// create the camera
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	//Luz frontal
	mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();

	//Luz desde abajo
	//mLightNode->setDirection(Ogre::Vector3(0, 1, 0));  //vec3.normalise();

	//Luz lateral
	//mLightNode->setDirection(Ogre::Vector3(1, 0, 0));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	//------------------------------------------------------------------------

	// finally something to render

	//Sinbad
	Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
	mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
	mSinbadNode->attachObject(ent);

	mSinbadNode->setPosition(100, 50, -300);
	mSinbadNode->setScale(20, 20, 20);
	//mSinbadNode->yaw(Ogre::Degree(-45));
	//mSinbadNode->showBoundingBox(true);
	//mSinbadNode->setVisible(false);

	//------------------------------------------------------------------------

	//Espada
	//Ogre::Entity* ent = mSM->createEntity("Sword.mesh");

	//mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	//mSinbadNode->attachObject(ent);

	////mSinbadNode->setPosition(400, 100, -300);
	//mSinbadNode->setScale(100, 100, 100);
	////mSinbadNode->yaw(Ogre::Degree(-45));
	////mSinbadNode->showBoundingBox(true);
	////mSinbadNode->setVisible(false);
	//------------------------------------------------------------------------
	//Casco
	//Ogre::Entity* ent = mSM->createEntity("DamagedHelmet.mesh");

	//mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	//mSinbadNode->attachObject(ent);

	////mSinbadNode->setPosition(400, 100, -300);
	//mSinbadNode->setScale(100, 100, 100);
	////mSinbadNode->yaw(Ogre::Degree(-45));
	////mSinbadNode->showBoundingBox(true);
	////mSinbadNode->setVisible(false);
	//------------------------------------------------------------------------
	//Cabeza de ogre
	/*Ogre::Entity* ent = mSM->createEntity("ogrehead.mesh");

	mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	mSinbadNode->attachObject(ent);

	//mSinbadNode->setPosition(400, 100, -300);
	mSinbadNode->setScale(10, 10, 10);
	//mSinbadNode->yaw(Ogre::Degree(-45));
	//mSinbadNode->showBoundingBox(true);
	//mSinbadNode->setVisible(false);*/
	//------------------------------------------------------------------------
	//Cabeza
	/*Ogre::Entity* ent = mSM->createEntity("facial.mesh");

	mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	mSinbadNode->attachObject(ent);

	//mSinbadNode->setPosition(400, 100, -300);
	mSinbadNode->setScale(10, 10, 10);
	//mSinbadNode->yaw(Ogre::Degree(-45));
	//mSinbadNode->showBoundingBox(true);
	//mSinbadNode->setVisible(false);*/
	//------------------------------------------------------------------------
	//Baño romano 
	Ogre::Entity* sc = mSM->createEntity("RomanBathLower.mesh");

	Ogre::SceneNode* mBathNode = mSM->getRootSceneNode()->createChildSceneNode();
	mBathNode->attachObject(sc);

	Ogre::Entity* roof = mSM->createEntity("RomanBathUpper.mesh");

	mBathNode = mSM->getRootSceneNode()->createChildSceneNode();
	mBathNode->attachObject(roof);
	
	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);


	//------------------------------------------------------------------------

}

