#include "Noria.h"
using namespace Ogre;

Noria::Noria(Ogre::SceneManager* mSM)
{
	feria = mSM->getRootSceneNode()->createChildSceneNode("feria");
	AspaNoria* aspa;
	for (size_t i = 0; i < 12; i++)
	{
		Ogre::SceneNode* childAspa = feria->createChildSceneNode("Aspa " + std::to_string(i));
		
		childAspa->setPosition(250 * Ogre::Math::Cos(Ogre::Degree( i)), 250 *
			Ogre::Math::Sin(Ogre::Degree( i)), 0);
		aspa = new AspaNoria (mSM, childAspa);
		feria->addChild(childAspa);
	}
}
