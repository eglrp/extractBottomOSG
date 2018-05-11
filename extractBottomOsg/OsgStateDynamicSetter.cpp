#include "StdAfx.h"
#include "OsgStateDynamicSetter.h"


//************************************
// Method:    apply
// FullName:  COsgStateDynamicSetter::apply
// Access:    virtual protected 
// Returns:   void
// Qualifier:
// Parameter: osg::Geode & geode
//************************************
void COsgStateDynamicSetter::apply(osg::Geode& geode)
{
	if (geode.getStateSet())
	{
		apply(geode.getStateSet());
	}
	unsigned int cnt = geode.getNumDrawables();
	for (unsigned int i = 0; i < cnt; i++)
	{
		osg::Drawable* draw = geode.getDrawable(i);
		if (draw)
		{
			osg::StateSet *state = draw->getStateSet();
			if (state)
				apply(state);
		}
	}
	traverse(geode);
}

//************************************
// Method:    apply
// FullName:  COsgStateDynamicSetter::apply
// Access:    virtual protected 
// Returns:   void
// Qualifier:
// Parameter: osg::StateSet * state
//************************************
void COsgStateDynamicSetter::apply(osg::StateSet* state)
{
	if (!state)
	{
		return;
	}

	osg::StateSet::TextureAttributeList& texAttribList = state->getTextureAttributeList();

	for(unsigned int i = 0; i < texAttribList.size(); i++)
	{
		osg::Texture2D* tex2D = dynamic_cast<osg::Texture2D*>(state->getTextureAttribute(i, osg::StateAttribute::TEXTURE));

		if (tex2D)
		{
			
			osg::ref_ptr<osg::Image> image = tex2D->getImage();

			if (!image)
			{
				continue;
			}
			std::string ss = image->getName();
			osgDB::writeImageFile(*image, mDir + ss);
			
		}
	}
}

void COsgStateDynamicSetter::apply(osg::Node& node)
{
	if (node.getStateSet())
	{
		apply(node.getStateSet());
	}
	traverse(node);
}