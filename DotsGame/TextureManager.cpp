#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(const char* fileName, string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName); 

	if (pTempSurface == 0)
	{
		cout << "error loading file: " << fileName << endl;
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface); 
	SDL_FreeSurface(pTempSurface); 

	if (pTexture == 0) 
	{
		cout << "error creating Texture of file: " << fileName << endl;
		return false;
	}

	m_textureMap[id] = pTexture; 
	return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, float angle, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect; //source rectangle
	SDL_Rect destRect; //destination rectangle

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x; //select x axis on game window
	destRect.y = y; //select y axis on game window

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip); //Load image to render buffer.
}


void TextureManager::clearFromTextureMap(string id)
{
	m_textureMap.erase(id);
}

bool TextureManager::loadFont(const char* aFontFile, const unsigned int &size)
{
	m_font = TTF_OpenFont(aFontFile, size);
	return m_font ? true : false;
}

void TextureManager::drawText(const char* aText, int aX, int aY, SDL_Renderer* pRenderer, SDL_Color fontColor )
{
	
	SDL_Surface* surface = TTF_RenderText_Solid(m_font, aText, fontColor);
	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(pRenderer, surface);

	SDL_Rect sizeRect;
	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = surface->w;
	sizeRect.h = surface->h;

	SDL_Rect posRect;
	posRect.x = aX;
	posRect.y = aY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(pRenderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
}

void TextureManager::clearFont() 
{
	TTF_CloseFont(m_font);
}

TextureManager::~TextureManager() 
{
	for (auto const& x : m_textureMap)
	{
		SDL_DestroyTexture(x.second);
	}
}