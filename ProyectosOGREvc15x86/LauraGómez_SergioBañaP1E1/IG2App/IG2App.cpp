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
	case SDLK_g:
		mClock->roll(Ogre::Degree(5));
		break;
	case SDLK_y:
		mHours->yaw(Ogre::Degree(5));
		break;
	case SDLK_0:
		mSM->getCamera("Cam")->getViewport()->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));
		sNoria->setVisible(false);
		sReloj->setVisible(true);
		sAvion->setVisible(false);
		sSinbad->setVisible(false);
		l->hide();
		break;
	case SDLK_1:
		mSM->getCamera("Cam")->getViewport()->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));
		sReloj->setVisible(false);
		sNoria->setVisible(true);
		sAvion->setVisible(false);
		sSinbad->setVisible(false);
		l->hide();
		break;
	case SDLK_2:
		mSM->getCamera("Cam")->getViewport()->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
		sReloj->setVisible(false);
		sNoria->setVisible(false);
		sAvion->setVisible(true);
		sSinbad->setVisible(false);
		l->show();
		break;
	case SDLK_3:
		mSM->getCamera("Cam")->getViewport()->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
		sReloj->setVisible(false);
		sNoria->setVisible(false);
		sAvion->setVisible(false);
		sSinbad->setVisible(true);
		l->hide();
		break;
	case SDLK_h:
		compuebaColisiones();
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
	l = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "Avispas", Ogre::DisplayString("Avispas: " + Ogre::StringConverter::toString(mDronesAvispa.size())), 200);

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
	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
	mLightNode->setPosition(0, 0, 2000);
	//------------------------------------------------------------------------

	//noria
	createNoria();

	//Reloj
	createReloj();

	//planeta
	createPlanetAvion();
	//Ogre node
	CreateSinbadScene();

	
	//------------------------------------------------------------------------
	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//------------------------------------------------------------------------

}

