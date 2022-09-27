#include "Entity.h"

EntityIG::EntityIG(SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();
}


bool EntityIG::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	return false;
}

void EntityIG::frameRendered(const Ogre::FrameEvent& evt)
{
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
	float increase = 360.0 / numAspas;
	for (size_t i = 0; i < numAspas; i++)
	{
		Ogre::SceneNode* nodoAspa = mNode->createChildSceneNode("Aspa " + std::to_string(i));
		AspaNoria* aspa = new AspaNoria(nodoAspa);
		nodoAspa->roll(Ogre::Degree(increase * i));
	}
	Ogre::SceneNode* centro = mNode->createChildSceneNode("centro");
	Ogre::Entity* cubo = mSM->createEntity("Barrel.mesh");
	centro->attachObject(cubo);
	centro->pitch(Ogre::Degree(90));
	centro->setPosition(0, 0, 0);
	centro->scale(10, 10, 10);


}
