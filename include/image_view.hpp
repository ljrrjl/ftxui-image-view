#pragma once

#include <memory>

#include "ftxui/util/ref.hpp"
#include "ftxui/dom/node.hpp"

namespace ftxui {
Element image_view(std::string_view url);
}