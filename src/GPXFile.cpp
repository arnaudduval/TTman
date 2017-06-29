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
        auto list = pNode->get_children();
        for(auto iter = list.begin() ; iter != list.end() ; ++iter)
        {
          pNode = dynamic_cast<const xmlpp::Node*>(*iter);
          std::cout << "pNode->get_name() : " << pNode->get_name() << std::endl;
          // Read metadata
          if(pNode->get_name() == "metadata")
            ReadMetadataXMLNode(pNode);
          // Read track(s)
          if(pNode->get_name() == "trk")
          {
            GPXtrk trk(pNode);
            tracks.push_back(trk);
          }
        }
      }
      
      
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

void GPXFile::ReadMetadataXMLNode(const xmlpp::Node* pNode)
{
  auto list = pNode->get_children();
  for(auto iter = list.begin() ; iter != list.end() ; ++iter)
  {
    auto pChildNode = dynamic_cast<const xmlpp::Node*>(*iter);
    std::string metadataName = pChildNode->get_name();
    std::string metadataValue;
    if(pChildNode->get_children().size() != 0)
       metadataValue = ((xmlpp::TextNode*)(*((pChildNode->get_children()).begin())))->get_content();
    std::cout << "metadata : " << metadataName << "\t" << metadataValue << std::endl;    
    Metadata m = std::make_tuple(metadataName, metadataValue);
    metadata.push_back(m);
  }
}

GPXtrk::GPXtrk(const xmlpp::Node* pNode)
{
  std::cout << "Contructor GPXtrk::GPXtrk(const xmlpp::Node*)" << std::endl;
  auto list = pNode->get_children();
  for(auto iter = list.begin() ; iter != list.end() ; ++iter)
  {
    pNode = dynamic_cast<const xmlpp::Node*>(*iter);
    std::cout << "pNode->get_name() : " << pNode->get_name() << std::endl;
    // Read name
    if(pNode->get_name() == "name")
      ReadNameXML(pNode);
    /*// Read metadata
    if(pNode->get_name() == "metadata")
      ReadMetadataXMLNode(pNode);
    */
    // Read track segment
    if(pNode->get_name() == "trkseg")
    {
      GPXtrkseg trkseg(pNode);
      trksegs.push_back(trkseg);
    }
  }
}

void GPXtrk::ReadNameXML(const xmlpp::Node* pNode)
{
  if(pNode->get_children().size() != 0)
    name = ((xmlpp::TextNode*)(*(pNode->get_children().begin())))->get_content();
}

GPXtrkseg::GPXtrkseg(const xmlpp::Node* pNode)
{
  std::cout << "Constructor GPXtrkseg::GPXtrkseg(const xmlpp::Node*)" << std::endl;
  auto list = pNode->get_children();
  for(auto iter = list.begin() ; iter != list.end() ; ++iter)
  {
    pNode = dynamic_cast<const xmlpp::Node*>(*iter);
    std::cout << "pNode->get_name() : " << pNode->get_name() << std::endl;
    if(pNode->get_name() == "trkpt")
    {
      GPXtrkpt trkpt(pNode);
      trkpts.push_back(trkpt);
    }
  }
}

GPXwpt::GPXwpt(const xmlpp::Node* pNode)
{
  std::cout << "Constructor GPXwpt::GPXwpt(const xmlpp::Node*) << std::endl";
  // Read node attributes : latitude and longitude
  auto attributes = dynamic_cast<const xmlpp::Element*>(pNode)->get_attributes();
  for(auto iAttribute = attributes.begin() ; iAttribute != attributes.end() ; ++iAttribute)
  {
    const xmlpp::Attribute* attribute = *iAttribute;
    if(attribute->get_name() == "lat")
    {
      coords.lat = std::stod(attribute->get_value());
    }
    else if(attribute->get_name() == "lon")
    {
      coords.lon = std::stod(attribute->get_value());      
    }
  }
  // Read nodes children
  auto list = pNode->get_children();
  for(auto iter = list.begin() ; iter != list.end() ; ++iter)
  {
    pNode = dynamic_cast<const xmlpp::Node*>(*iter);
    std::cout << "pNode->get_name() : " << pNode->get_name() << std::endl;
    std::string singleValue;
    if(pNode->get_children().size() != 0)
       singleValue = ((xmlpp::TextNode*)(*((pNode->get_children()).begin())))->get_content();
    if(pNode->get_name() == "ele")
    {
      elevation = std::stod(singleValue);
      std::cout << "elevation : " << elevation << "\n";
    }
  }
}

