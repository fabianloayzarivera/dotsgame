#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include	<iostream>
#include	<string>
#include	<map>
#include	<SDL.h>
#include	<SDL_image.h>
#include	<SDL_ttf.h>

using namespace std;

class TextureManager 
{
public:
	
	static TextureManager* Instance()               
	{                                               
		if (s_pInstance == 0)                        
		{                                           
			s_pInstance = new TextureManager();     
		}                                           
													
		return s_pInstance;                        
	}

	bool load(const char* fileName, string id, SDL_Renderer* pRenderer);
	bool loadFont(const char* aFontFile, const unsigned int &size);
	void draw(string id, int x, int y, int width, int height, float angle,
		SDL_Renderer* pRenderer, SDL_RendererFlip = SDL_FLIP_NONE);
	void drawText(const char* aText, int aX, int aY, SDL_Renderer* pRenderer, SDL_Color fontColor = { 255,255,255,255 });
	void clearFromTextureMap(string id); //delete SDL_Texture from the map
	void clearFont();
private:
	map<string, SDL_Texture*> m_textureMap; //map with all the SDL_Textures
	TextureManager() {};
	~TextureManager();
	TTF_Font* m_font;
	static TextureManager* s_pInstance;
};

#endif // TEXTUREMANAGER_H