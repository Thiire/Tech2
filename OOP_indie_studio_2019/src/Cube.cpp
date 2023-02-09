/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Cube
*/

#include "../include/Component/Cube.hpp"

Cube::Cube(double x, double y, double z, irr::scene::ISceneManager *smgr, irr::video::ITexture *texture) : Component(Cmp::Type::CUBE)
{
    this->_coords.X = x;
    this->_coords.Y = y;
    this->_coords.Z = z;
    this->_smgr = smgr;
    this->_node = _smgr->addCubeSceneNode(1.0f, nullptr, 1, irr::core::vector3df(x, y, z), irr::core::vector3df(0,0,0), irr::core::vector3df(100.0f, 100.0f, 100.0f));
    this->_node->setMaterialTexture(0, texture);
    this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    if (this->_node) {
        this->_selector = smgr->createOctreeTriangleSelector(this->_node->getMesh(), this->_node, 128);
        this->_node->setTriangleSelector(this->_selector);
    }
}

Cube::~Cube()
{
    this->_selector->drop();
    this->_smgr->addToDeletionQueue(this->_node);
}

irr::scene::ITriangleSelector *Cube::getTriangleSelector() const
{
    return this->_selector;
}

irr::scene::IMeshSceneNode *Cube::getNode() const
{
    return this->_node;
}

irr::core::vector3df &Cube::getCoords()
{
    return this->_coords;
}

void Cube::setCoords(float x, float y, float z)
{
    this->_coords.X = x;
    this->_coords.Y = y;
    this->_coords.Z = z;
}
