#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include "block_id.h"
#include "texture_tiles.h"

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

// number of tiles per row/col
constexpr int texPerRow = 16;
// fractional width of one texture tile
constexpr float texSize = 1.f/texPerRow;

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
	UVCoords getTexCorners(int pos);

	TexUVCoords();
	TexUVCoords(TexTile topTile, TexTile sideTile, TexTile botTile);
	// initialiser if all textures are the same
	TexUVCoords(TexTile allTile);
};

#endif