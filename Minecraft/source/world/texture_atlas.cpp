#include "texture_atlas.h"

std::unordered_map<BlockID, TexUVCoords> TextureAtlas::texturesMap;

TextureAtlas::TextureAtlas() {
	addTextures(BlockID::Grass, TexUVCoords(2, 9, 3, 0, 2, 0));
}

void TextureAtlas::addTextures(BlockID id, TexUVCoords coords) {
	texturesMap.insert({ id, coords });
}

TexUVCoords TextureAtlas::getTextures(BlockID id) {
	return texturesMap[id];
}

TexUVCoords::TexUVCoords() {
	topTexCoords = getTexCorners(0, 0);
	sideTexCoords = getTexCorners(0, 0);
	bottomTexCoords = getTexCorners(0,0);
}

TexUVCoords::TexUVCoords(int topU, int topV, int sideU, int sideV, int botU, int botV) {
	topTexCoords = getTexCorners(topU, topV);
	sideTexCoords = getTexCorners(sideU, sideV);
	bottomTexCoords = getTexCorners(botU, botV);
}

TexUVCoords::TexUVCoords(int allU, int allV) {
	topTexCoords = getTexCorners(allU, allV);
	sideTexCoords = getTexCorners(allU, allV);
	bottomTexCoords = getTexCorners(allU, allV);
}

UVCoords TexUVCoords::getTexCorners(int row, int col) {
	// UV positions of top left coord of texture square
	float u = row * texSize;
	float v = col * texSize;

	// Order of coordinate specification:
	// 4--------3
	// |        |
	// |		|
	// |		|
	// 1--------2

	return UVCoords{ u, v + texSize, u + texSize, v + texSize, u + texSize, v, u, v };
}