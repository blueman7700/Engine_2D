#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

// used to check if the signatures of two entities match, 
// i.e. they have the same components
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

// array storing all the components that an entity can have, max 32.
using ComponentArray = std::array<Component*, maxComponents>;

/// <summary>
/// 
/// </summary>
class Component
{
public:

	Entity* ownerEntity;

	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

	virtual ~Component() {};
};

/// <summary>
/// 
/// </summary>
class Entity
{
public:
	Entity(Manager& p_manager) : manager(p_manager) {}

	void update() 
	{
		for (auto& c : components) c->update();
	}

	void draw()
	{
		for (auto& c : components) c->draw();
	}

	bool hasGroup(Group group)
	{
		return groupBitSet[group];
	}

	void addGroup(Group group);

	void delGroup(Group group)
	{
		groupBitSet[group] = false;
	}

	bool isActive() const { return active; }
	void destroy() { active = false; }

	/// <summary>
	/// Checks to see if the component type is attached to the entity.
	/// </summary>
	/// <typeparam name="T">Component type</typeparam>
	/// <returns>true if the component exists, otherwise false.</returns>
	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	/// <summary>
	/// Creates and attaches a component to the entity.
	/// </summary>
	/// <typeparam name="T">Component type to attach</typeparam>
	/// <typeparam name="...TArgs"></typeparam>
	/// <param name="...mArgs">Arguments to be forwarded to the type constructor</param>
	/// <returns>Reference to the attached component.</returns>
	template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs)
	{
		// create the component
		T* c(new T(std::forward<TArgs>(mArgs)...));
		// set component owner to this entity
		c->ownerEntity = this;
		// create a unique pointer for this component
		std::unique_ptr<Component> uPtr{ c };
		// add component to the back of the component vector
		components.emplace_back(std::move(uPtr));

		// add component to the array depending on its type
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		// init the component
		c->init();

		return *c;
	}

	/// <summary>
	/// Gets a reference to an attached component from the entity.
	/// </summary>
	/// <typeparam name="T">Component type to get</typeparam>
	/// <returns>pointer to an attached component, nullptr if requested component does not exist.</returns>
	template <typename T> T& getComponent() const
	{
		// grab a pointer from the component array, 
		// if this type of component does not exist then a nulllptr will be returned
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
};

/// <summary>
/// Entity Manager class to hold all entity instances and handle all entity creation and deletion.
/// </summary>
class Manager
{
public:
	/// <summary>
	/// Calls the update method for all stored entities.
	/// </summary>
	void update()
	{
		for (auto& e : entities) e->update();
	}

	/// <summary>
	/// Calls the draw method for all stored entities.
	/// </summary>
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	/// <summary>
	/// Removes any entities that are no longer active.
	/// </summary>
	void clean()
	{

		for (auto i(0u); i < maxGroups; i++)
		{
			auto& vec = groupedEntities[i];
			vec.erase(std::remove_if(std::begin(vec), std::end(vec),
				[i](Entity* e)
				{
					return !e->isActive() || !e->hasGroup(i);
				}),
				std::end(vec));
		}

		// remove entities if they are no longer active
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	void addToGroup(Entity* e, Group g)
	{
		groupedEntities[g].emplace_back(e);
	}

	std::vector<Entity*>& getGroup(Group g)
	{
		return groupedEntities[g];
	}

	/// <summary>
	/// Creates and adds a new entity to the entity vector.
	/// </summary>
	/// <returns>Reference to the new entity.</returns>
	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};
