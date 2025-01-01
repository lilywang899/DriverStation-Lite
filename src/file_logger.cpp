/*
* The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

#include "nlohmann/json.hpp"
#include <fstream>

#include "tinyxml2.h"

using namespace nlohmann;
using namespace tinyxml2;


// void basic_logfile_example()
// {
//     try
//     {
//         // auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
//         // logger->info("This is a basic logger test");
//         // logger->warn("warning");
//         // logger->error("error");
//         auto logger = spdlog::basic_logger_mt("test_logger", "logs/test.txt");
//         spdlog::set_default_logger(logger);
//         spdlog::flush_on(spdlog::level::info);
//
//         spdlog::get("test_logger")->info("LoggingTest::ctor");
//     }
//     catch (const spdlog::spdlog_ex &ex)
//     {
//         printf("Log init failed: \"%s\"\n", ex.what());
//     }
// }

void rotating_logfiles(const std::string &logPath)
{
 // Create a file rotating logger with 5 MB size max and 3 rotated files
 auto max_size = 3000 * 1;
 auto max_files = 3;
 auto logger = spdlog::rotating_logger_mt("test_logger", logPath, max_size, max_files);

 spdlog::set_default_logger(logger);
 spdlog::flush_on(spdlog::level::info);

 spdlog::get("test_logger")->info("LoggingTest::ctor");
}

int init_logging()
{
 std::string fileLocation_json = "/home/lily/share/ds_config.json";
 std::ifstream f(fileLocation_json.c_str());

 if (!f.is_open()) {
  XMLDocument configObj;
  XMLError result = configObj.LoadFile( "/home/lily/share/ds_config.xml" );
  if (result != XML_SUCCESS) {
   printf("could not find .xml or .json");
   return -1;
  }

  XMLElement * RootElement = configObj.RootElement();
  const char* logLevel = RootElement->FirstChildElement( "logger_config" )->FirstChildElement( "log_level" )->GetText();
  const char* logPath = RootElement->FirstChildElement( "logger_config" )->FirstChildElement( "log_file_path" )->GetText();
  spdlog::info("xml configObj.logger_config.log_level : {}", logLevel);
  rotating_logfiles(logPath);
 }
 else
 {
  json configObj = json::parse(f);
  std::string logLevel = configObj.at("logger_config").at("log_level");
  std::string logPath = configObj.at("logger_config").at("log_file_path");
  spdlog::info("json configObj.logger_config.log_level : {}", logLevel);
  rotating_logfiles(logPath);
 }
 return 0;
}



