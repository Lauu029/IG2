#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneNode.h>

using namespace Ogre;


bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	default:
		break;
	}
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
	srand(time(NULL));//change random seed
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1.0,1.0,1.0);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);
	//Luz frontal
	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
	mLightNode->setPosition(0, 0, 2000);
	//------------------------------------------------------------------------
	CreateBombaRioSinbadScene();
	mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -40),
		"IG2/SkyTexture"
		, 1, 1, true, 1.0, 100, 100);
	

	//------------------------------------------------------------------------
	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//------------------------------------------------------------------------

}

void IG2App::CreateBombaRioSinbadScene()
{
	sBomba = mSM->getRootSceneNode()->createChildSceneNode();
	Ogre::SceneNode* n = sBomba->createChildSceneNode();
	Bomba* bomb = new Bomba(n);
	addInputListener(bomb);
	EntityIG::addListener(bomb);

	Ogre::SceneNode* PlaneNodo = sBomba->createChildSceneNode();
	Plano* p = new Plano(PlaneNodo, "rioBomba");
	addInputListener(p);
	EntityIG::addListener(p);

	//plano rojo
	MeshManager::getSingleton().createPlane("redPlane",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		250, 250, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	Ogre::Entity* redPlane = mSM->createEntity("redPlane");
	Ogre::SceneNode* redPlaneNode = sBomba->createChildSceneNode();
	redPlaneNode->attachObject(redPlane);
	redPlane->setMaterialName("Practica1/rojo");
	redPlaneNode->translate(400, 1, -250);

	//Simbad
	Ogre::SceneNode* _sinbad = sBomba->createChildSceneNode();
	Ogre::SceneNode* sinbadAnimation = _sinbad->createChildSceneNode();
	Sinbad* _simpBad = new Sinbad(sinbadAnimation, true);
	sinbadAnimation->translate(-400, 50, 250);
	_simpBad->arma();
	addInputListener(_simpBad);
	EntityIG::addListener(_simpBad);

	//Noria
	Ogre::SceneNode* _norianodo = sBomba->createChildSceneNode();
	Noria* _norita = new Noria(_norianodo, 20);
	_norianodo->setScale(0.5, 0.5, 0.5);
	_norianodo->translate(400, 0, -350);
	addInputListener(_norita);
	EntityIG::addListener(_norita);

	//Muñeco
	Ogre::SceneNode* _muniecoNodo = sBomba->createChildSceneNode();
	Munieco* _mun = new Munieco(_muniecoNodo);
	_muniecoNodo->yaw(Degree(-90));
	addInputListener(_mun);
	EntityIG::addListener(_mun);

	//Avion
	Ogre::SceneNode* avionBomba = sBomba->createChildSceneNode();
	Ogre::SceneNode* _aeroPlane = avionBomba->createChildSceneNode();
	Avion* ent_avion = new Avion(_aeroPlane);
	_aeroPlane->translate(-150.0, 250.0, 0.0);
	_aeroPlane->scale(0.3, 0.3, 0.3);
	addInputListener(ent_avion);
	sBomba->setVisible(true);
}