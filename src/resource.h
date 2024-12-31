#ifndef RESOURCE_H
#define RESOURCE_H

#include "my_functions.h"

class Resource{
public:
    virtual ~Resource() = default;  // Virtual destructor for polymorphism
};

class ResourceManager {
public:
    std::unordered_map<std::string, std::shared_ptr<Resource>> resourceCache;	// A map to store resources by their file paths

	void Initialize();



    template <typename T>												// Template method to load or get a resource
    std::shared_ptr<T> Load(const std::string& filepath) {
        auto it = resourceCache.find(filepath);
        if (it != resourceCache.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        std::shared_ptr<T> resource = std::make_shared<T>(filepath);
        resourceCache[filepath] = resource;
        return resource;
    }

    template <typename T>												// Template method to get an already loaded resource
    std::shared_ptr<T> Get(const std::string& filepath) {
        auto it = resourceCache.find(filepath);
        if (it != resourceCache.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;													// If the resource is not found, return a null pointer
    }

    void Unload(const std::string& filepath) {							// Unload a resource
        resourceCache.erase(filepath);
        std::cout << "Unloaded Resource: " << filepath << std::endl;
    }
};

class myTexture : public Resource {
public:
	Texture2D myyTexture;
    std::string filepath;

    myTexture(const std::string& path) : filepath(path) {
		myyTexture= LoadTexture(to_const_char(path));
        std::cout << "Loading Texture: " << filepath << std::endl;		// Simulate loading a texture
    }
};

class myModel : public Resource {
public:
    std::string filepath;

    myModel(const std::string& path) : filepath(path) {
		Model model= LoadModel(to_const_char(path));
        std::cout << "Loading Model: " << filepath << std::endl;		 // Simulate loading a model
    }
};

#endif // RESOURCE_H