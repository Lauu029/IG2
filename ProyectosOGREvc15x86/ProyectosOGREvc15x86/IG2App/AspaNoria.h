#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

class AspaNoria
{
public:
	AspaNoria(Ogre::SceneManager* mSM, Ogre::SceneNode* feria);
	~AspaNoria() {};
protected:
	Ogre::SceneNode* Aspa = nullptr;
	Ogre::SceneNode* Base = nullptr;
	Ogre::SceneNode* Lateral1 = nullptr;
	Ogre::SceneNode* Lateral2 = nullptr;

};

