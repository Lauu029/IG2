#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneNode.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	if (evt.keysym.sym == SDLK_g) {
		Clock->roll(Ogre::Degree(5));
	}
	if (evt.keysym.sym == SDLK_h) {
		Hours->yaw(Ogre::Degree(5));
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

	////Sinbad
	//Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
	//mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
	//mSinbadNode->attachObject(ent);

	//mSinbadNode->setPosition(100, 50, -300);
	//mSinbadNode->setScale(20, 20, 20);
	////mSinbadNode->yaw(Ogre::Degree(-45));
	////mSinbadNode->showBoundingBox(true);
	////mSinbadNode->setVisible(false);


	//Reloj
	//Clock = mSM->getRootSceneNode()->createChildSceneNode();
	//Hours = Clock->createChildSceneNode();

	//float increase = 360.0 / 12;
	//for (size_t i = 0; i < 12; i++)
	//{
	//	Ogre::Entity* Sphere = mSM->createEntity("uv_sphere.mesh");
	//	Ogre::SceneNode* Hour = Hours->createChildSceneNode("Hora " + std::to_string(i));
	//	Hour->setScale(.5, .5, .5);

	//	Hour->attachObject(Sphere);
	//	Hour->setPosition(250 * Ogre::Math::Cos(Ogre::Degree(increase * i)), 250 * Ogre::Math::Sin(Ogre::Degree(increase * i)), 0);
	//	/*if (i % 2)
	//		mSM->getSceneNode("Hora " + std::to_string(i))->setScale(.2, .2, .2);*/
	//}
	////Agujas
	//Ogre::Entity* agujaHoras = mSM->createEntity("cube.mesh");
	//Ogre::SceneNode* aguja = Clock->createChildSceneNode("Horas");
	//aguja->setScale(.25, 1.6, .05);
	//aguja->setPosition(65, 0, 0);
	//aguja->roll(Ogre::Degree(-90));

	//aguja->attachObject(agujaHoras);

	//Ogre::Entity* agujaMinutos = mSM->createEntity("cube.mesh");
	//Ogre::SceneNode* agujaM = Clock->createChildSceneNode("Minutos");
	//agujaM->setScale(.15, 2, .05);
	//agujaM->setPosition(0, 65, 0);

	//agujaM->attachObject(agujaMinutos);

	//Ogre::Entity* agujaSegundos = mSM->createEntity("cube.mesh");
	//Ogre::SceneNode* agujaS = Clock->createChildSceneNode("Segundos");
	//agujaS->setScale(.05, 2, .05);
	//agujaS->setPosition(-70, -60, 0);
	//agujaS->roll(Ogre::Degree(125));

	//agujaS->attachObject(agujaSegundos);
	//------------------------------------------------------------------------
	Noria* n = new Noria(mSM);
	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);


	//------------------------------------------------------------------------

}

