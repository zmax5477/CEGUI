/************************************************************************
	filename: 	ogrerenderer.h
	created:	11/5/2004
	author:		Paul D Turner
	
	purpose:	Interface for main Ogre GUI renderer class
*************************************************************************/
/*************************************************************************
    Crazy Eddie's GUI System (http://crayzedsgui.sourceforge.net)
    Copyright (C)2004 Paul D Turner (crayzed@users.sourceforge.net)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*************************************************************************/
/*************************************************************************
	This file contains code that is specific to Ogre (http://www.ogre3d.org)
*************************************************************************/
#ifndef _ogrerenderer_h_
#define _ogrerenderer_h_

#if defined( __WIN32__ ) || defined( _WIN32 )
#   ifdef OGRE_GUIRENDERER_EXPORTS
#       define OGRE_GUIRENDERER_API __declspec(dllexport)
#   else
#       define OGRE_GUIRENDERER_API __declspec(dllimport)
#   endif
#else
#   define OGRE_GUIRENDERER_API
#endif

#include "CEGUIBase.h"
#include "CEGUIRenderer.h"
#include "CEGUITexture.h"

#include <Ogre.h>

// Start of CEGUI namespace section
namespace CEGUI
{
/*************************************************************************
	Forward refs
*************************************************************************/
class OgreTexture;
class OgreRenderer;
class OgreRQListener;


/*!
\brief
	RenderQueueListener based class used to hook into the ogre rendering system
*/
class OgreRQListener : public Ogre::RenderQueueListener
{
public:
	OgreRQListener(OgreRenderer* renderer, Ogre::RenderQueueGroupID queue_id, bool post_queue)
	{
		d_renderer		= renderer;
		d_queue_id		= queue_id;
		d_post_queue	= post_queue;
	}

	virtual ~OgreRQListener() {}

	virtual void	renderQueueStarted(Ogre::RenderQueueGroupID id, bool& skipThisQueue);
	virtual void	renderQueueEnded(Ogre::RenderQueueGroupID id, bool& repeatThisQueue);

private:
	/*************************************************************************
		Implementation Data
	*************************************************************************/
	OgreRenderer*				d_renderer;		//!< CEGUI renderer object for Ogre.
	Ogre::RenderQueueGroupID	d_queue_id;		//!< ID of the queue that we are hooked into
	bool						d_post_queue;	//!< true if we render after everything else in our queue.
};


/*!
\brief
	Renderer class to interface with Ogre engine.
*/
class OGRE_GUIRENDERER_API OgreRenderer : public Renderer
{
public:
	/*!
	\brief
		Constructor for renderer class that uses Ogre for rendering.

	\param queue_id
		Ogre::RenderQueueGroupID value that specifies where the GUI should appear in the ogre rendering output.

	\param post_queue
		set to true to have GUI rendered after render queue \a queue_id, or false to have the GUI rendered before render queue
		\a queue_id.

	\param max_quads
		Maximum number of quads that the Renderer will be able to render per frame.
	*/
	OgreRenderer(Ogre::RenderWindow* window, Ogre::RenderQueueGroupID queue_id, bool post_queue, uint max_quads);


	/*!
	\brief
		Destructor for Ogre renderer.
	*/
	virtual ~OgreRenderer(void);



	// add's a quad to the list to be rendered
	virtual	void	addQuad(const Rect& dest_rect, float z, const Texture* tex, const Rect& texture_rect, const ColourRect& colours);

	// perform final rendering for all queued renderable quads.
	virtual	void	doRender(void);

	// clear the queue
	virtual	void	clearRenderList(void);


	/*!
	\brief
		Enable or disable the queueing of quads from this point on.

		This only affects queueing.  If queueing is turned off, any calls to addQuad will cause the quad to be rendered directly.  Note that
		disabling queueing will not cause currently queued quads to be rendered, nor is the queue cleared - at any time the queue can still
		be drawn by calling doRender, and the list can be cleared by calling clearRenderList.  Re-enabling the queue causes subsequent quads
		to be added as if queueing had never been disabled.

	\param setting
		true to enable queueing, or false to disable queueing (see notes above).

	\return
		Nothing
	*/
	virtual void	setQueueingEnabled(bool setting)		{d_queueing = setting;}


	// create an empty texture
	virtual	Texture*	createTexture(void);

	// create a texture and load it with the specified file.
	virtual	Texture*	createTexture(const String& filename);

	// create a texture and set it to the specified size
	virtual	Texture*	createTexture(float size);

	// destroy the given texture
	virtual	void		destroyTexture(Texture* texture);

	// destroy all textures still active
	virtual void		destroyAllTextures(void);


	/*!
	\brief
		Return whether queueing is enabled.

	\return
		true if queueing is enabled, false if queueing is disabled.
	*/
	virtual bool	isQueueingEnabled(void) const	{return d_queueing;}


