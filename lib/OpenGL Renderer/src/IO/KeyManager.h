#ifndef __OPENGLRENDERER_IO_KEY_MANAGER_H
#define __OPENGLRENDERER_IO_KEY_MANAGER_H

#include <Renderer/RenderWindow.h>

class KeyManager
{
public:
	/**
	*	\brief Setup the KeyManager
	*	\param[in] window The window the keys should be registered in
	*/
	inline static void setup(const RenderWindow& window) { _instance->setupImpl(window); }

	/**
	*	\brief Checks if a key is pressed
	*	\param[in] key The key to be checked
	*	\return True if the key is pressed, false otherwise
	*/
	inline static bool isKeyDown(const uint32_t& key) { return _instance->isKeyDownImpl(key); }

	/**
	*	\brief Check if the left mouse button is pressed
	*	\return True if the key is pressed, false otherwise
	*/
	inline static bool leftClicked() { return _instance->leftClickedImpl(); }

	/**
	*	\brief Check if the right mouse button is pressed
	*	\return True if the key is pressed, false otherwise
	*/
	inline static bool rightClicked() { return _instance->rightClickedImpl(); }

private:
	void setupImpl(const RenderWindow& window);
	bool isKeyDownImpl(const uint32_t& key);
	bool leftClickedImpl();
	bool rightClickedImpl();

	static KeyManager* _instance; /**<< The static KeyManager Pointer*/
	KeyManager() = default; /**<< Make KeyManager private*/
	KeyManager(const KeyManager&); /**<< Make KeyManager private*/

	RenderWindow _window; /**<< The Window of the KeyManager*/
};

#endif