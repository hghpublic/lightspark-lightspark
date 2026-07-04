/**************************************************************************
    Lightspark, a free flash player implementation

    Copyright (C) 2010-2013  Alessandro Pignotti (a.pignotti@sssup.it)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#ifndef BACKENDS_GRAPHICS_H
#define BACKENDS_GRAPHICS_H 1

#define CHUNKSIZE_REAL 126 // 1 pixel on each side is used for clamping to edge
#define CHUNKSIZE 128

#include "interfaces/backends/graphics.h"
#include "interfaces/threading.h"
#include "compat.h"
#include <vector>
#include "smartrefs.h"
#include "swftypes.h"
#ifdef ENABLE_CAIRO
#include <cairo.h>
#endif
#include "backends/geometry.h"
#include "memory_support.h"

namespace lightspark
{
class RenderThread;
class SurfaceState;
class DisplayObject;
class ColorTransformBase;
	
class TextureChunk
{
friend class GLRenderContext;
friend class RenderThread;
private:
	/*
	 * For GLRenderContext texId is an OpenGL texture id and chunks is an array of used
	 * chunks inside such texture.
	 * For CairoRenderContext texId is an arbitrary id for the texture and chunks is
	 * not used.
	 */
	uint32_t* chunks = nullptr;
	uint32_t texId = 0;
	TextureChunk(uint32_t w, uint32_t h);
public:
	TextureChunk() {}
	TextureChunk(const TextureChunk& r);
	TextureChunk& operator=(const TextureChunk& r);
	~TextureChunk();
	bool resizeIfLargeEnough(uint32_t w, uint32_t h);
	uint32_t getNumberOfChunks() const { return ((width+CHUNKSIZE_REAL-1)/CHUNKSIZE_REAL)*((height+CHUNKSIZE_REAL-1)/CHUNKSIZE_REAL); }
	bool isValid() const { return chunks; }
	void makeEmpty();
	void setChunks(uint8_t* buf);
	uint32_t width = 0;
	uint32_t height = 0;
	number_t xContentScale = 1; // scale the bitmap content was generated for
	number_t yContentScale = 1;
	number_t xOffset = 0; // texture topleft from Shape origin
	number_t yOffset = 0;
};

struct RefreshableSurface
{
	IDrawable* drawable;
	DisplayObject* displayobject;
};

class IDrawable
{
protected:
	int32_t width;
	int32_t height;
	float xContentScale;
	float yContentScale;
	SurfaceState* state;
public:
	IDrawable(float w, float h, float x, float y,
			  float xs, float ys, float xcs, float ycs,
			  bool _ismask, bool _cacheAsBitmap,
			  float _scaling, float a,
			  const ColorTransformBase& _colortransform,
			  SMOOTH_MODE _smoothing,
			  AS_BLENDMODE _blendmode,
			  const MATRIX& _m);
	IDrawable(float _width, float _height, float _xContentScale, float _yContentScale,SurfaceState* _state)
		:width(_width),height(_height), xContentScale(_xContentScale), yContentScale(_yContentScale),state(_state)
	{
		// state will be deleted in cachedSurface
	}
	virtual ~IDrawable();
	/*
	 * This method returns a raster buffer of the image
	 * The various implementation are responsible for applying the
	 * masks
	 */
	virtual uint8_t* getPixelBuffer(bool* isBufferOwner=nullptr, uint32_t* bufsize=nullptr)=0;
	virtual bool isCachedSurfaceUsable(const DisplayObject*) const {return true;}
	int32_t getWidth() const { return width; }
	int32_t getHeight() const { return height; }
	float getXContentScale() const { return xContentScale; }
	float getYContentScale() const { return yContentScale; }
	SurfaceState* getState() const { return state; }
};
#ifdef ENABLE_CAIRO
class AsyncDrawJob: public IThreadJob, public ITextureUploadable
{
private:
	IDrawable* drawable;
	/**
	 * The DisplayObject owning this render request. We incRef/decRef it
	 * in our constructor/destructor to make sure that it does not go away
	 */
	DisplayObject* owner;
	uint8_t* surfaceBytes;
	bool uploadNeeded;
	bool isBufferOwner;
public:
	/*
	 * @param o The DisplayObject that is being rendered. It is a reference to
	 * make sure the object survives until the end of the rendering
	 * @param d IDrawable to be rendered asynchronously. The pointer is now
	 * owned by this instance
	 */
	AsyncDrawJob(IDrawable* d, DisplayObject* o);
	~AsyncDrawJob();
	//IThreadJob interface
	void execute() override;
	void threadAbort() override;
	void jobFence() override;
	//ITextureUploadable interface
	uint8_t* upload(bool refresh) override;
	void sizeNeeded(uint32_t& w, uint32_t& h) const override;
	TextureChunk& getTexture() override;
	void uploadFence() override;
	void contentScale(number_t& x, number_t& y) const override;
	void contentOffset(number_t& x, number_t& y) const override;
	DisplayObject* getOwner() { return owner; }
};

