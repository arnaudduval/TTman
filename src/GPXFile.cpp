#include <GPXFile.h>
#include <libxml++/libxml++.h>
#include <iostream>
#include <fstream>




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
      if(nodeName == "gpx")     // root node is gpx. Let's start here
      {
        auto list = pNode->get_children();
        for(auto iter = list.begin() ; iter != list.end() ; ++iter)
        {
          pNode = dynamic_cast<const xmlpp::Node*>(*iter);
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
    {
      metadataValue = ((xmlpp::TextNode*)(*((pChildNode->get_children()).begin())))->get_content();
      Metadata m = std::make_tuple(metadataName, metadataValue);
      metadata.push_back(m);
    }
  }
}

void GPXFile::MakeLog(const std::string& filePath)
{
  std::ofstream fout(filePath); 
  fout << "This file has " << metadata.size() << " metadata(s) :\n";
  for (auto imetadata = metadata.begin() ; imetadata != metadata.end() ; ++imetadata)
  {
    fout << "  " << std::get<0>(*imetadata) << "\t" << std::get<1>(*imetadata) << "\n";
  }
  
  
}


GPXtrk::GPXtrk(const xmlpp::Node* pNode)
{
  auto list = pNode->get_children();
  for(auto iter = list.begin() ; iter != list.end() ; ++iter)
  {
    pNode = dynamic_cast<const xmlpp::Node*>(*iter);
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
  auto list = pNode->get_children();
  for(auto iter = list.begin() ; iter != list.end() ; ++iter)
  {
    pNode = dynamic_cast<const xmlpp::Node*>(*iter);
    if(pNode->get_name() == "trkpt")
    {
      GPXtrkpt trkpt(pNode);
      trkpts.push_back(trkpt);
    }
  }
}

GPXwpt::GPXwpt(const xmlpp::Node* pNode)
{
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
    std::string singleValue;
    if(pNode->get_children().size() != 0)
       singleValue = ((xmlpp::TextNode*)(*((pNode->get_children()).begin())))->get_content();
    if(pNode->get_name() == "ele")
    {
      elevation = std::stod(singleValue);
    }
  }
}

