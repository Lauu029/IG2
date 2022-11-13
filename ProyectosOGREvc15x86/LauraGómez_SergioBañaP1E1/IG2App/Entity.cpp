#include "Entity.h"
#include <iostream>


std::vector<EntityIG*>EntityIG::appListeners = std::vector<EntityIG*>(0, nullptr);

EntityIG::EntityIG(SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();
}
void EntityIG::sendEvent(EntityIG* entidad, MessageKind k)
{
	for (EntityIG* e : appListeners)
		e->receiveEvent(this, k);
}
//------------------------------------------------------------------
AspaNoria::AspaNoria(Ogre::SceneNode* aspaNodo) : EntityIG(aspaNodo)
{
	Base = aspaNodo->createChildSceneNode();
	Ogre::SceneNode* Lateral1 = aspaNodo->createChildSceneNode();
	Ogre::SceneNode* Lateral2 = aspaNodo->createChildSceneNode();

	Ogre::Entity* cubo = mSM->createEntity("cube.mesh");
	Ogre::Entity* LadoI = mSM->createEntity("cube.mesh");
	Ogre::Entity* LadoD = mSM->createEntity("cube.mesh");

	LadoI->setMaterialName("Practica1/noria/marron");
	LadoD->setMaterialName("Practica1/noria/marron");
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
//------------------------------------------------------------------
Noria::Noria(Ogre::SceneNode* noria, int numAspas) : EntityIG(noria)
{
	this->numAspas = numAspas;

	float increase = 360.0 / numAspas;
	for (size_t i = 0; i < numAspas; i++)
	{
		Ogre::SceneNode* nodoAspa = mNode->createChildSceneNode();
		AspaNoria* aspa = new AspaNoria(nodoAspa);
		nodoAspa->roll(Ogre::Degree(increase * i));
		aspa->getBase()->roll(Ogre::Degree(-increase * i));
		aspasNoria.push_back(aspa);
	}

	Ogre::SceneNode* centro = mNode->createChildSceneNode();
	Ogre::Entity* cubo = mSM->createEntity("Barrel.mesh");
	centro->attachObject(cubo);
	centro->pitch(Ogre::Degree(90));
	centro->setPosition(0, 0, 0);
	centro->scale(10, 10, 10);
	cubo->setMaterialName("Practica1/noria/piedra");


}
void Noria::receiveEvent(EntityIG* entidad, MessageKind k)
{
	if (k == MessageKind::NoriaScene)
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
		double rot = 10.0f * evt.timeSinceLastFrame;
		for (auto aspa : aspasNoria) {
			aspa->getSceneNode()->roll(Ogre::Degree(rot));
			aspa->getBase()->roll(Ogre::Degree(-rot));
		}
	}
}
//---------------------------------------------------------------
Munieco::Munieco(Ogre::SceneNode* mun) : EntityIG(mun)
{
	Ogre::SceneNode* head = mNode->createChildSceneNode();
	mHead = mSM->createEntity("uv_sphere.mesh");
	head->attachObject(mHead);
	head->setScale(.3, .3, .3);
	head->translate(0, 70, 0);
	//mHead->setMaterialName("Practica1/munieco/cabeza");
	mHead->setMaterialName("Practica1/naranja");

	Ogre::SceneNode* nose = head->createChildSceneNode();
	Ogre::Entity* n = mSM->createEntity("uv_sphere.mesh");
	nose->attachObject(n);
	n->setMaterialName("Practica1/munieco/ombligo");
	nose->setScale(.1, .1, .1);
	nose->translate(100, 0, 0);

	Ogre::SceneNode* body = mNode->createChildSceneNode();
	mBody = mSM->createEntity("uv_sphere.mesh");
	body->attachObject(mBody);
	body->setScale(.5, .5, .5);
	//mBody->setMaterialName("Practica1/munieco/cuerpo");
	mBody->setMaterialName("Practica1/naranja");

	Ogre::SceneNode* bellyButton = body->createChildSceneNode();
	Ogre::Entity* bB = mSM->createEntity("uv_sphere.mesh");
	bellyButton->attachObject(bB);
	bellyButton->setScale(.1, .1, .1);
	bellyButton->translate(100, 0, 0);
	bB->setMaterialName("Practica1/munieco/ombligo");


	mNode->setScale(0.5, 0.5, 0.5);
	mNode->setPosition(500, 30, -150);
	mNode->yaw(Degree(-90));

	mNode->setInitialState();
	Real duration = 10;
	Animation* anim = mSM->createAnimation("MuniecoMueve", duration);
	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	Vector3 src(0.0, 0.0, 1.0);
	Real durPaso = duration / 4.0;

	Vector3 keyFramePos(0, 0, 0);// 0
	TransformKeyFrame* kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Vector3(0.5, 0.0, 0.0)));

	keyFramePos = Vector3(0, 0, 0);//1 
	kf = track->createNodeKeyFrame(durPaso);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Vector3(-1.0, 0.0,0.0)));

	keyFramePos = Vector3(-200, 0, 0);//2
	kf = track->createNodeKeyFrame(durPaso * 2);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Vector3(-1.0, 0.0, 0.0)));

	keyFramePos = Vector3(-200, 0, 0);//3
	kf = track->createNodeKeyFrame(durPaso * 3);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Vector3(1.0, 0.0, 0.0)));

	keyFramePos = Vector3(0, 0, 0);//4
	kf = track->createNodeKeyFrame(durPaso * 4);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Vector3(1.0, 0.0, 0.0)));

	animationState = mSM->createAnimationState("MuniecoMueve");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}

