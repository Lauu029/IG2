#include "Entity.h"


std::vector<EntityIG*>EntityIG::appListeners = std::vector<EntityIG*>(0, nullptr);

EntityIG::EntityIG(SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();
}

void EntityIG::sendEvent(EntityIG* entidad)
{
	for (EntityIG* e : appListeners)
		e->receiveEvent(this);
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

	LadoI->setMaterialName("noria/marron");
	LadoD->setMaterialName("noria/marron");
	cubo->setMaterialName("Practica1/metal");

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
	this->numAspas = numAspas;

	float increase = 360.0 / numAspas;
	for (size_t i = 0; i < numAspas; i++)
	{
		Ogre::SceneNode* nodoAspa = mNode->createChildSceneNode("Aspa " + std::to_string(i));
		AspaNoria* aspa = new AspaNoria(nodoAspa);
		nodoAspa->roll(Ogre::Degree(increase * i));
		aspa->getBase()->roll(Ogre::Degree(-increase * i));
		aspasNoria.push_back(aspa);
	}

	Ogre::SceneNode* centro = mNode->createChildSceneNode("centro");
	Ogre::Entity* cubo = mSM->createEntity("Barrel.mesh");
	centro->attachObject(cubo);
	centro->pitch(Ogre::Degree(90));
	centro->setPosition(0, 0, 0);
	centro->scale(10, 10, 10);
	cubo->setMaterialName("noria/piedra");


}

void Noria::receiveEvent(EntityIG* entidad)
{
	moving = !moving;
}

bool Noria::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_q) {
		double rot = 3.0f;
		for (auto aspa : aspasNoria) {
			aspa->getSceneNode()->roll(Ogre::Degree(rot));
			aspa->getBase()->roll(Ogre::Degree(-rot));
		}
	}


	return true;
}

void Noria::frameRendered(const Ogre::FrameEvent& evt)
{
	if (moving) {
		double rot = 1.0f;
		for (auto aspa : aspasNoria) {
			aspa->getSceneNode()->roll(Ogre::Degree(rot));
			aspa->getBase()->roll(Ogre::Degree(-rot));
		}
	}
}

Munieco::Munieco(Ogre::SceneNode* mun) : EntityIG(mun)
{
	head = mNode->createChildSceneNode("head");
	Ogre::Entity* h = mSM->createEntity("uv_sphere.mesh");
	head->attachObject(h);
	head->setScale(.3, .3, .3);
	head->translate(0, 70, 0);
	h->setMaterialName("munieco/cabeza");

	/*nose = head->createChildSceneNode("nose");
	Ogre::Entity* n = mSM->createEntity("uv_sphere.mesh");
	nose->attachObject(n);
	n->setMaterialName("nariz");
	nose->setScale(.1, .1, .1);
	nose->translate(0, 0, 100);*/

	body = mNode->createChildSceneNode("body");
	Ogre::Entity* b = mSM->createEntity("uv_sphere.mesh");
	body->attachObject(b);
	body->setScale(.5, .5, .5);
	b->setMaterialName("munieco/cuerpo");

	bellyButton = body->createChildSceneNode("bellyButton");
	Ogre::Entity* bB = mSM->createEntity("uv_sphere.mesh");
	bellyButton->attachObject(bB);
	bellyButton->setScale(.1, .1, .1);
	bellyButton->translate(0, 0, 100);
	bB->setMaterialName("munieco/ombligo");

	mNode->translate(100, 50, 250);
}

void Munieco::receiveEvent(EntityIG* entidad)
{
	if (!moving) {
		rojo = !rojo;
		if (rojo) {
			((Ogre::Entity*)head->getAttachedObjects().at(0))->setMaterialName("munieco/cabeza/rojo");
			((Ogre::Entity*)body->getAttachedObjects().at(0))->setMaterialName("munieco/cuerpo/rojo");
		}
		else {
			((Ogre::Entity*)head->getAttachedObjects().at(0))->setMaterialName("munieco/cabeza");
			((Ogre::Entity*)body->getAttachedObjects().at(0))->setMaterialName("munieco/cuerpo");
		}
	}
}

