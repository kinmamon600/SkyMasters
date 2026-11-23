#ifndef _WORLDSETTINGS_H
#define _WORLDSETTINGS_H

/// <summary>
/// ƒ[ƒ‹ƒhİ’è
/// </summary>
class WorldSettings
{
public:
	// ¢ŠE(“›)‚Ì”¼Œa
	static constexpr float WorldRadius = 10000.0f;

	// ¢ŠE(“›)‚Ì‚‚³
	static constexpr float WorldLength = 10000.0f;

	// °‚Ì‚‚³
	static constexpr float FloorHeight = -8000.0f;

	// •¨—¢ŠE‚Ì‘å‚«‚³
	static constexpr float PhysicsWorldSizeX = 11000.0f;
	static constexpr float PhysicsWorldSizeY = 11000.0f;
	static constexpr float PhysicsWorldSizeZ = 11000.0f;

	// ¢ŠE‚ÌƒXƒP[ƒŠƒ“ƒO”{—¦
	static constexpr float WorldScale = 0.01f;
};
#endif
