#include "Entity.h"


std::vector<EntityIG*>EntityIG::appListeners = std::vector<EntityIG*>(0, nullptr);

EntityIG::EntityIG(SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();
}

//------------------------------------------------------------------
AspaNoria::AspaNoria(Ogre::SceneNode* aspaNodo) : EntityIG(aspaNodo)
{
	Base = aspaNodo->createChildSceneNode();
	Lateral1 = aspaNodo->createChildSceneNode();
	Lateral2 = aspaNodo->createChildSceneNode();

	Ogre::Entity* cubo = mSM->createEntity("cube.mesh");
	Ogre::Entity* LadoI = mSM->createEntity("cube.mesh");
	Ogre::Entity* LadoD = mSM->createEntity("cube.mesh");

	Base->attachObject(cubo);
	Base->setPosition(300, 0, 0);
	Base->scale(.4, .4, .4);
	Base->setInheritOrientation(false);

	Lateral1->attachObject(LadoI);
	Lateral1->translate(160, 0, -20);
	Lateral1->scale(3, .3, .03);

	Lateral2->attachObject(LadoD);
	Lateral2->translate(160, 0, 20);
	Lateral2->scale(3, .3, .03);
}
//---------------------------------------------------------------
Noria::Noria(Ogre::SceneNode* noria, int numAspas) : EntityIG(noria)
{
	this->numAspas = numAspas;

	float increase = 360.0 / numAspas;
	for (size_t i = 0; i < numAspas; i++)
	{
		Ogre::SceneNode* nodoAspa = mNode->createChildSceneNode("Aspa " + std::to_string(i));
		AspaNoria* aspa = new AspaNoria(nodoAspa);
		nodoAspa->roll(Ogre::Degree(increase * i));
		aspasNoria.push_back(aspa);
	}

	Ogre::SceneNode* centro = mNode->createChildSceneNode("centro");
	Ogre::Entity* cubo = mSM->createEntity("Barrel.mesh");
	centro->attachObject(cubo);
	centro->pitch(Ogre::Degree(90));
	centro->setPosition(0, 0, 0);
	centro->scale(10, 10, 10);


}

bool Noria::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_q) {
		double rot = 3.0f;
		for (auto aspa : aspasNoria)
			aspa->getSceneNode()->roll(Ogre::Degree(rot));

	}


	return true;
}

void Noria::frameRendered(const Ogre::FrameEvent& evt)
{
	double rot = 1.0f;
	for (auto aspa : aspasNoria)
		aspa->getSceneNode()->roll(Ogre::Degree(rot));
}

Munieco::Munieco(Ogre::SceneNode* mun) : EntityIG(mun)
{
	head = mNode->createChildSceneNode("head");
	Ogre::Entity* h = mSM->createEntity("uv_sphere.mesh");
	head->attachObject(h);
	head->setScale(.3, .3, .3);
	head->translate(0, 70, 0);

	nose = head->createChildSceneNode("nose");
	Ogre::Entity* n = mSM->createEntity("uv_sphere.mesh");
	nose->attachObject(n);
	nose->setScale(.1, .1, .1);
	nose->translate(0, 0, 100);

	body = mNode->createChildSceneNode("body");
	Ogre::Entity* b = mSM->createEntity("uv_sphere.mesh");
	body->attachObject(b);
	body->setScale(.5, .5, .5);

	bellyButton = body->createChildSceneNode("bellyButton");
	Ogre::Entity* bB = mSM->createEntity("uv_sphere.mesh");
	bellyButton->attachObject(bB);
	bellyButton->setScale(.1, .1, .1);
	bellyButton->translate(0, 0, 100);

	mNode->translate(100, 50, 250);
}

Plano::Plano(Ogre::SceneNode* plan) : EntityIG(plan)
{
	
	MeshManager::getSingleton().createPlane("mPlane1080x800",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	Ogre::Entity* plane = mSM->createEntity("mPlane1080x800");
	mNode->attachObject(plane);
}
