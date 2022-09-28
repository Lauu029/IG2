#pragma once

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>

#include <vector>

using namespace Ogre;
using namespace std;

class EntityIG : public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntityIG(Ogre::SceneNode* node);
	~EntityIG() {}
	//Vector estático de listeners
	static std::vector<EntityIG*> appListeners;
	//Añadir entidad como listener al vector con push_back()
	static void addListener(EntityIG* entidad) {
		appListeners.push_back(entidad);
	};

	SceneNode* getSceneNode() { return mNode; }

protected:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneManager* mSM = nullptr;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) { return false; };
	virtual void frameRendered(const Ogre::FrameEvent& evt) {};
};
//--------------------------------------------------------------
class AspaNoria : public EntityIG {
public:
	AspaNoria(Ogre::SceneNode* aspaNoria);
	~AspaNoria() {};

protected:
	Ogre::SceneNode* Base = nullptr;
	Ogre::SceneNode* Lateral1 = nullptr;
	Ogre::SceneNode* Lateral2 = nullptr;
};
//---------------------------------------------------------------
class Noria : public EntityIG {

public:
	Noria(Ogre::SceneNode* noria, int numAspas);
	~Noria() {};
protected:
	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

	int numAspas;
	std::vector<AspaNoria*> aspasNoria;
};


