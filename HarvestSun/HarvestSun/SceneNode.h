//#pragma once
//#include <memory>
//#include <vector>
//#include <SFML/Graphics.hpp>
//
//class SceneNode : public sf::Transformable, public sf::Drawable,
//	private sf::NonCopyable
//{
//public:
//	SceneNode();
//	~SceneNode();
//
//	typedef std::unique_ptr<SceneNode> Ptr;
//
//	void attachChild(Ptr child);
//	SceneNode::Ptr detachChild(const SceneNode& node);
//
//private:
//	std::vector<Ptr> m_children;
//	SceneNode* p_parent;
//
//	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
//	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
//};
//
