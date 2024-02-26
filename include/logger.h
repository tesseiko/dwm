/*
 ==============================================================================
 
 logger.h
 Created: 26 Feb 2024 10:45:34am
 Author: Manos Lefakis
 
 ==============================================================================
 */

#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

class logger
{
public:
    logger()
    {
        filename = "dwm.log";
        myfile.open(filename, std::ios_base::app);
    };

    ~logger()
    {
        myfile.close();
    };

    void Print(const std::string msg)
    {
        output(msg);
    }

    void Info(const std::string msg)
    {
        std::string new_msg = "INFO: " + msg;
        output(new_msg);
    }

    void Warn(const std::string msg)
    {
        std::string new_msg = "WARNING: " + msg;
        output(new_msg);
    }

    void Error(const std::string msg)
    {
        std::string new_msg = "ERROR: " + msg;
        output(new_msg);
        myfile.close();
        exit(1);
    }

private:
    std::ofstream myfile;
    std::string filename;

    const std::string WHITESPACE = " \n\r\t\f\v";

    void output(const std::string msg)
    {
        auto now = std::chrono::system_clock::now();
        std::string formatted_time = std::format("{0:%F_%T}", now);
        std::cout << rtrim(msg) << std::endl;
        myfile << formatted_time << ": " << rtrim(msg) << std::endl;
    }

    std::string rtrim(const std::string &s)
    {
        size_t end = s.find_last_not_of(WHITESPACE);
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }
};