void Munieco::receiveEvent(EntityIG* entidad, MessageKind k)
{
	if (k == MessageKind::NoriaScene) {
		mRojo = !mRojo;
		if (mRojo) {
			mHead->setMaterialName("Practica1/munieco/cabeza/rojo");
			mBody->setMaterialName("Practica1/munieco/cuerpo/rojo");
		}
		else {
			mHead->setMaterialName("Practica1/munieco/cabeza");
			mBody->setMaterialName("Practica1/munieco/cuerpo");
		}
		mMoving = !mMoving;
	}
}

bool Munieco::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	mMoving = false;

	switch (evt.keysym.sym)
	{
	case SDLK_UP:
		mNode->translate(3, 0, 0, Ogre::Node::TS_LOCAL);
		break;
	case SDLK_DOWN:
		mNode->translate(-3, 0, 0, Ogre::Node::TS_LOCAL);
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
	animationState->addTime(t.timeSinceLastFrame);
	if (mMoving) {
		mNode->yaw(Ogre::Degree(3.0f * t.timeSinceLastFrame));
		mHead->getParentNode()->yaw(Ogre::Degree(-6.0f * t.timeSinceLastFrame));
	}
}
//---------------------------------------------------------------
Plano::Plano(Ogre::SceneNode* plan, string name) : EntityIG(plan)
{
	MeshManager::getSingleton().createPlane(name,
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	mPlane = mSM->createEntity(name);
	mNode->attachObject(mPlane);
	mPlane->setMaterialName("Practica1/plano/aguaMueve");
}
bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_p) {
		mNode->yaw(Ogre::Degree(3.0f));
	}
	else if (evt.keysym.sym == SDLK_r) {
		sendEvent(this, MessageKind::NoriaScene);
		changeMovingWater();
	}
	return true;
}
void Plano::receiveEvent(EntityIG* entidad, MessageKind k)
{
	if (k == MessageKind::BombScene) {
		mPlane->setMaterialName("Practica1/plano/pieadras");
	}
}
void Plano::changeMovingWater()
{
	mMoveWater = !mMoveWater;
	if (!mMoveWater)
		mPlane->setMaterialName("Practica1/plano/aguaQuieta");
	else
		mPlane->setMaterialName("Practica1/plano/aguaMueve");
}
//---------------------------------------------------------------
Aspa::Aspa(Ogre::SceneNode* aspa) : EntityIG(aspa)
{
	//tablero
	Ogre::SceneNode* tablero = aspa->createChildSceneNode();
	Ogre::Entity* ent_tablero = mSM->createEntity("cube.mesh");
	ent_tablero->setMaterialName("Practica1/noria/marron");
	tablero->attachObject(ent_tablero);
	tablero->translate(60, 0, 0);
	tablero->scale(1.5, .2, .025);


	//cilindro
	mCilinder = aspa->createChildSceneNode();
	Ogre::Entity* ent_cilindro = mSM->createEntity("Barrel.mesh");
	ent_cilindro->setMaterialName("Practica1/rojo");
	mCilinder->attachObject(ent_cilindro);
	mCilinder->scale(1, 2.5, 1);
	mCilinder->translate(125, 0, 3);
}
//---------------------------------------------------------------
AspasNave::AspasNave(Ogre::SceneNode* aspasNave, int num_aspas) : EntityIG(aspasNave)
{

	float increase = 360.0 / num_aspas;
	for (size_t i = 0; i < num_aspas; i++)
	{
		Ogre::SceneNode* aspa = aspasNave->createChildSceneNode();
		Aspa* ent_aspa = new Aspa(aspa);
		aspa->roll(Ogre::Degree(increase * i));
		ent_aspa->getCilinder()->roll(Ogre::Degree(-increase * i));
		mAspas.push_back(ent_aspa);
	}

	Ogre::SceneNode* centro = aspasNave->createChildSceneNode();
	Ogre::Entity* ent_centro = mSM->createEntity("Barrel.mesh");
	centro->attachObject(ent_centro);
	ent_centro->setMaterialName("Practica1/Avion/aspa/cilindro");
	centro->pitch(Ogre::Degree(-90.0f));
	centro->scale(5, 1.5, 5);
}
//---------------------------------------------------------------
Avion::Avion(Ogre::SceneNode* avion) : EntityIG(avion)
{
	//esfera
	Ogre::Entity* centro = mSM->createEntity("uv_sphere.mesh");
	centro->setMaterialName("Practica1/rojo");
	avion->attachObject(centro);

	//morro
	Ogre::Entity* ent_morro = mSM->createEntity("Barrel.mesh");
	Ogre::SceneNode* morro = avion->createChildSceneNode();
	morro->attachObject(ent_morro);
	ent_morro->setMaterialName("Practica1/naranja");
	morro->pitch(Ogre::Degree(-90.0f));
	morro->scale(8, 1.5, 8);
	morro->translate(0, 0, 95);

	//piloto
	Ogre::Entity* ent_piloto = mSM->createEntity("ninja.mesh");
	Ogre::SceneNode* piloto = avion->createChildSceneNode();
	piloto->attachObject(ent_piloto);
	ent_piloto->setMaterialName("Practica1/amarillo");
	piloto->yaw(Ogre::Degree(180));
	piloto->translate(0, -50, 0);

	//ala1
	Ogre::Entity* ent_ala1 = mSM->createEntity("cube.mesh");
	Ogre::SceneNode* ala1 = avion->createChildSceneNode();
	ala1->attachObject(ent_ala1);
	ent_ala1->setMaterialName("Practica1/ala");
	ala1->scale(2.2, .1, 1.5);
	ala1->translate(-150, 0, 0);

	Ogre::SceneNode* helice1 = avion->createChildSceneNode();
	mHelice1 = new AspasNave(helice1, 5);
	helice1->scale(.4, .4, .4);
	helice1->translate(-150, 0, 75);

	//ala2
	Ogre::Entity* ent_ala2 = mSM->createEntity("cube.mesh");
	Ogre::SceneNode* ala2 = avion->createChildSceneNode();
	ala2->attachObject(ent_ala2);
	ent_ala2->setMaterialName("Practica1/ala");
	ala2->scale(2.2, .1, 1.5);
	ala2->translate(150, 0, 0);

	Ogre::SceneNode* helice2 = avion->createChildSceneNode();
	mHelice2 = new AspasNave(helice2, 5);
	helice2->scale(.4, .4, .4);
	helice2->translate(150, 0, 75);

	//10points
	BillboardSet* bbSet = mSM->createBillboardSet("cartel", 1);
	bbSet->setDefaultDimensions(50, 50);
	bbSet->setMaterialName("Practica1/10points");

	mNode->attachObject(bbSet);

	Billboard* bb = bbSet->createBillboard(0, 0, -150);

	//humo
	ParticleSystem* pSys = mSM->createParticleSystem("psSmoke", "Practica1/smoke");
	pSys->setEmitting(true);
	mNode->attachObject(pSys);
}
bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	//if (evt.keysym.sym == SDLK_h) {
	//	mNode->getParent()->pitch(Ogre::Degree(3));

	//	//desrotar cilindros de las helices
	//	double rot = 15.0f;
	//	mHelice1->getSceneNode()->roll(Ogre::Degree(rot));

	//	for (auto aspa : mHelice1->mAspas)
	//		aspa->getCilinder()->roll(Ogre::Degree(-rot));


	//	mHelice2->getSceneNode()->roll(Ogre::Degree(rot));

	//	for (auto aspa : mHelice2->mAspas)
	//		aspa->getCilinder()->roll(Ogre::Degree(-rot));

	//}
	//else if (evt.keysym.sym == SDLK_j) {
	//	mNode->getParent()->yaw(Ogre::Degree(3));
	//}
	return true;
}
void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	mNode->getParent()->yaw(Ogre::Degree(20 * evt.timeSinceLastFrame));

	//desrotar cilindros de las helices
	double rot = 200.0f * evt.timeSinceLastEvent;
	mHelice1->getSceneNode()->roll(Ogre::Degree(rot));

	for (auto aspa : mHelice1->mAspas)
		aspa->getCilinder()->roll(Ogre::Degree(-rot));


	mHelice2->getSceneNode()->roll(Ogre::Degree(rot));

	for (auto aspa : mHelice2->mAspas)
		aspa->getCilinder()->roll(Ogre::Degree(-rot));
}
//---------------------------------------------------------------
BrazoDron::BrazoDron(Ogre::SceneNode* brazo) : EntityIG(brazo)
{
	Ogre::Entity* extremo = mSM->createEntity("uv_sphere.mesh");
	extremo->setMaterialName("Practica1/naranja");
	Ogre::SceneNode* esfera = brazo->createChildSceneNode();
	esfera->attachObject(extremo);
	esfera->scale(.4, .4, .4);
	esfera->translate(180, 0, 0);

	Ogre::Entity* cuerpo = mSM->createEntity("Barrel.mesh");
	cuerpo->setMaterialName("Practica1/metal/amarillo");
	Ogre::SceneNode* cilindro = brazo->createChildSceneNode();
	cilindro->attachObject(cuerpo);
	cilindro->setScale(5, 15, 5);
	cilindro->translate(100, 0, 0);
	cilindro->roll(Ogre::Degree(90));

	Ogre::SceneNode* aspaDron = brazo->createChildSceneNode();
	mHelice = new AspasNave(aspaDron, 3);
	aspaDron->pitch(Ogre::Degree(-90));
	aspaDron->setScale(.3, .3, .3);
	aspaDron->translate(180, 38, 0);
}
//---------------------------------------------------------------
Dron::Dron(Ogre::SceneNode* dron, int numBrazos, bool avispa) : EntityIG(dron)
{
	myTimer = new Timer();
	Ogre::SceneNode* centro = dron->createChildSceneNode();
	mCenter = mSM->createEntity("uv_sphere.mesh");
	if (!avispa)
		mCenter->setMaterialName("Practica1/rojo");
	else
		mCenter->setMaterialName("Practica1/munieco/cabeza");
	centro->attachObject(mCenter);
	centro->scale(.6, .6, .6);

	Ogre::SceneNode* aspaPrincipal = centro->createChildSceneNode();
	BrazoDron* ent_brazoPrinc = new BrazoDron(aspaPrincipal);
	aspaPrincipal->scale(1.5, 1.5, 1.5);
	mBrazos.push_back(ent_brazoPrinc);

	float increase = 360.0 / numBrazos - 1;
	for (size_t i = 1; i < numBrazos; i++)
	{
		Ogre::SceneNode* br = dron->createChildSceneNode();
		BrazoDron* ent_brazo = new BrazoDron(br);
		br->yaw(Ogre::Degree(increase * i));
		br->scale(.7, .7, .7);
		mBrazos.push_back(ent_brazo);
	}
	if (avispa)
		dron->scale(.5, .5, .5);
}
void Dron::changeBodyColor()
{
	mCenter->setMaterialName("Practica1/amarillo");
}
void Dron::frameRendered(const Ogre::FrameEvent& evt)
{
	if (myTimer->getMilliseconds() < 2000) {//move
		mNode->getParent()->roll(Ogre::Degree(-10 * evt.timeSinceLastFrame));
		for (auto brazo : mBrazos) {
			brazo->getHelice()->getSceneNode()->roll(Ogre::Degree(360 * evt.timeSinceLastFrame));
			for (auto aspa : brazo->getHelice()->mAspas)
				aspa->getCilinder()->roll(Ogre::Degree(-360 * evt.timeSinceLastFrame));
		}

		rot = ((rand() % 11 < 5) ? -1 : 1) * (rand() % 199 + 1);
	}
	else if (myTimer->getMilliseconds() < 4000) //rotate
		mNode->getParent()->yaw(Ogre::Degree(rot * evt.timeSinceLastFrame));

	else
		myTimer->reset();

}
//---------------------------------------------------------------
Sinbad::Sinbad(Ogre::SceneNode* _sinbad, bool dP) :EntityIG(_sinbad)
{
	desplazaPlano = dP;
	_Sinbad = mSM->createEntity("Sinbad.mesh");
	_sinbad->attachObject(_Sinbad);
	_sinbad->setScale(10, 10, 10);
	_sinbad->setPosition(-400, 50, 250);

	animation_piernas = _Sinbad->getAnimationState("RunBase"); //entity se construye sobre una mesh
	animation_piernas->setEnabled(true);
	animation_piernas->setLoop(true);

	animation_brazos = _Sinbad->getAnimationState("RunTop"); //entity se construye sobre una mesh
	animation_brazos->setEnabled(true);
	animation_brazos->setLoop(true);

	animation_dance = _Sinbad->getAnimationState("Dance");
	animation_dance->setEnabled(false);
	animation_dance->setLoop(true);

	AnimationStateSet* aux = _Sinbad->getAllAnimationStates();
	auto it = aux->getAnimationStateIterator().begin();
	std::cout << "\nEstado animaciones Sinbad:\n";
	while (it != aux->getAnimationStateIterator().end())
	{
		auto s = it->first; ++it;
		std::cout << s << "\n";
	}
	std::cout << "\n";

	sword_right = mSM->createEntity("Sword.mesh");
	sword_left = mSM->createEntity("Sword.mesh");

	if (desplazaPlano) {
		_sinbad->setInitialState();
		Vector3 initialPose = _sinbad->getPosition();
		Real duration = 20;
		Animation* anim = mSM->createAnimation("SinbadCorriendo", duration);
		NodeAnimationTrack* track = anim->createNodeTrack(0);
		track->setAssociatedNode(mNode);

		Vector3 src(0, 0, 1);
		Real durPaso = duration / 5.0;

		Vector3 keyFramePos(0, 0, 0);// 0
		TransformKeyFrame* kf = track->createNodeKeyFrame(durPaso * 0);
		kf->setTranslate(keyFramePos);
		kf->setRotation(src.getRotationTo(Vector3(0.0, 0.0, 1.0)));

		keyFramePos = Vector3(0, 0, 0);//1 
		kf = track->createNodeKeyFrame(durPaso);
		kf->setTranslate(keyFramePos);
		kf->setRotation(src.getRotationTo(Vector3(0.5, 0.0, -0.5)));

		keyFramePos = Vector3(-initialPose.x * 2, 0, -initialPose.z * 2);//2
		kf = track->createNodeKeyFrame(durPaso * 2);
		kf->setTranslate(keyFramePos);
		kf->setRotation(src.getRotationTo(Vector3(0.5, 0.0, -0.5)));

		keyFramePos = Vector3(-initialPose.x * 2, 0, -initialPose.z * 2);//3
		kf = track->createNodeKeyFrame(durPaso * 3);
		kf->setTranslate(keyFramePos);
		kf->setRotation(src.getRotationTo(Vector3(-0.5, 0.0, 0.5)));

		keyFramePos = Vector3(0, 0, 0);//4
		kf = track->createNodeKeyFrame(durPaso * 4);
		kf->setTranslate(keyFramePos);
		kf->setRotation(src.getRotationTo(Vector3(-0.5, 0.0, 0.5)));

		keyFramePos = Vector3(0, 0, 0);//5
		kf = track->createNodeKeyFrame(durPaso * 5);
		kf->setRotation(src.getRotationTo(Vector3(0.0, 0.0, 1)));
		kf->setTranslate(keyFramePos);

		animationState = mSM->createAnimationState("SinbadCorriendo");
		animationState->setLoop(true);
		animationState->setEnabled(true);
	}
}
void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if (!animation_dance->getEnabled()) {
		if (!desplazaPlano) {
			double rot = ((rand() % 11 < 5) ? -1 : 1) * (rand() % 119 + 1);
			mNode->getParent()->yaw(Ogre::Degree(rot * evt.timeSinceLastFrame));
			mNode->getParent()->pitch(Ogre::Degree(20 * evt.timeSinceLastFrame));
		}
		else {
			animationState->addTime(evt.timeSinceLastFrame);
		}
	}
	animation_piernas->addTime(evt.timeSinceLastFrame);
	animation_brazos->addTime(evt.timeSinceLastFrame);
	animation_dance->addTime(evt.timeSinceLastFrame);
}
bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt) {
	switch (evt.keysym.sym) {
	case SDLK_b:
		cambiaEspada();
		break;
	case SDLK_v:
		arma();
		break;
	case SDLK_n:
		arma(true);
		break;
	case SDLK_m:
		arma(false);
		break;
	case SDLK_c:
		dance();
	default:
		break;
	}
	return true;
}