/**
	The base class for render jobs based on cairo
	Stores an internal copy of the data to be rendered
*/
class CairoRenderer: public IDrawable
{
protected:
	static void cairoClean(cairo_t* cr);
	cairo_surface_t* allocateSurface(uint8_t*& buf);
	virtual void executeDraw(cairo_t* cr)=0;
	static void copyRGB15To24(uint32_t& dest, uint8_t* src);
	static void copyRGB24To24(uint32_t& dest, uint8_t* src);
public:
	CairoRenderer(const MATRIX& _m, float _x, float _y, float _w, float _h
				  , float _xs, float _ys
				  , bool _ismask, bool _cacheAsBitmap
				  , float _scaling, float _a
				  , const ColorTransformBase& _colortransform
				  , SMOOTH_MODE _smoothing
				  , AS_BLENDMODE _blendmode);
	//IDrawable interface
	uint8_t* getPixelBuffer(bool* isBufferOwner=nullptr, uint32_t* bufsize=nullptr) override;
	bool isCachedSurfaceUsable(const DisplayObject*) const override;
	/*
	 * Converts data (which is in RGB format) to the format internally used by cairo.
	 */
	static void convertBitmapToCairo(std::vector<uint8_t, reporter_allocator<uint8_t>>& data, uint8_t* inData, uint32_t width,
					 uint32_t height, size_t* dataSize, size_t* stride, uint32_t bpp);
	/*
	 * Converts data (which is in ARGB or RGBA(png) format) to the format internally used by cairo.
	 */
	static void convertBitmapWithAlphaToCairo(std::vector<uint8_t, reporter_allocator<uint8_t>>& data, uint8_t* inData, uint32_t width,
			uint32_t height, size_t* dataSize, size_t* stride, bool frompng);
};

class CairoTokenRenderer : public CairoRenderer
{
private:
	static void adjustFillStyle(cairo_t* cr, const FILLSTYLE* style, cairo_matrix_t* origmat, double scaleCorrection);
	static void executefill(cairo_t* cr, const FILLSTYLE* style, cairo_pattern_t* pattern, double scaleCorrection);
	static void executestroke(cairo_t* stroke_cr, const LINESTYLE2* style, cairo_pattern_t* pattern, double scaleCorrection, bool isMask, CairoTokenRenderer* th, bool skippaint=false);
	static cairo_pattern_t* FILLSTYLEToCairo(const FILLSTYLE& style, double scaleCorrection, bool isMask);
	static bool cairoPathFromTokens(cairo_t* cr, NullableRef<tokenListRef> tokens, double scaleCorrection, bool skipFill, bool isMask, number_t xstart, number_t ystart, CairoTokenRenderer* th=nullptr, int* starttoken=nullptr,bool* hasFillTokens=nullptr);
	static void quadraticBezier(cairo_t* cr, double control_x, double control_y, double end_x, double end_y);
	/*
	   The tokens to be drawn
	*/
	_NR<tokenListRef> filltokens;
	_NR<tokenListRef> stroketokens;
	/*
	 * This is run by CairoRenderer::execute()
	 */
	void executeDraw(cairo_t* cr) override;
	number_t xstart;
	number_t ystart;
public:
	/*
	   CairoTokenRenderer constructor

	   @param _filltokens pointer to the filltokens to be drawn.
	   @param _stroketokens pointer to the stroketokens to be drawn.
	   @param _m The whole transformation matrix
	   @param _s The scale factor to be applied in both the x and y axis
	   @param _a The alpha factor to be applied
	   @param _ms The masks that must be applied
	   @param _smoothing indicates if the tokens should be rendered with antialiasing
	*/
	CairoTokenRenderer(_NR<tokenListRef> _filltokens,_NR<tokenListRef> _stroketokens, const MATRIX& _m,
			int32_t _x, int32_t _y, int32_t _w, int32_t _h,
			float _xs, float _ys,
			bool _ismask, bool _cacheAsBitmap,
			float _scaling, float _a,
			const ColorTransformBase& _colortransform,
			SMOOTH_MODE _smoothing, AS_BLENDMODE _blendmode,
			number_t _xstart, number_t _ystart);
	/*
	   Hit testing helper. Uses cairo to find if a point in inside the shape

	   @param tokens The tokens of the shape being tested
	   @param scaleFactor The scale factor to be applied
	   @param x The X in local coordinates
	   @param y The Y in local coordinates
	*/
	static bool hitTest(NullableRef<tokenListRef> tokens, float scaleFactor, const Vector2f& point);
	static void fillFromMATRIX(cairo_matrix_t* m, const MATRIX& mat);
};
#endif

class RefreshableDrawable: public IDrawable
{
public:
	RefreshableDrawable(float _x, float _y, float _w, float _h
				  , float _xs, float _ys
				  , bool _ismask, bool _cacheAsBitmap
				  , float _scaling, float _a
				  , const ColorTransformBase& _colortransform
				  , SMOOTH_MODE _smoothing,AS_BLENDMODE _blendmode, const MATRIX& _m);
	//IDrawable interface
	uint8_t* getPixelBuffer(bool* isBufferOwner=nullptr, uint32_t* bufsize=nullptr) override { return nullptr; }
};

class InvalidateQueue
{
protected:
	_NR<DisplayObject> cacheAsBitmapObject;
public:
	InvalidateQueue(_NR<DisplayObject> _cacheAsBitmapObject=NullRef);
	virtual ~InvalidateQueue();
	//Invalidation queue management
	virtual void addToInvalidateQueue(DisplayObject* d) = 0;
	_NR<DisplayObject> getCacheAsBitmapObject() const;
};

}
#endif /* BACKENDS_GRAPHICS_H */
