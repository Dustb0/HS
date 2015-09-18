//#include "SceneNode.h"
//#include <algorithm>
//
//SceneNode::SceneNode()
//{
//}
//
//SceneNode::~SceneNode()
//{
//}
//
//void SceneNode::attachChild(Ptr child)
//{
//	child->p_parent = this;
//	m_children.push_back(std::move(child));
//}
//
//SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
//{
//	auto found = std::find_if(m_children.begin(), m_children.end(), [&](Ptr& p) -> bool { return p.get() == &node; });
//	Ptr result = std::move(*found);
//	result->p_parent = nullptr;
//	m_children.erase(found);
//	return result;
//}
//
//void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	states.transform *= getTransform();
//	drawCurrent(target, states);
//
//	for (auto itr = m_children.begin(); itr != m_children.end(); ++itr)
//	{
//		(*itr)->draw(target, states);
//	}
//}