#include "CCNode+CCBRelativePositioning.h"
#include "CCBReader.h"

using namespace cocos2d;

namespace spritebuilder {

Point getAbsolutePosition(const Point &pt, CCBReader::PositionType type, const Size &containerSize, const char *propName)
{
    Point absPt = Point(0,0);
    if (type == CCBReader::PositionType::RELATIVE_BOTTOM_LEFT)
    {
        absPt = pt;
    }
    else if (type == CCBReader::PositionType::RELATIVE_TOP_LEFT)
    {
        absPt.x = pt.x;
        absPt.y = containerSize.height - pt.y;
    }
    else if (type == CCBReader::PositionType::RELATIVE_TOP_RIGHT)
    {
        absPt.x = containerSize.width - pt.x;
        absPt.y = containerSize.height - pt.y;
    }
    else if (type == CCBReader::PositionType::RELATIVE_BOTTOM_RIGHT)
    {
        absPt.x = containerSize.width - pt.x;
        absPt.y = pt.y;
    }
    else if (type == CCBReader::PositionType::PERCENT)
    {
        absPt.x = (int)(containerSize.width * pt.x / 100.0f);
        absPt.y = (int)(containerSize.height * pt.y / 100.0f);
    }
    else if (type == CCBReader::PositionType::MULTIPLY_RESOLUTION)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        absPt.x = pt.x * resolutionScale;
        absPt.y = pt.y * resolutionScale;
    }
    
    return absPt;
}

void setRelativeScale(Node *pNode, float scaleX, float scaleY, CCBReader::ScaleType type, const char* propName)
{
    CCASSERT(pNode, "pNode should not be null");
    
    if (type == CCBReader::ScaleType::MULTIPLY_RESOLUTION)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        scaleX *= resolutionScale;
        scaleY *= resolutionScale;
    }
    
    pNode->setScaleX(scaleX);
    pNode->setScaleY(scaleY);
}

}