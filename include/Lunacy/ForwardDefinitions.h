#pragma once
// Defines all classes and structures needed
#include "ConstEnums.h"

#pragma region PopStructs
class PopString;
class PopWString;

template <typename T>
class PopList;

template <typename T>
class PopSet;

template <typename T>
class PopVector;

template <typename K, typename V>
class PopMap;

template <typename K, typename V>
class PopPair;
#pragma endregion

#pragma region Sexy
namespace Sexy
{
	float ClampAngle(float Angle);
	float Clamp(float Value, float Min, float Max);

	// General
	template <typename N>
	class Rect;
	
	template <typename N>
	class Vector2;

	template <typename N>
	class Vector3;

	class Color;
	class SColor;
	class Padding;
	class Matrix3;
	class Ratio;
	class Transform;
	class Transform2D;
	class Span;
	class Edge;
	class TriVertex;

	class SexyAppBase;
	class SexyApp;

	class SexyCacheData;
	class SexyCache;

	// UI Elements
	class UIContainer;
	class UIElement;
	class UIRoot;
	class UIDialog;
	class UITextbox;
	class UIButton;
	class UIScrollBar;
	class UISafeDeleteInfo;
	class UIHyperlink;
	class UICheckbox;
	class UISlider;
	class UIList;

	class DataElement;
	class DialogButton;
	class ListDataElement;

	// Listeners
	class ButtonListener;
	class DialogListener;
	class TextBoxListener;
	class ScrollBarListener;
	class CheckboxListener;
	class ListListener;
	class SliderListener;

	// Resources
	class ResourceManager;
	class ResourceManagerException;
	class Buffer;

	// Audio
	class MusicInterface;
	class SoundManager;
	class SoundInstance;
	class DSoundInterface;
	class BassMusicInfo;
	class BASS_INSTANCE;
	class BassMusicInterface;

	// Graphical
	class Graphics;
	class GraphicsState;
	class DDInterface;
	class NativeDisplay;
	class D3DInterface;
	class RenderCommand;
	class AnimInfo;
	class GraphicsAutoState;

	class Image;
	class Font;

	class DDImage;
	class SharedImage;
	class MemoryImage;
	class SharedImageRef;

	class FontData;
	class FontLayer;
	class ActiveFontLayer;
	class ImageFont;
	class SysFont;

	// Randomness
	class MTRand;

	// HTTP Stuff
	class WinInetHTTPTransfer;
	class HTTPTransfer;

	// XML Stuff
	class XMLParser;
	class XMLElement;
	class EncodingParser;
	class PropertiesParser;
	class DescParser;
	class CharData;

	// Weird stuff idk
	class FlagsMod;
	class ModalFlags;
	class PreModalInfo;
	class AutoModalFlags;

	class AutoCrit;
	class BetaSupport;
	class InternetManager;

	class SexyAutoPerf;
	class SexyPerf;
	class PerfInfo;
	class PerfTimer;
}
#pragma endregion

#pragma region MSD3D
class IDirectDrawSurface;
class _DDSURFACEDESC;
class _DDSURFACEDESC2;
#pragma endregion


// PvZ Specific Stuff
class LawnApp;

template <typename T>
class DataArray;
#pragma region GameObjects
class GameObject;
class Plant;
class Zombie;
class GridItem;
class Pickup;
class LawnMower;
class Projectile;
class CursorObject;
class CursorPreview;
class SeedPacket;
class SeedBank;
class HitResult;

class Challenge;
class CutScene;
#pragma endregion

#pragma region Extended UI
class GameButton;
class UIMessage;
class UIToolTip;
#pragma endregion


class TypingCheck;
class PopDRM;
class Music;
class LevelStats;
class UserData;
class ProfileManager;
class ReanimatorCache;
class EffectSystem;
class ZenGarden;
class PoolEffect;
class Lawn;
class LoadingScreen;
class MainMenu;
class SeedChooser;
class AwardScreen;
class CreditScreen;
class ChallengeScreen;
class SoundSystem;
class Reanimation;
class ReanimatorDefinition;
class ReanimatorTrackInstance;
class ReanimationHolder;
class AttachEffect;
class Attachment;
class ParticleSystem;

Reanimation* TryToGet(ReanimationID);
Attachment* TryToGet(AttachmentID);
Zombie* TryToGet(ZombieID);
Plant* TryToGet(PlantID);