/*                                                                                                                                                                             
** EPITECH PROJECT, 2020                                                                                                                                                       
** Mesh.cpp                                                                                                                                                                    
** File description:                                                                                                                                                           
** Mesh                                                                                                                                                                        
*/

#include "../include/Component/Mesh.hpp"

Mesh::Mesh(double x, double y, double z, const char *path, irr::scene::ISceneManager *smgr, double rotx, double roty, double rotz, bool rotate, const char *texture, irr::core::vector3df scale) : Component(Cmp::Type::MESH)
{
    this->_coords.X = x;
    this->_coords.Y = y;
    this->_coords.Z = z;
    irr::core::vector3df r;
    r.X = rotx;
    r.Y = roty;
    r.Z = rotz;
    this->_selector = nullptr;
    this->_selectors = nullptr;
    this->_animator = nullptr;
    this->_mesh = smgr->getMesh(path);
    this->_smgr = smgr;
    this->_node = NULL;
    if (_mesh) {
        this->_node = smgr->addAnimatedMeshSceneNode(this->_mesh);
        this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

        this->_node->setMD2Animation(irr::scene::EMAT_STAND);
        this->_node->setPosition(this->_coords);
        this->_node->setScale(scale);
        this->_node->setRotation(r);
        if (texture) {
            std::cout << "set texture" << std::endl;
            this->_node->setMaterialTexture(0, this->_smgr->getVideoDriver()->getTexture(texture));
            this->_node->setFrameLoop(irr::s32(0), irr::s32(178));
        }
    }
    if (_node) {
        this->_selector = smgr->createOctreeTriangleSelector(this->_node->getMesh(), this->_node, 128);
        this->_node->setTriangleSelector(this->_selector);
    }
    if (rotate) {
        irr::scene::ISceneNodeAnimator *anim = smgr->createRotationAnimator(irr::core::vector3df(0,1,0));
        _node->addAnimator(anim);
    }
}

Mesh::~Mesh()
{
    if (this->_selector)
        this->_selector->drop();
    if (this->_selectors)
        this->_selectors->drop();
    if (this->_animator)
        this->_animator->drop();
    this->_smgr->addToDeletionQueue(this->_node);
}

void Mesh::createTriangleSelector(irr::scene::ISceneManager *smgr)
{
    this->_selectors = smgr->createMetaTriangleSelector();
}

irr::scene::IMetaTriangleSelector *Mesh::getTriangleSelectors() const
{
    return this->_selectors;
}

irr::scene::ITriangleSelector *Mesh::getTriangleSelector() const
{
    return this->_selector;
}

irr::scene::IAnimatedMeshSceneNode *Mesh::getNode() const
{
    return this->_node;
}

irr::scene::IAnimatedMesh *Mesh::getMesh() const
{
    return this->_mesh;
}

irr::core::vector3df &Mesh::getCoords()
{
    return this->_coords;
}

void Mesh::setCoords(float x, float y, float z)
{
    this->_coords.X = x;
    this->_coords.Y = y;
    this->_coords.Z = z;
    this->toggleMeshPosition();
}

void Mesh::toggleMeshPosition()
{
    this->_node->setPosition(this->_coords);
}

void Mesh::pushTriangleSelector(irr::scene::ITriangleSelector *selector)
{
    this->_selectors->addTriangleSelector(selector);
}

void Mesh::removeTriangleSelector(irr::scene::ITriangleSelector *selector)
{
    this->_selectors->removeTriangleSelector(selector);
}

void Mesh::createCollisionResponse(irr::scene::ISceneManager *smgr)
{
    if (this->_animator) {
        this->_node->removeAnimator(this->_animator);
        this->_animator->drop();
    }
    this->_animator = smgr->createCollisionResponseAnimator(
        this->_selectors, this->_node, irr::core::vector3df(40, 50, 40),
        irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 0, 0)
    );
    this->_node->addAnimator(this->_animator);
}