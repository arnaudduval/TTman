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
              pNode = dynamic_cast<const xmlpp::Node*>(*iterActivities);
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
  auto list = pNode->get_children();
  auto attributes = dynamic_cast<const xmlpp::Element*>(pNode)->get_attributes();
  for(auto iAttribute = attributes.begin() ; iAttribute != attributes.end() ; ++iAttribute)
  {
    const xmlpp::Attribute* pAttribute = *iAttribute;
    if(pAttribute->get_name() == "Sport")
    {
      sport = pAttribute->get_value();
    }
  }
  
  for(auto iter = list.begin() ; iter != list.end() ; ++iter)
  {
    const xmlpp::Node* pActNode = dynamic_cast<const xmlpp::Node*>(*iter);
    if(pActNode->get_name() == "Lap")
    {
      TCXLap lap(pActNode);
      laps.push_back(lap);
    }
    else if(pActNode->get_name() == "Id")
    {
      id = ((xmlpp::TextNode*)(*((pNode->get_children()).begin())))->get_content();
    } 
  }
}

TCXLap::TCXLap(const xmlpp::Node* pNode)
{
  std::cout << "Lecture Lap\n";
  auto list = pNode->get_children();
  auto attributes = dynamic_cast<const xmlpp::Element*>(pNode)->get_attributes();
  for(auto iAttribute = attributes.begin() ; iAttribute != attributes.end() ; ++iAttribute)
  {
  const xmlpp::Attribute* pAttribute = *iAttribute;
    if(pAttribute->get_name() == "StartTime")
    {
      startTime = pAttribute->get_value();
    }
  }
  
  for(auto iter = list.begin() ; iter != list.end() ; ++iter)
  {
    const xmlpp::Node* pActNode = dynamic_cast<const xmlpp::Node*>(*iter);
    if(pActNode->get_name() == "TotalTimeSeconds")
    {
      totalTimeSeconds = std::stod(((xmlpp::TextNode*)(*((pActNode->get_children()).begin())))->get_content());
    }
    else if(pActNode->get_name() == "DistanceMeters")
    {
      distanceMeters = std::stod(((xmlpp::TextNode*)(*((pActNode->get_children()).begin())))->get_content());
    } 
    else if(pActNode->get_name() == "MaximumSpeed")
    {
      maximumSpeed = std::stod(((xmlpp::TextNode*)(*((pActNode->get_children()).begin())))->get_content());
    }
    else if(pActNode->get_name() == "Calories")
    {
      calories = std::stoi(((xmlpp::TextNode*)(*((pActNode->get_children()).begin())))->get_content());
    }
    else if(pActNode->get_name() == "Intensity")
    {
      intensity = ((xmlpp::TextNode*)(*((pActNode->get_children()).begin())))->get_content();
    }
    else if(pActNode->get_name() == "Cadence")
    {
      cadence = std::stoi(((xmlpp::TextNode*)(*((pActNode->get_children()).begin())))->get_content());
    }
    else if(pActNode->get_name() == "triggerMethod")
    {
      triggerMethod = ((xmlpp::TextNode*)(*((pActNode->get_children()).begin())))->get_content();
    }
    else if(pActNode->get_name() == "AverageHeartRateBpm")
    {
      //averageHeartRateBPM = std::stoi(((xmlpp::TextNode*)(*(((xmlpp::Node*)(*((pActNode->get_children()).begin())))->get_children()).begin()))->get_content());
      std::cout << averageHeartRateBPM << "\n";
    }
    
    
      
  }
  
  // A lire :

  //int averageHeartRateBPM;
  //int maximumHeartRateBPM;
  //TCXTrack track;
  //double averageSpeed;
  //int maxBikeCadence;
  //int steps;
  //int averageWatts;
  //int maxWatts;
  
}

