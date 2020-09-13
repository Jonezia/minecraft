#include "texture_atlas.h"

TextureAtlas::TextureAtlas() {
	addTextures(BlockID::Grass, TexUVCoords(2, 6, 3, 15, 2, 15));
}

void TextureAtlas::addTextures(BlockID id, TexUVCoords coords) {
	texturesMap.insert({ id, coords });
}

TexUVCoords TextureAtlas::getTextures(BlockID id) {
	return texturesMap[id];
}

TexUVCoords::TexUVCoords() {
	topTexCoords = getTexCorners(0, 15);
	sideTexCoords = getTexCorners(0, 15);
	bottomTexCoords = getTexCorners(0, 15);
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
	// UV positions of bottom left coord of texture square
	float u = row / texSize;
	float v = col / texSize;

	// Order of coordinate specification:
	// 2--------3
	// |        |
	// |		|
	// |		|
	// 1--------4

	return UVCoords{ u, v, u, v + 1 / 16, u + 1 / 16, v + 1 / 16, u + 1 / 16, v };
}