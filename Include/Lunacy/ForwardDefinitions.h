#pragma once
// Defines all classes and structures needed

// Classes exported:
// TRect, Vector2, Vector3, Matrix, Ratio, Padding, Color, Transform, Transform2D, Span, TriVertex, Edge

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

#pragma region General
template <typename N>
class Rect;

template <typename N>
class Vector2;

template <typename N>
class Vector3;

template <typename N>
class Padding;

template <typename N>
class RGBA;

class Ratio;
class Matrix3;
class Transform;
class Transform2D;
class Span;
class TriVertex;
class Edge;

#define Color RGBA<int>
#define iRGBA RGBA<int>
#define cRGBA RGBA<unsigned char>

#define IRect Rect<int>
#define FRect Rect<float>
#define DRect Rect<double>

#define IVector2 Vector2<int>
#define FVector2 Vector2<float>
#define DVector2 Vector2<double>

#define IVector3 Vector3<int>
#define IVector3 Vector3<float>
#define IVector3 Vector3<double>

#define Pad Padding<int>
#pragma endregion

namespace Sexy
{
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
#pragma endregion