void IG2App::CreateSinbadScene()
{
	sSinbad = mSM->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* Sphere = mSM->createEntity("uv_sphere.mesh");
	Ogre::SceneNode* Planet = sSinbad->createChildSceneNode();
	Sphere->setMaterialName("Practica1/azul");
	Planet->attachObject(Sphere);
	Planet->scale(1.5, 1.5, 1.5);
	
	Ogre::SceneNode* _sinbad= sSinbad->createChildSceneNode();
	Ogre::SceneNode* sinbadAnimation = _sinbad->createChildSceneNode();
	Sinbad* _simpBad = new Sinbad(sinbadAnimation);
	sinbadAnimation->translate(0.0, 170.0, 0.0);
	sinbadAnimation->scale(6,6,6);
	addInputListener(_simpBad);
	

	sSinbad->setVisible(false);
	
}
void IG2App::createReloj()
{
	sReloj = mSM->getRootSceneNode()->createChildSceneNode();
	mClock = sReloj->createChildSceneNode();
	mHours = mClock->createChildSceneNode();

	float increase = 360.0 / 12;
	for (size_t i = 0; i < 12; i++)
	{
		Ogre::Entity* Sphere = mSM->createEntity("uv_sphere.mesh");
		Ogre::SceneNode* Hour = mHours->createChildSceneNode("Hora " + std::to_string(i));
		Hour->setScale(.5, .5, .5);

		Hour->attachObject(Sphere);
		Hour->setPosition(250 * Ogre::Math::Cos(Ogre::Degree(increase * i)), 250 * Ogre::Math::Sin(Ogre::Degree(increase * i)), 0);
		if (i % 2)
			mSM->getSceneNode("Hora " + std::to_string(i))->setScale(.2, .2, .2);
	}
	//Agujas
	Ogre::Entity* agujaHoras = mSM->createEntity("cube.mesh");
	Ogre::SceneNode* aguja = mClock->createChildSceneNode("Horas");
	aguja->setScale(.25, 1.6, .05);
	aguja->setPosition(65, 0, 0);
	aguja->roll(Ogre::Degree(-90));

	aguja->attachObject(agujaHoras);

	Ogre::Entity* agujaMinutos = mSM->createEntity("cube.mesh");
	Ogre::SceneNode* agujaM = mClock->createChildSceneNode("Minutos");
	agujaM->setScale(.15, 2, .05);
	agujaM->setPosition(0, 65, 0);

	agujaM->attachObject(agujaMinutos);

	Ogre::Entity* agujaSegundos = mSM->createEntity("cube.mesh");
	Ogre::SceneNode* agujaS = mClock->createChildSceneNode("Segundos");
	agujaS->setScale(.05, 2, .05);
	agujaS->setPosition(-70, -60, 0);
	agujaS->roll(Ogre::Degree(125));

	agujaS->attachObject(agujaSegundos);

	sReloj->setVisible(true);
}
void IG2App::createNoria()
{
	sNoria = mSM->getRootSceneNode()->createChildSceneNode("escenaNoria");
	Ogre::SceneNode* PlaneNodo = sNoria->createChildSceneNode("suelo");
	Plano* p = new Plano(PlaneNodo);
	addInputListener(p);

	Ogre::SceneNode* norianodo = PlaneNodo->createChildSceneNode("noria");
	Noria* n = new Noria(norianodo, 20);
	addInputListener(n);
	EntityIG::addListener(n);

	Ogre::SceneNode* muniecoNodo = PlaneNodo->createChildSceneNode("Munieco");
	Munieco* m = new Munieco(muniecoNodo);
	muniecoNodo->yaw(Degree(200));
	addInputListener(m);
	EntityIG::addListener(m);

	sNoria->setVisible(false);
}
void IG2App::createPlanetAvion()
{
	sAvion = mSM->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* Sphere = mSM->createEntity("uv_sphere.mesh");
	Ogre::SceneNode* Planet = sAvion->createChildSceneNode();
	Sphere->setMaterialName("Practica1/azul");
	Planet->attachObject(Sphere);
	Planet->scale(2.5, 2.5, 2.5);

	mAvionFicticio = sAvion->createChildSceneNode();
	Ogre::SceneNode* aeroPlane = mAvionFicticio->createChildSceneNode();
	Avion* ent_avion = new Avion(aeroPlane);
	aeroPlane->translate(0.0, 255.0, 0.0);
	aeroPlane->scale(0.2, 0.2, 0.2);
	addInputListener(ent_avion);

	Ogre::SceneNode* nodrizaFicticio = sAvion->createChildSceneNode();
	Ogre::SceneNode* nodriza = nodrizaFicticio->createChildSceneNode();
	mEnt_dron = new Dron(nodriza, 3, false);
	nodriza->translate(0.0, 255.0, 0.0);
	nodriza->scale(0.2, 0.2, 0.2);
	addInputListener(mEnt_dron);
	nodrizaFicticio->yaw(Ogre::Degree(rand() % 310 + 20));
	nodrizaFicticio->pitch(Ogre::Degree(rand() % 310 + 20));

	for (int i = 0; i < nNumDron; i++)
	{
		Ogre::SceneNode* avispaFicticio = sAvion->createChildSceneNode();
		Ogre::SceneNode* avispa = avispaFicticio->createChildSceneNode();
		Dron* ent_dron_avispa = new Dron(avispa, 3, true);
		avispa->translate(0.0, 245.0, 0.0);
		avispa->scale(0.1, 0.1, 0.1);

		avispaFicticio->yaw(Ogre::Degree(rand() % 310 + 20));
		avispaFicticio->pitch(Ogre::Degree(rand() % 310 + 20));

		addInputListener(ent_dron_avispa);
		mDronesAvispa.push_back({ avispaFicticio,ent_dron_avispa });
	}
	l->setCaption(Ogre::DisplayString("Avispas: " + Ogre::StringConverter::toString(mDronesAvispa.size())));
	
	sAvion->setVisible(false);
}
void IG2App::compuebaColisiones()
{
	AxisAlignedBox aabPlane = mAvionFicticio->_getWorldAABB();
	for (int i = 0; i < mDronesAvispa.size(); i++)
	{
		AxisAlignedBox aabAvispa = mDronesAvispa[i].first->_getWorldAABB();
		if (aabAvispa.intersects(aabPlane)) {
			removeInputListener(mDronesAvispa[i].second);
			delete mDronesAvispa[i].second;
			mSM->destroySceneNode(mDronesAvispa[i].first);
			mDronesAvispa.erase(mDronesAvispa.begin() + i);
			i--;
			//av->setVisible(false);
		}
	}

	l->setCaption(Ogre::DisplayString("Avispas: " + Ogre::StringConverter::toString(mDronesAvispa.size())));

	if (mDronesAvispa.size() == 0) 
		mEnt_dron->changeBodyColor();
	
}