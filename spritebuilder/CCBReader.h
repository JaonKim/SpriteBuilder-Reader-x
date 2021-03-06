#ifndef _SB_CCBREADER_H_
#define _SB_CCBREADER_H_

#include "cocos2d.h"
#include <string>
#include <vector>
#include "CCBSequence.h"
#include "extensions/GUI/CCControlExtension/CCControl.h"

#define SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(T, METHOD) static T * METHOD() { \
    T * ptr = new T(); \
    if(ptr != NULL) { \
        ptr->autorelease(); \
        return ptr; \
    } \
    CC_SAFE_DELETE(ptr); \
    return NULL; \
}

#define SB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(T, METHOD) static T * METHOD() { \
    T * ptr = new T(); \
    if(ptr != NULL && ptr->init()) { \
        ptr->autorelease(); \
        return ptr; \
    } \
    CC_SAFE_DELETE(ptr); \
    return NULL; \
}

#define SB_VERSION 6

namespace spritebuilder {

/**
 * @addtogroup spritebuilder
 * @{
 */

class CCBFile : public cocos2d::Node
{
private:
    cocos2d::Node *_CCBFileNode;
    
public:
    CCBFile();
    
    static CCBFile* create();
    
    cocos2d::Node* getCCBFileNode();
    void setCCBFileNode(Node *pNode); // retain
};

/* Forward declaration. */
class NodeLoader;
class NodeLoaderLibrary;
class NodeLoaderListener;
class CCBMemberVariableAssigner;
class CCBSelectorResolver;
class CCBAnimationManager;
class CCBKeyframe;

/**
 * @brief Parse CCBI file which is generated by CocosBuilder
 */
class CCBReader : public cocos2d::Object 
{
public:
    enum class PropertyType {
        POSITION = 0,
        SIZE,
        POINT,
        POINT_LOCK,
        SCALE_LOCK,
        DEGREES,
        INTEGER,
        FLOAT,
        FLOAT_VAR,
        CHECK,
        SPRITEFRAME,
        TEXTURE,
        BYTE,
        COLOR3,
        COLOR4F_VAR,
        FLIP,
        BLEND_MODE,
        FNT_FILE,
        TEXT,
        FONT_TTF,
        INTEGER_LABELED,
        BLOCK,
        ANIMATION,
        SB_FILE,
        STRING,
        BLOCK_CONTROL,
        FLOAT_SCALE,
        FLOAT_XY,
		COLOR4,
    };
    
    enum class FloatType {
        _0 = 0,
        _1,
        MINUS1,
        _05,
        INTEGER,
        FULL
    };
    
    enum class PlatformType {
        ALL = 0,
        IOS,
        MAC
    };
    
    enum class TargetType {
        NONE = 0,
        DOCUMENT_ROOT = 1,
        OWNER = 2,
    };
    
    enum class PositionType
    {
        RELATIVE_BOTTOM_LEFT,
        RELATIVE_TOP_LEFT,
        RELATIVE_TOP_RIGHT,
        RELATIVE_BOTTOM_RIGHT
    };

	enum class PositionUnit
    {
        POINTS,
        SCALED,
        NORMALIZED
    };
    
    enum class SizeType
    {
        ABSOLUTE,
        PERCENT,
        RELATIVE_CONTAINER,
        HORIZONTAL_PERCENT,
        VERTICAL_PERCENT,
        MULTIPLY_RESOLUTION,
    };
    
    enum class SizeUnit
    {
        POINTS,
        SCALED,
        NORMALIZED,
        INSETPOINTS,
        INSETSCALED
    };
    
    enum class ScaleType
    {
        ABSOLUTE,
        MULTIPLY_RESOLUTION
    };
    
    static CCBReader* getInstance();
    static void end();
    
