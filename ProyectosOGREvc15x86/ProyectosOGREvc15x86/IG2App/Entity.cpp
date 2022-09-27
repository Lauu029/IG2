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
	Base->setPosition(100, 0, 0);
	Base->setScale(.4, .4, .4);

	Lateral1->attachObject(LadoI);
	Lateral1->setScale(3, .3, .03);
	Lateral1->setPosition(-50, 0, -20);

	Lateral2->attachObject(LadoD);
	Lateral2->setScale(3, .3, .05);
	Lateral2->setPosition(-50, 0, 20);
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
     
}
