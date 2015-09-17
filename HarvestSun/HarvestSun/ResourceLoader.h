#pragma once
#include <map>
#include <memory>

namespace Textures
{
	enum ID {Jack};
}

template <typename Resource, typename Identifier>
class ResourceLoader
{
public:
	ResourceLoader()
	{

	}

	~ResourceLoader()
	{

	}

	void Load(Identifier resID, const std::string& filename)
	{
		std::unique_ptr<Resource> resource(new Resource());
		resource->loadFromFile(filename);

		m_resources.insert(std::make_pair(resID, std::move(resource)));
	}

	template <typename Parameter>
	void Load(Identifier resID, const std::string& filename, const Parameter& secondParam)
	{
		std::unique_ptr<Resource> resource(new Resource());
		resource->loadFromFile(filename, secondParam);

		m_resources.insert(std::make_pair(resID, std::move(resource)));
	}

	Resource& Get(Identifier resID)	{		auto res = m_resources.find(resID);
		return *res->second;	}	const Resource& Get(Identifier resID) const
	{
		auto res = m_resources.find(resID);
		return *res->second;
	}

private:
	std::map<Identifier, std::unique_ptr<Resource>> m_resources;

};

