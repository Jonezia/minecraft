#include "texture_atlas.h"

std::unordered_map<BlockID, TexUVCoords> TextureAtlas::texturesMap;

typedef TexTile T;

TextureAtlas::TextureAtlas() {
	// C++20 will introduce "using" keyword for scoped enums
	addTextures(BlockID::Grass, TexUVCoords(T::grassTop, T::dirtSide, T::dirtBottom));
	addTextures(BlockID::Dirt, TexUVCoords(T::dirtBottom));
}

void TextureAtlas::addTextures(BlockID id, TexUVCoords coords) {
	texturesMap.insert({ id, coords });
}

TexUVCoords TextureAtlas::getTextures(BlockID id) {
	return texturesMap[id];
}

TexUVCoords::TexUVCoords() {
	topTexCoords = getTexCorners(0);
	sideTexCoords = getTexCorners(0);
	bottomTexCoords = getTexCorners(0);
}

TexUVCoords::TexUVCoords(TexTile topTile, TexTile sideTile, TexTile botTile) {
	int topPos = static_cast<int>(topTile);
	int sidePos = static_cast<int>(sideTile);
	int botPos = static_cast<int>(botTile);
	topTexCoords = getTexCorners(topPos);
	sideTexCoords = getTexCorners(sidePos);
	bottomTexCoords = getTexCorners(botPos);
}

TexUVCoords::TexUVCoords(TexTile allTile) {
	int allPos = static_cast<int>(allTile);
	topTexCoords = getTexCorners(allPos);
	sideTexCoords = getTexCorners(allPos);
	bottomTexCoords = getTexCorners(allPos);
}

UVCoords TexUVCoords::getTexCorners(int pos) {
	// pos = position of tile when arranged with the
	// first in top left, row by row to bottom right

	// positions of top left coord of texture square
	int col = pos % texPerRow;
	int row = pos / texPerRow;

	float u = col * texSize;
	float v = row * texSize;

	// Order of coordinate specification:
	// 4--------3
	// |        |
	// |		|
	// |		|
	// 1--------2

	return UVCoords{ u, v + texSize, u + texSize, v + texSize, u + texSize, v, u, v };
}