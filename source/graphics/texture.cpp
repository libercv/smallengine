//
//	texture.cpp - source file
//
//	David Henry - tfc_duke@hotmail.com
//

#include "texture.h"

// initialize the singleton
CTextureManager	*CTextureManager::m_singleton = 0;

// ----------------------------------------------
// GetInstance() - get a pointer to the unique
// CTextureManager instance (the singleton)
// ----------------------------------------------

CTextureManager *CTextureManager::GetInstance( void )
{
	if( m_singleton == 0 )
		m_singleton = new CTextureManager;

	return ((CTextureManager *)m_singleton);
}

// ----------------------------------------------
// FreeInstance() - delete the unique CTextureManager
// instance.
// ----------------------------------------------

void CTextureManager::FreeInstance( void )
{
	if( m_singleton != 0 )
	{
		delete m_singleton;
		m_singleton = 0;
	}
}



// ----------------------------------------------
// Initialize() - create a checker for the default texture.
// ----------------------------------------------

void CTextureManager::Initialize( void )
{
	// this is the first texture loaded. If a texture
	// can't be loaded, we use this instead

	// initialize only once!

	// HACK: asi no me compilaba.
	//if( (*m_texlist.begin()) == (*m_texlist.end()) )
	if( m_texlist.begin() == m_texlist.end() )
	{
		CTexture *tex = new CTexture( "default" );

		// create and initialize the texture
		glGenTextures( 1, &tex->m_id );
		glBindTexture( GL_TEXTURE_2D, tex->m_id );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		m_texlist.push_back( tex );

		// create a checker for the default texture
		int i, j, c;				// temporary variable
		unsigned char *checker;		// texture data

		checker = new unsigned char[ 64 * 64 * 4 ];

		for( i = 0; i < 64; i++ )
		{
			for( j = 0; j < 64; j++ )
			{
				c = ( !(i & 8) ^ !(j & 8)) * 255;

				checker[ (i * 256) + (j * 4) + 0 ] = (unsigned char)c;
				checker[ (i * 256) + (j * 4) + 1 ] = (unsigned char)c;
				checker[ (i * 256) + (j * 4) + 2 ] = (unsigned char)c;
				checker[ (i * 256) + (j * 4) + 3 ] = (unsigned char)255;

			}
		}


		glTexImage2D( GL_TEXTURE_2D, 0, 4, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, checker );

		delete [] checker;
	}
}



// ----------------------------------------------
// LoadTexture() - load a texture from file. Verify
// if it has not already been loaded before. If yes,
// return stored texture's id, otherwise, load it
// and return the new texture id generated.
// ----------------------------------------------

unsigned int CTextureManager::LoadTexture(  char *filename )
{
	unsigned int id = 0;
	unsigned char *texels = 0;
	bool success;
	//int				width, height;

	for( TListItor itor = m_texlist.begin(); itor != m_texlist.end(); ++itor )
	{
		if( strcmp( (*itor)->GetName(), filename ) == 0 )
			return (*itor)->GetTexId();
	}

	Small::Image *imagen;
	imagen = new Small::Image();
	success = imagen->Load(filename);
	
	if( success == true  )
	{
		// imagen->FlipVertically();
		glGenTextures( 1, &id );
		glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
		glBindTexture( GL_TEXTURE_2D, id );
		int textureType = GL_RGB;
		if(imagen->bpp == 32)
			textureType = GL_RGBA;

		gluBuild2DMipmaps(GL_TEXTURE_2D, imagen->bpp/8, imagen->width, imagen->height, textureType ,GL_UNSIGNED_BYTE, imagen->data);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		// PENDIENTE: Si hacemos esto las texturas del BSP se ven mal.
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// PENDIENTE: pero si hacemos esto se ve mal el bitmap del mouse
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );


		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// create a new CTexture object and push it at the end of the linked list

		CTexture *tex = new CTexture( id, filename );
		m_texlist.push_back( tex );
	}
	else
	{
		Small::Log::Instance().Write("Textura %s no encontrada", filename);

		// No podemos cargar la textura. Usamos la textura por defecto.
		id = (*m_texlist.begin())->GetTexId();
	}

	//if( texels )
	//	delete [] texels;

	delete imagen;
	return id;
}



// ----------------------------------------------
// DeleteTexture() - delete texture.
// ----------------------------------------------

void CTextureManager::DeleteTexture( unsigned int id )
{
	for( TListItor itor = m_texlist.begin(); itor != m_texlist.end(); ++itor )
	{
		if( (*itor)->GetTexId() == id )
		{
			delete (*itor);
			itor = m_texlist.erase( itor );
			break;
		}
	}
}



// ----------------------------------------------
// CleanAllTextures() - delete all textures stored
// in the linked list.
// ----------------------------------------------

void CTextureManager::CleanAllTextures( void )
{
	if( m_texlist.size() <= 0 )
		return;

	for( TListItor itor = m_texlist.begin(); itor != m_texlist.end(); ++itor)
	{
		delete (*itor);
		itor = m_texlist.erase( itor );
	}
}