void Sinbad::arma(bool setDerecha) {
	if (setDerecha) {
		if (!swordRight) {
			_Sinbad->attachObjectToBone("Handle.R", sword_right);
			swordRight = true;
		}
		if (swordLeft) {
			_Sinbad->detachObjectFromBone(sword_left);
			swordLeft = false;
		}
	}
	else {
		if (!swordLeft) {
			_Sinbad->attachObjectToBone("Handle.L", sword_left);
			swordLeft = true;
		}
		if (swordRight) {
			_Sinbad->detachObjectFromBone(sword_right);
			swordRight = false;
		}
	}
}
void Sinbad::arma() {
	if (!swordRight) {
		_Sinbad->attachObjectToBone("Handle.R", sword_right);
		swordRight = true;
	}
	if (!swordLeft) {
		_Sinbad->attachObjectToBone("Handle.L", sword_left);
		swordLeft = true;
	}
}
void Sinbad::cambiaEspada() {
	arma(!swordRight);
}
void Sinbad::dance() {
	if (!animation_dance->getEnabled()) {
		animation_brazos->setEnabled(false);
		animation_piernas->setEnabled(false);
		animation_dance->setEnabled(true);
	}
	else {
		animation_brazos->setEnabled(true);
		animation_piernas->setEnabled(true);
		animation_dance->setEnabled(false);
	}
}


