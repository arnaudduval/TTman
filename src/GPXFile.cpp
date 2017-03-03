#include <GPXFile.h>
#include <libxml++/libxml++.h>
#include <iostream>




GPXFile::GPXFile(std::string fileName)
{
  try
  {
    xmlpp::DomParser parser;
    parser.set_substitute_entities();
    parser.parse_file(fileName);
    if(parser)
    {
      // Walk the tree
      const xmlpp::Node* pNode = parser.get_document()->get_root_node();
      const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(pNode);
      const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(pNode);
      const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(pNode);
      std::string nodeName = pNode->get_name();
      std::cout << nodeName << std::endl;
      if(nodeName == "gpx")     // root node is gpx. Let's start here
      {
        xmlpp::Node::NodeList list = pNode->get_children();
        for(auto iter = list.begin() ; iter != list.end() ; ++iter)
        {
          pNode = dynamic_cast<const xmlpp::Node*>(*iter);
          std::cout << pNode->get_name() << std::endl;
        }
      }
      
      
    }
    else
    {
      std::cout << "Probelem d'initialisation du parser\n";
    }
    
    
  }
  catch(const std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << std::endl;
  }
  
}
