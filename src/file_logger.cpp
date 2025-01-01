/*
* The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include "spdlog/fmt/ostr.h"
//#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

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

#include "spdlog/sinks/rotating_file_sink.h"
void rotating_example(const std::string &logPath)
{
 // Create a file rotating logger with 5 MB size max and 3 rotated files
 auto max_size = 3000 * 1;
 auto max_files = 3;
 auto logger = spdlog::rotating_logger_mt("test_logger", logPath, max_size, max_files);

 spdlog::set_default_logger(logger);
 spdlog::flush_on(spdlog::level::info);

 spdlog::get("test_logger")->info("LoggingTest::ctor");
}