	/*!
	\brief
	Return the current width of the display in pixels

	\return
	float value equal to the current width of the display in pixels.
	*/
	virtual float	getWidth(void) const		{return d_display_area.getWidth();}


	/*!
	\brief
	Return the current height of the display in pixels

	\return
	float value equal to the current height of the display in pixels.
	*/
	virtual float	getHeight(void) const		{return d_display_area.getHeight();}


	/*!
	\brief
	Return the size of the display in pixels

	\return
	Size object describing the dimensions of the current display.
	*/
	virtual Size	getSize(void) const			{return d_display_area.getSize();}


	/*!
	\brief
	Return a Rect describing the screen

	\return
	A Rect object that describes the screen area.  Typically, the top-left values are always 0, and the size of the area described is
	equal to the screen resolution.
	*/
	virtual Rect	getRect(void) const			{return d_display_area;}


	/*!
	\brief
		Return the maximum texture size available

	\return
		Size of the maximum supported texture in pixels (textures are always assumed to be square)
	*/
	virtual	uint	getMaxTextureSize(void) const		{return 2048;}		// TODO: Change to proper value


	/*!
	\brief
		Return the horizontal display resolution dpi

	\return
		horizontal resolution of the display in dpi.
	*/
	virtual	uint	getHorzScreenDPI(void) const	{return 96;}


	/*!
	\brief
		Return the vertical display resolution dpi

	\return
		vertical resolution of the display in dpi.
	*/
	virtual	uint	getVertScreenDPI(void) const	{return 96;}


private:
	/************************************************************************
		Implementation Constants
	************************************************************************/
	static const int			VERTEX_PER_QUAD;							//!< number of vertices per quad
	static const int			VERTEX_PER_TRIANGLE;						//!< number of vertices for a triangle
	static const int			VERTEXBUFFER_CAPACITY;						//!< capacity of the allocated vertex buffer


	/*************************************************************************
	    Implementation Structs & classes
	*************************************************************************/
	/*!
	\brief
		structure used for all vertices.
	*/
	struct QuadVertex {
		float x, y, z;			//!< The position for the vertex.
		Ogre::RGBA diffuse;		//!< colour of the vertex
		float tu1, tv1;			//!< texture coordinates
	};

	/*!
	\brief
		structure holding details about a quad to be drawn
	*/
	struct QuadInfo
	{
		Ogre::Texture*		texture;
		Rect				position;
		float				z;
		Rect				texPosition;
		ColourRect			colours;
	};


	// this is a function object that is used by the sorting algorithm to
	// sort the quads.  It would be possible to define comparison operators
	// the the QuadInfo structure and not have this - the reason this was
	// not done, is because the system could be extended to have >1 quad
	// list each sorted by a different key (by texture for non-alpha stuff, etc).
	struct quadsorter
		: public std::binary_function<QuadInfo*, QuadInfo*, bool>
	{
		bool operator()(const QuadInfo* _Left, const QuadInfo* _Right) const
		{return (_Left->z > _Right->z);}
	};

	/*************************************************************************
	    Implementation Methods
	*************************************************************************/
	// setup states etc
	void	initRenderStates(void);

	// renders whatever is in the vertex buffer
	void	renderVBuffer(void);

	// sort quads list according to texture
	void	sortQuads(void);

	// render a quad directly to the display
	void	renderQuadDirect(const Rect& dest_rect, float z, const Texture* tex, const Rect& texture_rect, const ColourRect& colours);

	// convert ARGB colour value to whatever the Ogre render system is expecting.
	ulong	colourToOgre(colour col) const;

	/*************************************************************************
	    Implementation Data
	*************************************************************************/
	Rect				d_display_area;
	QuadInfo**			d_quadList;
	QuadInfo*			d_quadBuff;
	int					d_quadBuffPos;
	int					d_quadBuffSize;

	bool	d_queueing;		//!< setting for queueing control.

	// Ogre specific bits.
	Ogre::Root*					d_ogre_root;		//!< pointer to the Ogre root object that we attach to
	Ogre::RenderSystem*			d_render_sys;		//!< Pointer to the render system for Ogre.
	Ogre::RenderQueueGroupID	d_queue_id;			//!< ID of the queue that we are hooked into
	Ogre::Texture*				d_currTexture;		//!< currently set texture;
	Ogre::RenderOperation		d_render_op;		//!< Ogre render operation we use to do our stuff.
	Ogre::HardwareVertexBufferSharedPtr	d_buffer;	//!< vertex buffer to queue sprite rendering

	OgreRQListener*				d_ourlistener;
	bool						d_post_queue;		//!< true if we render after everything else in our queue.
	int							d_bufferPos;		//!< index into buffer where next vertex should be put.
	bool						d_sorted;			//!< true when data in quad list is sorted.
	Point						d_texelOffset;		//!< Offset required for proper texel mapping.

	std::list<OgreTexture*>		d_texturelist;		//!< List used to track textures.
};

} // End of  CEGUI namespace section


#endif	// end of guard _ogrerenderer_h_
