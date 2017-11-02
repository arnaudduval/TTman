#include <TCXFile.h>
#include <libxml++/libxml++.h>
#include <iostream>

TCXFile::TCXFile(std::string fileName)
{
  try
  {
    xmlpp::DomParser parser;
    parser.set_substitute_entities();
    parser.parse_file(fileName);
    if(parser)
    {
      //Walk the tree
      const xmlpp::Node* pNode = parser.get_document()->get_root_node();
      const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(pNode);
      const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(pNode);
      const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(pNode);
      std::string nodeName = pNode->get_name();
      if(nodeName == "TrainingCenterDatabase")
      {
        auto list = pNode->get_children();
        for(auto iter = list.begin() ; iter != list.end() ; ++iter)
        {
          pNode = dynamic_cast<const xmlpp::Node*>(*iter);
          if(pNode->get_name() == "Activities")
          {
            auto listActivities = pNode->get_children();
            for(auto iterActivities = listActivities.begin() ; iterActivities != listActivities.end() ; ++iterActivities)
            {
              pNode = dynamic_cast<const xmlpp::Node*>(*iter);
              if(pNode->get_name() == "Activity")
              {
                TCXActivity activity(pNode);
                activities.push_back(activity);
              }
            }
          }
        }
      }
      std::cout << nodeName << "\n";
      
    }
    else
    {
      std::cout << "Problem at parser initialisation\n";
    }
    
    
  }
  catch(const std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << std::endl;
  }
  
}


TCXActivity::TCXActivity(const xmlpp::Node* pNode)
{
  
}