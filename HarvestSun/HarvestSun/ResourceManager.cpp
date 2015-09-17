#include "ResourceManager.h"


sf::Texture& ResourceManager::Get(Resources::ID resID)
{
	auto res = m_resources.find(resID);
	return *res->second;
}

const sf::Texture& ResourceManager::Get(Resources::ID resID) const
{
	auto res = m_resources.find(resID);
	return *res->second;
}