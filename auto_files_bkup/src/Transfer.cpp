#include "Transfer.hpp"
#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <thread>

Transfer::Transfer(std::string current_dir): current_dir(current_dir)
{ }

Transfer::~Transfer()
{ }

std::string Transfer::getCurrentDir() const
{
    return current_dir;
}

std::string Transfer::getTargetDir() const
{
    return target_dir;
}

void Transfer::setTargetDir(std::string path)
{
    target_dir = path;
}

void Transfer::move()
{
    delete_dir(target_dir);

    boost::filesystem::path curr_dir(current_dir);

    if(!helpers::copyDir(curr_dir, boost::filesystem::path(target_dir)))
    {
        throw "OperationFailed! Something went wrong. Choose backup path correctly.";
    }

    time_t rawtime;
    struct tm * timeinfo;
    char formatted_time[80];

    time(&rawtime);

    timeinfo = localtime(&rawtime);

    strftime(formatted_time, 80, "%H:%M", timeinfo);

    helpers::printl("");
    std::cout << "\\|/ [" << formatted_time << "] - Backing up files to " << getTargetDir() << std::endl;

}

// TODO: use uintmax_t instead of int
int Transfer::delete_dir(std::string dir_path)
{
    boost::filesystem::path path = dir_path;

    return boost::filesystem::remove_all(path);
}

unsigned int Transfer::getDelay() const
{
    return delay;
}

void Transfer::setDelay(unsigned int delay_minute)
{
    delay = delay_minute;
}
