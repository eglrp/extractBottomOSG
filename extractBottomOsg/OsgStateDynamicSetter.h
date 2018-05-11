#pragma once
#include<osg/Geode>
#include<osg/NodeVisitor>
#include<osg/Geometry>
#include<osg/Texture2D>
#include "osgDB/WriteFile"
#include <string>
class COsgStateDynamicSetter : public osg::NodeVisitor
{
public:
	COsgStateDynamicSetter::COsgStateDynamicSetter(std::string dir) : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{
		mDir = dir;
	}
	
protected:
	virtual void apply(osg::Geode& geode);
	virtual void apply(osg::Node& node);
	void apply(osg::StateSet* state);

	std::string mDir;
};

