#include "AspaNoria.h"



using namespace Ogre;
AspaNoria::AspaNoria(Ogre::SceneManager* mSM)
{
	Aspa = mSM->getRootSceneNode()->createChildSceneNode();
	Base = Aspa->createChildSceneNode();
	Lateral1 = Aspa->createChildSceneNode();
	Lateral2 = Aspa->createChildSceneNode();
	Ogre::Entity* cubo = mSM->createEntity("cube.mesh");
	Ogre::Entity* LadoI = mSM->createEntity("cube.mesh");
	Ogre::Entity* LadoD = mSM->createEntity("cube.mesh");


	Base->attachObject(cubo);
	Base->setPosition(100, 0, 0);
	Base->setScale(.4, .4, .4);

	Lateral1->attachObject(LadoI);
	Lateral1->setScale(3, .3, .03);
	Lateral1->setPosition(-50, 0,-20);

	Lateral2->attachObject(LadoD);
	Lateral2->setScale(3, .3, .05);
	Lateral2->setPosition(-50, 0,20);
}