    /**
     * @js NA
     * @lua NA
     */
    CCBReader(NodeLoaderLibrary *pNodeLoaderLibrary, CCBMemberVariableAssigner *pCCBMemberVariableAssigner = NULL, CCBSelectorResolver *pCCBSelectorResolver = NULL, NodeLoaderListener *pNodeLoaderListener = NULL);
    /**
     * @js NA
     * @lua NA
     */
    CCBReader(CCBReader *ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CCBReader();
    /**
     * @js NA
     * @lua NA
     */
    CCBReader();
   
    void setCCBRootPath(const char* ccbRootPath);
    const std::string& getCCBRootPath() const;

    cocos2d::Node* readNodeGraphFromFile(const char *pCCBFileName);
    cocos2d::Node* readNodeGraphFromFile(const char *pCCBFileName, cocos2d::Object *pOwner);
    cocos2d::Node* readNodeGraphFromFile(const char *pCCBFileName, cocos2d::Object *pOwner, const cocos2d::Size &parentSize);
    /**
     * @js NA
     * @lua NA
     */
    cocos2d::Node* readNodeGraphFromData(cocos2d::Data *pData, cocos2d::Object *pOwner, const cocos2d::Size &parentSize);
   
    /**
     @lua NA
     */
    cocos2d::Scene* createSceneWithNodeGraphFromFile(const char *pCCBFileName);
    /**
     @lua NA
     */
    cocos2d::Scene* createSceneWithNodeGraphFromFile(const char *pCCBFileName, cocos2d::Object *pOwner);
    /**
     @lua NA
     */
    cocos2d::Scene* createSceneWithNodeGraphFromFile(const char *pCCBFileName, cocos2d::Object *pOwner, const cocos2d::Size &parentSize);
    
    /**
     * @js NA
     * @lua NA
     */
    CCBMemberVariableAssigner* getCCBMemberVariableAssigner();
    /**
     * @js NA
     * @lua NA
     */
    CCBSelectorResolver* getCCBSelectorResolver();
    
    /**
     * @js getActionManager
     * @lua getActionManager
     */
    CCBAnimationManager* getAnimationManager();
    /**
     * @js setActionManager
     * @lua setActionManager
     */
    void setAnimationManager(CCBAnimationManager *pAnimationManager);
    
    /**  Used in NodeLoader::parseProperties()
     * @js NA
     * @lua NA
     */
    std::set<std::string>* getAnimatedProperties();
    /**
     * @js NA
     * @lua NA
     */
    std::set<std::string>& getLoadedSpriteSheet();
    /**
     * @js NA
     * @lua NA
     */
    cocos2d::Object* getOwner();

    /* Utility methods. 
     * @js NA
     * @lua NA
     */
    static std::string lastPathComponent(const char* pString);
    /**
     * @js NA
     * @lua NA
     */
    static std::string deletePathExtension(const char* pString);
    /**
     * @js NA
     * @lua NA
     */
    static std::string toLowerCase(const char* pString);
    /**
     * @js NA
     * @lua NA
     */
    static bool endsWith(const char* pString, const char* pEnding);

    /* Parse methods. 
     * @js NA
     * @lua NA
     */
    int readInt(bool pSigned);
    /**
     * @js NA
     * @lua NA
     */
    unsigned char readByte();
    /**
     * @js NA
     * @lua NA
     */
    bool readBool();
    std::string readUTF8();
    /**
     * @js NA
     * @lua NA
     */
    float readFloat();
    /**
     * @js NA
     * @lua NA
     */
    std::string readCachedString();
    /**
     * @js NA
     * @lua NA
     */
    bool isJSControlled();
    
    bool readCallbackKeyframesForSeq(CCBSequence* seq);
    bool readSoundKeyframesForSeq(CCBSequence* seq);
    
    cocos2d::Array* getOwnerCallbackNames();
    cocos2d::Array* getOwnerCallbackNodes();
    cocos2d::Array* getOwnerCallbackControlEvents();
    
    cocos2d::Array* getOwnerOutletNames();
    cocos2d::Array* getOwnerOutletNodes();
    cocos2d::Array* getNodesWithAnimationManagers();
    cocos2d::Array* getAnimationManagersForNodes();
    /**
     * @js NA
     * @lua NA
     */
    cocos2d::Dictionary* getAnimationManagers();
    /**
     * @js NA
     * @lua NA
     */
    void setAnimationManagers(cocos2d::Dictionary* x);  // weak reference
    /**
     * @js NA
     * @lua NA
     */
    void addOwnerCallbackName(const std::string& name);
    /**
     * @js NA
     * @lua NA
     */
    void addOwnerCallbackNode(cocos2d::Node *node);
    void addOwnerCallbackControlEvents(cocos2d::extension::Control::EventType type);
    /**
     * @js NA
     * @lua NA
     */
    void addDocumentCallbackName(const std::string& name);
    /**
     * @js NA
     * @lua NA
     */
    void addDocumentCallbackNode(cocos2d::Node *node);
    void addDocumentCallbackControlEvents(cocos2d::extension::Control::EventType eventType);
    /**
     * @js NA
     * @lua NA
     */
    static float getResolutionScale();
    static void setResolutionScale(float scale);
    /**
     * @js NA
     * @lua NA
     */
    cocos2d::Node* readFileWithCleanUp(bool bCleanUp, cocos2d::Dictionary* am);
    
    void addOwnerOutletName(std::string name);
    void addOwnerOutletNode(cocos2d::Node *node);
    
    void addNodeByTagName(const char * name, cocos2d::Node *node);
    cocos2d::Node * getNodeByTagName(const char * name);

private:
    void cleanUpNodeGraph(cocos2d::Node *pNode);
    bool readSequences();
    CCBKeyframe* readKeyframe(PropertyType type);
    
    bool readHeader();
    bool readStringCache();
    //void readStringCacheEntry();
    cocos2d::Node* readNodeGraph();
    cocos2d::Node* readNodeGraph(cocos2d::Node * pParent);

    bool getBit();
    void alignBits();

    bool init();
    
    friend class NodeLoader;

private:
    cocos2d::Data *_data;
    unsigned char *_bytes;
    int _currentByte;
    int _currentBit;
    
    std::vector<std::string> _stringCache;
    std::set<std::string> _loadedSpriteSheets;
    
    cocos2d::Object *_owner;
    
    CCBAnimationManager *_actionManager; //retain
    cocos2d::Dictionary* _actionManagers;
    
    std::set<std::string> *_animatedProps;
    
    NodeLoaderLibrary *_nodeLoaderLibrary;
    NodeLoaderListener *_nodeLoaderListener;
    CCBMemberVariableAssigner *_CCBMemberVariableAssigner;
    CCBSelectorResolver *_CCBSelectorResolver;
    
    std::vector<std::string> _ownerOutletNames;
    cocos2d::Array* _ownerOutletNodes;
    cocos2d::Array* _nodesWithAnimationManagers;
    cocos2d::Array* _animationManagersForNodes;
    
    std::vector<std::string> _ownerCallbackNames;
    cocos2d::Array* _ownerCallbackNodes;
    cocos2d::Array* _ownerOwnerCallbackControlEvents;
    std::string _CCBRootPath;
    
    std::map<std::string, cocos2d::Node*> _nodeByTagName;
    
    bool _jsControlled;
};

// end of effects group
/// @}

}

#endif
