#ifndef __OPENGLRENDERER_IO_KEY_MANAGER_H
#define __OPENGLRENDERER_IO_KEY_MANAGER_H

#include <Renderer/RenderWindow.h>

class KeyManager
{
public:
	/**
	*	\brief Instance of the KeyManager (Singleton)
	*	\return A pointer to the KeyManager Instance
	*/
	static KeyManager* instance();

	/**
	*	\brief Destroys the KeyManager instance
	*/
	static void destroy();

	/**
	*	\brief Setup the KeyManager
	*	\param[in] window The window the keys should be registered in
	*/
	void setup(const RenderWindow& window);

	/**
	*	\brief Checks if a key is pressed
	*	\param[in] key The key to be checked
	*	\return True if the key is pressed, false otherwise
	*/
	bool isKeyDown(const uint32_t& key);

	/**
	*	\brief Check if the left mouse button is pressed
	*	\return True if the key is pressed, false otherwise
	*/
	bool leftClicked();

	/**
	*	\brief Check if the right mouse button is pressed
	*	\return True if the key is pressed, false otherwise
	*/
	bool rightClicked();

private:
	static KeyManager* _instance; /**<< The static KeyManager Pointer*/
	KeyManager() = default; /**<< Make KeyManager private*/
	KeyManager(const KeyManager&); /**<< Make KeyManager private*/

	RenderWindow _window; /**<< The Window of the KeyManager*/
};

#endif