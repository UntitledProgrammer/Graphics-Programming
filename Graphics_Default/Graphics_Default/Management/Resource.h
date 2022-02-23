#pragma once
#ifndef RESOURCE_H
#define RESOURCE_H

//Includes:
#include<string>
#include<map>

/// <summary>A resource is a very basic base class that offers some simple functonality that will be needed for any managment of a specific type of object. It is the users responsability to decide how they handle each resource object.</summary>
template<typename ResourceType> class Resource
{
private:
    //Attributes:
    std::map<std::string, ResourceType> resources;

public:
    //Constructor:
    Resource() {};

    //Destructor:
    ~Resource() {};

    //Methods:
    /// <summary>Add a resource of 'ResourceType' to structure.</summary>
    void Insert(std::string key, ResourceType resource)
    {
        resources.emplace(key, resource);
    }

    ResourceType Get(std::string key)
    {
        return resources[key];
    }

    //Friends:
    friend class ResourceManager;
    friend class Hierarchy;
};
#endif // !RESOURCE_H