bool Munieco::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	moving = false;
	switch (evt.keysym.sym)
	{
	case SDLK_UP:
		mNode->translate(3, 0, 0);
		break;
	case SDLK_DOWN:
		mNode->translate(-3, 0, 0);
		break;
	case SDLK_LEFT:
		mNode->yaw(Ogre::Degree(-3.0f));
		break;
	case SDLK_RIGHT:
		mNode->yaw(Ogre::Degree(3.0f));
		break;
	default:
		break;
	}
	return true;
}

void Munieco::frameRendered(const Ogre::FrameEvent& t)
{
	if (moving) {
		mNode->yaw(Ogre::Degree(3.0f));
		head->yaw(Ogre::Degree(-6.0f));
	}
}

Plano::Plano(Ogre::SceneNode* plan) : EntityIG(plan)
{

	MeshManager::getSingleton().createPlane("mPlane1080x800",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	Ogre::Entity* plane = mSM->createEntity("mPlane1080x800");
	mNode->attachObject(plane);
	plane->setMaterialName("plano/aguaMueve");
}

bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_p) {
		mNode->yaw(Ogre::Degree(3.0f));
	}
	else if (evt.keysym.sym == SDLK_r) {
		sendEvent(this);
		changeMovingWater();
	}
	return true;
}

void Plano::changeMovingWater()
{
	moveWater = !moveWater;
	if (!moveWater)
		((Ogre::Entity*)mNode->getAttachedObjects().at(0))->setMaterialName("plano/aguaQuieta");
	else
		((Ogre::Entity*)mNode->getAttachedObjects().at(0))->setMaterialName("plano/aguaMueve");
}

Aspa::Aspa(Ogre::SceneNode* aspa) : EntityIG(aspa)
{
	//tablero
	tablero = aspa->createChildSceneNode();
	Ogre::Entity* ent_tablero = mSM->createEntity("cube.mesh");
	ent_tablero->setMaterialName("noria/marron");
	tablero->attachObject(ent_tablero);
	tablero->translate(60, 0, 0);
	tablero->scale(1.5, .2, .025);


	//cilindro
	cilindro = aspa->createChildSceneNode();
	Ogre::Entity* ent_cilindro = mSM->createEntity("Barrel.mesh");
	ent_cilindro->setMaterialName("Practica1/rojo");
	cilindro->attachObject(ent_cilindro);
	cilindro->scale(1, 2.5, 1);
	cilindro->translate(125, 0, 3);
}

AspasNave::AspasNave(Ogre::SceneNode* aspasNave, int num_aspas) : EntityIG(aspasNave)
{

	float increase = 360.0 / num_aspas;
	for (size_t i = 0; i < num_aspas; i++)
	{
		Ogre::SceneNode* aspa = aspasNave->createChildSceneNode();
		Aspa* ent_aspa = new Aspa(aspa);
		aspa->roll(Ogre::Degree(increase * i));
		ent_aspa->getCilindro()->roll(Ogre::Degree(-increase * i));
		aspas.push_back(ent_aspa);
	}

	centro = aspasNave->createChildSceneNode();
	Ogre::Entity* ent_centro = mSM->createEntity("Barrel.mesh");
	centro->attachObject(ent_centro);
	ent_centro->setMaterialName("Avion/aspa/cilindro");
	centro->pitch(Ogre::Degree(-90.0f));
	centro->scale(5, 1.5, 5);


}

