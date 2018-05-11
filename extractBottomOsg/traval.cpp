#include "stdafx.h"
#include "traval.h"


COsgPagedLodBottomLevelFinder::COsgPagedLodBottomLevelFinder(std::vector<std::string>* VecBottomLevelPagedLodFileName) : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
{
	vecBottomLevelPagedLodFileName = VecBottomLevelPagedLodFileName;
}

COsgPagedLodBottomLevelFinder::~COsgPagedLodBottomLevelFinder(void)
{

}

void COsgPagedLodBottomLevelFinder::apply(osg::PagedLOD& pagedLod)
{


	int numFileName = pagedLod.getNumFileNames();

	for (int i = 0; i < numFileName; i++)
	{
		std::string pagedLodFileTitle = pagedLod.getFileName(i);



		if (pagedLodFileTitle.size() > 0)
		{
			std::string databasePath = pagedLod.getDatabasePath();
			std::string pagedLodFileName = databasePath + pagedLodFileTitle;

			if (pagedLodFileName.size() == 0)
			{
				continue;
			}

			osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(pagedLodFileName);

			if (node)					//�ҵ���һ��
			{
				node->setName(pagedLodFileTitle.c_str());
				osg::ref_ptr<osg::Geode> geode = node->asGeode();
				osg::ref_ptr<osg::PagedLOD> childPagedLod = dynamic_cast<osg::PagedLOD*>(node.get());
				osg::ref_ptr<osg::Group> childGroup = node->asGroup();

				if (geode)
				{
					vecBottomLevelPagedLodFileName->push_back(pagedLodFileName);
				}
				else if (childPagedLod)					//��������һ��
				{
					COsgPagedLodBottomLevelFinder iveFinder(vecBottomLevelPagedLodFileName);
					childPagedLod->accept(iveFinder);
				}
				else if (childGroup)
				{
					for (int j = 0; j < childGroup->getNumChildren(); j++)
					{
						osg::ref_ptr<osg::PagedLOD> childPagedLod = dynamic_cast<osg::PagedLOD*> (childGroup->getChild(j));

						if (childPagedLod)
						{
							COsgPagedLodBottomLevelFinder iveFinder(vecBottomLevelPagedLodFileName);
							childPagedLod->accept(iveFinder);
						}
					}
				}
			}
			else
			{
				std::string pagedLodTitle = pagedLod.getName();

				if (pagedLodTitle.size() > 0)
				{
					std::string databasePath = pagedLod.getDatabasePath();
					std::string pagedLodFileName = databasePath + pagedLodTitle;

					if (pagedLodFileName.size() == 0)
					{
						continue;
					}

					vecBottomLevelPagedLodFileName->push_back(pagedLodFileName);
				}

			}
		}
	}
}
