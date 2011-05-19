#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include "DSMD2.h"
#include "Singleton.h"
#include "Factory.h"

typedef Factory<IMesh> MeshFactory;
typedef Singleton<MeshFactory> TheMeshFactory;

IMesh* CreateMD2()
{
	return new DSMD2;
}

static bool md2 = TheMeshFactory::Instance()->AddType("md2", CreateMD2);

#endif