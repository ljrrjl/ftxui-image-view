#include <iostream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <random>

#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/component/component.hpp"

#include "image_view.hpp"

namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " [picture dir]" << std::endl;
        return 1;
    }

    auto dirpath = fs::directory_iterator(argv[1]);
    std::vector<std::string> pictures;
    for(auto& file : dirpath)
    {
        if(file.is_regular_file() && file.path().extension() == ".png")
        {
            pictures.emplace_back(file.path().native());
        }
    }
    auto cell = [](const std::string& path){ return ftxui::image_view(path); };


    int displayIndex{0};
    auto catDisplay = ftxui::Renderer([&]{
        return cell(pictures[displayIndex]);
    });

    auto selectButton = ftxui::Button("Click", [&]{
        std::random_device seed;
        std::default_random_engine en(seed());
        std::uniform_int_distribution<> dist(0, pictures.size() - 1);
        displayIndex = dist(en);
    });

    auto mainPannelContainer = ftxui::Container::Vertical({
        catDisplay,
        selectButton
    });
    
    auto mainPannelRender = ftxui::Renderer(mainPannelContainer, [&]{
        return ftxui::vbox({
            catDisplay->Render() | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 60),
            ftxui::separator(),
            selectButton->Render() | ftxui::size(ftxui::HEIGHT, ftxui::GREATER_THAN, 10)});
    });

    auto screen = ftxui::ScreenInteractive::FitComponent();
    screen.Loop(mainPannelRender);
}