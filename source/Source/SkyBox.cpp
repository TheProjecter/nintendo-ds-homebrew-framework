#include "SkyBox.h"
#include "ResourceManager.h"
#include "GameObjectFactory.h"
#include "Game.h"
#include <nds.h>

static bool skyBoxCreator = TheGameObjectFactory::Instance()->AddType("SkyBox", SkyBox::CreateSkyBox);

GameObject* SkyBox::CreateSkyBox()
{
	return new SkyBox;
}

SkyBox::SkyBox()
{
}

bool SkyBox::Load(File* pFile)
{
	return true;
}

void SkyBox::Update(float gameSpeed)
{

}

void SkyBox::Draw()
{
	glColor3f(1,1,1);

	glTexParameter(0, GL_TEXTURE_WRAP_S);
	glTexParameter(0, GL_TEXTURE_WRAP_T);
	glPushMatrix();
	glScalef(50.0f, 50.0f, 50.0f);

	// Render the front quad
	glBindTexture(0, TheResourceManager::Instance()->GetTexture("surround"));

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
	glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
	glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
	glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f, -0.5f );

	glEnd();

	// Render the left quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
	glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
	glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
	glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
	glEnd();

	// Render the back quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
	glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
	glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
	glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f,  0.5f );
	glEnd();

	// Render the right quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
	glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
	glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f,  0.5f );
	glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
	glEnd();

	// Render the top quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
	glTexCoord2f(0, 0); glVertex3f( -0.5f,  0.5f,  0.5f );
	glTexCoord2f(1, 0); glVertex3f(  0.5f,  0.5f,  0.5f );
	glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
	glEnd();

	// Render the bottom quad
	glBindTexture(0, TheResourceManager::Instance()->GetTexture("bottom"));

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
	glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
	glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
	glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
	glEnd();

	glPopMatrix(1);
}