Bomba::Bomba(Ogre::SceneNode* _bomba) : EntityIG(_bomba)
{
	Ogre::Entity* bomba = mSM->createEntity("Barrel.mesh");
	bomba->setMaterialName("Practica1/bomba");
	_bomba->attachObject(bomba);
	_bomba->setScale(10, 10, 10);

	_bomba->setInitialState();
	Real duration = 3;
	Real desplazamiento = 35;
	Animation* anim = mSM->createAnimation("animVV", duration);
	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	Vector3 keyFramePos(0, 0, 0);// 0 origen
	Vector3 src(0, 0, 1);
	Real durPaso = duration / 4;
	TransformKeyFrame* kf = track->createNodeKeyFrame(0);
	kf->setTranslate(keyFramePos);

	keyFramePos = Vector3(0, desplazamiento, 0);//1 arriba 
	kf = track->createNodeKeyFrame(durPaso);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Vector3(1, 0, 1)));

	keyFramePos = Vector3(0, 0, 0);//2 origen
	kf = track->createNodeKeyFrame(durPaso * 2);
	kf->setTranslate(keyFramePos);

	keyFramePos = Vector3(0, -desplazamiento, 0);//3 abajo
	kf = track->createNodeKeyFrame(durPaso * 3);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1)));

	keyFramePos = Vector3(0, 0, 0);//4 origen
	kf = track->createNodeKeyFrame(durPaso * 4);
	kf->setTranslate(keyFramePos);

	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}

void Bomba::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
	if (time != 0) {
		time -= evt.timeSinceLastFrame;
		std::cout << time << "\n";
		if (time <= 0) {
			time = 0;
			sendEvent(this, MessageKind::BombScene);
		}
	}

}

bool Bomba::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_t) {
		animationState->setEnabled(false);
		time = 350;
	}
	return false;
}
