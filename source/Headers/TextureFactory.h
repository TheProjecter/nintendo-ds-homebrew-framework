#ifndef TEXTURE_FACTORY_H
#define TEXTURE_FACTORY_H

#include "Singleton.h"
#include "Factory.h"
#include "PCXTexture.h"
#include "BMPTexture.h"

typedef Factory<ITexture> TextureFactory;
typedef Singleton<TextureFactory> TheTextureFactory;

ITexture* CreatePCX()
{
	return new PCXTexture;
}

static bool pcx = TheTextureFactory::Instance()->AddType("pcx", CreatePCX);

ITexture* CreateBMP()
{
	return new BMPTexture;
}

static bool bmp = TheTextureFactory::Instance()->AddType("bmp", CreateBMP);


#endif