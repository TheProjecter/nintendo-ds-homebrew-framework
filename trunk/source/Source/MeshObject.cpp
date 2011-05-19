#include "MeshObject.h"
#include "ResourceManager.h"
#include <math.h>
#include <iostream>
#include <nds.h>

MeshObject::MeshObject() :  m_meshName(""),
							m_texName(""),
							m_currentAnim("stand"),
							m_rotation(0),
							m_animTimer(0),
							m_bMoving(false)
{
}

bool MeshObject::Load(File* pFile)
{
	char mesh[50], tex[50], anim[50];
	float x, y, rot;

	pFile->GetString(mesh);
	m_meshName.assign(mesh);

	pFile->GetString(tex);
	m_texName.assign(tex);

	pFile->GetString(anim);
	m_currentAnim.assign(anim);

	pFile->GetFloat(&x);
	pFile->GetFloat(&y);

	pFile->GetFloat(&rot);

	m_rotation = rot;
	m_position = Vec2f(x, y);

	return true;
}

void MeshObject::Update(float gameSpeed)
{
	m_position += m_velocity * gameSpeed;

	if(m_animTimer < 1.0f)
	{
		m_animTimer += gameSpeed;
	}
	else
	{
		m_animTimer = 0;
	}
}

void MeshObject::Draw()
{
	TheResourceManager::Instance()->GetMesh(m_meshName)->SetAnimation(m_currentAnim.c_str());

	glPushMatrix();

	glTranslatef(m_position.m_x, -3.0f, m_position.m_y); // magic number y

	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glRotatef(m_rotation, 0.0f, 0.0f, 1.0f);

	TheResourceManager::Instance()->GetMesh(m_meshName)->Draw(m_animTimer, m_texName);

	Animate();

	glPopMatrix(1);
}

void MeshObject::Animate()
{
	if(m_velocity.m_x > Fixed(0) || m_velocity.m_y > Fixed(0) || m_velocity.m_x < Fixed(0) || m_velocity.m_y < Fixed(0))
	{
		m_currentAnim = "run";
	}
	else
	{
		m_currentAnim = "stand";
	}
}