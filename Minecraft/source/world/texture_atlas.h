#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include "block_id.h"

#include <array>
#include <unordered_map>

// (0,0)     (1,0)
// ------------->(U) 
// |    
// |  UV diagram
// |     
// V (V)        -
// (0,1)     (1,1)

using UVCoords = std::array<float, 8>;
// fractional width of one texture tile
constexpr float texSize = 1.f/16;

struct TexUVCoords;

class TextureAtlas {
public:
	TextureAtlas();
	static void addTextures(BlockID id, TexUVCoords coords);
	static TexUVCoords getTextures(BlockID id);
private:
	static std::unordered_map<BlockID, TexUVCoords> texturesMap;
};

struct TexUVCoords {
	UVCoords topTexCoords;
	UVCoords sideTexCoords;
	UVCoords bottomTexCoords;
	
	// row and col starting with 0,0 in top left corner
	UVCoords getTexCorners(int row, int col);

	TexUVCoords();
	TexUVCoords(int topU, int topV, int sideU, int sideV, int botU, int botV);
	// initialiser if all textures are the same
	TexUVCoords(int allU, int allV);
};

#endif