Avion::Avion(Ogre::SceneNode* avion) : EntityIG(avion)
{
	//esfera
	Ogre::Entity* centro = mSM->createEntity("uv_sphere.mesh");
	centro->setMaterialName("Practica1/rojo");
	avion->attachObject(centro);

	//morro
	Ogre::Entity* ent_morro = mSM->createEntity("Barrel.mesh");
	morro = avion->createChildSceneNode();
	morro->attachObject(ent_morro);
	ent_morro->setMaterialName("Practica1/naranja");
	morro->pitch(Ogre::Degree(-90.0f));
	morro->scale(8, 1.5, 8);
	morro->translate(0, 0, 95);

	//piloto
	Ogre::Entity* ent_piloto = mSM->createEntity("ninja.mesh");
	piloto = avion->createChildSceneNode();
	piloto->attachObject(ent_piloto);
	ent_piloto->setMaterialName("Practica1/amarillo");
	piloto->yaw(Ogre::Degree(180));
	piloto->translate(0, -50, 0);

	//ala1
	Ogre::Entity* ent_ala1 = mSM->createEntity("cube.mesh");
	ala1 = avion->createChildSceneNode();
	ala1->attachObject(ent_ala1);
	ent_ala1->setMaterialName("Practica1/ala");
	ala1->scale(2.2, .1, 1.5);
	ala1->translate(-150, 0, 0);

	helice1 = avion->createChildSceneNode();
	AspasNave* aspas1 = new AspasNave(helice1, 5);
	helice1->scale(.4, .4, .4);
	helice1->translate(-150, 0, 75);

	//ala2
	Ogre::Entity* ent_ala2 = mSM->createEntity("cube.mesh");
	ala2 = avion->createChildSceneNode();
	ala2->attachObject(ent_ala2);
	ent_ala2->setMaterialName("Practica1/ala");
	ala2->scale(2.2, .1, 1.5);
	ala2->translate(150, 0, 0);

	helice2 = avion->createChildSceneNode();
	AspasNave* aspas2 = new AspasNave(helice2, 5);
	helice2->scale(.4, .4, .4);
	helice2->translate(150, 0, 75);

}

BrazoDron::BrazoDron(Ogre::SceneNode* brazo) : EntityIG(brazo)
{
	Ogre::Entity* extremo = mSM->createEntity("uv_sphere.mesh");
	extremo->setMaterialName("Practica1/naranja");
	esfera = brazo->createChildSceneNode();
	esfera->attachObject(extremo);
	esfera->scale(.4, .4, .4);
	esfera->translate(180, 0, 0);

	Ogre::Entity* cuerpo = mSM->createEntity("Barrel.mesh");
	cuerpo->setMaterialName("Practica1/metal/amarillo");
	cilindro = brazo->createChildSceneNode();
	cilindro->attachObject(cuerpo);
	cilindro->setScale(5, 15, 5);
	cilindro->translate(100, 0, 0);
	cilindro->roll(Ogre::Degree(90));

	aspaDron = brazo->createChildSceneNode();
	AspasNave* a = new AspasNave(aspaDron, 3);
	aspaDron->pitch(Ogre::Degree(-90));
	aspaDron->setScale(.3, .3, .3);
	aspaDron->translate(180, 38, 0);
}

Dron::Dron(Ogre::SceneNode* dron, int numBrazos) : EntityIG(dron)
{
	centro = dron->createChildSceneNode();
	Ogre::Entity* ent_centro = mSM->createEntity("uv_sphere.mesh");
	ent_centro->setMaterialName("Practica1/rojo");
	centro->attachObject(ent_centro);
	centro->scale(.6, .6, .6);
	
	aspaPrincipal = centro->createChildSceneNode();
	BrazoDron* ent_brazoPrinc = new BrazoDron(aspaPrincipal);
	aspaPrincipal->scale(1.5, 1.5, 1.5);
	//aspaPrincipal->translate(100, 0, 0);
	brazos.push_back(ent_brazoPrinc);

	float increase = 360.0 / numBrazos - 1;
	for (size_t i = 1; i < numBrazos; i++)
	{
		Ogre::SceneNode* br = dron->createChildSceneNode();
		BrazoDron* ent_brazo = new BrazoDron(br);
		br->yaw(Ogre::Degree(increase * i));
		br->scale(.7, .7, .7);
		brazos.push_back(ent_brazo);
	}

}
